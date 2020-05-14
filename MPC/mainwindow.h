#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "tcpclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//the tcp client related members
private:
    TcpClient *tcpClient{nullptr};
    enum TcpState {connecting,connected,disconnecting,disconnected};
    TcpState curTcpState{TcpState::disconnected};
    int linked=0;
    int unlinked=0;
signals:
    void tcpConnectToHost(const QString &addr,int port,int links);
    void tcpDisconnectFromHost();
    void tcpSend(const QString &data);
    void tcpSend(size_t packageSize,int sendTimes);
public slots:
    void onTcpConnected(int linked);
    void onTcpDisconnected(int linked);
    void onTcpError(const QString &info,int linked);
    void onTcpReturned(const QString &info);
private slots:
    void on_btnTcpConnect_clicked();

    void on_btnTcpSend_clicked();

private:
    Ui::MainWindow *ui;

    QLabel *statusLabel;


};
#endif // MAINWINDOW_H
