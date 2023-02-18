#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QLabel>
#include <QStringList>
#include <QString>
#include <QDateTime>
#include <QTimer>
#include <QMessageBox>
#include "secondwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class CentralBankWidget; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onResult(QNetworkReply *reply);
    void update();
//    void showTime(QDateTime UTC);

    void on_graphButton_clicked();

private:
    Ui::CentralBankWidget *ui;
    secondwindow *graph;
    QNetworkAccessManager *networkManager;
    QNetworkAccessManager *networManagerUpdate;
    QScrollArea *scrollArea;
    QStringList str{"Букв. код", "Номинал", "Валюта", "Курс"};
    QTimer *timer;
};

#endif // MAINWINDOW_H
