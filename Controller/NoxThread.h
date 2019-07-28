#ifndef NOXTHREAD_H
#define NOXTHREAD_H

#include <QObject>
#include "AppDefines.h"
#include "NoxIntance.h"
#include "NoxRunner.h"
#include <QThread>

class NoxThread : public QObject
{
    Q_OBJECT
public:
    explicit NoxThread(QObject *parent = nullptr);
    ~NoxThread();

private:
    void setNoxInstance();

private:
    NoxIntance* m_noxInstance;
    NoxRunner* m_Worker;
    QThread* m_workerThread;

signals:
    void operate();
    void quitThread();
    void missionCompleted(NoxThread*);

public slots:
    void finishedATask();
};

#endif // NOXTHREAD_H
