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
    void doConnect(QString addr,int port);
    void doDisconnect();
    void doSend(QString data);
    void doSend(size_t packageSize,int sendTimes);
    void doRecv();

    void socketConnected();
    void socketDisconnected();
signals:
    void tcpConnected(bool connected);
    void tcpDisconnected();
    void tcpReturned(bool result,QString info); //if result==true,info will be the responsed data,or else the error message;
    void tcpReturned(bool result,QString info,int throughout);

};

#endif // TcpWorkerS_H
