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
    TcpClient tcpClient;
    enum TcpState {connected,disconnected};
    TcpState curTcpState{TcpState::disconnected};
    int linked=0;
signals:
    void tcpConnect(QString addr,int port,int links);
    void tcpDisconnect();
    void tcpSend(QString data);
    void tcpSend(size_t packageSize,int sendTimes);
public slots:
    void onTcpConnected(bool connected);
    void onTcpReturned(QString info);
private slots:
    void on_btnTcpConnect_clicked();

private:
    Ui::MainWindow *ui;

    QLabel *statusLabel;


};
#endif // MAINWINDOW_H
