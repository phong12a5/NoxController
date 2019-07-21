#include "NoxThread.h"
#include "AppModel.h"
#include "AppController.h"

#define APP_CTRL    AppController::instance()
#define APP_MODEL   AppModel::instance()

NoxThread::NoxThread(QObject *parent) : QObject(parent)
{
    m_noxInstance = nullptr;
    m_Worker = nullptr;
    m_workerThread = new QThread(this);

    connect(this, SIGNAL(missionCompleted(NoxThread*)),APP_CTRL, SLOT(aMissionCompleted(NoxThread*)));
    this->setNoxInstance();
}

NoxThread::~NoxThread()
{
    LOG << m_noxInstance->instanceName();
    m_workerThread->quit();
    m_workerThread->wait();
    if(m_noxInstance) m_noxInstance->setIsRunning(false);
    m_noxInstance = nullptr;
    m_workerThread = nullptr;
}

void NoxThread::setNoxInstance()
{
    QMutex mutex;
    mutex.lock();
    if(APP_MODEL->latestRunningInstance() < APP_MODEL->devicesList().length()){
        APP_MODEL->setLatestRunningInstance(APP_MODEL->latestRunningInstance() + 1);

        m_noxInstance = dynamic_cast<NoxIntance*>(APP_MODEL->devicesList().at(APP_MODEL->latestRunningInstance()));
        m_noxInstance->setIsRunning(true);
        m_Worker = new NoxRunner(m_noxInstance->instanceName(),m_noxInstance->indexOf(),m_noxInstance->installedApp());

        m_Worker->moveToThread(m_workerThread);
        connect(m_workerThread, &QThread::finished, m_Worker, &NoxRunner::deleteLater);
        connect(this, &NoxThread::operate, m_Worker, &NoxRunner::run);
        connect(m_Worker, &NoxRunner::finished, this, &NoxThread::finishedATask);
        connect(m_Worker, &NoxRunner::installedApp, this, &NoxThread::onInstalledApp);
        m_workerThread->start();
        emit this->operate();
    }
    mutex.unlock();
}

void NoxThread::finishedATask()
{
    m_noxInstance->setIsRunning(false);
    emit missionCompleted(this);
}

void NoxThread::onInstalledApp()
{
    if(!m_noxInstance->installedApp()){
        m_noxInstance->setInstalledApp(true);
        APP_MODEL->saveConfig();
    }
}
