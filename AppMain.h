#ifndef APPMAIN_H
#define APPMAIN_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QProcess>
#include "AppDefines.h"
#include "AppModel.h"
#include "Controller/AppController.h"

class AppMain : public QObject
{
    Q_OBJECT
public:
    explicit AppMain(QObject *parent = nullptr);
    ~AppMain();

    void initApplication(QQmlApplicationEngine* engine);

private:
    void loadConfigSetting();
    void initDevicesList();

private:
    QQmlApplicationEngine* m_engine;

signals:

public slots:
    void requestToStartStopMultiTask();
};

#endif // APPMAIN_H
