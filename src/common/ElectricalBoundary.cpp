#include "common/ElectricalBoundary.h"

void electricalBoundary::setVoltage(double value)
{
    _fixedVoltageValue = value;
}



double electricalBoundary::getVoltage()
{
    return _fixedVoltageValue;
}



void electricalBoundary::setSigma(double value)
{
    _surfaceChargeDensity = value;
}



double electricalBoundary::getSigma()
{
    return _surfaceChargeDensity;
}


void electricalBoundary::setBC(bcEnumElectroStatic BC)
{
    _type = BC;
}


bcEnumElectroStatic electricalBoundary::getBC()
{
    return _type;
}
