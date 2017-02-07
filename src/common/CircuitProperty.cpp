#include "common/CircuitProperty.h"


void circuitProperty::setName(string name)
{
    _circuitName = name;
}



string circuitProperty::getName()
{
    return _circuitName;
}



void circuitProperty::toggleSeriesCircuit()
{
    if(_isSeries)
        _isSeries = false;
    else
        _isSeries = true;
}



bool circuitProperty::getCircuitState()
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