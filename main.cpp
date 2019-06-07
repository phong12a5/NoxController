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

    return app.exec();
}
