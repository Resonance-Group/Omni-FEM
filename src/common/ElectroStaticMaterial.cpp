#include "common/ElectroStaticMaterial.h"


void electrostaticMaterial::setEpsilonX(double value)
{
    _relativePermittivityX = value;
}



double electrostaticMaterial::getEpsilonX()
{
    return _relativePermittivityX;
}



void electrostaticMaterial::setEpsilonY(double value)
{
    _relativePermittivityY = value;
}



double electrostaticMaterial::getEpsilonY()
{
    return _relativePermittivityY;
}