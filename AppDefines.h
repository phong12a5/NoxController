#ifndef APPDEFINES_H
#define APPDEFINES_H

#include <QDebug>
#include <QTest>

#define LOG qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "] >>"
#define delay(milescond)    QTest::qSleep(milescond)

#define FARM_PACKAGE_NAME       "org.qtproject.example.AutoFarm"
#define INSTALL_FOLDER_PREFIX   "installation-folder:"
#define INSTALL_FOLDER_NAME     "config.json"

#define CONFIG_FILE_NAME        "config.json"

#define ISNOX_PATH              "/sdcard/DCIM/"
#define ENDSCRIPT_PATH          "/sdcard/DCIM/"
#define ENDSCRIPT_FILENAME      "endScript.st"
#define APK_FILENAME            "android-build-debug.apk"

#define INSTALL_FOLDER_FIELD    "installation_folder"
#define NOX_LIST_FIELD          "devices_list_config"

#define API_SERVER              "https://api.autofarmer.xyz/api/"

#define ANDROID_VERSION         5

#define MAX_THREAD              30
#define NOX_DEVICES_COUNT       30

typedef struct app_config_struct {
    int timeout;
    int reset_3g;
    QString debug_mode;
    int user_type;
    QString encryption;
    int m_mobileCloneCount;
    int m_noxCount;
    int m_noxCloneCount;

    app_config_struct(){
        timeout = 30;
        reset_3g = 10;
        debug_mode = "test";
        user_type = 0;
        encryption = "00110001";
        m_mobileCloneCount = 0;
        m_noxCount = NOX_DEVICES_COUNT;
        m_noxCloneCount = 0;
    }
} APP_CONFIG;

#endif // APPDEFINES_H
