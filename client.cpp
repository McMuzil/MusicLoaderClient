#include "client.h"
#include <QDockWidget>
#include <QFile>
#include <QSettings>

Client::Client()
{
    mainWindow = new MainWindow();
    socket = new QTcpSocket(mainWindow);

    QObject::connect(socket, SIGNAL(readyRead()),this,SLOT(ConfigureReading()));
    //QObject::connect(mainWindow->ui->pushButton,SIGNAL(clicked(bool)), this, SLOT(sendMessage(bool)));
    QObject::connect(mainWindow->ui->actionConnect_to_server,SIGNAL(triggered(bool)),this,SLOT(openDialog(bool)));


}

Client::~Client()
{
    delete mainWindow;
    delete socket;
}

void Client::openDialog(bool value)
{


    dialog = new ConnectionDialog();
    connect(dialog->buttonBox, SIGNAL(accepted()),this,SLOT(connectToServer()));
    dialog->exec();

}

void Client::connectToServer()
{


    socket->connectToHost(dialog->GetIP(), 9999);
    if(socket->waitForConnected(3000))
    {
        QMessageBox* msg = new QMessageBox(mainWindow);
        msg->setText("Connected!");
        msg->exec();
        dialog->close();
        connected = true;

        QSettings settings("sdcard/ConnectionSettings.ini", QSettings::IniFormat);

        settings.beginGroup("client");
        settings.setValue("ip", dialog->GetIP());

    }
    else
    {
        QMessageBox* msg = new QMessageBox(mainWindow);
        msg->setText("Failed to connect!<br>""Try again!");
        msg->exec();

    }
}

void Client::ConfigureReading()
{
    QDataStream stream(socket->read(4));
    int command;
    stream >> command;
    qDebug() << command << "Command";
    switch (command) {
    case commandList::MusicTransmission:
        qDebug() << "case";
        Init();
        QObject::disconnect(socket, SIGNAL(readyRead()),this,SLOT(ConfigureReading()));
        QObject::connect(socket, SIGNAL(readyRead()),this, SLOT(ReceiveFiles()));
        break;
    default:
        qErrnoWarning("there is no command with code - " + command);
        break;
    }

}

void Client::Init()
{
    qDebug() << "Init";
    bytesReceived = totalBytes = 0;
}

void Client::ReceiveFiles()
{

    if(!initialized)
    {
        QDataStream stream(socket->read(4)); // reading Size of File
        stream >> totalBytes;
        qDebug() << totalBytes << "total bytes";

        QDataStream streamSizeOfFileName(socket->read(4)); // reading size of file name
        quint32 fileNameLength;
        streamSizeOfFileName >> fileNameLength;
        qDebug() << fileNameLength << "length of fileName";

        //QString fileName = socket->read(fileNameLength).data(); // reading song name
        //qDebug() << fileName;
        file = new QFile(savePath + socket->read(fileNameLength).data());
        file->open(QIODevice::WriteOnly);

        initialized = true;
    }

    bytesReceived += (int)socket->bytesAvailable();
    file->write(socket->readAll());

    mainWindow->ui->progressBar->setMaximum(totalBytes);
    mainWindow->ui->progressBar->setValue(bytesReceived);
    mainWindow->ui->label->setText(tr("Received %1MB").arg(bytesReceived / (1024 * 1024)));

    if(bytesReceived == totalBytes)
    {
        file->flush();
        file->close();
        delete file;
        initialized = false;

        QObject::disconnect(socket, SIGNAL(readyRead()),this,SLOT(ReceiveFiles()));
        QObject::connect(socket, SIGNAL(readyRead()),this, SLOT(ConfigureReading()));
    }
}
