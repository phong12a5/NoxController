#include "AppMain.h"
#include <QFile>

#define APP_MODEL AppModel::instance()
#define APP_CTRL    AppController::instance()

AppMain::AppMain(QObject *parent) : QObject(parent)
{
    m_engine = nullptr;

    connect(APP_MODEL,SIGNAL(reInitDeviceList()),this,SLOT(initDevicesList()));
    connect(APP_MODEL,SIGNAL(saveConfig()),this,SLOT(onSaveConfig()));
    connect(APP_MODEL,SIGNAL(loadConfig()),this,SLOT(onLoadConfig()));
}

AppMain::~AppMain()
{
    NoxCommand::quitAll();
}

void AppMain::initApplication(QQmlApplicationEngine* engine)
{
    LOG;
    m_engine = engine;
    m_engine->rootContext()->setContextProperty("AppModel",APP_MODEL);
    this->onLoadConfig();
    APP_CTRL->initAppController();

    QObject::connect(APP_MODEL,SIGNAL(isLaunchMutiTaskChanged()),this,SLOT(requestToStartStopMultiTask()));
}

void AppMain::onLoadConfig()
{
    LOG;
    QFile configFile(INSTALL_FOLDER_NAME);
    if(configFile.exists()){
        QJsonObject config = this->loadJson(CONFIG_FILE_NAME).object();
        APP_MODEL->setNoxIntallFolder(config[INSTALL_FOLDER_FIELD].toString(),true);
        if(APP_MODEL->noxIntallFolder() == "")
        {
            LOG << "Nox installation folder has not set yet";
        }else{
            this->initDevicesList();
            QJsonObject noxListObj = config[NOX_LIST_FIELD].toObject();
            if(!noxListObj.isEmpty()){
                for(int i = 0; i < APP_MODEL->devicesList().length(); i++){
                    NoxIntance* noxInstance = dynamic_cast<NoxIntance*>(APP_MODEL->devicesList().at(i));
                    QString instanceName = noxInstance->instanceName();
                    bool state = noxListObj[instanceName].toBool();
                    noxInstance->setInstalledApp(state);
                }
            }else{
                LOG << "[AppMain]" << " appDataObj is empty";
            }
        }
        this->onSaveConfig();
    }else{
        // Do nothing
    }
}

void AppMain::onSaveConfig()
{
    LOG;
    QJsonObject config;
    QJsonObject noxConfigList;

    for(int i = 0; i < APP_MODEL->devicesList().length(); i++){
        NoxIntance* instance = dynamic_cast<NoxIntance*>(APP_MODEL->devicesList().at(i));;
        noxConfigList[instance->instanceName()] = instance->installedApp();
    }
    config[INSTALL_FOLDER_FIELD] = APP_MODEL->noxIntallFolder();
    config[NOX_LIST_FIELD] = noxConfigList;

    this->saveJson(QJsonDocument(config),CONFIG_FILE_NAME);
}

void AppMain::initDevicesList()
{
    LOG;
    if(APP_MODEL->noxIntallFolder() == ""){
        LOG << "Installation folder has not set up yet!";
        return;
    }else{
        QProcess process;
        process.setWorkingDirectory(APP_MODEL->noxIntallFolder());
        process.start("NoxConsole.exe list");
        process.waitForFinished(-1);
        if(process.readAllStandardError() != ""){
            LOG << "ERROR: " << process.readAllStandardError();
        }else{
            QStringList listNameDevices = QString(process.readAllStandardOutput()).split("\r\n",QString::SkipEmptyParts);
            QList<QObject*> deviceList;
            deviceList.clear();
            for (int i = 0; i < listNameDevices.length(); i++) {
                listNameDevices[i] = listNameDevices.at(i).split(",").at(1);
                deviceList.append(new NoxIntance(this,listNameDevices.at(i),i));
            }
            APP_MODEL->setDevicesList(deviceList);
        }
    }
}

QJsonDocument AppMain::loadJson(QString fileName)
{
    LOG << "[AppMain]";
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}

void AppMain::saveJson(QJsonDocument document, QString fileName)
{
    LOG << "[AppMain]";
    QFile jsonFile(fileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(document.toJson());
}


void AppMain::requestToStartStopMultiTask()
{
    LOG << (APP_MODEL->isLaunchMutiTask()? "Start" : "Stop");
    if(APP_MODEL->isLaunchMutiTask())
        APP_CTRL->startMultiTask();
    else
        APP_CTRL->stopMultiTask();
}
