#include "NoxCommand.h"
#include "AppMain.h"
#include <iostream>

#define APP_MODEL AppModel::instance()

bool NoxCommand::runNoxCommand(QString binaryName, QString args)
{
    QString cmd = QString("\"%1/%2\" %3").arg(APP_MODEL->noxIntallFolder()).arg(binaryName).arg(args);
    LOG << cmd;

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

bool NoxCommand::runNoxCommand(QString binaryName, QString args, QString &output, QString &error)
{
    QString cmd = QString("\"%1/%2\" %3").arg(APP_MODEL->noxIntallFolder()).arg(binaryName).arg(args);
//    LOG << cmd;

    QProcess process;
    process.setWorkingDirectory(APP_MODEL->noxIntallFolder());
    process.start(cmd);
    process.waitForFinished(-1);
    output = process.readAllStandardOutput();
    error = process.readAllStandardError();
    if(error != ""){
        return false;
    }else{
        return true;
    }
}

bool NoxCommand::lunchInstance(QString instanceName)
{
    LOG << instanceName;
    return NoxCommand::runNoxCommand("NoxConsole.exe", QString("launch -name:%1").arg(instanceName));
}

bool NoxCommand::installPackage(QString instanceName, QString apkPath)
{
    LOG << "instanceName: " << instanceName << " -- apkPath: " << apkPath;
    if(!QFile(apkPath).exists()){
        LOG << "apkPath has not existed!";
        return false;
    }
    return NoxCommand::runNoxCommand("NoxConsole.exe", QString("installapp -name:%1 -filename:%2").arg(instanceName).arg(apkPath));
}

bool NoxCommand::runApp(QString instanceName, QString packageName)
{
    LOG << "instanceName: " << instanceName << " -- packageName: " << packageName;
    return NoxCommand::runNoxCommand("NoxConsole.exe", QString("runapp -name:%1 -packagename:%2").arg(instanceName).arg(packageName));
}

bool NoxCommand::addInstance(QString instanceName, int androidVersion)
{
    LOG << instanceName;
    NoxCommand::runNoxCommand("NoxConsole.exe", QString("add -name:%1 -systemtype:%2").arg(instanceName).arg(androidVersion));
    return NoxCommand::runNoxCommand("Nox.exe", QString("-name:%1 -root:true -screen:vertical -lang:en -locale:sg -screen:vertical -resolution:1080x1920 -dpi:480 -virtualKey:true -cpu:1 -quit").arg(instanceName));
}

bool NoxCommand::nox_adb_command(QString instanceName, QString cmd)
{
    QString args = QString("adb -name:%1 -command:\"%2\"").arg(instanceName).arg(cmd);
    LOG << "args: " << args;
    return NoxCommand::runNoxCommand("NoxConsole.exe", args);
}

QString NoxCommand::nox_adb_command_str(QString instanceName, QString cmd)
{
    QString output, error, retVal;
    NoxCommand::runNoxCommand("NoxConsole.exe", QString("adb -name:%1 -command:\"%2\"").arg(instanceName).arg(cmd), output, error);
    if(error != ""){
        retVal = error;
    }else{
        retVal = output;
    }
    return  retVal;
}

bool NoxCommand::quitInstance(QString instanceName)
{
    LOG << instanceName;
    NoxCommand::setPropNox(instanceName,"persist.sys.language","en");
    NoxCommand::setPropNox(instanceName,"persist.sys.country","US");
    return NoxCommand::runNoxCommand("NoxConsole.exe", QString("quit -name:%1").arg(instanceName));
}

bool NoxCommand::quitAll()
{
    LOG;
    return NoxCommand::runNoxCommand("NoxConsole.exe","quitall");
}

bool NoxCommand::rebootInstance(QString instanceName)
{
    LOG << instanceName;
    return NoxCommand::runNoxCommand("NoxConsole.exe", QString("reboot -name:%1").arg(instanceName));
}

bool NoxCommand::checkConnection(QString instanceName)
{
    QString output, error;
    NoxCommand::runNoxCommand("NoxConsole.exe",QString("adb -name:%1 -command:\"shell ls | grep sdcard\"").arg(instanceName), output, error);
    bool retVal = false;
    if(error != ""){
        LOG << "ERROR: " << error;
    }else{
        output = output.simplified();
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
    return NoxCommand::runNoxCommand("NoxConsole.exe", QString("copy -name:%1 -from:%2").arg(instanceName).arg(fromInstanceName));
}

bool NoxCommand::setPropNox(QString instanceName, QString key, QString value)
{
    return NoxCommand::runNoxCommand("NoxConsole.exe", QString("setprop -name:%1 -key:%2 -value:%3").arg(instanceName).arg(key).arg(value));
}
