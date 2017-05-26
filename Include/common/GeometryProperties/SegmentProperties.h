#ifndef SEGMENTPROPERTIES_H_
#define SEGMENTPROPERTIES_H_

#include <string>

#include <common/ElectricalBoundary.h>
#include <common/MagneticBoundary.h>
#include <common/enums.h>
#include <common/ConductorProperty.h>

//! This class contains all of the solver properties that the user can set for the segment.
/*!
    The properties in the class does not include any properties that the user can set
    that pertain to the geometric properties. This is strictly for the solver.
    For geometric properties, refer to the geometric class.
    This property not only applies to the lines but also arcs.
*/ 
class segmentProperty
{
private:
    //! This will store a local copy of the current physics problem that the user is working
    physicProblems _problem = physicProblems::NO_PHYSICS_DEFINED;
    
    //! The name of the boundary condition that the segment belongs to.
    /*!
        The name is beginning stored so that the solver will have quick and easy
        access to the master list. In later versions, this will be a pointer
    */ 
    std::string _boundaryName = "None";
    
    //! Boolean that specifies if the mesher should automatically choose the mesh size along the boundary
    /*!
        If the user would like the mesher to choose the mesh size along the boundary, set
        to true, otherwise false.
        If false, then the mesher will look at the value _elementSize
    */ 
    bool _meshSpacingIsAuto = true;
    
    //! Value that specifies what the element size should be along the segment
    /*!
        This value is the maximum size that the Finite Elements should be
        long the segment
    */ 
    double _elementSize = 0;
    
    //! The conductor that the semgent belongs to
    /*!
        This only pertains to electrostatic simulations.
        This stores the name of the conductor that the segment belongs to.
        In later versions, this will be a pointer
    */ 
    std::string _conductorName = "None";
    
    //! Boolean that states if the segment is hidden in the mesher
    /*!
        A hidden segment is not considered within the mesher. This
        is also refered to as a construction line
    */
    bool _segmentIsHidden = false;
    
    //! The group number that the segment belongs to
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