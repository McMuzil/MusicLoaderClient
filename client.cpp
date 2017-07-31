#include "client.h"

Client::Client()
{
    mainWindow = new MainWindow();
    socket = new QTcpSocket(mainWindow);

    QObject::connect(socket, SIGNAL(readyRead()),this,SLOT(readTcpData()));
    QObject::connect(mainWindow->ui->pushButton,SIGNAL(clicked(bool)), this, SLOT(sendMessage(bool)));
    QObject::connect(mainWindow->ui->actionConnect_to_server,SIGNAL(triggered(bool)),this,SLOT(openDialog(bool)));

}

Client::~Client()
{
    delete mainWindow;
    delete socket;
}

void Client::sendMessage(bool value)
{
    if(!connected)
    {
        QMessageBox msg(mainWindow);
        msg.setText("No connection to the server!");
        msg.exec();
        return;
    }

    if(socket != NULL && socket->state() == QTcpSocket::ConnectedState)
    {
        socket->write(mainWindow->getLineEditText().toLatin1());
        socket->flush();

        socket->waitForBytesWritten(3000);
    }

}

void Client::openDialog(bool value)
{


    dialog = new ConnectionDialog();
    connect(dialog->buttonBox, SIGNAL(accepted()),this,SLOT(connectToServer())); // не конектиться
    dialog->exec();

}

void Client::connectToServer()  //сюда ми не доходим
{

    socket->connectToHost(dialog->GetIP(), 9999);
    if(socket->waitForConnected(3000))
    {
        QMessageBox* msg = new QMessageBox(mainWindow);
        msg->setText("Connected!");
        msg->exec();
        dialog->close();
        connected = true;

    }
    else
    {
        QMessageBox* msg = new QMessageBox(mainWindow);
        msg->setText("Failed to connect!<br>""Try again!");
        msg->exec();

    }
}

void Client::readTcpData()
{
    QByteArray data = socket->readAll();
    QMessageBox msg(mainWindow);
    msg.setText(data.data());
    msg.exec();
}
