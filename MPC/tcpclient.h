#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "tcpworker.h"

class TcpClient:public QObject
{
    Q_OBJECT
public:
    TcpClient();
    ~TcpClient();

    QVector<QThread*> tcpThreads;

signals:
    void tcpConnected(bool result);
    void tcpDisconnected();
    void tcpReturned(QString info);

    void tcpConnectTo(QString addr,int port);
    void tcpDisconnectFrom();

public slots:
    void onTcpConnectTo(QString addr,int port,int links);
    void onTcpDisconnect();
    void onTcpSend(QString data);
    void onTcpSend(size_t packageSize,int sendTimes);
    void onTcpReturned(QString info);

    void onWorkerTcpConnected(bool result);
};

#endif // TCPCLIENT_H
