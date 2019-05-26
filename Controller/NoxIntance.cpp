#include "NoxIntance.h"

NoxIntance::NoxIntance(QObject *parent, QString instanceName, int indexOf) :
    QObject(parent),
    m_instanceName(instanceName),
    m_indexOf(indexOf),
    m_isRunning(false)
{
    // Do something
    LOG << "Created new Nox instance: " << instanceName;
}

NoxIntance::~NoxIntance()
{
    NoxCommand::quitInstance(this->instanceName());
}

QString NoxIntance::instanceName() const
{
    return m_instanceName;
}

bool NoxIntance::isRunning() const
{
    return m_isRunning;
}

int NoxIntance::indexOf() const
{
    return m_indexOf;
}

void NoxIntance::startInstance()
{
    if(NoxCommand::lunchInstance(this->instanceName())){
        LOG << this->instanceName() << " is started";
        emit checkEndScript();
    }
}

void NoxIntance::quitInstance()
{
    LOG << NoxCommand::quitInstance(this->instanceName());
}

void NoxIntance::onCheckEndScript()
{
    LOG;
    if(!this->isRunning())
        return;

    QString endScptFile = ENDSCRIPT_PATH + QString("endScript%1.st").arg(this->indexOf());
    LOG << "endScptFile: " <<  endScptFile;
    while (!QFile(endScptFile).exists()) {
        NoxCommand::nox_adb_command(this->instanceName(),QString("pull %1 %2").arg(endScptFile).arg(QDir::currentPath()));
    }
}
