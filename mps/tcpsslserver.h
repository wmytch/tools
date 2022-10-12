#ifndef TCPSSLSERVER_H
#define TCPSSLSERVER_H

#include <QTcpServer>
#include <QSslSocket>

class TcpSslServer : public  QTcpServer
{
public:
    TcpSslServer();

    void incomingConnection(qintptr socketDescriptor);

public  slots:
    void ready();
};

#endif // TCPSSLSERVER_H
