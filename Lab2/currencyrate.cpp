#include "currencyrate.h"

CurrencyRate::CurrencyRate(QObject *parent):QObject(parent){}


CurrencyRate::CurrencyRate(QString url, QObject *parent):QObject(parent){
    accessManager = new QNetworkAccessManager;
    eventLoop = new QEventLoop;
    connect(accessManager, &QNetworkAccessManager::finished, eventLoop, &QEventLoop::quit);
    connect(accessManager, &QNetworkAccessManager::finished, this, &CurrencyRate::getCurrencyRate);
    accessManager->get(QNetworkRequest(QUrl("https:"+url)));

    waiting();
}

CurrencyRate::CurrencyRate(const CurrencyRate &curRate):QObject(){
    rate = curRate.rate;
    prevUrl=curRate.prevUrl;
    dateTime=curRate.dateTime;
}

CurrencyRate &CurrencyRate::operator=(CurrencyRate curRate){
    rate = curRate.rate;
    prevUrl=curRate.prevUrl;
    dateTime=curRate.dateTime;
    return *this;
}

ValuteCurrency &CurrencyRate::operator[](QString charCode){
    for (ValuteCurrency &i:rate){
        if (i.getCharCode()==charCode){
            return i;

        }
    }
    return rate[0];
}

void CurrencyRate::getCurrencyRate(QNetworkReply *reply){
    if (!reply->error()){

        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonObject root = document.object();

        prevUrl=root["PreviousURL"].toString();

        QString str = root["Date"].toString();

        str.truncate(str.lastIndexOf(QChar('+')));

        QString format = "yyyy'-'MM'-'dd'T'hh:mm:ss";

        dateTime = QDateTime::fromString(str, format);
        QJsonObject valutes = root["Valute"].toObject();

        for (auto &i: valutes.keys()){
           rate.push_back(ValuteCurrency(valutes[i].toObject()));
        }

    }else{
        qDebug() << "\nNetwork reply error!";
        qDebug() << reply->url();
        qDebug() << reply->error();
        exit(-1);
    }
    reply->deleteLater();
}
bool CurrencyRate::contains(QString charCode){

    for (ValuteCurrency &i:rate){
        if (i.getCharCode()==charCode){
            return true;
        }
    }
    return false;
}
void CurrencyRate::waiting(){
    eventLoop->exec();
}

QString CurrencyRate::getUrl(){
    return prevUrl;
}

QDateTime CurrencyRate::getDateTime()const{
    return dateTime;
}
