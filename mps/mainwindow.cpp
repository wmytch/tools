#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpsslserver.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startPB_clicked()
{
    if(!serverStarted)
    {
        serverStarted=true;
        ui->startPB->setText("Stop");
        if(ui->sslCB->isChecked())
        {
            withSSL=" with SSL";
        }
        else
        {
            withSSL="";
        }
        if(ui->tcpRB->isChecked())
        {
            ui->infoPTE->appendPlainText("TCP server"+withSSL+" started at port:"+ui->portSB->text());
        }
        else if(ui->udpRB->isChecked())
        {
            ui->infoPTE->appendPlainText("UDP"+withSSL+" started at port:"+ui->portSB->text());
        }
        TcpSslServer *tcpSslServer=new TcpSslServer;
        tcpSslServer->listen(QHostAddress::Any,ui->portSB->value());
        connect(tcpSslServer,&TcpSslServer::newConnection,[this](){
                    this->ui->infoPTE->appendPlainText("new connection.");
                });
    }
    else
    {
        serverStarted=false;
        ui->startPB->setText("Start");
        ui->infoPTE->appendPlainText("Server Stopped.");
    }
}

