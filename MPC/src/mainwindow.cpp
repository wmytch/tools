#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMediaCaptureSession>
#include <QMediaRecorder>
#include <QAudioInput>
#include <QMediaDevices>
#include <QAudioDevice>

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

void MainWindow::onTcpConnected(int linked)
{

    curTcpState=TcpState::connected;
    ui->btnTcpSend->setEnabled(true);
    ui->btnTcpConnect->setEnabled(true);
    ui->btnTcpConnect->setText("断开");
    statusLabel->setText(QString("Total links:%1 linked:%2").arg(ui->spinLinkThread->value()).arg(linked));
}

void MainWindow::onTcpDisconnected(int linked)
{
    statusLabel->setText(QString("Total links:%1 linked:%2 ")
                         .arg(ui->spinLinkThread->value()).arg(linked));
    if(linked==0)
    {
        curTcpState=TcpState::disconnected;
        ui->btnTcpConnect->setText("连接");
        ui->btnTcpConnect->setEnabled(true);
        ui->btnTcpSend->setEnabled(false);
        if(tcpClient)
        {
            delete tcpClient;
            tcpClient=nullptr;
        }
    }

}

void MainWindow::onTcpError(const QString &info,int linked)
{

    statusLabel->setText(QString("Total links:%1 linked:%2 ")
                         .arg(ui->spinLinkThread->value()).arg(linked));
    ui->plainTextEdit->appendPlainText(info);
    if(tcpClient&&linked==0)
    {
        curTcpState=TcpState::disconnected;
        ui->btnTcpConnect->setText("连接");
        ui->btnTcpConnect->setEnabled(true);
        ui->btnTcpSend->setEnabled(false);
        delete tcpClient;
        tcpClient=nullptr;
    }
}

void MainWindow::onTcpReturned(const QString &info)
{
    ui->plainTextEdit->appendPlainText("Recv:"+info.trimmed());
}

void MainWindow::on_btnTcpConnect_clicked()
{
    switch(curTcpState)
    {
    case TcpState::disconnected:
    {
        if(tcpClient)
            delete tcpClient;

        tcpClient=new TcpClient;

        connect(this,&MainWindow::tcpConnectToHost,tcpClient,&TcpClient::onConnectToHost);
        connect(this,&MainWindow::tcpDisconnectFromHost,tcpClient,&TcpClient::onDisconnectFromHost);
        connect(this,SIGNAL(tcpSend(QString)),tcpClient,SLOT(onSend(QString)));

        connect(tcpClient,&TcpClient::tcpConnected,this,&MainWindow::onTcpConnected);
        connect(tcpClient,&TcpClient::tcpDisconnected,this,&MainWindow::onTcpDisconnected);
        connect(tcpClient,&TcpClient::tcpError,this,&MainWindow::onTcpError);
        connect(tcpClient,&TcpClient::tcpReturned,this,&MainWindow::onTcpReturned);

        ui->btnTcpConnect->setEnabled(false);
        statusLabel->setText("Connecting...");
        ui->plainTextEdit->clear();


        QString addr=ui->editHostIP->text().trimmed();
        int port=ui->editHostPort->text().trimmed().toInt();
        int links=ui->spinLinkThread->text().trimmed().toInt();
        curTcpState=TcpState::connecting;
        emit tcpConnectToHost(addr,port,links);
    }
        break;
    case TcpState::connected:
    {
        ui->btnTcpSend->setEnabled(false);
        curTcpState=TcpState::disconnecting;
        emit tcpDisconnectFromHost();
    }
        break;
    default:
        break;
    }
}

void MainWindow::on_btnTcpSend_clicked()
{
    if(ui->rbText->isChecked())
    {
        ui->plainTextEdit->appendPlainText("Send:"+ui->editTextData->text());
        emit tcpSend(ui->editTextData->text());
    }
}

void MainWindow::on_btmCapature_clicked()
{

    for(auto &audioInput:QMediaDevices::audioInputs())
    {
        qDebug()<<audioInput.description();
    }

    QMediaCaptureSession session;
    QAudioInput audioInput{QMediaDevices::audioInputs().at(0)};
    session.setAudioInput(&audioInput);
    QMediaRecorder recorder;
    session.setRecorder(&recorder);
    recorder.setQuality(QMediaRecorder::HighQuality);
    recorder.setOutputLocation(QUrl::fromLocalFile("./test.mp3"));
    ui->statusbar->showMessage(recorder.outputLocation().toLocalFile());
    static bool start=false;
    if(!start)
    {
        start=true;
        ui->btmCapature->setText("Stop");
        recorder.record();
    }
    else
    {
        start=false;
        recorder.stop();
        ui->btmCapature->setText("Capture");
    }
}

