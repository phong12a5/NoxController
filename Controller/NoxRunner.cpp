#include "NoxRunner.h"
#include <QThread>
#include "NoxCommand.h"

NoxRunner::NoxRunner(QString instanceName, int index, bool installApp):
    m_instanceName(instanceName),
    m_index(index),
    m_installApp(installApp),
    m_setIsNoxFile(false),
    isRunApp(false)
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

    NoxCommand::lunchInstance(m_instanceName);

    m_checkConnectionTimer->start();
}

void NoxRunner::onCheckConnection()
{
    if (NoxCommand::checkConnection(m_instanceName) && !m_checkEndScriptTimer->isActive()){
        LOG << m_instanceName << " is connected";

        // Run app
        if(!isRunApp){
            while ( !NoxCommand::currentActivity(m_instanceName).contains(FARM_PACKAGE_NAME)) {
                NoxCommand::runApp(m_instanceName, FARM_PACKAGE_NAME);
                delay(1000);
            }
            isRunApp = true;
            LOG << "Run app successfully!";
        }



        QString endScptNameFile = ENDSCRIPT_FILENAME;
        QString endScptNamePath = ENDSCRIPT_PATH + endScptNameFile;
        NoxCommand::nox_adb_command(m_instanceName,QString("shell rm %1").arg(endScptNamePath));
        m_checkEndScriptTimer->start();
    }
}

void NoxRunner::onCheckEnscript()
{
//    LOG;
    QString endScptNameFile = ENDSCRIPT_FILENAME;
    QString endScptNamePath = ENDSCRIPT_PATH + endScptNameFile;
    QString output = NoxCommand::nox_adb_command_str(m_instanceName,QString("shell [ -f %1 ] && echo true || echo false").arg(endScptNamePath)).simplified();
    if(output == "true"){
        LOG << "Output: " << output;
        emit finished();
    }
}
