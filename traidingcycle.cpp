#include "traidingcycle.h"

TradingCycle::TradingCycle(QVector<bid *> *_vector, long _date_start, long _date_end, int w1, int w2, int w3, int w4)
{
    vector=_vector;
    date_start=_date_start;
    date_end=_date_end;
    p = new Perceptron(_vector,w1,w2,w3,w4);
    deal=NULL;
}

TradingCycle::~TradingCycle()
{
    for(int i=0;i<deals.count();i++)
        delete deals.at(i);
}

void TradingCycle::trade()
{
    for(int i=date_start;i<date_end;i++) {
        bid* curr=vector->at(i);
        double p=this->p->perceptron(i);
        if(deal!=NULL){
            if(deal->direction()==BUY) {
                if(deal->open_value()-curr->close()>STOP_LOSS || p>0) {
                    deal->close_at(curr->close());
                    deals.append(deal);
                    deal=NULL;
//                    qDebug() << QObject::tr("Closing deal at %1").arg(i);
                }
            }
            else {
                if(curr->close()-deal->open_value()>STOP_LOSS || p<0) {
                    deal->close_at(curr->close());
                    deals.append(deal);
                    deal=NULL;
//                    qDebug() << QObject::tr("Closing deal at %1").arg(i);
                }
            }
        }
        else {
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
        deal=NULL;
    }
}

double TradingCycle::profit()
{
    double s=0;
    for(int i=0;i<deals.count();i++) {
        s+=deals.at(i)->profit();
    }
    return s;
}
