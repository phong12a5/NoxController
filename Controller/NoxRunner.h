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
    QTimer *m_checkRunAppTimer;

public:

signals:
    void finished();

public slots:
    void run();
    void quitRunner();
    void onCheckConnection();
    void onCheckEnscript();
    void onCheckRunApp();
};

#endif // NOXRUNNER_H
