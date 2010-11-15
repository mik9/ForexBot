#ifndef TradingCycle_H
#define TradingCycle_H

#include <QVector>
#include "bid.h"
#include "perceptron.h"
#include "deal.h"
#include "bid.h"

#define STOP_LOSS 0.001

class TradingCycle
{
public:
    TradingCycle(QVector<bid*>* _vector,long _date_start,long _date_end,int w1,int w2,int w3,int w4);
    ~TradingCycle();
    void trade();
    double profit();
    double _profit;
private:
    QVector<bid*>* vector;
    QVector<Deal*> deals;
    long date_start;
    long date_end;
    Perceptron* p;
    Deal* deal;
    void open_deal(bool direction);
    void close_deal();
};

#endif // TradingCycle_H
