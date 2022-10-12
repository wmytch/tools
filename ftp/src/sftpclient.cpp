#include "sftpclient.h"
#include <QRegularExpression>
#include <QFile>
#include <QDateTime>

SftpClient::~SftpClient()
{
    if(sftpSession)
    {
        libssh2_sftp_shutdown(sftpSession);
    }
    if(sshSession)
    {
        libssh2_session_disconnect(sshSession, "Normal Shutdown");
        libssh2_session_free(sshSession);
    }
    if(sock){
        closesocket(sock);
    }
    libssh2_exit();
}
void SftpClient::onConnectToServer()
{
    sock = socket(AF_INET, SOCK_STREAM, 0);
    sin.sin_family = AF_INET;
    sin.sin_port =htons(serverPort);
    sin.sin_addr.s_addr = inet_addr(serverAddr.toStdString().c_str());
    if(::connect(sock, (struct sockaddr*)(&sin),
                 sizeof(struct sockaddr_in)) != 0)
    {
        emit notice(ClientStatus::CONNECT_FAIL,QString("failed to connect!"));
        return;
    }
    emit notice(ClientStatus::CONNECT_SUCCESS,QString("connect success."));
    emit notice(ClientStatus::CONNECT_SUCCESS,QString("init ssh2 session."));
    sshSession = libssh2_session_init();
    if(!sshSession)
    {
        emit notice(ClientStatus::CONNECT_FAIL,QString("failed to init ssh2 session!"));
        return;
    }
    emit notice(ClientStatus::CONNECT_SUCCESS,QString("init ssh2 session success."));
    emit notice(ClientStatus::CONNECT_SUCCESS,QString("establishing SSH session."));

    int rc = libssh2_session_handshake(sshSession, sock);
    if(rc)
    {
        emit notice(ClientStatus::CONNECT_FAIL,QString("Failure establishing SSH session: %1").arg(rc));
        return;
    }
    emit notice(ClientStatus::CONNECT_SUCCESS,QString("establishing SSH session success."));
    emit notice(ClientStatus::CONNECT_SUCCESS,QString("Authentication."));

    /* check what authentication methods are available */
    userAuthList = libssh2_userauth_list(sshSession, serverUser.toStdString().c_str(), serverUser.length());

    if(strstr(userAuthList, "password") != NULL)
    {
        /* We could authenticate via password */
        if(libssh2_userauth_password(sshSession,  serverUser.toStdString().c_str(), serverPassword.toStdString().c_str())) {
            emit notice(ClientStatus::CONNECT_FAIL,QString("Authentication by password failed!"));
            return;
//            emit shutdown();
        }
        else
        {
            emit notice(ClientStatus::CONNECT_SUCCESS,QString("Authentication success"));
            emit notice(ClientStatus::CONNECT_SUCCESS,QString("init SFTP session."));
        }
    }
    else
    {
        emit notice(ClientStatus::CONNECT_FAIL,QString("Authentication methods:%1").arg(userAuthList));
        emit notice(ClientStatus::CONNECT_FAIL,QString("Only support authentication by password!"));
        return;
    }

    sftpSession = libssh2_sftp_init(sshSession);
    if(sftpSession)
    {
        emit notice(ClientStatus::CONNECT_SUCCESS,QString("SFTP session initted!"));
    }
    else
    {
        emit notice(ClientStatus::CONNECT_FAIL,QString("Unable to init SFTP session!"));
        return;
    }

    /* Since we have not set non-blocking, tell libssh2 we are blocking */
    libssh2_session_set_blocking(sshSession, 1);
    sftpServerPath=realPath(".");
    emit ftpServerConnected(sftpServerPath);
    return;
}

//void SftpClient::onShutdown()
//{
//    libssh2_session_disconnect(sshSession, "Normal Shutdown");
//    libssh2_session_free(sshSession);
//    closesocket(sock);
//    libssh2_exit();
//}

//void SftpClient::onDisconnect()
//{
//    libssh2_sftp_shutdown(sftpSession);
//}

//void SftpClient::onConnected()
//{
//    emit notice("Sftp server connected.");
//    listServer(".");
//    getRealPath(".");
//}

