#include "common/ConductorProperty.h"


void conductorProperty::setName(string name)
{
    _conductorName = name;
}



string conductorProperty::getName()
{
    return _conductorName;
}



void conductorProperty::setIsTotalChargeState(bool state)
{
    _isTotalCharge = state;
}



bool conductorProperty::getIsTotalChargeState()
{
    return _isTotalCharge;
}



void conductorProperty::setValue(double value)
{
    _value = value;
}



double conductorProperty::getValue()
{
    return _value;
}
