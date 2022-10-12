#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QDateTime>
//#include "sftpclient.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initLocalFileTree();
}


MainWindow::~MainWindow()
{
    if(ftpClient)
    {
        delete ftpClient;
        ftpClient=nullptr;
    }
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

//    operationLog(QString("connect info:%1@%2:%3").arg(curUser).arg(curRemoteHost).arg(curRemotePort));

    ftpClient=new SftpClient(curRemoteHost,curRemotePort,curUser,curPassword);

    connect(this,&MainWindow::connectToServer,ftpClient,&SftpClient::onConnectToServer);

    connect(ftpClient,&SftpClient::notice,this,&MainWindow::onNoticed);
    connect(ftpClient,&SftpClient::ftpServerConnected,this,&MainWindow::onFtpServerConnected);

    ui->pbConnect->setEnabled(false);
    emit connectToServer();
}


inline void MainWindow::operationLog(const QString &info)
{
    ui->operationLog->appendPlainText("SFTP: "+info);
}


void MainWindow::onFtpServerConnected(QString serverPath)
{
    remoteDir=serverPath;
    homeDir=serverPath;
    ui->cbRemotePath->setEditText(serverPath);
//    operationLog("home directory:"+serverPath);

    connect(this,&MainWindow::listServerDir,ftpClient,&SftpClient::onListServerDir);
    connect(this,&MainWindow::downloadDir,ftpClient,&SftpClient::onDownloadDir);
    connect(this,&MainWindow::downloadFile,ftpClient,&SftpClient::onDownloadFile);
    connect(this,&MainWindow::uploadFile,ftpClient,&SftpClient::onUploadFile);
    connect(this,&MainWindow::uploadDir,ftpClient,&SftpClient::onUploadDir);

    connect(ftpClient,&SftpClient::fileList,this,&MainWindow::onFileList);
//    connect(ftpClient,&SftpClient::realServerPath,this,
//            [=](QString realPath)
//            {
//                ui->cbRemotePath->setCurrentText(realPath);
//                remoteDir=realPath;
//            }
//    );

    emit listServerDir(serverPath);
}


void MainWindow::onNoticed(ClientStatus status,QString info)
{
    switch(status)
    {
    case ClientStatus::CONNECT_SUCCESS:
    {
        operationLog(info);
    }
        break;
    case ClientStatus::CONNECT_FAIL:
    {
        operationLog(info);
        operationLog("Destroy ftp client.");
        if(ftpClient)
        {
            delete ftpClient;
            ftpClient=nullptr;
        }
        ui->pbConnect->setEnabled(true);
    }
        break;
    case ClientStatus::DOWNLOAD_DIR_FAIL:
    {
        operationLog("Download dir fail:"+info);
    }
        break;
    case ClientStatus::DOWNLOAD_DIR_SUCCESS:
    {
        operationLog("Download dir success:"+info);
    }
        break;
    case ClientStatus::DOWNLOAD_FILE_FAIL:
    {
        operationLog("Download file fail:"+info);
    }
        break;
    case ClientStatus::DOWNLOAD_FILE_SUCCESS:
    {
        operationLog("Download file sucess:"+info);
    }
        break;
    case ClientStatus::UPLOAD_DIR_FAIL:
    {
        operationLog("Upload dir fail:"+info);
    }
        break;
    case ClientStatus::UPLOAD_DIR_SUCCESS:
    {
        operationLog("Upload dir success:"+info);
        emit listServerDir(ui->cbRemotePath->currentText());
    }
        break;
    case ClientStatus::UPLOAD_FILE_FAIL:
    {
        operationLog("Upload file fail:"+info);
    }
        break;
    case ClientStatus::UPLOAD_FILE_SUCCESS:
    {
        operationLog("Upload file sucess:"+info);
        emit listServerDir(ui->cbRemotePath->currentText());
    }
        break;
    case ClientStatus::INFO:
    {
        operationLog(info);
    }
        break;
    default:
        operationLog(info);
        break;
    }
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


void MainWindow::onFileList(QHash<QString,QString> &fileList)
{
    ui->remoteFileSystem->clear();
    int columnCount=ui->remoteFileSystem->columnCount();
//    ui->remoteFileSystem->setHeaderLabel(QString("Total %1").arg(fileList.count()));
    for(auto &fileInfo:fileList.values())
    {
        auto fileItem=new QTreeWidgetItem(ui->remoteFileSystem);
        auto fileAttr=fileInfo.split(QRegularExpression("\\s+"));
        int i;
        for(i=0;i<columnCount-1; i++)
        {
            fileItem->setText(i,fileAttr[i]);
            fileItem->setTextAlignment(i,Qt::AlignLeft|Qt::AlignJustify);
//            operationLog(fileAttr[i]);
        }
        fileItem->setText(i,fileList.key(fileInfo));
        fileItem->setTextAlignment(i,Qt::AlignLeft|Qt::AlignJustify);
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
        Q_UNUSED(column)
        if(item->text(0).startsWith('d')&&item->text(item->columnCount()-1)!=".")
        {
            remoteDir=ui->cbRemotePath->currentText();
            if(item->text(item->columnCount()-1)!="..")
            {
                remoteDir=remoteDir=="/"?remoteDir+item->text(item->columnCount()-1):remoteDir+"/"+item->text(item->columnCount()-1);
            }
            else
            {
               auto index=remoteDir.lastIndexOf("/");
               remoteDir.remove(index,remoteDir.length()-index+1);
               if(remoteDir.isEmpty())  //for remote windows hosts,remote path assured cannot be empty
                   remoteDir="/";
            }
//            emit realServerPath(remoteDir);
            ui->cbRemotePath->setCurrentText(remoteDir);
            emit listServerDir(remoteDir);
            operationLog(remoteDir);
        }
}


void MainWindow::on_pbUpload_clicked()
{
    if(remoteDir.startsWith(homeDir))
    {
        for(auto index:ui->localView->selectionModel()->selectedRows())
        {
            if(localFileSystem->isDir(index))
            {
//                operationLog("Upload dir.Full local path:"+localFileSystem->filePath(index)+". local dir:"+localFileSystem->fileName(index)+" To remote:"+remoteDir);
                emit uploadDir(localFileSystem->filePath(index),localFileSystem->fileName(index),remoteDir);
            }
            else
            {
//                operationLog("Upload file.Full local path:"+localFileSystem->filePath(index)+". local file:"+localFileSystem->fileName(index)+" To remote:"+remoteDir);
                emit uploadFile(localFileSystem->filePath(index),localFileSystem->fileName(index),remoteDir);
            }
        }
    }
    else
    {
        QMessageBox::critical(this,"错误",QString("上传到%1目录是不允许的").arg(remoteDir));
    }
}


void MainWindow::on_pbDownload_clicked()
{
    for(auto item:ui->remoteFileSystem->selectedItems())
    {
        if(item->text(item->columnCount()-1)=="."||item->text(item->columnCount()-1)=="..")
        {
            continue;
        }
        if(item->text(0).startsWith('d'))
        {
//            operationLog("download dir:"+item->text(item->columnCount()-1));
            emit downloadDir(item->text(item->columnCount()-1),ui->cbLocalPath->currentText());
        }
        else
        {
//            operationLog("download file:"+item->text(item->columnCount()-1));
            emit downloadFile(item->text(item->columnCount()-1),ui->cbLocalPath->currentText());
        }
    }
}




