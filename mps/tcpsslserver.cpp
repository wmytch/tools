#include "tcpsslserver.h"


TcpSslServer::TcpSslServer()
{

}

void TcpSslServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<"TcpServer received:"<<socketDescriptor;
    QSslSocket *serverSocket = new QSslSocket;
    if (serverSocket->setSocketDescriptor(socketDescriptor))
    {
        qDebug()<<"TcpServer received.";
        addPendingConnection(serverSocket);
        connect(serverSocket, &QSslSocket::encrypted, this, &TcpSslServer::ready);
        serverSocket->startServerEncryption();
    } else {
        delete serverSocket;
    }
}

void TcpSslServer::ready()
{
    qDebug()<<"TcpServer received.";
}
