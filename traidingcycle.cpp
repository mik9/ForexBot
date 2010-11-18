#include "traidingcycle.h"

TradingCycle::TradingCycle(QVector<bid*> *_vector, long _date_start, long _date_end, int w1, int w2, int w3, int w4)
{
    vector=_vector;
    date_start=_date_start;
    date_end=_date_end;
    p = new Perceptron(_vector,w1,w2,w3,w4);
    deal=NULL;
    _profit=0;
    save_parameters(w1,w2,w3,w4);
}

TradingCycle::~TradingCycle()
{
    for(int i=0;i<deals.count();i++)
        delete deals.at(i);
}

//void TradingCycle::set_parameters(int w1, int w2, int w3, int w4)
//{
//    delete p;
//    p = new Perceptron(vector,w1,w2,w3,w4);
//    _profit=0;
//    save_parameters(w1,w2,w3,w4);
//}
void TradingCycle::save_parameters(int w1, int w2, int w3, int w4)
{
    _w1=w1;
    _w2=w2;
    _w3=w3;
    _w4=w4;
}
void TradingCycle::get_parameters(int *w1, int *w2, int *w3, int *w4)
{
    *w1=_w1;
    *w2=_w2;
    *w3=_w3;
    *w4=_w4;
}

void TradingCycle::trade()
{
    for(int i=date_start;i<date_end;i++) {
        bid* curr=vector->at(i);
        double p=this->p->perceptron(i);
        if(deal){
            if(deal->direction()==BUY) {
                if(/*deal->open_value()-curr->close()>STOP_LOSS && */p>0) {
                    deal->close_at(curr->close());
                    deals.append(deal);
                    _profit+=deal->profit();
//                    delete deal;
                    deal=NULL;
//                    qDebug() << QObject::tr("Closing deal at %1").arg(i);
                }
            }
            else {
                if(/*curr->close()-deal->open_value()>STOP_LOSS && */p<0) {
                    deal->close_at(curr->close());
                    deals.append(deal);
                    _profit+=deal->profit();
//                    delete deal;
                    deal=NULL;
//                    qDebug() << QObject::tr("Closing deal at %1").arg(i);
                }
            }
        }
        if(!deal) {
            if(p>0) {
                deal=new Deal(curr->close(),SELL);
//                qDebug() << QObject::tr("Opening deal for SELL at %1").arg(i);
            }
            else if (p<0) {
                deal=new Deal(curr->close(),BUY);
//                qDebug() << QObject::tr("Opening deal for BUY at %1").arg(i);
            }
        }
    }
    if(deal) {
        deal->close_at(vector->at(date_end)->close());
        deals.append(deal);
        _profit+=deal->profit();
//        delete deal;
        deal=NULL;
    }
}

double TradingCycle::profit()
{
//    double s=0;
//    for(int i=0;i<deals.count();i++) {
//        s+=deals.at(i)->profit();
//    }
//    return s;
    return _profit;
}

void TradingCycle::run()
{
    trade();
    emit my_finished(this);
    quit();
}

void TradingCycle::view_results()
{
    int p=0,m=0;
    for(int i=0;i<deals.count();i++){
        if(deals.at(i)->profit()<0)
            m++;
        else
            p++;
    }
    qDebug() << "Deals all:" << deals.count();
    qDebug() << "Deals +:" << p;
    qDebug() << "Deals -:" << m;
}
