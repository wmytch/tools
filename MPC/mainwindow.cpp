#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusLabel=new QLabel;
    statusLabel->setMinimumWidth(150);
    ui->statusbar->addWidget(statusLabel);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTcpConnected(bool connected)
{
    if(connected)
    {
        linked++;
        curTcpState=TcpState::connected;
        ui->btnTcpConnect->setText("断开");
    }

    statusLabel->setText(QString("Total links:%1  successed links:%2").arg(ui->spinLinkThread->value()).arg(linked));
}

void MainWindow::onTcpDisconnected()
{
    unlinked++;
    if(unlinked==linked)  //I know this condition is problematic,but it is trival as a client.
    {
        curTcpState=TcpState::disconnected;
        ui->btnTcpConnect->setText("连接");
        ui->btnTcpSend->setEnabled(true);
        delete tcpClient;
        tcpClient=nullptr;
    }
    statusLabel->setText(QString("Total links:%1 unlinked:%2")
                         .arg(ui->spinLinkThread->value()).arg(unlinked));
}

void MainWindow::onTcpReturned(QString info)
{
    ui->plainTextEdit->appendPlainText(info);
}

void MainWindow::on_btnTcpConnect_clicked()
{
    if(curTcpState==TcpState::disconnected)
    {
        QString addr=ui->editHostIP->text().trimmed();
        int port=ui->editHostPort->text().trimmed().toInt();
        int linkThread=ui->spinLinkThread->text().trimmed().toInt();

        tcpClient=new TcpClient;
        connect(this,SIGNAL(tcpConnectTo(QString,int,int)),tcpClient,SLOT(onTcpConnectTo(QString,int,int)));
        connect(this,SIGNAL(tcpDisconnect()),tcpClient,SLOT(onTcpDisconnect()));

        connect(tcpClient,SIGNAL(tcpConnected(bool)),this,SLOT(onTcpConnected(bool)));
        connect(tcpClient,SIGNAL(tcpDisconnected()),this,SLOT(onTcpDisconnected()));
        connect(tcpClient,SIGNAL(tcpReturned(QString)),this,SLOT(onTcpReturned(QString)));


        linked=0;
        statusLabel->clear();

        emit tcpConnectTo(addr,port,linkThread);
    }
    else
    {
        unlinked=0;
        ui->btnTcpSend->setEnabled(false);
        emit tcpDisconnect();
    }
}
