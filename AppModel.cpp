#include "AppModel.h"
#include "AppMain.h"

AppModel* AppModel::m_instance = nullptr;

AppModel::AppModel(QObject *parent) : QObject(parent)
{
    m_noxIntallFolder = "";
    m_amountOfThread = 1;
    m_isLaunchMutiTask = false;
    m_latestRunningInstance = -1;
}

AppModel *AppModel::instance()
{
    if(m_instance == nullptr){
        m_instance = new AppModel();
    }
    return m_instance;
}

QString AppModel::noxIntallFolder() const
{
    return m_noxIntallFolder;
}

void AppModel::setNoxIntallFolder(const QString path, bool standardPath)
{
    if(standardPath == false){
        LOG << path.mid(8);
        if(QFile(path.mid(8) + "/NoxConsole.exe").exists()){
            if(m_noxIntallFolder != path.mid(8) ){
                m_noxIntallFolder = path.mid(8);
                emit noxIntallFolderChanged();
            }
        }else{
            LOG << "Invalid folder.";
        }

    }else{
        LOG << path;
        if(m_noxIntallFolder != path){
            m_noxIntallFolder = path;
            emit noxIntallFolderChanged();
        }
    }

    emit reInitDeviceList();
    emit saveConfig();
}

QList<QObject*> AppModel::devicesList() const
{
    return m_devicesList;
}

void AppModel::setDevicesList(QList<QObject*> devices)
{
    if(m_devicesList != devices){
        m_devicesList = devices;
        emit devicesListChanged();
    }
}

uint AppModel::amountOfThread() const
{
    return m_amountOfThread;
}

void AppModel::setAmountOfThread(const uint data)
{
    LOG << data;
    if(data != m_amountOfThread){
        m_amountOfThread = data;
        emit amountOfThreadChanged();
    }
}

bool AppModel::isLaunchMutiTask() const
{
    return m_isLaunchMutiTask;
}

void AppModel::setIsLaunchMutiTask(const bool data)
{
    LOG << data;
    if(m_isLaunchMutiTask != data){
        m_isLaunchMutiTask = data;
        emit isLaunchMutiTaskChanged();
    }
}

int AppModel::latestRunningInstance() const
{
    return m_latestRunningInstance;
}

void AppModel::setLatestRunningInstance(const int data)
{
    if(m_latestRunningInstance != data){
        QMutex mutex;
        mutex.lock();
        if(data >= this->devicesList().length()){
            m_latestRunningInstance = 0;
        }else{
            m_latestRunningInstance = data;
        }
        mutex.unlock();
    }
}

void AppModel::requestToLaunchInstance(QString instanceName)
{
    NoxCommand::lunchInstance(instanceName);
}





