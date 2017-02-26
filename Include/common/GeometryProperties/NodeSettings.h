#ifndef NODESETTING_H_
#define NODESETTING_H_

#include <common/NodalProperty.h>
#include <common/ConductorProperty.h>
#include <common/enums.h>



/*! /brief 
 *  This class differs from the nodal property class becuase this is the 
 *  actual setting of the node. This class will be composed of the 
 *  nodal property class
 */ 
class nodeSetting
{
private:
    physicProblems _problem = physicProblems::NO_PHYSICS_DEFINED;

    nodalProperty _nodeProperty;
    
    unsigned int _groupNumber = 0;
    
    conductorProperty _conductorProperty;
    
    bool _nodePropertyIsSet = false;
    
    bool _conductorPropertyIsSet = false;
public:
    void setPhysicsProblem(physicProblems problem)
    {
        _problem = problem;
    }
    
    physicProblems getPhysicsProblem()
    {
        return _problem;
    }

    void setNodalProperty(nodalProperty property)
    {
        _nodeProperty = property;
        _nodePropertyIsSet = true;
    }
    
    nodalProperty getNodalProperty()
    {
        return _nodeProperty;
    }
    
    void setGroupNumber(unsigned int number)
    {
        _groupNumber = number;
    }
    
    unsigned int getGroupNumber()
    {
        return _groupNumber;
    }
    
    void setConductorProperty(conductorProperty property)
    {
        _conductorProperty = property;
        _conductorPropertyIsSet = true;
    }
    
    conductorProperty getConductorProperty()
    {
        return _conductorProperty;
    }
    
    bool getNodePropertyState()
    {
        return _nodePropertyIsSet;
    }
    
    bool getConductorPropertyState()
    {
        return _conductorPropertyIsSet;
    }
    
};


#endif