#ifndef NOXCOMMAND_H
#define NOXCOMMAND_H

#include <QObject>
#include "AppDefines.h"
#include <QProcess>

class NoxCommand : public QObject
{
    Q_OBJECT

public:
    static bool runNoxCommand(QString binaryName, QString args);
    static bool runNoxCommand(QString binaryName, QString args, QString &output, QString &error);
    static bool lunchInstance(QString instanceName);
    static bool installPackage(QString instanceName, QString apkPath);
    static bool runApp(QString instanceName, QString packageName);
    static bool addInstance(QString instanceName, int androidVersion);
    static bool nox_adb_command(QString instanceName, QString cmd);
    static QString nox_adb_command_str(QString instanceName, QString cmd);
    static bool quitInstance(QString instanceName);
    static bool quitAll();
    static bool rebootInstance(QString instanceName);
    static bool checkConnection(QString instanceName);
    static bool coppyInstance(QString instanceName, QString fromInstanceName);

signals:

public slots:
};

#endif // NOXCOMMAND_H
