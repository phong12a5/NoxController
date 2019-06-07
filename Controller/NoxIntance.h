#ifndef NOXINTANCE_H
#define NOXINTANCE_H

#include <QObject>
#include "NoxCommand.h"

class NoxIntance : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString instanceName READ instanceName CONSTANT)
    Q_PROPERTY(bool isRunning READ isRunning WRITE setIsRunning NOTIFY isRunningChanged)
    Q_PROPERTY(bool installedApp READ installedApp WRITE setInstalledApp NOTIFY installedAppChanged)

public:
    explicit NoxIntance(QObject *parent, QString instanceName, int indexOf);
    ~NoxIntance();

    QString instanceName() const;
    bool isRunning() const;
    void setIsRunning(const bool data);
    int indexOf() const;
    bool installedApp() const;
    void setInstalledApp(bool data);

private:
    QString m_instanceName;
    int m_indexOf;
    bool m_isRunning;
    bool m_installedApp;

signals:
    void isRunningChanged();
    void installedAppChanged();

private slots:
};

#endif // NOXINTANCE_H
