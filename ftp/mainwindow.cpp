#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include <QMessageBox>
#include <QDir>
#include <QDateTime>
#include "sftpdefs.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initLocalFileTree();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initLocalFileTree()
{
    auto curPath=QDir::currentPath();
    localFileSystem=new QFileSystemModel(this);
    localFileSystem->setRootPath("");
    localSelection=new QItemSelectionModel(localFileSystem);
    ui->localView->setModel(localFileSystem);
    ui->localView->setRootIndex(localFileSystem->index(curPath));
    ui->cbLocalPath->addItem(curPath);
    ui->cbLocalPath->setInsertPolicy(QComboBox::NoInsert);
}

void MainWindow::on_pbConnect_clicked()
{
    curRemoteHost=ui->cbRemoteHostIP->currentText().trimmed();
    bool ok;
    curRemotePort=ui->sbRemoteHostPort->text().toInt(&ok);
    curUser=ui->editUser->text().trimmed();
    curPassword=ui->editPassword->text().trimmed();

    if(curRemoteHost.isEmpty())
    {
        QMessageBox::critical(this,"错误","远程主机地址不能为空");
        ui->cbRemoteHostIP->setFocus();
        return;
    }
    if(!ok)
    {
        QMessageBox::critical(this,"错误","远程主机端口错误");
        ui->sbRemoteHostPort->setFocus();
        return;
    }
    if(curUser.isEmpty())
    {
        QMessageBox::critical(this,"错误","用户不能为空");
        ui->editUser->setFocus();
        return;
    }
    if(curPassword.isEmpty())
    {
        QMessageBox::critical(this,"错误","密码不能为空");
        ui->editPassword->setFocus();
        return;
    }

    connectToHost(curRemoteHost,curRemotePort,curUser,curPassword);
//    QMessageBox::information(this,"",curRemoteHost+":"+QString::asprintf("%d",curRemotePort)+":"+curUser+":"+curPassword);

}

bool MainWindow::connectToHost(QString remoteHost,int remotePort,QString user,QString password)
{
//    QMessageBox::information(this,"",remoteHost+":"+QString::asprintf("%d",remotePort)+":"+user+":"+password);
    QSsh::SshConnectionParameters params;
    params.host = remoteHost;
    params.userName = user;
    params.password = password;
    params.authenticationType = QSsh::SshConnectionParameters::AuthenticationByPassword;
    params.timeout = 30;
    params.port = remotePort;

    m_connection = new QSsh::SshConnection(params, this); // TODO free this pointer!
    connect(m_connection, SIGNAL(connected()), SLOT(onConnected()));
    connect(m_connection, SIGNAL(error(QSsh::SshError)), SLOT(onConnectionError(QSsh::SshError)));

    m_connection->connectToHost();
    return true;
}

void MainWindow::onConnected()
{
    qDebug() << "SecureUploader: Connected";
    qDebug() << "SecureUploader: Creating SFTP channel...";

    m_channel = m_connection->createSftpChannel();

    if (m_channel) {
        connect(m_channel.data(), SIGNAL(initialized()),
                SLOT(onChannelInitialized()));
        connect(m_channel.data(), SIGNAL(initializationFailed(QString)),
                SLOT(onChannelError(QString)));
        connect(m_channel.data(), SIGNAL(finished(QSsh::SftpJobId, QString)),
                SLOT(onOpfinished(QSsh::SftpJobId, QString)));
        connect(m_channel.data(), SIGNAL(dataAvailable(QSsh::SftpJobId, QString)),
                SLOT(onDataAvailable(QSsh::SftpJobId, QString)));
        connect(m_channel.data(),SIGNAL(fileInfoAvailable(QSsh::SftpJobId, QList<QSsh::SftpFileInfo>)),
                SLOT(onFileInfoAvailable(QSsh::SftpJobId, QList<QSsh::SftpFileInfo>)));

        m_channel->initialize();

    } else {
        QMessageBox::critical(this,"连接错误", m_connection->errorString());
//        qDebug() << "SecureUploader: Error null channel";
    }
}

void MainWindow::onConnectionError(QSsh::SshError err)
{    
    qDebug() << "SecureUploader: Connection error" << m_connection->errorString();
    QMessageBox::critical(this,"连接错误", m_connection->errorString());
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_Enter:
    case Qt::Key_Return:
    {
        auto index=localFileSystem->index(ui->cbLocalPath->currentText());
        if(index.row()>=0)
        {
            ui->localView->setRootIndex(index);
            auto curPath=localFileSystem->filePath(index);
            if(!curPath.isEmpty()&&ui->cbLocalPath->findText(curPath,Qt::MatchExactly)<0)
            {
                ui->cbLocalPath->addItem(localFileSystem->filePath(index));
            }
        }
    }
    }
}

void MainWindow::onChannelInitialized()
{
    QSsh::SftpJobId job=m_channel->realPath(".");
    curJob=RealPath;
    ui->pbUpload->setEnabled(true);

//
    if (job != QSsh::SftpInvalidJob) {
        qDebug() << "SecureUploader: Starting job #" << job;
    } else {
        qDebug() << "SecureUploader: Invalid Job";
    }

}

void MainWindow::onChannelError(const QString &err)
{
    qDebug() << "SecureUploader: Error: " << err;
}

void MainWindow::onOpfinished(QSsh::SftpJobId job, const QString &err)
{
    qDebug() << "SecureUploader: Finished job #" << job << ":" << (err.isEmpty() ? "OK" : err);
}

