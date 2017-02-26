#ifndef BLOCKPROPERTY_H_
#define BLOCKPROPERTY_H_

#include <common/ElectroStaticMaterial.h>
#include <common/MagneticMaterial.h>
#include <common/CircuitProperty.h>
#include <common/enums.h>


class blockProperty
{
private:
    physicProblems _problem = physicProblems::NO_PHYSICS_DEFINED;
    
    electrostaticMaterial _electricMaterial;
    
    magneticMaterial _magneticMaterial;
    
    bool _meshSizeIsAuto = true;
    
    double _meshSize = 0;
    
    circuitProperty _circuit;
    
    unsigned long _numberOfTurns = 1;
    
    double _magnetization = 0;
    
    unsigned int _groupNumber = 0;
    
    bool _isExternalRegion = false;
    
    bool _isDefault = false;
    
    bool _magneticMaterialIsSet = false;
    
    bool _electricMaterialIsSet = false;
    
    bool _circuitIsSet = false;
    
public:
    void setPhysicsProblem(physicProblems problem)
    {
        _problem = problem;
    }
    
    physicProblems getPhysicsProblem()
    {
        return _problem;
    }
    
    void setElectricMaterial(electrostaticMaterial material)
    {
        _electricMaterial = material;
        _electricMaterialIsSet = true;
    }
    
    electrostaticMaterial getElectricMaterial()
    {
        return _electricMaterial;
    }
    
    void setMagneticMaterial(magneticMaterial material)
    {
        _magneticMaterial = material;
        _magneticMaterialIsSet = true;
    }
    
    magneticMaterial getMagneticMaterial()
    {
        return _magneticMaterial;
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
    
    void setCircuit(circuitProperty circuit)
    {
        _circuit = circuit;
        _circuitIsSet = true;
    }
    
    circuitProperty getCircuit()
    {
        return _circuit;
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
    
    bool getMagneticMaterialSetState()
    {
        return _magneticMaterialIsSet;
    }
    
    bool getElectricMaterialSetState()
    {
        return _electricMaterialIsSet;
    }
    
    bool getCircuitSetState()
    {
        return _circuitIsSet;
    }
};

#endif