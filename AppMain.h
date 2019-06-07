#ifndef APPMAIN_H
#define APPMAIN_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QProcess>
#include "AppDefines.h"
#include "AppModel.h"
#include "AppController.h"
#include <QJsonObject>
#include <QJsonDocument>

class AppMain : public QObject
{
    Q_OBJECT
public:
    explicit AppMain(QObject *parent = nullptr);
    ~AppMain();

    void initApplication(QQmlApplicationEngine* engine);


private:

    QJsonDocument loadJson(QString fileName);
    void saveJson(QJsonDocument document, QString fileName);

private:
    QQmlApplicationEngine* m_engine;

public slots:
    void requestToStartStopMultiTask();
    void onSaveConfig();
    void onLoadConfig();
    void initDevicesList();
};

#endif // APPMAIN_H
