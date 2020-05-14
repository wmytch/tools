#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "tcpworker.h"

class TcpClient:public QObject
{
    Q_OBJECT
public:
    TcpClient();
    ~TcpClient();

private:
    QVector<QThread*> tcpThreads;
    int linked{0};

signals:
    void tcpConnected(int linked);
    void tcpDisconnected(int linked);
    void tcpError(const QString &info,int linked);
    void tcpSend(const QString &data);
    void tcpSend(size_t packageSize,int sendTimes);
    void tcpReturned(const QString &info);

    void connectToHost(const QString &addr,int port);
    void disconnectFromHost();

public slots:
    void onConnectToHost(const QString &addr,int port,int links);
    void onDisconnectFromHost();
    void onSend(const QString &data);
    void onSend(size_t packageSize,int sendTimes);
    void onReturned(const QString &info);

};

#endif // TCPCLIENT_H