void MainWindow::onDataAvailable(QSsh::SftpJobId job,const QString& data)
{
    Q_UNUSED(job)
    qDebug()<<"List:"<<data;
}

void MainWindow::onFileInfoAvailable(QSsh::SftpJobId job, const QList<QSsh::SftpFileInfo> &fileInfoList)
{
    Q_UNUSED(job)
    switch(curJob)
    {
    case RealPath:
    {
        QSsh::SftpJobId job=m_channel->listDirectory(".");
        curJob=ListDir;
        remoteDir=fileInfoList[0].name;
        if(homeDir.isEmpty())
        {
            homeDir=remoteDir;
        }
        ui->cbRemotePath->setEditText(remoteDir);
        ui->pbDownload->setEnabled(true);
//        if (job != QSsh::SftpInvalidJob) {
//            qDebug() << "SecureUploader: Starting job #" << job;
//        } else {
//            qDebug() << "SecureUploader: Invalid Job";
//        }
    }
        break;
    case ListDir:
    {
        ui->cbRemotePath->setEditText(remoteDir);
        ui->remoteFileSystem->clear();
        for(auto fileInfo:fileInfoList)
        {
            auto fileItem=new QTreeWidgetItem(ui->remoteFileSystem);
            fileItem->setText(0,fileInfo.name);
            fileItem->setTextAlignment(1,Qt::AlignRight);
            fileItem->setText(1,QLocale().toString(fileInfo.size)+" 字节");
            QString fileType;
            switch(fileInfo.type)
            {
            case QSsh::FileTypeRegular:
                fileType="文件";
                break;
            case QSsh::FileTypeDirectory:
                fileType="目录";
                break;
            case QSsh::FileTypeOther:
                fileType="其它类型";
                break;
            case QSsh::FileTypeUnknown:
                fileType="未知类型";
                break;
            }
            fileItem->setText(2,fileType);
            fileItem->setText(3,QDateTime::fromSecsSinceEpoch(fileInfo.mtime,Qt::LocalTime).toString("yyyy/MM/dd hh:mm"));
        }
        curJob=None;
    }
        break;
    }


}
void MainWindow::on_cbLocalPath_currentIndexChanged(const QString &arg1)
{
    auto index=localFileSystem->index(arg1);
    if(index.row()>=0)
    {
        ui->localView->setRootIndex(index);
    }
    else
    {
        ui->localView->setRootIndex(ui->localView->rootIndex());
    }
}

void MainWindow::on_localView_doubleClicked(const QModelIndex &index)
{
    if(localFileSystem->isDir(index))
    {
        ui->localView->setRootIndex(index);
        auto curPath=localFileSystem->filePath(index);
        ui->cbLocalPath->setEditText(curPath);
        if(!curPath.isEmpty()&&ui->cbLocalPath->findText(curPath,Qt::MatchExactly)<0)
        {
            ui->cbLocalPath->addItem(localFileSystem->filePath(index));
        }
    }
}


void MainWindow::on_tbLocalParentPath_clicked()
{
    on_localView_doubleClicked(ui->localView->rootIndex().parent());
}

void MainWindow::on_remoteFileSystem_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(item->text(2)=="目录"&&item->text(0)!=".")
    {
        remoteDir=ui->cbRemotePath->currentText();
        if(item->text(0)!="..")
        {
            remoteDir=remoteDir=="/"?remoteDir+item->text(0):remoteDir+"/"+item->text(0);
        }
        else
        {
           auto index=remoteDir.lastIndexOf("/");
           remoteDir.remove(index,remoteDir.length()-index+1);
           if(remoteDir.isEmpty())  //if windows,remote cannot be empty,so,no problem
               remoteDir="/";
        }
        m_channel->listDirectory(remoteDir);
        curJob=ListDir;
    }
}

void MainWindow::on_pbUpload_clicked()
{
    QString target;
    if(remoteDir!="/") //in fact,we ensure the remoteDir cannot be something like c:/,it only can be c: or something
    {
        for(auto index:ui->localView->selectionModel()->selectedRows())
        {
            if(localFileSystem->isDir(index))
            {
               m_channel->uploadDir(localFileSystem->filePath(index),remoteDir);
            }
            else
            {
                target=remoteDir+"/"+localFileSystem->fileName(index);
                m_channel->uploadFile(localFileSystem->filePath(index),target,QSsh::SftpOverwriteExisting);
            }
        }
    }
    else
    {
        QMessageBox::critical(this,"错误","上传到根目录是不允许的");
    }
}

void MainWindow::on_pbDownload_clicked()
{
    QString remoteFilePath;
    QString localFilePath;
    for(auto item:ui->remoteFileSystem->selectedItems())
    {
//        qDebug()<<item->text(0);
        if(item->text(0)=="."||item->text(0)=="..")
        {
            continue;
        }
        remoteFilePath=remoteDir+"/"+item->text(0);
        localFilePath=ui->cbLocalPath->currentText()+"/"+item->text(0);
        qDebug()<<"remote:"<<remoteFilePath<<"  local:"<<localFilePath;
//        continue;
        if(item->text(2)=="目录")
        {
            m_channel->downloadDir(remoteFilePath,localFilePath,QSsh::SftpOverwriteExisting);
        }
        else
        {
            m_channel->downloadFile(remoteFilePath,localFilePath,QSsh::SftpOverwriteExisting);
        }
    }
}
