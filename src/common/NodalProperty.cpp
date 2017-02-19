#include "common/NodalProperty.h"


void nodalProperty::setName(string name)
{
    _nodalName = name;
}



string nodalProperty::getName()
{
    return _nodalName;
}



void nodalProperty::setState(bool state)
{
    _isSpecificPotential = state;
}



bool nodalProperty::getState()
{
    return _isSpecificPotential;
}



void nodalProperty::setValue(double value)
{
    _value = value;
}



double nodalProperty::getValue()
{
    return _value;
}