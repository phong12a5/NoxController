#ifndef APPDEFINES_H
#define APPDEFINES_H

#include <QDebug>
#include <QTest>

#define LOG qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "] >>"
#define delay(milescond)    QTest::qSleep(milescond)

#define INSTALL_FOLDER_PREFIX   "installation-folder:"
#define INSTALL_FOLDER_NAME     "config.txt"

#define ENDSCRIPT_PATH          "/storage/emulated/legacy/DCIM/"

#endif // APPDEFINES_H
