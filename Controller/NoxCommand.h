#ifndef NOXCOMMAND_H
#define NOXCOMMAND_H

#include <QObject>
#include "AppDefines.h"

class NoxCommand : public QObject
{
    Q_OBJECT

public:
    static bool runNoxCommand(QString cmd);
    static bool lunchInstance(QString instanceName);
    static bool installPackage(QString instanceName, QString apkPath);
    static bool runApp(QString instanceName, QString packageName);
    static bool addInstance(QString instanceName, int androidVersion);
    static bool nox_adb_command(QString instanceName, QString cmd);
    static bool quitInstance(QString instanceName);
    static bool quitAll();
    static bool rebootInstance(QString instanceName);

signals:

public slots:
};

#endif // NOXCOMMAND_H
