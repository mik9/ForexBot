#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <QVector>
#include "bid.h"

class Perceptron
{
public:
    Perceptron(QVector<bid*>* _vector,int _w1,int _w2,int _w3,int _w4);
    double perceptron(long pos);
    double oscillator(long);
    double SMA(long,int);

private:
    QVector<bid*> *vector;
    int w1,w2,w3,w4;
};

#endif // PERCEPTRON_H
