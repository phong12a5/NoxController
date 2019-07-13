#ifndef APPMODEL_H
#define APPMODEL_H

#include <QObject>
#include "AppDefines.h"
#include "Controller/NoxCommand.h"
#include "Controller/NoxIntance.h"
#include <QMutex>

class AppModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString noxIntallFolder READ noxIntallFolder WRITE setNoxIntallFolder NOTIFY noxIntallFolderChanged)
    Q_PROPERTY(QList<QObject*> devicesList READ devicesList WRITE setDevicesList NOTIFY devicesListChanged)
    Q_PROPERTY(uint amountOfThread READ amountOfThread WRITE setAmountOfThread NOTIFY amountOfThreadChanged)
    Q_PROPERTY(bool isLaunchMutiTask READ isLaunchMutiTask WRITE setIsLaunchMutiTask NOTIFY isLaunchMutiTaskChanged)
    Q_PROPERTY(QString token READ token WRITE setToken NOTIFY tokenChanged)
    Q_PROPERTY(int maxNumberThread READ maxNumberThread CONSTANT)

private:
    explicit AppModel(QObject *parent = nullptr);

public:
    static AppModel* instance();

    QString noxIntallFolder() const;
    void setNoxIntallFolder(const QString path, bool standardPath = false);

    QList<QObject*> devicesList() const;
    void setDevicesList(const QList<QObject*> devices);

    uint amountOfThread() const;
    void setAmountOfThread(const uint data);

    bool isLaunchMutiTask() const;
    void setIsLaunchMutiTask(const bool data);

    int latestRunningInstance() const;
    void setLatestRunningInstance(const int data);

    QString token() const;
    void setToken(QString data);

    APP_CONFIG appConfig() const;
    void setAppConfig(APP_CONFIG data);

    int maxNumberThread() const;

public:
    Q_INVOKABLE void startProgram();
    Q_INVOKABLE void stopProgarm();

signals:
    void noxIntallFolderChanged();
    void devicesListChanged();
    void amountOfThreadChanged();
    void isLaunchMutiTaskChanged();
    void tokenChanged();

    void reInitDeviceList();
    void loadConfig();
    void saveConfig();

    void sigStartProgram();
    void sigStoptProgram();

private:
    static AppModel* m_instance;

    QString m_noxIntallFolder;
    QList<QObject*> m_devicesList;
    uint m_amountOfThread;
    bool m_isLaunchMutiTask;
    int m_latestRunningInstance;
    QString m_token;
    APP_CONFIG m_appConfig;

public slots:
};

#endif // APPMODEL_H
