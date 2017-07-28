#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()),this,SLOT(readTcpData()));
    socket->connectToHost("192.168.1.163", 9999);
    if(socket->waitForConnected(3000))
    {
        QMessageBox* msg = new QMessageBox(this);
        msg->setText("Connected!");
        msg->exec();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::readTcpData()
{
    QByteArray data = socket->readAll();
    QMessageBox* msg = new QMessageBox(this);
    msg->setText(data.data());
    msg->exec();
}

void MainWindow::on_pushButton_clicked()
{
    if(socket->state() == QTcpSocket::ConnectedState)
    {
        socket->write(ui->lineEdit->text().toLatin1());
        socket->flush();

        socket->waitForBytesWritten(3000);
    }
}
