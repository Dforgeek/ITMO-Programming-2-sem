#include "valutecurrency.h"

ValuteCurrency::ValuteCurrency()
{
    CharCode="";
    Value=0;

}

ValuteCurrency::ValuteCurrency(const ValuteCurrency &val){
    CharCode=val.CharCode;
    Value=val.Value;
}

ValuteCurrency::ValuteCurrency(QJsonObject obj){
    CharCode=obj.value("CharCode").toString();
    Value=obj.value("Value").toDouble();
}

ValuteCurrency &ValuteCurrency::operator=(const ValuteCurrency &val) = default;

double ValuteCurrency::getVal()const{
    return Value;
}
QString ValuteCurrency::getCharCode()const{
    return CharCode;
}
