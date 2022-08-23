#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QDateTime>

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

    localFileSystem=new QFileSystemModel(this);
    localFileSystem->setRootPath("");

    ui->localView->setModel(localFileSystem);

    auto curPath=QDir::currentPath();
    ui->localView->setRootIndex(localFileSystem->index(curPath));
    ui->cbLocalPath->addItem(curPath);

    ui->cbLocalPath->setInsertPolicy(QComboBox::NoInsert);//ensure no auto insert
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
}

bool MainWindow::connectToHost(QString remoteHost,int remotePort,QString user,QString password)
{
    QSslSocket *socket = new QSslSocket(this);
    connect(socket, SIGNAL(encrypted()), this, SLOT(onConnected()));

    socket->connectToHostEncrypted(remoteHost, remotePort);

    return true;
}

void MainWindow::onConnected()
{
    ui->operationLog->appendPlainText("SFTP: Connected");
    ui->operationLog->appendPlainText("SFTP: Creating SFTP channel...");

//    m_channel = m_connection->createSftpChannel();

//    if (m_channel) {
//        connect(m_channel.data(), SIGNAL(initialized()),
//                SLOT(onChannelInitialized()));
//        connect(m_channel.data(), SIGNAL(initializationFailed(QString)),
//                SLOT(onChannelError(QString)));
//        connect(m_channel.data(), SIGNAL(finished(QSsh::SftpJobId, QString)),
//                SLOT(onOpfinished(QSsh::SftpJobId, QString)));
//        connect(m_channel.data(), SIGNAL(dataAvailable(QSsh::SftpJobId, QString)),
//                SLOT(onDataAvailable(QSsh::SftpJobId, QString)));
//        connect(m_channel.data(),SIGNAL(fileInfoAvailable(QSsh::SftpJobId, QList<QSsh::SftpFileInfo>)),
//                SLOT(onFileInfoAvailable(QSsh::SftpJobId, QList<QSsh::SftpFileInfo>)));

//        m_channel->initialize();

//    } else {
//        QMessageBox::critical(this,"连接错误", m_connection->errorString());
//    }
}

//void MainWindow::onConnectionError(QSsh::SshError err)
//{
//    Q_UNUSED(err)
//    QMessageBox::critical(this,"连接错误", m_connection->errorString());
//}

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
//    QSsh::SftpJobId jobId=m_channel->realPath(".");
//    curJob=RealPath;
//    this->jobLog(jobId,"RealPath");

//    ui->pbUpload->setEnabled(true);
}

//void MainWindow::onChannelError(const QString &err)
//{
//    ui->operationLog->appendPlainText("Error:"+err);
//}

//void MainWindow::onOpfinished(QSsh::SftpJobId job, const QString &err)
//{
//    ui->operationLog->appendPlainText(QString("Job %1: Finished ").arg(job)+(err.isEmpty()?"OK":err));

//}

//void MainWindow::onDataAvailable(QSsh::SftpJobId job,const QString& data)
//{
//    Q_UNUSED(job)
//    Q_UNUSED(data);
//}

//void MainWindow::onFileInfoAvailable(QSsh::SftpJobId job, const QList<QSsh::SftpFileInfo> &fileInfoList)
//{
//    Q_UNUSED(job)
//    switch(curJob)
//    {
//    case RealPath:
//    {
//        remoteDir=fileInfoList[0].name;
//        if(homeDir.isEmpty())
//        {
//            homeDir=remoteDir;
//        }
//        ui->cbRemotePath->setEditText(remoteDir);
//        ui->pbDownload->setEnabled(true);

//        QSsh::SftpJobId jobId=m_channel->listDirectory(remoteDir);
//        curJob=ListDir;
//        this->jobLog(jobId,"ListDir "+remoteDir);
//    }
//        break;
//    case ListDir:
//    {
//        ui->cbRemotePath->setEditText(remoteDir);
//        ui->remoteFileSystem->clear();
//        for(auto fileInfo:fileInfoList)
//        {
//            auto fileItem=new QTreeWidgetItem(ui->remoteFileSystem);
//            fileItem->setText(RemoteColumn::Name,fileInfo.name);
//            fileItem->setTextAlignment(RemoteColumn::Size,Qt::AlignRight);
//            fileItem->setText(RemoteColumn::Size,QLocale().toString(fileInfo.size)+" 字节");
//            QString fileType;
//            switch(fileInfo.type)
//            {
//            case QSsh::FileTypeRegular:
//                fileType="文件";
//                break;
//            case QSsh::FileTypeDirectory:
//                fileType="目录";
//                break;
//            case QSsh::FileTypeOther:
//                fileType="其它类型";
//                break;
//            case QSsh::FileTypeUnknown:
//                fileType="未知类型";
//                break;
//            }
//            fileItem->setText(RemoteColumn::Type,fileType);
//            fileItem->setText(RemoteColumn::DateModified,QDateTime::fromSecsSinceEpoch(fileInfo.mtime,Qt::LocalTime).toString("yyyy/MM/dd hh:mm"));
//        }
//        curJob=None;
//    }
//        break;
//    case None:
//        break;
//    }


