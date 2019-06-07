#include "NoxRunner.h"
#include <QThread>
#include "NoxCommand.h"

NoxRunner::NoxRunner(QString instanceName, int index):
    m_instanceName(instanceName),
    m_index(index)
{

}

NoxRunner::~NoxRunner()
{
    LOG;
}

void NoxRunner::run()
{
    LOG << "Thread ID: " << QThread::currentThreadId();
    NoxCommand::lunchInstance(m_instanceName);

    QString endScptNameFile = QString("endScript%1.st").arg(m_index);
    QString endScptNamePath = ENDSCRIPT_PATH + endScptNameFile;

    while (NoxCommand::checkConnection(m_instanceName)) {
        LOG << "[Thread ID: " << QThread::currentThreadId() << "]" << " Waiting for starting device";
        delay(1000);
    }

    QString output = "";
    while (output != "true") {
        output = NoxCommand::nox_adb_command_str(m_instanceName,QString("shell [ -f %1 ] && echo true || echo false").arg(endScptNamePath)).simplified();
        delay(2000);
    }
    LOG << "Output: " << output;
    emit finished();
}
