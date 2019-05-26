#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include "MyWorker.h"
#include "AppDefines.h"

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    ~MyThread();

private:
    QThread workerThread;

signals:
    void operate(const QString &);

public slots:
    void handleResults(const QString &result);
};

#endif // MYTHREAD_H
