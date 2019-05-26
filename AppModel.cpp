#include "AppModel.h"

AppModel* AppModel::m_instance = nullptr;

AppModel::AppModel(QObject *parent) : QObject(parent)
{
    m_noxIntallFolder = "";
    m_amountOfThread = 1;
    m_isLaunchMutiTask = false;
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
        if(m_noxIntallFolder != path.mid(8)){
            m_noxIntallFolder = path.mid(8);
            emit noxIntallFolderChanged();
        }
    }else{
        LOG << path;
        if(m_noxIntallFolder != path){
            m_noxIntallFolder = path;
            emit noxIntallFolderChanged();
        }
    }

    QFile file(INSTALL_FOLDER_NAME);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << INSTALL_FOLDER_PREFIX << m_noxIntallFolder;
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

void AppModel::requestToLaunchInstance(QString instanceName)
{
    NoxCommand::lunchInstance(instanceName);
}





