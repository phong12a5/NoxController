#include "NoxIntance.h"

NoxIntance::NoxIntance(QObject *parent, QString instanceName, int indexOf) :
    QObject(parent),
    m_instanceName(instanceName),
    m_indexOf(indexOf),
    m_isRunning(false),
    m_installedApp(false)
{
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

void NoxIntance::setIsRunning(const bool data)
{
    if(data != m_isRunning){
        m_isRunning = data;
        emit isRunningChanged();
    }
}


int NoxIntance::indexOf() const
{
    return m_indexOf;
}

bool NoxIntance::installedApp() const
{
    return m_installedApp;
}

void NoxIntance::setInstalledApp(bool data)
{
    if(m_installedApp != data) {
        m_installedApp = data;
        emit installedAppChanged();
    }
}

