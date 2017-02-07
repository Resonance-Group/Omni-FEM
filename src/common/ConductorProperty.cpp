#include "common/ConductorProperty.h"


void conductorProperty::setName(string name)
{
    _conductorName = name;
}



string conductorProperty::getName()
{
    return _conductorName;
}



void conductorProperty::togglePrescribeVoltage()
{
    if(!_isTotalCharge)
    {
        if(_isPrescribeVoltage)
            _isPrescribeVoltage = false;
        else
            _isPrescribeVoltage = true;
    }
}



bool conductorProperty::getPrescribeVoltageState()
{
    return _isPrescribeVoltage;
}



void conductorProperty::toggleTotalCharge()
{
    if(!_isPrescribeVoltage)
    {
        if(_isTotalCharge)
        {
            _isTotalCharge = false;
        }
        else
            _isTotalCharge = true;
    }
}



void conductorProperty::setVoltage(double value)
{
    _voltageValue = value;
}



double conductorProperty::getVoltage()
{
    return _voltageValue;
}



void conductorProperty::setCharge(double value)
{
    _charge = value;
}