#include "common/NodalProperty.h"


void nodalProperty::setName(string name)
{
    _nodalName = name;
}



string nodalProperty::getName()
{
    return _nodalName;
}



void nodalProperty::toggleSpecificPotentialState()
{
    if(_isSpecificPotential)
        _isSpecificPotential = false;
    else
        _isSpecificPotential = true;
}



bool nodalProperty::getSpecificPotentialState()
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