#ifndef CURRENCYRATE_H
#define CURRENCYRATE_H
#include <QVector>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QUrl>
#include <QEventLoop>
#include <QDateTime>
#include <QTimer>
#include "valutecurrency.h"

class CurrencyRate:public QObject
{
public:
    CurrencyRate(QObject *parent=nullptr);
    CurrencyRate(QString url, QObject *parent=nullptr);
    CurrencyRate(const CurrencyRate &rate);
    void getCurrencyRate(QNetworkReply *reply);
    CurrencyRate &operator=(CurrencyRate rate);
    ValuteCurrency &operator[](QString charCode);
    QString str;
    QString getUrl();
    QDateTime getDateTime()const;
    QDateTime dateTime;
    bool contains(QString charCode);

private:
    void waiting();
    QVector<ValuteCurrency> rate;
    QNetworkAccessManager *accessManager;
    QEventLoop *eventLoop;
    QString prevUrl;

};

#endif // CURRENCYRATE_H
