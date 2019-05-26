#include "MyThread.h"

MyThread::MyThread(QObject *parent) : QObject(parent)
{
    MyWorker *worker = new MyWorker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &MyThread::operate, worker, &MyWorker::doWork);
    connect(worker, &MyWorker::resultReady, this, &MyThread::handleResults);
    workerThread.start();
}

MyThread::~MyThread()
{
    workerThread.quit();
    workerThread.wait();
}

void MyThread::handleResults(const QString &result)
{
    LOG << result;
}
