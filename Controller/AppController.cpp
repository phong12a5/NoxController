#include "AppController.h"

#define APP_MODEL AppModel::instance()

AppController* AppController::m_instance = nullptr;

AppController::AppController(QObject *parent) : QObject(parent)
{

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
}

void AppController::stopMultiTask()
{
    LOG;
}

void AppController::onDevicesListChanged()
{
    LOG;
}
