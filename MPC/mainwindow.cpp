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

    connect(this,SIGNAL(tcpConnect(QString,int,int)),&tcpClient,SLOT(onTcpConnect(QString,int,int)));
    connect(this,SIGNAL(tcpDisconnect()),&tcpClient,SLOT(onTcpDisconnect()));

    connect(&tcpClient,SIGNAL(tcpConnected(bool)),this,SLOT(onTcpConnected(bool)));
    connect(&tcpClient,SIGNAL(tcpReturned(QString)),this,SLOT(onTcpReturned(QString)));
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
    else
    {
        linked--;
        if(linked<0) linked=0;
        curTcpState=TcpState::disconnected;
        ui->btnTcpConnect->setText("连接");
    }
    statusLabel->setText(QString("Total links:%1  successed links:%2").arg(ui->spinLinkThread->value()).arg(linked));
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
        linked=0;
        statusLabel->clear();
        emit tcpConnect(addr,port,linkThread);
    }
    else
    {
        emit tcpDisconnect();
    }
}
