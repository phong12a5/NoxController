#include "AppController.h"

#define APP_MODEL AppModel::instance()

AppController* AppController::m_instance = nullptr;

AppController::AppController(QObject *parent) : QObject(parent)
{
    m_noxThreadList.clear();
}

AppController *AppController::instance()
{
    if(m_instance == nullptr)
        m_instance = new AppController();
    return m_instance;
}

void AppController::initAppController()
{
    QObject::connect(APP_MODEL,SIGNAL(devicesListChanged()),this,SLOT(onDevicesListChanged()));
}

void AppController::startMultiTask()
{
    LOG;
    for(int i = 0; i < static_cast<int>(APP_MODEL->amountOfThread()); i++){
        m_noxThreadList.append(new NoxThread());
    }
}

void AppController::stopMultiTask()
{
    LOG;
    while (!m_noxThreadList.isEmpty()) {
        delete m_noxThreadList.at(0);
        m_noxThreadList.removeAt(0);
    }
}

void AppController::onDevicesListChanged()
{
    LOG;
}

void AppController::aMissionCompleted(NoxThread* threadAdd)
{
    if(threadAdd){
        if(m_noxThreadList.contains(threadAdd)){
            int index = m_noxThreadList.indexOf(threadAdd);
            delete m_noxThreadList.at(index);
            m_noxThreadList.removeAt(index);
        }
        while (m_noxThreadList.length() < static_cast<int>(APP_MODEL->amountOfThread())) {
            m_noxThreadList.append(new NoxThread(this));
        }
    }
}
