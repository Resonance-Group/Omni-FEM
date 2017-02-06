#include "common/MagneticMaterial.h"


void magneticMaterial::setBHCurveLinearity(bool isLinear)
{
    _isLinear = isLinear;
}



void magneticMaterial::setPhiMax(double value)
{
    _phiMax = value;
}


double magneticMaterial::getPhiMax()
{
    return _phiMax;
}



bool magneticMaterial::getBHState()
{
    return _isLinear;
}



void magneticMaterial::setMUrX(double value)
{
    _relativePermeabilityX = value;
}



double magneticMaterial::getMUrX()
{
    return _relativePermeabilityX;
}



void magneticMaterial::setMUrY(double value)
{
    _relativePermeabilityY = value;
}



double magneticMaterial::getMUrY()
{
    return _relativePermeabilityY;
}



void magneticMaterial::setPhiX(double value)
{
    _phiHX = value;
}



double magneticMaterial::getPhiX()
{
    return _phiHX;
}



void magneticMaterial::setPhiY(double value)
{
    _phiHY = value;
}



double magneticMaterial::getPhiY()
{
    return _phiHY;
}



void magneticMaterial::setCoercivity(double value)
{
    _coercivity = value;
}



double magneticMaterial::getCoercivity()
{
    return _coercivity;
}



void magneticMaterial::setSigma(double value)
{
    _electricalConductivity = value;
}



double magneticMaterial::getSigma()
{
    return _electricalConductivity;
}



void magneticMaterial::setCurrentDensity(double value)
{
    _currentDensity = value;
}



double magneticMaterial::getCurrentDensity()
{
    return _currentDensity;
}



void magneticMaterial::setSpecialAttribute(lamWireEnum value)
{
    _attribute = value;
}



lamWireEnum magneticMaterial::getSpecialAttribute()
{
    return _attribute;
}



void magneticMaterial::setLaminationThickness(double value)
{
    _lamThickness = value;
}



double magneticMaterial::getLaminationThickness()
{
    return _lamThickness;
}



void magneticMaterial::setNumberStrands(double value)
{
    _numStrands = value;
}



double magneticMaterial::getNumberStrands()
{
    return _numStrands;
}



void magneticMaterial::setLaminationFillFactor(double value)
{
    _lamFF = value;
}



double magneticMaterial::getLaminationFillFactor()
{
    return _lamFF;
}



void magneticMaterial::setStrandDiameter(double value)
{
    _strandDia = value;
}



double magneticMaterial::getStrandDiameter()
{
    return _strandDia;
}


