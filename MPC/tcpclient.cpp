#include "tcpclient.h"
#include "tcpthreads.h"
#include <QDebug>


TcpClient::TcpClient()
{

}

void TcpClient::onTcpConnect(QString addr,int port,int links)
{
    for(int i=0;i<links;i++)
    {
        tcpThread *worker=new tcpThread;
        QThread *linkThread=new QThread;

        worker->moveToThread(linkThread);
        tcpThreads.append(linkThread);

        connect(linkThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this,SIGNAL(tcpConnectTo(QString,int)),worker,SLOT(doConnect(QString,int)));
        connect(worker,SIGNAL(tcpConnected(bool)),this,SLOT(onWorkerTcpConnected(bool)));

        linkThread->start();

    }
    emit tcpConnectTo(addr,port);
}

void TcpClient::onTcpDisconnect()
{
    qDebug()<<"Disconnected";
    emit tcpConnected(false);
}

void TcpClient::onTcpSend(QString data)
{

}

void TcpClient::onTcpSend(size_t packageSize,int sendTimes)
{

}

void TcpClient::onTcpReturned(QString info)
{

}

void TcpClient::onWorkerTcpConnected(bool result)
{
    emit tcpConnected(result);
}