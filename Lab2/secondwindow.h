#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QWidget>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QUrl>
#include <QTimer>
#include "currencyrate.h"

namespace Ui {
class secondwindow;
}

class secondwindow : public QWidget
{
    Q_OBJECT

public:
    explicit secondwindow(QString charCode, QDateTime upToDate, QWidget *parent = nullptr);
    ~secondwindow();
    void update(QString url);
    bool charCodeIsCorrect;

private:
    Ui::secondwindow *ui;
    QVector<CurrencyRate> archive;
    QString charCode;
    QLineSeries* series;
    QChart *chart;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;

};

#endif // SECONDWINDOW_H
