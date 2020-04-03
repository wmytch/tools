#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QKeyEvent>
#include <QTreeWidgetItem>
#include "sftpchannel.h"
#include "sshconnection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum JobCommand {None,RealPath,ListDir};
private slots:

    void on_pbConnect_clicked();

    void onConnected();
    void onConnectionError(QSsh::SshError err);
    void onChannelInitialized();
    void onChannelError(const QString &errString);
    void onOpfinished(QSsh::SftpJobId,const QString&);
    void onDataAvailable(QSsh::SftpJobId,const QString&);
    void onFileInfoAvailable(QSsh::SftpJobId, const QList<QSsh::SftpFileInfo> &);


//    void on_cbLocalPath_editTextChanged(const QString &arg1);
    void on_cbLocalPath_currentIndexChanged(const QString &arg1);

    void on_localView_doubleClicked(const QModelIndex &index);

    void on_tbLocalParentPath_clicked();

    void on_remoteFileSystem_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_pbUpload_clicked();

    void on_pbDownload_clicked();

protected:
    void keyPressEvent(QKeyEvent *e);
private:
    Ui::MainWindow *ui;

    QString curUser;
    QString curPassword;
    QString curRemoteHost;
    int curRemotePort;
    QString remoteDir;
    QString homeDir{""};
    JobCommand curJob;

    QSsh::SftpChannel::Ptr m_channel;
    QSsh::SshConnection *m_connection;

    QFileSystemModel *localFileSystem;
    QItemSelectionModel *localSelection;


    void initLocalFileTree();
    bool connectToHost(QString remoteHost,int remotePort,QString user,QString password);

};
#endif // MAINWINDOW_H
