#include "tcpclient.h"
#include "tcpworker.h"
#include <QDebug>


TcpClient::TcpClient()
{

}

TcpClient::~TcpClient()
{
    for(auto linkThread:tcpThreads)
    {
        linkThread->quit();
        linkThread->wait();
        delete linkThread;
    }
}

void TcpClient::onTcpConnectTo(QString addr,int port,int links)
{
    for(int i=0;i<links;i++)
    {
        TcpWorker *worker=new TcpWorker;
        QThread *linkThread=new QThread;

        worker->moveToThread(linkThread);
        tcpThreads.append(linkThread);

        connect(linkThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this,SIGNAL(tcpConnectTo(QString,int)),worker,SLOT(doConnect(QString,int)));
        connect(this,SIGNAL(tcpDisconnectFrom()),worker,SLOT(doDisconnect()));
        connect(worker,SIGNAL(tcpConnected(bool)),this,SLOT(onWorkerTcpConnected(bool)));
        connect(worker,&TcpWorker::tcpDisconnected,[=](){emit tcpDisconnected();});

        linkThread->start();

    }
    emit tcpConnectTo(addr,port);
}

void TcpClient::onTcpDisconnect()
{
    emit tcpDisconnectFrom();
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

