#include "sshtest.h"

Q_LOGGING_CATEGORY(sshtest, "ssh.client", QtDebugMsg)

int SshTest::s_nbInstance = 0;

SshTest::SshTest(const QString &name, QObject *parent) : QObject(parent), m_name(name)
{
    if(s_nbInstance == 0)
    {
        qCDebug(sshtest)  << "["  << __FILE__ << ","<<__FUNCTION__  << "(" << __LINE__ << ")]" << m_name << ": libssh2_init()";
        Q_ASSERT(libssh2_init(0) == 0);
    }
    ++s_nbInstance;

    qCDebug(sshtest)  << "["  << __FILE__ << ","<<__FUNCTION__  << "(" << __LINE__ << ")]" << m_name << ": created " << this;
}

SshTest::~SshTest()
{
    qCDebug(sshtest)  << "["  << __FILE__ << ","<<__FUNCTION__  << "(" << __LINE__ << ")]" << m_name << ": SshTest::~SshTest() " << this;
    --s_nbInstance;
    if(s_nbInstance == 0)
    {
        qCDebug(sshtest)  << "["  << __FILE__ << ","<<__FUNCTION__  << "(" << __LINE__ << ")]" << m_name << ": libssh2_exit()";
        libssh2_exit();
    }
    qCDebug(sshtest)  << "["  << __FILE__ << ","<<__FUNCTION__  << "(" << __LINE__ << ")]" << m_name << ": destroyed";
}

QString SshTest::getName() const
{
    return m_name;
}
void SshTest::setName(const QString &name)
{
    m_name = name;
}
