#include "tcpworker.h"

TcpWorker::TcpWorker()
{
    /* were not this 'this' argument,
     * qt will issue the classic complaint:
     * QObject: Cannot create children for a parent that is in a different thread.
     */
    tcpSocket=new QTcpSocket(this);
}

void TcpWorker::doConnect(const QString &addr,int port)
{
   connect(tcpSocket,&QTcpSocket::connected,this,&TcpWorker::onSocketConnected);
   connect(tcpSocket,&QTcpSocket::disconnected,this,&TcpWorker::onSocketDisconnected);
   connect(tcpSocket,&QTcpSocket::readyRead,this,&TcpWorker::doRecv);
   connect(tcpSocket,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&TcpWorker::onSocketError);
   tcpSocket->connectToHost(addr,port);
}
void  TcpWorker::doDisconnect()
{
    tcpSocket->disconnectFromHost();
}

void  TcpWorker::doSend(const QString &data)
{
    qDebug()<<data;
    tcpSocket->write(data.toLatin1(),data.length());
    tcpSocket->write("\n",1);
}

void  TcpWorker::doSend(size_t packageSize,int sendTimes)
{

}

void  TcpWorker::doRecv()
{
    QString recvData{""};
    while(tcpSocket->canReadLine())
        recvData+=tcpSocket->readLine();
    qDebug()<<"recv:"<<recvData;
    emit tcpReturned(recvData);

}

void TcpWorker::onSocketConnected()
{
    qDebug()<<"connect to:"<<tcpSocket->peerName()<<":"<<tcpSocket->peerPort();
    emit tcpConnected();
}

void TcpWorker::onSocketDisconnected()
{
    qDebug()<<"disconnect from:"<<tcpSocket->peerName()<<":"<<tcpSocket->peerPort();
    emit tcpDisconnected();
}

void TcpWorker::onSocketError(QAbstractSocket::SocketError socketError)
{
    qDebug()<<"error:"<<socketError;
    switch(socketError)
    {
    case QAbstractSocket::HostNotFoundError:
        emit tcpError("HostNotFoundError");
        break;
    case  QAbstractSocket::ConnectionRefusedError:
        emit tcpError("ConnectionRefusedError");
        break;
    case QAbstractSocket::RemoteHostClosedError:
        emit tcpError("RemoteHostClosedError");
        break;
    default:
        emit tcpError("Unspecified socket error");

    }
}