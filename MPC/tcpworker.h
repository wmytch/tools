#ifndef TcpWorkerS_H
#define TcpWorkerS_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

class TcpWorker : public QObject
{
    Q_OBJECT
public:
    TcpWorker();

    QTcpSocket *tcpSocket{nullptr};
public slots:
    void doConnect(const QString &addr,int port);
    void doDisconnect();
    void doSend(const QString &data);
    void doSend(size_t packageSize,int sendTimes);
    void doRecv();

    void onSocketConnected();
    void onSocketDisconnected();
    void onSocketError(QAbstractSocket::SocketError socketError);
signals:
    void tcpConnected();
    void tcpDisconnected();
    void tcpError(const QString &info);
    void tcpReturned(const QString &info); //if result==true,info will be the responsed data,or else the error message;
};

#endif // TcpWorkerS_H
