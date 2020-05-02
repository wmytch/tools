#include "tcpworker.h"

TcpWorker::TcpWorker()
{
    /* were not this 'this' argument,
     * qt will issue the classic complain:
     * QObject: Cannot create children for a parent that is in a different thread.
     */
    tcpSocket=new QTcpSocket(this);
}

void TcpWorker::doConnect(QString addr,int port)
{
   connect(tcpSocket,SIGNAL(connected()),this,SLOT(socketConnected()));
   connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(socketDisconnected()));
   tcpSocket->connectToHost(addr,port);
}
void  TcpWorker::doDisconnect()
{
    tcpSocket->disconnectFromHost();
}

void  TcpWorker::doSend(QString data)
{

}

void  TcpWorker::doSend(size_t packageSize,int sendTimes)
{

}

void  TcpWorker::doRecv()
{

}

void TcpWorker::socketConnected()
{
    qDebug()<<"connect to:"<<tcpSocket->peerName()<<":"<<tcpSocket->peerPort();
    emit tcpConnected(true);
}

void TcpWorker::socketDisconnected()
{
    qDebug()<<"disconnect from:"<<tcpSocket->peerName()<<":"<<tcpSocket->peerPort();
    emit tcpDisconnected();
}