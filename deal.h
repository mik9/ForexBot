#ifndef DEAL_H
#define DEAL_H

#define SELL true
#define BUY false

class Deal
{
public:
    Deal(double _value, bool __direction);
    ~Deal();
    double open_value();
    double close_value();
    void close_at(double value);
    bool direction();
    double profit();

private:
    double _open_value;
    double _close_value;
    bool _direction;
};

#endif // DEAL_H
