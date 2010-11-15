#ifndef TradingCycle_H
#define TradingCycle_H

#include <QVector>
#include <QThread>
#include <QObject>
#include "bid.h"
#include "perceptron.h"
#include "deal.h"
#include "bid.h"

#define STOP_LOSS 0.01

class TradingCycle : public QThread
{
    Q_OBJECT
public:
    TradingCycle(QVector<bid*>* _vector,long _date_start,long _date_end,int w1,int w2,int w3,int w4);
    void trade();
    double profit();
//    void set_parameters(int w1,int w2,int w3,int w4);
    void get_parameters(int *w1,int *w2,int *w3,int *w4);
    virtual void run();

signals:
    void my_finished( TradingCycle* );

private:
    QVector<bid*>* vector;
//    QVector<Deal*> deals;
    long date_start;
    long date_end;
    Perceptron* p;
    Deal* deal;
    void open_deal(bool direction);
    void close_deal();
    double _profit;
    void save_parameters(int w1,int w2,int w3,int w4);
    int _w1,_w2,_w3,_w4;
};

#endif // TradingCycle_H
