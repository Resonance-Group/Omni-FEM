#include "common/BoundaryConditions.h"

void boundaryCondition::setBoundaryName(string name)
{
    _boundaryName = name;
}



string boundaryCondition::getBoundaryName()
{
    return _boundaryName;
}



void boundaryCondition::setC0(double value)
{
    _c0 = value;
}



double boundaryCondition::getC0Value()
{
    return _c0;
}



void boundaryCondition::setC1(double value)
{
    _c1 = value;
}



double boundaryCondition::getC1Value()
{
    return _c1;
}
