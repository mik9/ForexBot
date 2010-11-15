#include "deal.h"
/*
 * НІКОЛИ більше не юзать в іменах змінних більше ніж 2 нижнів підкреслювання
 * НІКОЛИ!!!
 */
Deal::Deal(double _value, bool __direction)
{
    _close_value = _open_value=_value;
    _direction = __direction;
}
Deal::~Deal()
{
}

void Deal::close_at(double value)
{
    _close_value = value;
}

bool Deal::direction()
{
    return _direction;
}

double Deal::open_value()
{
    return _open_value;
}

double Deal::close_value()
{
    return _close_value;
}

double Deal::profit()
{
    return (_direction == SELL) ? (_close_value - _open_value) : (_open_value - _close_value);
}
