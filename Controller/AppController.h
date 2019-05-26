#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include "AppDefines.h"
#include "AppModel.h"

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
signals:

public slots:
    void onDevicesListChanged();
};

#endif // APPCONTROLLER_H
