#include "NoxCommand.h"
#include "AppMain.h"
#include <iostream>

#define APP_MODEL AppModel::instance()

bool NoxCommand::runNoxCommand(QString cmd)
{
    LOG << "Cmd: " << cmd;
    QProcess process;
    process.setWorkingDirectory(APP_MODEL->noxIntallFolder());
    process.start(cmd);
    process.waitForFinished(-1);
    if(process.readAllStandardError() != ""){
        LOG << process.readAllStandardError();
        return false;
    }else{
        return true;
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
    NoxCommand::runNoxCommand(QString("NoxConsole.exe add -name:%1 -systemtype:%2").arg(instanceName).arg(androidVersion));
    return NoxCommand::runNoxCommand(QString("Nox.exe -name:%1 -root:true -screen:vertical -lang:en -resolution:720x1280 -virtualKey:true -cpu:1 -quit").arg(instanceName));
}

bool NoxCommand::nox_adb_command(QString instanceName, QString cmd)
{
    QString fullCmd = QString("NoxConsole.exe adb -name:%1 -command:\"%2\"").arg(instanceName).arg(cmd);
    return NoxCommand::runNoxCommand(fullCmd);
}

QString NoxCommand::nox_adb_command_str(QString instanceName, QString cmd)
{
    QProcess process;
    QString fullCmd = QString("NoxConsole.exe adb -name:%1 -command:\"%2\"").arg(instanceName).arg(cmd);
    QString retVal = "";
    process.setWorkingDirectory(APP_MODEL->noxIntallFolder());
    process.start(fullCmd);
    process.waitForFinished(-1);
    if(process.readAllStandardError() != ""){
        retVal = process.readAllStandardError();
    }else{
        retVal = process.readAllStandardOutput();
    }
    LOG << retVal;
    return  retVal;
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

bool NoxCommand::checkConnection(QString instanceName)
{
    QProcess process;
    QString fullCmd = QString("NoxConsole.exe adb -name:%1 -command:\"shell ls | grep sdcard\"").arg(instanceName);
    bool retVal = false;
    process.setWorkingDirectory(APP_MODEL->noxIntallFolder());
    process.start(fullCmd);
    process.waitForFinished(-1);
    if(process.readAllStandardError() != ""){
        LOG << "ERROR: " << process.readAllStandardError();
    }else{
        QString output = process.readAllStandardOutput().simplified();
        if(output == "sdcard"){
            retVal = true;
        }else{
            retVal = false;
        }
    }
    return retVal;
}

bool NoxCommand::coppyInstance(QString instanceName, QString fromInstanceName)
{
    LOG << instanceName << " from "  << fromInstanceName;
    return NoxCommand::runNoxCommand(QString("NoxConsole.exe copy -name:%1 -from:%2").arg(instanceName).arg(fromInstanceName));
}
