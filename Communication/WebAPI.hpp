#ifndef WEBAPI_H
#define WEBAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "Processing/QAESEncryption.hpp"
#include <QTextCodec>
#include <QStandardPaths>

class WebAPI : public QObject
{
    Q_OBJECT

private:
    explicit WebAPI(QObject *parent = nullptr);

public:
    static WebAPI *instance();

private:
    static WebAPI* s_instance;

private:

    QString getKeyByToken() const;
    QString getKeyByIMEI() const;
    QString getIV() const;
    QByteArray getEncodedDeviceInfo() const;
    QByteArray getEncodedString(QString action) const;
    QByteArray getEncodedStringByImei(QString action) const;
    QByteArray getEncodedJsonDoc(QJsonDocument json) const;

public:
    void getConfig();

public slots:

signals:
};

#endif // WEBAPI_H
