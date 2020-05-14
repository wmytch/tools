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

void TcpClient::onConnectToHost(const QString &addr,int port,int links)
{
    for(int i=0;i<links;i++)
    {
        TcpWorker *worker=new TcpWorker;
        QThread *linkThread=new QThread;

        worker->moveToThread(linkThread);
        tcpThreads.append(linkThread);

        connect(linkThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this,&TcpClient::connectToHost,worker,&TcpWorker::doConnect);
        connect(this,&TcpClient::disconnectFromHost,worker,&TcpWorker::doDisconnect);

        connect(this,SIGNAL(tcpSend(QString)),worker,SLOT(doSend(QString)));
        connect(worker,&TcpWorker::tcpReturned,this,&TcpClient::onReturned);

        connect(worker,&TcpWorker::tcpConnected,this,
                [&]()
                {
                    linked++;
                    emit tcpConnected(linked);
                }
        );
        connect(worker,&TcpWorker::tcpDisconnected,this,
                [&]()
                {
                    linked--;
                    emit tcpDisconnected(linked>0?linked:0);
                }
        );
        connect(worker,&TcpWorker::tcpError,this,
                [&](const QString &info)
                {
                    linked--;
                    emit tcpError(info,linked>0?linked:0);
                }
        );

        linkThread->start();

    }
    emit connectToHost(addr,port);
}

void TcpClient::onDisconnectFromHost()
{
    emit disconnectFromHost();
}

void TcpClient::onSend(const QString &data)
{
    emit tcpSend(data);
}

void TcpClient::onSend(size_t packageSize,int sendTimes)
{

}

void TcpClient::onReturned(const QString &info)
{
    emit tcpReturned(info);
}

