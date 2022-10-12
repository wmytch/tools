#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QKeyEvent>
#include <QTreeWidgetItem>
#include <QMessageBox>

#include "common.h"
#include "sftpclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void connectToServer();
    void listServerDir(const QString& path);
    void downloadDir(const QString &dir,const QString &localPath);
    void downloadFile(const QString &file,const QString &localPath);
    void uploadDir(const QString &fullPath,const QString &dir,const QString &remotePath);
    void uploadFile(const QString &fullPath,const QString &file,const QString &remotePath);
//    void realServerPath(QString& path);

private:
    SftpClient *ftpClient{nullptr};

    void operationLog(const QString &info);

private slots:

    void onFtpServerConnected(QString serverPath);
    void onNoticed(ClientStatus status,QString info);
    void onFileList(QHash<QString,QString> &fileList);

    void on_pbConnect_clicked();
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

    QFileSystemModel *localFileSystem;


    void initLocalFileTree();

};
#endif // MAINWINDOW_H
