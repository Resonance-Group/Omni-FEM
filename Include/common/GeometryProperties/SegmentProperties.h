#ifndef SEGMENTPROPERTIES_H_
#define SEGMENTPROPERTIES_H_

#include <common/ElectricalBoundary.h>
#include <common/MagneticBoundary.h>
#include <common/enums.h>
#include <common/ConductorProperty.h>

class segmentProperty
{
private:
    physicProblems _problem = physicProblems::NO_PHYSICS_DEFINED;

    magneticBoundary _magneticBoundaryCondition;
    
    electricalBoundary _electroStaticBoundaryCondition;
    
    bool _meshSpacingIsAuto = true;
    
    double _elementSize = 0;
    
    conductorProperty _conductor;
    
    bool _segmentIsHidden = false;
    
    unsigned int _groupNumber = 0;
    
    bool _boundaryConditionIsSet = false;
    
    bool _conductorIsSet = false;
    
public:
    void setPhysicsProblem(physicProblems problem)
    {
        _problem = problem;
    }
    
    physicProblems getPhysicsProblem()
    {
        return _problem;
    }
    
    void setMagneticBoudnary(magneticBoundary boundary)
    {
        _magneticBoundaryCondition = boundary;
        _boundaryConditionIsSet = true;
    }
    
    magneticBoundary getMagneticBoundary()
    {
        return _magneticBoundaryCondition;
    }
    
    void setElectricalBoundary(electricalBoundary boundary)
    {
        _electroStaticBoundaryCondition = boundary;
        _boundaryConditionIsSet = true;
    }
    
    electricalBoundary getElectricalBoundary()
    {
        return _electroStaticBoundaryCondition;
    }
    
    void setMeshAutoState(bool state)
    {
        _meshSpacingIsAuto = state;
    }
    
    bool getMeshAutoState()
    {
        return _meshSpacingIsAuto;
    }
    
    void setElementSizeAlongLine(double size)
    {
        _elementSize = size;
    }
    
    double getElementSizeAlongLine()
    {
        return _elementSize;
    }
    
    void setConductor(conductorProperty conductor)
    {
        _conductor = conductor;
        _conductorIsSet = true;
    }
    
    conductorProperty getConductor()
    {
        return _conductor;
    }

    void setHiddenState(bool isHidden)
    {
        _segmentIsHidden = isHidden;
    }
    
    bool getHiddenState()
    {
        return _segmentIsHidden;
    }
    
    void setGroupNumber(unsigned int number)
    {
        _groupNumber = number;
    }
    
    unsigned int getGroupNumber()
    {
        return _groupNumber;
    }
    
    bool checkIsBoundarySet()
    {
        return _boundaryConditionIsSet;
    }
    
    bool checkIsCircuitSet()
    {
        return _conductorIsSet;
    }
};
#endif