#ifndef CLIENT_H
#define CLIENT_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include "connectiondialog.h"

class Client : QObject
{
    Q_OBJECT
public:
    Client();
    ~Client();
    MainWindow* mainWindow;
public slots:
    void readTcpData();
    void sendMessage(bool value);
private:
    ConnectionDialog* dialog;
    QTcpSocket* socket = NULL;
    bool connected = false;
private slots:
    void openDialog(bool value);
    void connectToServer();
};

#endif // CLIENT_H
