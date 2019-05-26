#ifndef NOXINTANCE_H
#define NOXINTANCE_H

#include <QObject>
#include "NoxCommand.h"

class NoxIntance : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString instanceName READ instanceName CONSTANT)

public:
    explicit NoxIntance(QObject *parent, QString instanceName, int indexOf);
    ~NoxIntance();

    QString instanceName() const;
    bool isRunning() const;
    int indexOf() const;

    void startInstance();
    void quitInstance();

private:
    QString m_instanceName;
    bool m_isRunning;
    int m_indexOf;

signals:
    void checkEndScript();

private slots:
    void onCheckEndScript();
};

#endif // NOXINTANCE_H
