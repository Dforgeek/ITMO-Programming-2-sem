#include "mainwindow.h"

#include <QApplication>
#include <QNetworkAccessManager>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1200, 800);
    w.show();

    return a.exec();
}
