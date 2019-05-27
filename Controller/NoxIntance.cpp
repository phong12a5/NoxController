#include "NoxIntance.h"

NoxIntance::NoxIntance(QObject *parent, QString instanceName, int indexOf) :
    QObject(parent),
    m_instanceName(instanceName),
    m_indexOf(indexOf),
    m_isRunning(false)
{
    // Do something
    QObject::connect(this,SIGNAL(checkEndScript()),this,SLOT(onCheckEndScript()));
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
        if(data){
            if(NoxCommand::lunchInstance(this->instanceName())){
                LOG << this->instanceName() << " is started";
                emit checkEndScript();
            }
        }else{
            if(NoxCommand::quitInstance(this->instanceName())){
                LOG << this->instanceName() << " is stopped";
            }
        }
    }
}


int NoxIntance::indexOf() const
{
    return m_indexOf;
}

void NoxIntance::onCheckEndScript()
{
    LOG;
    if(!this->isRunning())
        return;

    QString endScptNameFile = QString("endScript%1.st").arg(this->indexOf());
    QString endScptNamePath = ENDSCRIPT_PATH + endScptNameFile;
    LOG << "endScptNamePath: " <<  endScptNamePath;

    QString cmd = QString("shell [ -f %1 ] && echo true || echo false").arg(endScptNamePath);
    LOG << "Cmd: " << cmd;

    QString output = "";
    while (output != "true") {
        output = NoxCommand::runNoxCommand_Str("NoxConsole.exe adb -name:NoxPlayer -command:\"-s [ -f /storage/emulated/legacy/DCIM/endScript0.st ] && echo true || echo false\"");
//        LOG << "Output: " << output;
        delay(2000);
    }
    LOG << "Mission completed!";
    this->setIsRunning(false);
}
