#ifndef APPMODEL_H
#define APPMODEL_H

#include <QObject>
#include "AppDefines.h"
#include "Controller/NoxCommand.h"
#include "Controller/NoxIntance.h"

class AppModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString noxIntallFolder READ noxIntallFolder WRITE setNoxIntallFolder NOTIFY noxIntallFolderChanged)
    Q_PROPERTY(QList<QObject*> devicesList READ devicesList WRITE setDevicesList NOTIFY devicesListChanged)
    Q_PROPERTY(uint amountOfThread READ amountOfThread WRITE setAmountOfThread NOTIFY amountOfThreadChanged)
    Q_PROPERTY(bool isLaunchMutiTask READ isLaunchMutiTask WRITE setIsLaunchMutiTask NOTIFY isLaunchMutiTaskChanged)

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

public:
    Q_INVOKABLE void requestToLaunchInstance(QString instanceName);

signals:
    void noxIntallFolderChanged();
    void devicesListChanged();
    void amountOfThreadChanged();
    void isLaunchMutiTaskChanged();

private:
    static AppModel* m_instance;

    QString m_noxIntallFolder;
    QList<QObject*> m_devicesList;
    uint m_amountOfThread;
    bool m_isLaunchMutiTask;

public slots:
};

#endif // APPMODEL_H
