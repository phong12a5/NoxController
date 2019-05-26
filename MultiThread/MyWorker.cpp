#include "MyWorker.h"

MyWorker::MyWorker(QObject *parent) : QObject(parent)
{

}

void MyWorker::doWork(const QString &parameter)
{
    QString result;
    /* ... here is the expensive or blocking operation ... */
    emit resultReady(result);
}