//}
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
//    Q_UNUSED(column)
//    if(item->text(RemoteColumn::Type)=="目录"&&item->text(RemoteColumn::Name)!=".")
//    {
//        remoteDir=ui->cbRemotePath->currentText();
//        if(item->text(RemoteColumn::Name)!="..")
//        {
//            remoteDir=remoteDir=="/"?remoteDir+item->text(RemoteColumn::Name):remoteDir+"/"+item->text(RemoteColumn::Name);
//        }
//        else
//        {
//           auto index=remoteDir.lastIndexOf("/");
//           remoteDir.remove(index,remoteDir.length()-index+1);
//           if(remoteDir.isEmpty())  //for remote windows hosts,remote path assured cannot be empty
//               remoteDir="/";
//        }
//        auto jobId=m_channel->listDirectory(remoteDir);
//        this->jobLog(jobId,"ListDir "+remoteDir);
//        curJob=ListDir;
//    }
}

void MainWindow::on_pbUpload_clicked()
{
//    QString target;
//    QSsh::SftpJobId jobId;
//    if(remoteDir!="/") //in fact,we can ensure the remoteDir cannot be something like c:/,it only can be c: or something
//    {
//        for(auto index:ui->localView->selectionModel()->selectedRows())
//        {
//            if(localFileSystem->isDir(index))
//            {
//               jobId=m_channel->uploadDir(localFileSystem->filePath(index),remoteDir);
//               this->jobLog(jobId,"Upload directory local:"+localFileSystem->filePath(index)+" To remote:"+remoteDir);
//            }
//            else
//            {
//                target=remoteDir+"/"+localFileSystem->fileName(index);
//                jobId=m_channel->uploadFile(localFileSystem->filePath(index),target,QSsh::SftpOverwriteExisting);
//                this->jobLog(jobId,"Upload file local:"+localFileSystem->filePath(index)+" To remote:"+target);
//            }
//        }
//    }
//    else
//    {
//        QMessageBox::critical(this,"错误","上传到根目录是不允许的");
//    }
}

void MainWindow::on_pbDownload_clicked()
{
//    QString remoteFilePath;
//    QString localFilePath;
//    QSsh::SftpJobId jobId;
//    for(auto item:ui->remoteFileSystem->selectedItems())
//    {
//        if(item->text(RemoteColumn::Name)=="."||item->text(RemoteColumn::Name)=="..")
//        {
//            continue;
//        }
//        remoteFilePath=remoteDir+"/"+item->text(RemoteColumn::Name);
//        localFilePath=ui->cbLocalPath->currentText()+"/"+item->text(RemoteColumn::Name);
//        if(item->text(RemoteColumn::Type)=="目录")
//        {
//            jobId=m_channel->downloadDir(remoteFilePath,localFilePath,QSsh::SftpOverwriteExisting);
//            this->jobLog(jobId,"Download directory remote:"+remoteFilePath+" To  local:"+localFilePath);
//        }
//        else
//        {
//            jobId=m_channel->downloadFile(remoteFilePath,localFilePath,QSsh::SftpOverwriteExisting);
//            this->jobLog(jobId,"Download file remote:"+remoteFilePath+" To  local:"+localFilePath);
//        }

//    }
}

//void MainWindow::jobLog( QSsh::SftpJobId jobId,QString jobName)
//{
//    if (jobId != QSsh::SftpInvalidJob)
//    {
//        ui->operationLog->appendPlainText("Starting job "+QString("%1: ").arg(jobId)+jobName);
//    }
//    else
//    {
//        ui->operationLog->appendPlainText("Invalid job "+QString("%1: ").arg(jobId)+jobName);
//    }
//}
