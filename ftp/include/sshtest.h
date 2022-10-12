#ifndef SSHTEST_H
#define SSHTEST_H

#include <QLoggingCategory>
#include <QObject>
#include "libssh2.h"
#include "libssh2_sftp.h"
#include "libssh2_publickey.h"
Q_DECLARE_LOGGING_CATEGORY(sshtest)

class SshTest : public QObject
{
    Q_OBJECT
    static int s_nbInstance;
    QString m_name;


public:
    explicit SshTest(const QString &name = "noname",QObject *parent = nullptr);
    virtual ~SshTest();
    QString getName() const;
    void setName(const QString &name);

signals:

};
#endif // SSHTEST_H
