#ifndef BID_H
#define BID_H

#include <QDate>
#include <QTime>
#include <QStringList>
#include <QDebug>

class bid
{
public:
    bid(QString row);
    QDate date();
    QTime time();
    double open();
    double close();
    double high();
    double low();
    double median();
    bool isValid();

private:
    bool is_valid;
    QDate _date;
    QTime _time;
    double _open;
    double _close;
    double _high;
    double _low;
};

#endif // BID_H
