#include "perceptron.h"

Perceptron::Perceptron(QVector<bid *> *_vector, int _w1, int _w2, int _w3, int _w4)
{
    vector=_vector;
    w1=_w1;
    w2=_w2;
    w3=_w3;
    w4=_w4;
}

double Perceptron::perceptron(long pos)
{
    return (w1-100)*oscillator(pos) +
            (w2-100)*oscillator(pos-7) +
            (w3-100)*oscillator(pos-14) +
            (w4-100)*oscillator(pos-21);
}

double Perceptron::oscillator(long pos)
{
    return SMA(pos,34) - SMA(pos,5);
}

double Perceptron::SMA(long pos,int n)
{
    if(pos<n)
        return 0;
    double s=0;
    for(long i=pos-n;i<pos;i++) {
        s+=vector->at(i)->median();
    }
    return s/n;
}
