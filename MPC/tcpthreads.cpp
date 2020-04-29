#include "tcpthreads.h"

tcpThread::tcpThread()
{

}

void tcpThread::doConnect(QString addr,int port)
{
    qDebug()<<"connect to:"<<addr<<":"<<port;
    emit tcpConnected(true);
}
void  tcpThread::doDisconnect()
{

}

void  tcpThread::doSend(QString data)
{

}

void  tcpThread::doSend(size_t packageSize,int sendTimes)
{

}

void  tcpThread::doRecv()
{

}