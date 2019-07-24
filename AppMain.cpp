#include "AppMain.h"
#include <QFile>
#include <Communication/WebAPI.hpp>

#define APP_MODEL   AppModel::instance()
#define APP_CTRL    AppController::instance()
#define WEB_API     WebAPI::instance()

AppMain::AppMain(QObject *parent) : QObject(parent)
{
    m_engine = nullptr;
    m_getAppConfig = false;
    connect(APP_MODEL,SIGNAL(reInitDeviceList()),this,SLOT(initDevicesList()));
    connect(APP_MODEL,SIGNAL(saveConfig()),this,SLOT(onSaveConfig()));
    connect(APP_MODEL,SIGNAL(loadConfig()),this,SLOT(onLoadConfig()));
    connect(APP_MODEL,SIGNAL(sigStartProgram()),this,SLOT(onStartProgram()));
    connect(APP_MODEL,SIGNAL(sigStoptProgram()),this,SLOT(onStoptProgram()));
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
    APP_MODEL->setCurrentDir(QDir::currentPath());
    this->onLoadConfig();
    APP_CTRL->initAppController();
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
        QString output, error;
        NoxCommand::runNoxCommand("NoxConsole.exe", "list", output, error);
        if(error != ""){
            LOG << "ERROR: " << error;
        }else{
            QStringList listNameDevices = QString(output).split("\r\n",QString::SkipEmptyParts);
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

void AppMain::onStartProgram()
{
    LOG;
    if(!m_getAppConfig){
        WEB_API->getConfig();
        QStringList devicesNameList;
        foreach(QObject* deviceObj,APP_MODEL->devicesList()){
            devicesNameList.append(dynamic_cast<NoxIntance* >(deviceObj)->instanceName());
        }

        if(devicesNameList.length() < APP_MODEL->appConfig().m_noxCount){
            bool isAddedNewDevice = false;
            for(int i = 1; i <= APP_MODEL->appConfig().m_noxCount; i++){
                if(!devicesNameList.contains(QString("Device(%1)").arg(i))){
                    isAddedNewDevice = true;
                    if(i == 1){
                        NoxCommand::addInstance(QString("Device(%1)").arg(i),ANDROID_VERSION);
                        if(devicesNameList.isEmpty()){
                            NoxCommand::lunchInstance("Device(1)");
                            while(!NoxCommand::checkConnection("Device(1)"));
                            NoxCommand::nox_adb_command("Device(1)",QString("shell touch %1isNox.st").arg(ISNOX_PATH));
                            NoxCommand::runNoxCommand("nox_adb.exe", QString("install %1").arg(APP_MODEL->currentDir() + "/" + APK_FILENAME));
                            NoxCommand::runApp("Device(1)", FARM_PACKAGE_NAME);
                            delay(20000);
                            NoxCommand::quitInstance("Device(1)");
                            while(NoxCommand::checkConnection("Device(1)"));
                        }
                    }else{
                        NoxCommand::coppyInstance(QString("Device(%1)").arg(i),"Device(1)");
                    }
                }
            }

            //
            if(isAddedNewDevice){
                initDevicesList();
            }
        }
    }

    APP_MODEL->setInitializing(false);

    APP_CTRL->startMultiTask();
}

void AppMain::onStoptProgram()
{
    LOG;
    APP_CTRL->stopMultiTask();
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
