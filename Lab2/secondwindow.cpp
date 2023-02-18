#include "secondwindow.h"
#include "ui_graph.h"
#include <QTimer>
#include <QThread>
#include <unordered_map>
#include <algorithm>
#include <QCoreApplication>


secondwindow::secondwindow(QString valCode, QDateTime upToDate, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::secondwindow)
{
    ui->setupUi(this);

    charCode=valCode;
    series = new QLineSeries();
    setWindowTitle("График изменения курса валюты");
    QVector<double> values;
    double avg=0;
    int i=0;
    update("//www.cbr-xml-daily.ru/daily_json.js");
    if (!archive[i].contains(valCode)){
        QMessageBox::critical(this, "Ошибка ввода", "Братан такой валюты я не знаю");
        charCodeIsCorrect=false;
        return;
    }
    charCodeIsCorrect=true;
    avg+=archive[i][valCode].getVal();
    values.append(archive[i][valCode].getVal());

//    for (int i=1; i<30; i++){
//        update(archive[i].getUrl());
//        avg+=archive[i][valCode].getVal();
//        values.append(archive[i][valCode].getVal());
//    }
    qDebug() << "Updating replies...";
    while (upToDate<archive[i].getDateTime()){
        update(archive[i].getUrl());
//        if (upToDate<=archive[i].getDateTime()){
//            break;
//        }
        i++;
        avg+=archive[i][valCode].getVal();
        values.append(archive[i][valCode].getVal());
    }


    qDebug() << "Done with replies!\n";
    std::sort(values.begin(), values.end());
    avg/=i+1;
    ui->average->setText("Среднее значение: "+QString::number(avg));

    int medianNum=(i+1)/2;
    ui->median->setText("Медианное значение: "+QString::number(values[medianNum]));

    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("Изменение курса");


    axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("dd MMMM yyyy");
    axisX->setTitleText("Дата");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Цена в рублях");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);


    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setChart(chart);


}


secondwindow::~secondwindow()
{
    delete ui;
}

void secondwindow::update(QString url){
    CurrencyRate temp(url);
    qDebug() << temp.dateTime <<" "<< temp[charCode].getVal();
    series->append(temp.getDateTime().toMSecsSinceEpoch(), temp[charCode].getVal());
    archive.append(temp);
}


