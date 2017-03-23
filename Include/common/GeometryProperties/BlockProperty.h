#ifndef BLOCKPROPERTY_H_
#define BLOCKPROPERTY_H_

#include <string>

#include <common/ElectroStaticMaterial.h>
#include <common/MagneticMaterial.h>
#include <common/CircuitProperty.h>
#include <common/enums.h>


class blockProperty
{
private:
    physicProblems _problem = physicProblems::NO_PHYSICS_DEFINED;
    
    std::string _materialName = "None";
    
    std::string _circuitName = "None";
    
    bool _meshSizeIsAuto = true;
    
    double _meshSize = 0;
    
    unsigned long _numberOfTurns = 1;
    
    double _magnetization = 0;
    
    unsigned int _groupNumber = 0;
    
    bool _isExternalRegion = false;
    
    bool _isDefault = false;
    
public:
    void setPhysicsProblem(physicProblems problem)
    {
        _problem = problem;
    }
    
    physicProblems getPhysicsProblem()
    {
        return _problem;
    }
    
    void setMaterialName(std::string name)
    {
        _materialName = name;
    }
    
    std::string getMaterialName()
    {
        return _materialName;
    }
    
    void setCircuitName(std::string name)
    {
        _circuitName = name;
    }
    
    std::string getCircuitName()
    {
        return _circuitName;
    }
    
    void setAutoMeshState(bool state)
    {
        _meshSizeIsAuto = state;
    }
    
    bool getAutoMeshState()
    {
        return _meshSizeIsAuto;
    }
    
    void setMeshSize(double size)
    {
        _meshSize = size;
    }
    
    double getMeshSize()
    {
        return _meshSize;
    }

    
    void setNumberOfTurns(unsigned long turnCount)
    {
        _numberOfTurns = turnCount;
    }
    
    unsigned long getNumberOfTurns()
    {
        return _numberOfTurns;
    }
    
    void setMagnetization(double value)
    {
        _magnetization = value;
    }
    
    double getMagnetization()
    {
        return _magnetization;
    }
    
    void setGroupNumber(unsigned int number)
    {
        _groupNumber = number;
    }
    
    unsigned int getGroupNumber()
    {
        return _groupNumber;
    }
    
    void setIsExternalState(bool state)
    {
        _isExternalRegion = state;
    }
    
    bool getIsExternalState()
    {
        return _isExternalRegion;
    }
    
    void setDefaultState(bool state)
    {
        _isDefault = state;
    }
    
    bool getDefaultState()
    {
        return _isDefault;
    }
};

#endif