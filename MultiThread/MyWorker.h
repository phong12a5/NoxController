#ifndef MYWORKER_H
#define MYWORKER_H

#include <QObject>
#include "AppDefines.h"

class MyWorker : public QObject
{
    Q_OBJECT
public:
    explicit MyWorker(QObject *parent = nullptr);

signals:
    void resultReady(const QString &result);
public slots:
    void doWork(const QString &parameter);
};

#endif // MYWORKER_H
