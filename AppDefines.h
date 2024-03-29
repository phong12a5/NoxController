#ifndef APPDEFINES_H
#define APPDEFINES_H

#include <QDebug>
#include <QEventLoop>
#include <QTimer>

#define LOG qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "] "
#define FARM_PACKAGE_NAME       "org.qtproject.example.AutoFarm"
#define INSTALL_FOLDER_PREFIX   "installation-folder:"
#define INSTALL_FOLDER_NAME     "config.json"
#define CONFIG_FILE_NAME        "config.json"
#define ISNOX_PATH              "/sdcard/DCIM/"
#define ENDSCRIPT_PATH          "/sdcard/DCIM/"
#define ENDSCRIPT_FILENAME      "endScript.st"
#define INITSCRIPT_FILENAME     "/sdcard/DCIM/initApp.st"
#define APK_FILENAME            "xyz.autofarmer.apk"
#define INSTALL_FOLDER_FIELD    "installation_folder"
#define NOX_LIST_FIELD          "devices_list_config"
#define TOKEN_PROP_KEY          "farm_token"
#define API_SERVER              "https://api.autofarmer.xyz/api/"
#define ANDROID_VERSION         5
#define MAX_THREAD              30
#define NOX_DEVICES_COUNT       30

#define APP_DATA_FOLDER         "/data/data/xyz.autofarmer.app/"

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

inline void delay(int ms){
    QEventLoop even;
    QTimer timer;
    timer.setInterval(ms);
    timer.setSingleShot(true);
    QObject::connect(&timer, SIGNAL(timeout()), &even, SLOT(quit()));
    timer.start();
    even.exec();
}

#endif // APPDEFINES_H
