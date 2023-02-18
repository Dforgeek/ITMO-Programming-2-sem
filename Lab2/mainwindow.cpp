#include "mainwindow.h"
#include "ui_form.h"
#include "secondwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CentralBankWidget)
{
    ui->setupUi(this);

    networkManager = new QNetworkAccessManager();

    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onResult);\

    networkManager->get(QNetworkRequest(QUrl("https://www.cbr-xml-daily.ru/daily_json.js")));\

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnCount(str.size());
    ui->tableWidget->setHorizontalHeaderLabels(str);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::update);
    timer->start(1);

    update();
}




MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onResult(QNetworkReply *reply){
    if (!reply->error()){

        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonObject root = document.object();

        QString str = root["Date"].toString(), s="Last time update ";
        str.truncate(str.lastIndexOf(QChar('+')));

        QString format = "yyyy'-'MM'-'dd'T'hh:mm:ss";

        QDateTime valid = QDateTime::fromString(str, format);

        s.append(valid.toString("hh:mm:ss dd.MM.yyyy"));
        ui->lastUpdateLabel->setText(s);
        if (root["Valute"].isObject()){

            QJsonObject valutes = root["Valute"].toObject();
            ui->tableWidget->setRowCount(valutes.keys().size());
            int cnt=0;

            for (auto &i: valutes.keys()){

               QJsonObject valutesInfo = valutes[i].toObject();

               ui->tableWidget->setItem(cnt, 0, new QTableWidgetItem(valutesInfo["CharCode"].toString()));
               ui->tableWidget->setItem(cnt, 1, new QTableWidgetItem(QString::number(valutesInfo["Nominal"].toInteger())));\
               ui->tableWidget->setItem(cnt, 2, new QTableWidgetItem(valutesInfo["Name"].toString()));
               ui->tableWidget->setItem(cnt, 3, new QTableWidgetItem(QString::number(valutesInfo["Value"].toDouble())));\
               cnt++;
            }
        }

    }
}

void MainWindow::update(){

    QDateTime UTC(QDateTime::currentDateTimeUtc());
    ui->timeLabel->setText(UTC.toLocalTime().toString());

    if (UTC.currentSecsSinceEpoch()%10==0){
        networkManager->get(QNetworkRequest(QUrl("https://www.cbr-xml-daily.ru/daily_json.js")));
    }
}




void MainWindow::on_graphButton_clicked()
{
    QDateTime upToDate =QDateTime::fromString(ui->upToDateLine->text(), "dd/MM/yyyy");
    if (ui->charCodeLine->text().isEmpty() || ui->upToDateLine->text().isEmpty()){
        QMessageBox::critical(this, "Ошибка ввода", "Один из параметров был не введён");
    }else if(QDateTime::currentSecsSinceEpoch()-upToDate.toSecsSinceEpoch()>31536000){
        QMessageBox::critical(this, "Ошибка ввода", "Слишком большой промежуток времени или дата просто введена некорректно");
    }else{
        QString charCode = ui->charCodeLine->text();
        QDateTime upToDate =QDateTime::fromString(ui->upToDateLine->text(), "dd/MM/yyyy");
        upToDate.setTime(QTime(11, 30, 0));
        graph = new secondwindow(charCode, upToDate);
        if (graph->charCodeIsCorrect){
            graph->show();
        }
    }
}

