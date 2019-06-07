#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include "AppDefines.h"
#include "AppModel.h"
#include "Controller/NoxThread.h"

class AppController : public QObject
{
    Q_OBJECT
private:
    explicit AppController(QObject *parent = nullptr);

public:
    static AppController* instance();
    void initAppController();

    void startMultiTask();
    void stopMultiTask();

private:
    static AppController* m_instance;

    QList<NoxThread* > m_noxThreadList;

signals:

public slots:
    void onDevicesListChanged();
    void aMissionCompleted(NoxThread* threadAdd = nullptr);
};

#endif // APPCONTROLLER_H
