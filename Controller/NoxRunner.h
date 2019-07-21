#ifndef NOXRUNNER_H
#define NOXRUNNER_H

#include <QObject>
#include "AppDefines.h"
#include <QTimer>

class NoxRunner : public QObject
{
    Q_OBJECT
public:
    explicit NoxRunner(QString instanceName = "", int index = 0, bool installApp = false);
    ~NoxRunner();

private:
    QString m_instanceName;
    int m_index;
    bool m_installApp;
    bool m_setIsNoxFile;
    QTimer *m_checkConnectionTimer;
    QTimer *m_checkEndScriptTimer;
    bool isRunApp;

public:

signals:
    void finished();
    void installedApp();

public slots:
    void run();
    void onCheckConnection();
    void onCheckEnscript();
};

#endif // NOXRUNNER_H