QString SftpClient::realPath(const QString &path)
{
    int rc=0;
    int bufferSize=1024;
    char *buffer=(char *)malloc(bufferSize);
    memset(buffer,0,bufferSize);
    QString remotePath{""};
    while(1)
    {
        rc=libssh2_sftp_realpath(sftpSession,path.toStdString().c_str(),buffer,bufferSize);
        if(rc>=0)
        {
            remotePath=QString(buffer);
//            if(sftpHome.isEmpty())
//            {
//                sftpHome=sftpServerPath;
//            }
            free(buffer);
            return remotePath;
        }
        else if(rc==LIBSSH2_ERROR_BUFFER_TOO_SMALL)
        {
            bufferSize*=2;
            buffer=(char *)realloc(buffer,bufferSize);
            memset(buffer,0,bufferSize);
        }
        else
        {
            free(buffer);
            return "";
        }
    }

}
//void SftpClient::onGetRealPath(const QString &path)
//{
//    auto dir=realPath(path);
////todo: emit a signal
//}

bool SftpClient::listServerDir(const QString &path)
{
    LIBSSH2_SFTP_HANDLE *sftpHandle = libssh2_sftp_opendir(sftpSession, path.toStdString().c_str());
    if(!sftpHandle)
    {
        emit notice(ClientStatus::OPEN_DIR,"Unable to open dir with SFTP:"+path);
        return false;
    }
    sftpServerPath=path;
    int rc;
    int bufferSize=512;
    char *buffer=(char *)malloc(bufferSize);
    char mem[512];
    LIBSSH2_SFTP_ATTRIBUTES attrs;

    fileInfoList.clear();
    while(1)
    {
        rc=libssh2_sftp_readdir_ex(sftpHandle,mem,512, buffer, bufferSize, &attrs);
        if(rc>0)
        {
           // fileInfoList<<buffer;
           fileInfoList[mem]=buffer;
            memset(buffer,0,bufferSize);
            memset(mem,0,sizeof(mem));
//            emit notice(ClientStatus::SUCCESS,QString("filesize:%1").arg(attrs.filesize));
        }
        else if(rc==LIBSSH2_ERROR_BUFFER_TOO_SMALL)
        {
            bufferSize*=2;
            buffer=(char *)realloc(buffer,bufferSize);
            memset(buffer,0,bufferSize);
//            emit notice(QString("buffer to small:%1").arg(bufferSize));
        }
        else
        {
            free(buffer);
            break;
        }
    }

    libssh2_sftp_closedir(sftpHandle);
    return true;
}

void SftpClient::onListServerDir(const QString &path)
{
    if(listServerDir(path))
    {
        emit fileList(fileInfoList);
    }
}

void SftpClient::onDownloadFile(const QString &file,const QString &localPath)
{
    if(downloadFile(file,localPath))
    {
        emit notice(ClientStatus::DOWNLOAD_FILE_SUCCESS,file);
    }
    else
    {
        emit notice(ClientStatus::DOWNLOAD_FILE_FAIL,file);
    }
}

void SftpClient::onDownloadDir(const QString &dir,const QString &localPath)
{
    if(downloadDir(dir,localPath))
    {
        emit notice(ClientStatus::DOWNLOAD_DIR_SUCCESS,dir);
    }
    else
    {
        emit notice(ClientStatus::DOWNLOAD_DIR_FAIL,dir);
    }
}

bool SftpClient::downloadFile(const QString &file,const QString &localPath)
{
//    emit notice(ClientStatus::SUCCESS,QString("download to %1/").arg(localPath)+file);
    QString fileName;
    if(localPath.endsWith("/"))
    {
        fileName=localPath+file;
    }
    else
    {
        fileName=localPath+"/"+file;
    }
    QFile localFile(fileName);
    if(localFile.exists())
    {
        auto newName=fileName+QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
        emit notice(ClientStatus::INFO,QString("%1 exists,rename to %2").arg(fileName).arg(newName));
        localFile.rename(newName);
        localFile.setFileName(fileName);
    }

    if(!localFile.open(QIODevice::WriteOnly ))
    {
        emit notice(ClientStatus::DOWNLOAD_FILE_FAIL,
                    QString("Unable to create file: %1").arg(fileName));
        return false;
    }

    QString sftpPath=sftpServerPath+"/"+file;
    auto sftpHandle =libssh2_sftp_open(sftpSession, sftpPath.toStdString().c_str(), LIBSSH2_FXF_READ, 0);
    if(!sftpHandle)
    {
        emit notice(ClientStatus::DOWNLOAD_FILE_FAIL,
                    QString("Unable to open file with SFTP: %1").arg(libssh2_sftp_last_error(sftpSession)));
        localFile.close();
        return false;
    }
    emit notice(ClientStatus::SUCCESS, QString("Now receive data from %1.").arg(sftpPath));

    int rc=0;
    do {
        char mem[1024];
        rc = libssh2_sftp_read(sftpHandle, mem, sizeof(mem));

        if(rc > 0)
        {
            localFile.write(mem,rc);
        }
        else
        {
            break;
        }
    } while(1);
    localFile.close();
    libssh2_sftp_close(sftpHandle);
    return true;
}

