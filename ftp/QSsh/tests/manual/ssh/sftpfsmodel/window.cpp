/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: http://www.qt-project.org/
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**************************************************************************/
#include "window.h"
#include "ui_window.h"

#include <ssh/sftpfilesystemmodel.h>
#include <ssh/sshconnection.h>

#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QModelIndexList>
#include <QItemSelectionModel>
#include <QString>

using namespace QSsh;

SftpFsWindow::SftpFsWindow(QWidget *parent) : QDialog(parent), m_ui(new Ui::Window)
{
    m_ui->setupUi(this);
    connect(m_ui->connectButton, SIGNAL(clicked()), SLOT(connectToHost()));
    connect(m_ui->downloadButton, SIGNAL(clicked()), SLOT(downloadFile()));
}

SftpFsWindow::~SftpFsWindow()
{
    delete m_ui;
}

void SftpFsWindow::connectToHost()
{
    m_ui->connectButton->setEnabled(false);
    SshConnectionParameters sshParams;
    sshParams.host = m_ui->hostLineEdit->text();
    sshParams.userName = m_ui->userLineEdit->text();
    sshParams.authenticationType = SshConnectionParameters::AuthenticationByPassword;
    sshParams.password = m_ui->passwordLineEdit->text();
    sshParams.port = m_ui->portSpinBox->value();
    sshParams.timeout = 10;
    m_fsModel = new SftpFileSystemModel(this);
    connect(m_fsModel, SIGNAL(sftpOperationFailed(QString)),
        SLOT(handleSftpOperationFailed(QString)));
    connect(m_fsModel, SIGNAL(connectionError(QString)), SLOT(handleConnectionError(QString)));
    connect(m_fsModel, SIGNAL(sftpOperationFinished(QSsh::SftpJobId,QString)),
        SLOT(handleSftpOperationFinished(QSsh::SftpJobId,QString)));
    m_fsModel->setSshConnection(sshParams);
    m_ui->fsView->setModel(m_fsModel);
}

void SftpFsWindow::downloadFile()
{
    const QModelIndexList selectedIndexes = m_ui->fsView->selectionModel()->selectedIndexes();
    if (selectedIndexes.count() != 2)
        return;
    const QString targetFilePath = QFileDialog::getSaveFileName(this, tr("Choose target file"),
        QDir::tempPath());
    if (targetFilePath.isEmpty())
        return;
    const SftpJobId jobId = m_fsModel->downloadFile(selectedIndexes.at(1), targetFilePath);
    QString message;
    if (jobId == SftpInvalidJob)
        message = tr("Download failed.");
    else
        message = tr("Queuing download operation %1.").arg(jobId);
    m_ui->outputTextEdit->appendPlainText(message);
}

void SftpFsWindow::handleSftpOperationFailed(const QString &errorMessage)
{
    m_ui->outputTextEdit->appendPlainText(errorMessage);
}

void SftpFsWindow::handleSftpOperationFinished(SftpJobId jobId, const QString &error)
{
    QString message;
    if (error.isEmpty())
        message = tr("Operation %1 finished successfully.").arg(jobId);
    else
        message = tr("Operation %1 failed: %2.").arg(jobId).arg(error);
    m_ui->outputTextEdit->appendPlainText(message);
}

void SftpFsWindow::handleConnectionError(const QString &errorMessage)
{
    QMessageBox::warning(this, tr("Connection Error"),
        tr("Fatal SSH error: %1").arg(errorMessage));
    qApp->quit();
}
