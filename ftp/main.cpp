#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WSADATA wsadata;
    int err = WSAStartup(MAKEWORD(2, 0), &wsadata);
    if(err != 0)
    {
        QMessageBox::critical(nullptr,"WSAStartup",QString("WSAStartup failed with error: %1").arg(err));
        return -1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
