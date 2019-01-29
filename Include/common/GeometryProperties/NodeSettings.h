#ifndef NODESETTING_H_
#define NODESETTING_H_

#include <string>

#include <common/NodalProperty.h>
#include <common/ConductorProperty.h>
#include <common/enums.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>



//! Class that contains all of the properties for a specific node
/*! 
    This class differs from the nodal property class becuase this is the 
    actual setting of the node. This class will be composed of the 
    nodal property class. This class only contains 
    properties that are specific for the solve.
    For the geometric properties, those are stored in the corresponding
    geometric shape property found in geometryShapes.h
*/ 
class nodeSetting
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & _problem;
		ar & _nodalPropertyName;
		ar & _conductorPropertyName;
		ar & _groupNumber;
	}
    //! This will store a local copy of the current physics problem that the user is working
    physicProblems _problem = physicProblems::NO_PHYSICS_DEFINED;// Is this needed?
    
    //! This will store the name of the nodal property the the node is assigned to.
    /*!
        This name will be used to in the solver in order to look up the
        apprioate parameters when the program is solving the simulation
    */ 
    std::string _nodalPropertyName = "None";
	
	nodalProperty *p_nodalProperty = nullptr;
    
    //! This will store the name of the conductor property that the node is assigned to.
    /*!
        This only pertains to electrostatic simulations. This name will be used
        in the solver in order to apply the apprioate conditions 
        when the progam is solving the simulation
    */ 
    std::string _conductorPropertyName = "None";
	
	conductorProperty *p_conductorProperty = nullptr;
    
    //! The group number that the node belongs to.
    /*!
        The defualt value for all group numbers is 0
    */ 
    unsigned int _groupNumber = 0;
    
public:
    
    //! Sets the physics problem that the node is working in
    /*!
        \sa _problem
        \param problem THe physics problem that the node will belong to
    */ 
    void setPhysicsProblem(physicProblems problem)
    {
        _problem = problem;
    }
    
    //! Gets the physic problem that the node belongs to
    /*!
        \sa _problem
        \return Returns the physic problem that the node belongs to
    */ 
    physicProblems getPhysicsProblem()
    {
        return _problem;
    }
      
    //! Sets the name of nodal property that the node should belong to
    /*!
        The name of the property is used in order to to quickly reference
        the nodal property. Not the ideal solution. Later versions will have this 
        be a pointer to the name
        \sa _nodalPropertyName
        \param name The name of the nodal property that the node should be set to
    */ 
    void setNodalPropertyName(std::string name)
    {
        _nodalPropertyName = name;
    }
    
    //! Gets the name of the nodal property that the node belongs to
    /*!
        \sa _nodalPropertyName
        \return Returns the name of the nodal property that the node belongs to
    */ 
    std::string getNodalPropertyName()
    {
        return _nodalPropertyName;
    }
    
    //! Sets the name of the conductor property that the node belongs to
    /*!
        This only pertains to electrostatic simulations
        \sa _conductorPropertyName
        \param name The name of conductor property that the node belongs to
    */ 
    void setConductorPropertyName(std::string name)
    {
        _conductorPropertyName = name;
    }
    
    //! Gets the name of the conductor property that the node belongs to
    /*!
        \sa _conductorPropertyName
        \return Returns that name of the conductor property that the node belongs to
    */ 
    std::string getConductorPropertyName()
    {
        return _conductorPropertyName;
    }
    
    //! Sets the group number that the node should belong to
    /*!
        \sa _groupNumer
        \param number The group number that the node should belong to
    */ 
    void setGroupNumber(unsigned int number)
    {
        _groupNumber = number;
    }
    
    //! Gets the group number that the node should belong to
    /*!
        \sa _groupNumber
        \return Returns the group number that the node belongs to
    */ 
    unsigned int getGroupNumber()
    {
        return _groupNumber;
    }
	
	void setNodalProperty(nodalProperty &property)
	{
		p_nodalProperty = &property;
	}
	
	void setNodalProperty(nodalProperty *property)
	{
		p_nodalProperty = property;
	}
	
	nodalProperty* getNodalProperty()
	{
		return p_nodalProperty;
	}
	
	void setConductorProperty(conductorProperty *property)
	{
		p_conductorProperty = property;
	}
	
	void setConductorProperty(conductorProperty &property)
	{
		p_conductorProperty = &property;
	}
	
	conductorProperty* getConductorProperty()
	{
		return p_conductorProperty;
	}
};


#endif