#include "common/CircuitProperty.h"


void circuitProperty::setName(string name)
{
    _circuitName = name;
}



string circuitProperty::getName()
{
    return _circuitName;
}



void circuitProperty::setCircuitSeriesState(bool isSeries)
{
    _isSeries = isSeries;
}



bool circuitProperty::getCircuitSeriesState()
{
    return _isSeries;
}



void circuitProperty::setCurrent(double currentValue)
{
    _current = currentValue;
}



double circuitProperty::getCurrent()
{
    return _current;
}