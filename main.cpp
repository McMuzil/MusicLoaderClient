#include <QApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client* client = new Client();
    client->mainWindow->show();
    return a.exec();
}
