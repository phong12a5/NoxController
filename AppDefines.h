#ifndef APPDEFINES_H
#define APPDEFINES_H

#include <QDebug>
#include <QTest>

#define LOG qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "] >>"
#define delay(milescond)    QTest::qSleep(milescond)

#define INSTALL_FOLDER_PREFIX   "installation-folder:"
#define INSTALL_FOLDER_NAME     "config.json"

#define CONFIG_FILE_NAME        "config.json"

#define ENDSCRIPT_PATH          "/sdcard/DCIM/"
#define APK_FILENAME            "android-build-debug.apk"

#define INSTALL_FOLDER_FIELD    "installation_folder"
#define NOX_LIST_FIELD          "devices_list_config"

#endif // APPDEFINES_H
