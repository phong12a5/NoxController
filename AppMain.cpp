#include "AppMain.h"
#include <QFile>

#define APP_MODEL AppModel::instance()
#define APP_CTRL    AppController::instance()

AppMain::AppMain(QObject *parent) : QObject(parent)
{
    m_engine = nullptr;
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
    this->loadConfigSetting();
    this->initDevicesList();
    APP_CTRL->initAppController();

    QObject::connect(APP_MODEL,SIGNAL(isLaunchMutiTaskChanged()),this,SLOT(requestToStartStopMultiTask()));
}

void AppMain::loadConfigSetting()
{
    LOG;
    QFile configFile(INSTALL_FOLDER_NAME);
    if(configFile.exists()){
        if(!configFile.open(QIODevice::ReadOnly | QIODevice::Text)){
            APP_MODEL->setNoxIntallFolder(QString(""));
        }else{
            while (!configFile.atEnd()) {
                QByteArray line = configFile.readLine();
                if(QString(line).contains(INSTALL_FOLDER_PREFIX)){
                    int index = QString(line).indexOf(INSTALL_FOLDER_PREFIX);
                    APP_MODEL->setNoxIntallFolder(QString(line).mid(index + QString(INSTALL_FOLDER_PREFIX).length()),true);
                }
            }
        }
    }else{
        APP_MODEL->setNoxIntallFolder(QString(""));
    }
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

void AppMain::requestToStartStopMultiTask()
{
    LOG << (APP_MODEL->isLaunchMutiTask()? "Start" : "Stop");
    if(APP_MODEL->isLaunchMutiTask())
        APP_CTRL->startMultiTask();
    else
        APP_CTRL->stopMultiTask();
}
