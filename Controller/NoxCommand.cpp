#include "NoxCommand.h"
#include "AppMain.h"
#include <iostream>

#define APP_MODEL AppModel::instance()

bool NoxCommand::runNoxCommand(QString cmd)
{
    QProcess process;
    process.setWorkingDirectory(APP_MODEL->noxIntallFolder());
    process.start(cmd);
    process.waitForFinished(-1);
    if(process.readAllStandardError() != ""){
        LOG << process.readAllStandardError();
        return false;
    }else{
        LOG << process.readAllStandardOutput();
        return true;
    }
}

QString NoxCommand::runNoxCommand_Str(QString cmd)
{
    LOG << "Cmd: " << cmd;
    QProcess process;
    process.setWorkingDirectory(APP_MODEL->noxIntallFolder());
    process.start(cmd);
    process.waitForFinished(-1);
    if(process.readAllStandardError() != ""){
        return QString(process.readAllStandardError());
    }else{
        return QString(process.readAllStandardOutput());
    }
}

bool NoxCommand::lunchInstance(QString instanceName)
{
    LOG << instanceName;
    return NoxCommand::runNoxCommand(QString("NoxConsole.exe launch -name:%1").arg(instanceName));
}

bool NoxCommand::installPackage(QString instanceName, QString apkPath)
{
    LOG << "instanceName: " << instanceName << " -- apkPath: " << apkPath;
    if(!QFile(apkPath).exists()){
        LOG << "apkPath has not existed!";
        return false;
    }
    return NoxCommand::runNoxCommand(QString("NoxConsole.exe installapp -name:%1 -filename:%2").arg(instanceName).arg(apkPath));
}

bool NoxCommand::runApp(QString instanceName, QString packageName)
{
    LOG << "instanceName: " << instanceName << " -- packageName: " << packageName;
    return NoxCommand::runNoxCommand(QString("NoxConsole.exe runapp -name:%1 -packagename:%2").arg(instanceName).arg(packageName));
}

bool NoxCommand::addInstance(QString instanceName, int androidVersion)
{
    LOG << instanceName;
    return NoxCommand::runNoxCommand(QString("NoxConsole.exe add -name:%1 -systemtype:%2").arg(instanceName).arg(androidVersion));
}

bool NoxCommand::nox_adb_command(QString instanceName, QString cmd)
{
    QString fullCmd = QString("NoxConsole.exe adb -name:%1 -command:\"%2\"").arg(instanceName).arg(cmd);
    return NoxCommand::runNoxCommand(fullCmd);
}

bool NoxCommand::quitInstance(QString instanceName)
{
    LOG << instanceName;
    return NoxCommand::runNoxCommand(QString("NoxConsole.exe quit -name:%1").arg(instanceName));
}

bool NoxCommand::quitAll()
{
    LOG;
    return NoxCommand::runNoxCommand("NoxConsole.exe quitall");
}

bool NoxCommand::rebootInstance(QString instanceName)
{
    LOG << instanceName;
    return NoxCommand::runNoxCommand(QString("NoxConsole.exe reboot -name:%1").arg(instanceName));
}
