#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!QSslSocket::supportsSsl())
    {
        QMessageBox::critical(nullptr,"SSL","系统不支持SSL.");
        return -1;
    }
//    qDebug() << "build-time OpenSSL version:" <<QSslSocket::sslLibraryBuildVersionString();
//    qDebug() << "run-time OpenSSL version:" << QSslSocket::sslLibraryVersionString();

    MainWindow w;
    w.show();
    return a.exec();
}
