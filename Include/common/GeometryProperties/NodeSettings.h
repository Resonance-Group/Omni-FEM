#ifndef NODESETTING_H_
#define NODESETTING_H_

#include <string>

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
    physicProblems _problem = physicProblems::NO_PHYSICS_DEFINED;// Is this needed?
    
    //! This will store the name of the nodal property the the node is assigned to.
    std::string _nodalPropertyName = "None";
    
    std::string _conductorPropertyName = "None";
    
    unsigned int _groupNumber = 0;
    
public:
    nodeSetting()
    {
        _problem = physicProblems::NO_PHYSICS_DEFINED;
        _groupNumber = 0;
    }

    void setPhysicsProblem(physicProblems problem)
    {
        _problem = problem;
    }
    
    physicProblems getPhysicsProblem()
    {
        return _problem;
    }
    
    void setNodalPropertyName(std::string name)
    {
        _nodalPropertyName = name;
    }
    
    std::string getNodalPropertyName()
    {
        return _nodalPropertyName;
    }
    
    void setConductorPropertyName(std::string name)
    {
        _conductorPropertyName = name;
    }
    
    std::string getConductorPropertyName()
    {
        return _conductorPropertyName;
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