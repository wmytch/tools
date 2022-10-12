#ifndef SFTPCLIENT_H
#define SFTPCLIENT_H

#include <winsock2.h>
#include <windows.h>

#include <QObject>
#include <QHash>

#include "libssh2.h"
#include "libssh2_sftp.h"
#include "libssh2_publickey.h"

#include "common.h"

#define __FILESIZE "I64"


class SftpClient:public QObject
{
    Q_OBJECT
public:


    SftpClient(){}
    SftpClient(const QString &host,int port,const QString &user,const QString &password)
        :serverAddr{host},serverPort{port},serverUser{user},serverPassword{password} {}

    virtual ~SftpClient();

//    QString getServerHome(){return sftpHome;}

public slots:
    void onConnectToServer();
    void onListServerDir(const QString &path);
    void onDownloadDir(const QString &dir,const QString &localPath);
    void onDownloadFile(const QString &file,const QString &localPath);
    void onUploadDir(const QString &fullPath,const QString &dir,const QString &remotePath);
    void onUploadFile(const QString &fullPath,const QString &file,const QString &remotePath);
//    void onGetRealPath(const QString &path);
signals:
    void notice(ClientStatus status,QString info);
    void ftpServerConnected(QString path);
//    void shutdown();
//    void realServerPath(QString realPath);
    void fileList(QHash<QString,QString> &fileInfoList);
private slots:
//    void onConnected();
//    void onDisconnect();
//    void onShutdown();
private:
    QString serverAddr;
    int serverPort;
    QString serverUser;
    QString serverPassword;

    struct sockaddr_in sin;
    int sock{0};

    LIBSSH2_SESSION *sshSession{nullptr};
    LIBSSH2_SFTP *sftpSession{nullptr};

    char *userAuthList;
    int authPw = 0;

    QString sftpServerPath{""} ;
//    QString sftpHome{""} ;
    QHash<QString,QString> fileInfoList;

    QString realPath(const QString &path);
    bool listServerDir(const QString &path);
    bool downloadFile(const QString &file,const QString &localPath);
    bool downloadDir(const QString &dir,const QString &localPath);
    bool uploadFile(const QString &fullPath,const QString &file,const QString &remotePath);
    bool uploadDir(const QString &fullPath,const QString &dir,const QString &remotePath);

};

#endif // SFTPCLIENT_H