bool SftpClient::downloadDir(const QString &dir,const QString &localPath)
{
    emit notice(ClientStatus::INFO,QString("download to %1/").arg(localPath)+dir);
    return true;
}

void SftpClient::onUploadFile(const QString &fullPath,const QString &file,const QString &remotePath)
{
    if(uploadFile(fullPath,file,remotePath))
    {
        emit notice(ClientStatus::UPLOAD_FILE_SUCCESS,fullPath);
    }
    else
    {
        emit notice(ClientStatus::UPLOAD_FILE_FAIL,fullPath);
    }
}

void SftpClient::onUploadDir(const QString &fullPath,const QString &dir,const QString &remotePath)
{
    if(uploadDir(fullPath,dir,remotePath))
    {
        emit notice(ClientStatus::UPLOAD_DIR_SUCCESS,fullPath);
    }
    else
    {
        emit notice(ClientStatus::UPLOAD_DIR_FAIL,fullPath);
    }
}

bool SftpClient::uploadFile(const QString &fullPath,const QString &file,const QString &remotePath)
{
//    emit notice(ClientStatus::INFO,QString("%2 upload to %1/").arg(remotePath).arg(file));
    QString remoteFile;
    if(remotePath.endsWith("/"))
    {
        remoteFile=remotePath+file;
    }
    else
    {
        remoteFile=remotePath+"/"+file;
    }

    QFile localFile(fullPath);

    if(!localFile.open(QIODevice::ReadOnly ))
    {
        emit notice(ClientStatus::DOWNLOAD_FILE_FAIL,
                    QString("Unable to open file: %1").arg(file));
        return false;
    }

    auto sftpHandle =libssh2_sftp_open(sftpSession, remoteFile.toStdString().c_str(),
                                       LIBSSH2_FXF_WRITE|LIBSSH2_FXF_CREAT|LIBSSH2_FXF_EXCL,
                                       LIBSSH2_SFTP_S_IRUSR|LIBSSH2_SFTP_S_IWUSR|
                                       LIBSSH2_SFTP_S_IRGRP|LIBSSH2_SFTP_S_IROTH) ;
    if(!sftpHandle)
    {
        char *errMsg[1]{0};
        int len=1024;
        libssh2_session_last_error(sshSession,errMsg,&len,1);
        emit notice(ClientStatus::UPLOAD_FILE_FAIL,
                    QString("Unable to create file %2 with : %1").arg(*errMsg).arg(remoteFile));
        localFile.close();
        return false;
    }
//    emit notice(ClientStatus::INFO, QString("Now receive data from %1.").arg(remoteFile));

    int rc=0;
    char mem[1024];
    bool ok=true;
    do {
        rc=localFile.read(mem,sizeof(mem));
        if(rc>0)
        {
            if(libssh2_sftp_write(sftpHandle, mem, rc)<0)
            {
                emit notice(ClientStatus::UPLOAD_FILE_FAIL,QString("Write file %1 error.").arg(remoteFile));
                ok=false;
                break;
            }
        }
        else if(rc<0)
        {
            emit notice(ClientStatus::UPLOAD_FILE_FAIL,QString("read file %1 error.").arg(localFile.fileName()));
            ok=false;
        }
    } while(rc > 0);

    if(!ok)
    {
        libssh2_sftp_unlink(sftpSession,remoteFile.toStdString().c_str());
    }
    localFile.close();
    libssh2_sftp_close(sftpHandle);
    return ok;
}

bool SftpClient::uploadDir(const QString &fullPath,const QString &dir,const QString &remotePath)
{
    emit notice(ClientStatus::INFO,QString("%2 upload to %1/").arg(remotePath).arg(dir));
    return true;
}
