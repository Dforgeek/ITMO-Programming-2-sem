#ifndef VALUTECURRENCY_H
#define VALUTECURRENCY_H

#include <QString>
#include <QJsonObject>

class ValuteCurrency
{
public:
    ValuteCurrency();
    ValuteCurrency(const ValuteCurrency &val);
    ValuteCurrency(QJsonObject obj);
    ValuteCurrency &operator=(const ValuteCurrency &val);
    double getVal()const;
    QString getCharCode()const;

private:
    QString CharCode;
    double Value;
};

#endif // VALUTECURRENCY_H
