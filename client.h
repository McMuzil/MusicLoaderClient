#ifndef CLIENT_H
#define CLIENT_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include "connectiondialog.h"
#include <QFile>
#include <QString>

class Client : QObject
{
    Q_OBJECT
public:
    Client();
    ~Client();
    MainWindow* mainWindow;
public slots:
    void ConfigureReading();
private:
    void Init();
    QString savePath = "/sdcard/DownloadedFiles/";
    ConnectionDialog* dialog;
    QTcpSocket* socket = NULL;
    bool connected = false;
    int totalBytes = 0;
    int bytesReceived;
    bool initialized;
    QFile* file;
    enum commandList {None,MusicTransmission};
private slots:
    void ReceiveFiles();
    void openDialog(bool value);
    void connectToServer();
};

#endif // CLIENT_H
