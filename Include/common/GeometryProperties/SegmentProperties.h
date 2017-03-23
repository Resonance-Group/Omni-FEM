#ifndef SEGMENTPROPERTIES_H_
#define SEGMENTPROPERTIES_H_

#include <string>

#include <common/ElectricalBoundary.h>
#include <common/MagneticBoundary.h>
#include <common/enums.h>
#include <common/ConductorProperty.h>

class segmentProperty
{
private:
    physicProblems _problem = physicProblems::NO_PHYSICS_DEFINED;
    
    std::string _boundaryName = "None";
       
    bool _meshSpacingIsAuto = true;
    
    double _elementSize = 0;
    
    std::string _conductorName = "None";
    
    bool _segmentIsHidden = false;
    
    unsigned int _groupNumber = 0;
    
public:
    void setPhysicsProblem(physicProblems problem)
    {
        _problem = problem;
    }
    
    physicProblems getPhysicsProblem()
    {
        return _problem;
    }
    
    void setBoundaryName(std::string name)
    {
        _boundaryName = name;
    }
    
    std::string getBoundaryName()
    {
        return _boundaryName;
    }
    
    void setConductorName(std::string name)
    {
        _conductorName = name;
    }
    
    
    std::string getConductorName()
    {
        return _conductorName;
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
};
#endif