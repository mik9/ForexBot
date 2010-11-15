#include "bid.h"

bid::bid(QString row)
{
    is_valid=false;

    QStringList list=row.split(",");
    QStringList __date=list[0].split(".");
    int year=__date[0].toInt();
    int month=__date[1].toInt();
    int day=__date[2].toInt();

    if(QDate::isValid(year,month,day))
        _date=QDate(year,month,day);
    else
        return;

    QStringList __time=list[1].split(":");
    int hours=__time[0].toInt();
    int minutes=__time[1].toInt();
    if(QTime::isValid(hours,minutes,0))
        _time=QTime(hours,minutes);
    else
        return;
    bool ok;
    _open=list[2].toDouble(&ok);
    if(ok)
        _high=list[3].toDouble(&ok);
    else
        return;
    if(ok)
        _low=list[4].toDouble(&ok);
    else
        return;
    if(ok)
        _close=list[5].toDouble(&ok);
    else
        return;
    if(ok)
        is_valid=true;
}

double bid::close()
{
    return _close;
}
QDate bid::date()
{
    return _date;
}
double  bid::high()
{
    return _high;
}
double  bid::low()
{
    return _low;
}
double  bid::median()
{
    return (_high+_low)/2;
}
double  bid::open()
{
    return _open;
}
QTime bid::time()
{
    return _time;
}
bool bid::isValid()
{
    return is_valid;
}
