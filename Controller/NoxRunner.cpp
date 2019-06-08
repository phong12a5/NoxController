#include "NoxRunner.h"
#include <QThread>
#include "NoxCommand.h"

NoxRunner::NoxRunner(QString instanceName, int index, bool installApp):
    m_instanceName(instanceName),
    m_index(index),
    m_installApp(installApp)
{

}

NoxRunner::~NoxRunner()
{
    LOG << m_instanceName;
    NoxCommand::quitInstance(m_instanceName);
}

void NoxRunner::run()
{
    LOG << "Thread ID: " << QThread::currentThreadId();

    m_checkConnectionTimer = new QTimer(this);
    m_checkConnectionTimer->setInterval(1000);
    m_checkConnectionTimer->setSingleShot(false);
    connect(m_checkConnectionTimer,SIGNAL(timeout()),this,SLOT(onCheckConnection()));

    m_checkEndScriptTimer = new QTimer(this);
    m_checkEndScriptTimer->setInterval(1000);
    m_checkEndScriptTimer->setSingleShot(false);
    connect(m_checkEndScriptTimer,SIGNAL(timeout()),this,SLOT(onCheckEnscript()));

    if(!m_installApp){
        NoxCommand::installPackage(m_instanceName,QDir::currentPath() + "/" + APK_FILENAME);
    }else{
        NoxCommand::lunchInstance(m_instanceName);
    }

    m_checkConnectionTimer->start();
}

void NoxRunner::onCheckConnection()
{
    LOG;
    if (NoxCommand::checkConnection(m_instanceName) && !m_checkEndScriptTimer->isActive()){
        // Remove endScriptFile
        QString endScptNameFile = QString("endScript%1.st").arg(m_index);
        QString endScptNamePath = ENDSCRIPT_PATH + endScptNameFile;
        NoxCommand::nox_adb_command(m_instanceName,QString("shell rm %1").arg(endScptNamePath));
        m_checkEndScriptTimer->start();
    }
}

void NoxRunner::onCheckEnscript()
{
    LOG;
    QString endScptNameFile = QString("endScript%1.st").arg(m_index);
    QString endScptNamePath = ENDSCRIPT_PATH + endScptNameFile;
    QString output = NoxCommand::nox_adb_command_str(m_instanceName,QString("shell [ -f %1 ] && echo true || echo false").arg(endScptNamePath)).simplified();
    if(output == "true"){
        LOG << "Output: " << output;
        emit finished();
    }
}
