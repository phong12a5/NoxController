#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "AppMain.h"
#include <QtWidgets>
#include <QtConcurrent>

#include <functional>

using namespace QtConcurrent;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    AppMain appMain;
    appMain.initApplication(&engine);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()){
        LOG << "rootObject is NULL";
    }

    /*QApplication app(argc, argv);

    const int iterations = 20;

    // Prepare the vector.
    QVector<int> vector;
    for (int i = 0; i < iterations; ++i)
        vector.append(i);

    // Create a progress dialog.
    QProgressDialog dialog;
    dialog.setLabelText(QString("Progressing using %1 thread(s)...").arg(QThread::idealThreadCount()));

    // Create a QFutureWatcher and connect signals and slots.
    QFutureWatcher<void> futureWatcher;
    QObject::connect(&futureWatcher, &QFutureWatcher<void>::finished, &dialog, &QProgressDialog::reset);
    QObject::connect(&dialog, &QProgressDialog::canceled, &futureWatcher, &QFutureWatcher<void>::cancel);
    QObject::connect(&futureWatcher,  &QFutureWatcher<void>::progressRangeChanged, &dialog, &QProgressDialog::setRange);
    QObject::connect(&futureWatcher, &QFutureWatcher<void>::progressValueChanged,  &dialog, &QProgressDialog::setValue);

    // Our function to compute
    std::function<void(int&)> spin = [](int &iteration) {
        const int work = 1000 * 1000 * 40;
        volatile int v = 0;
        for (int j = 0; j < work; ++j){
            if(j %1000000 == 0){
                 qDebug() << "Running at iteration: " << iteration << " in thread: " << QThread::currentThreadId();
            }
            ++v;
        }
    };

    // Start the computation.
    futureWatcher.setFuture(QtConcurrent::map(vector, spin));

    // Display the dialog and start the event loop.
    dialog.exec();

    futureWatcher.waitForFinished();

    // Query the future to check if was canceled.
    qDebug() << "Canceled?" << futureWatcher.future().isCanceled();*/


    return app.exec();
}
