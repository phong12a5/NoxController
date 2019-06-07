#ifndef NOXRUNNER_H
#define NOXRUNNER_H

#include <QObject>
#include "AppDefines.h"

class NoxRunner : public QObject
{
    Q_OBJECT
public:
    explicit NoxRunner(QString instanceName = "", int index = 0);
    ~NoxRunner();

private:
    QString m_instanceName;
    int m_index;

public:

signals:
    void finished();

public slots:
    void run();
};

#endif // NOXRUNNER_H
