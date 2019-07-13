#include "WebAPI.hpp"
#include "AppModel.h"

#define MODEL AppModel::instance()

WebAPI* WebAPI::s_instance = nullptr;

WebAPI::WebAPI(QObject *parent) : QObject(parent)
{
    // Do nothing
}

WebAPI *WebAPI::instance()
{
    if(s_instance == nullptr){
        s_instance = new WebAPI();
    }
    return s_instance;
}

void WebAPI::getConfig()
{
    QString url = API_SERVER + QString("config?token=%1").arg(MODEL->token());
    QUrl serviceUrl = QUrl(url);
    QNetworkRequest request(serviceUrl);
    QJsonObject json;

    json.insert("action", QTextCodec::codecForMib(106)->toUnicode(getEncodedString("config")));
    json.insert("device", QTextCodec::codecForMib(106)->toUnicode(getEncodedDeviceInfo()));

    QByteArray jsonData = QJsonDocument(json).toJson();
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    QEventLoop evenlopp;
    QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply*)),
            &evenlopp, SLOT(quit()));
    QNetworkReply* reply = networkManager->post(request, jsonData);
    evenlopp.exec();

    QByteArray responseData = reply->readAll();
    QJsonObject jsonObj = QJsonDocument::fromJson(responseData).object();

    if(jsonObj.isEmpty()){
        LOG << "jsonObj is empty!";
        return;
    }else{
        // Continue
    }

    if(jsonObj["action"].toString() == QTextCodec::codecForMib(106)->toUnicode(getEncodedString("config"))){
        QString data =  jsonObj["data"].toString();

        QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
        QByteArray decodeText = encryption.decode(QByteArray::fromBase64(data.toUtf8()), getKeyByIMEI().toLocal8Bit(), getIV().toLocal8Bit());
        QJsonDocument jdoc = QJsonDocument::fromJson(encryption.removePadding(decodeText));
        QJsonObject jsonObj = jdoc.object();
        if(!jsonObj.isEmpty()){
            APP_CONFIG config;
            config.timeout =    jsonObj["Timeout"].toInt();
            config.reset_3g =   jsonObj["Reset3g"].toInt();
            config.debug_mode = jsonObj["Debug_mode"].toString();
            config.user_type = jsonObj["User_type"].toInt();
            config.encryption = jsonObj["Encryption"].toString();
            LOG << "config.timeout: " << config.timeout;
            LOG << "config.reset_3g: " << config.reset_3g;
            LOG << "config.debug_mode: " << config.debug_mode;
            LOG << "config.user_type: " << config.user_type;
            LOG << "config.encryption: " << config.encryption;
            MODEL->setAppConfig(config);
        }
    }else{
        LOG << "Another action!";
    }
}

QString WebAPI::getKeyByToken() const
{
    QString retVal = MODEL->token() + "congaubeo@123";
    return retVal;
}

QString WebAPI::getKeyByIMEI() const
{
    QString retVal;
    return retVal;
}

QString WebAPI::getIV() const
{
    QString retVal = "0123456789012345";
    return retVal;
}

QByteArray WebAPI::getEncodedDeviceInfo() const
{
    QJsonObject deviceInfo;

//    deviceInfo["GoogleSF"] =        MODEL->deviceInfo().googleSF;
//    deviceInfo["AndroidID"] =       MODEL->deviceInfo().androidID;
//    deviceInfo["IMEI"] =            MODEL->deviceInfo().iMEI;
//    deviceInfo["IMSI"] =            MODEL->deviceInfo().iMSI;
//    deviceInfo["SIMCardSerial"] =   MODEL->deviceInfo().sIMCardSerial;
//    deviceInfo["WifiMacAddress"] =  MODEL->deviceInfo().wifiMacAddress;
//    deviceInfo["android_verion"] =  MODEL->deviceInfo().android_verion;
//    deviceInfo["model"] =           MODEL->deviceInfo().model;
//    deviceInfo["isNox"] =           MODEL->deviceInfo().isNox;

    QByteArray deviceInfoData = QJsonDocument(deviceInfo).toJson();

    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);

    return encryption.encode(deviceInfoData, getKeyByToken().toLocal8Bit(), getIV().toLocal8Bit()).toBase64();
}

QByteArray WebAPI::getEncodedString(QString action) const
{
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
    return encryption.encode(action.toLocal8Bit(), getKeyByToken().toLocal8Bit(), getIV().toLocal8Bit()).toBase64();
}

QByteArray WebAPI::getEncodedStringByImei(QString action) const
{
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
    return encryption.encode(action.toLocal8Bit(), getKeyByIMEI().toLocal8Bit(), getIV().toLocal8Bit()).toBase64();
}

QByteArray WebAPI::getEncodedJsonDoc(QJsonDocument json) const
{
    QByteArray deviceInfoData = json.toJson();
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
    return encryption.encode(deviceInfoData, getKeyByIMEI().toLocal8Bit(), getIV().toLocal8Bit()).toBase64();
}




