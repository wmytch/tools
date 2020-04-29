#ifndef TCPTHREADS_H
#define TCPTHREADS_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

class tcpThread : public QObject
{
    Q_OBJECT
public:
    tcpThread();

    QTcpSocket tcpSocket;
public slots:
    void doConnect(QString addr,int port);
    void doDisconnect();
    void doSend(QString data);
    void doSend(size_t packageSize,int sendTimes);
    void doRecv();

signals:
    void tcpConnected(bool connected);
    void tcpReturned(bool result,QString info); //if result==true,info will be the responsed data,or else the error message;
    void tcpReturned(bool result,QString info,int throughout);
private:
    QString address;
    int port;
};

#endif // TCPTHREADS_H
