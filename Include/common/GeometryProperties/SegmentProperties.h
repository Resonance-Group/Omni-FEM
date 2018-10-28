#ifndef SEGMENTPROPERTIES_H_
#define SEGMENTPROPERTIES_H_

#include <string>

#include <common/ElectricalBoundary.h>
#include <common/MagneticBoundary.h>
#include <common/enums.h>
#include <common/ConductorProperty.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

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
	friend class boost::serialization::access;
	
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & _problem;
		ar & _boundaryName;
		ar & _meshSpacingIsAuto;
		ar & _elementSize;
		ar & _conductorName;
		ar & _segmentIsHidden;
		ar & _groupNumber;
	}

    //! This will store a local copy of the current physics problem that the user is working
    physicProblems _problem = physicProblems::NO_PHYSICS_DEFINED;
    
    //! The name of the boundary condition that the segment belongs to.
    /*!
        The name is beginning stored so that the solver will have quick and easy
        access to the master list. In later versions, this will be a pointer
    */ 
    std::string _boundaryName = "None";
	
	//! The boundary object for electrical boundary
	electricalBoundary *p_electricalBoundary = nullptr;
	
	//! The boundary object for magnetics
	magneticBoundary *p_magneticBoundary = nullptr;
    
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
	
	conductorProperty *p_conductoryProperty = nullptr;
    
    //! Boolean that states if the segment is hidden in the mesher
    /*!
        A hidden segment is not considered within the mesher. This
        is also refered to as a construction line
    */
    bool _segmentIsHidden = false;
    
    //! The group number that the segment belongs to
    unsigned int _groupNumber = 0;
    
public:
    //! Sets the physics problem to the segment property
    /*!
        \sa _problem
        \param problem The physics problem that the segment property needs to be set to
    */ 
    void setPhysicsProblem(physicProblems problem)
    {
        _problem = problem;
    }
    
    //! Gets the physics problem that the segment belongs to
    /*!
        \sa _problem
        \return Returns an enum represeting what physics problem the segment belongs to
    */ 
    physicProblems getPhysicsProblem()
    {
        return _problem;
    }
    
    //! Sets the boundary name that the property belongs to
    /*!
        This function will set the property to the boundary that is provided by the name
        parameter
        \sa _boundaryName
        \param name The name of the boundary that the semgment will belong to
    */ 
    void setBoundaryName(std::string name)
    {
        _boundaryName = name;
    }
    
    //! Gets the boundary name that the function belongs to
    /*!
        This function will return the boundary name that is associated with
        the segment. If there is no boundary, then the function will return 
        None.
        \sa _boundaryName
        \return The boundary name that is associated with the boundary. Will
                return None if there is no boundary
    */ 
    std::string getBoundaryName()
    {
        return _boundaryName;
    }
    
    //! Sets the conductor name that is associated with the segment
    /*!
        This function will set the segment to the conductor that is provided
        by the name parameter. This only applies for electrostatic simulations
        \sa _conductorName
        \param name The name of the conductor that the segment will belong to.
    */ 
    void setConductorName(std::string name)
    {
        _conductorName = name;
    }
    
    //! Gets the conductor name that is associated with the segment
    /*!
        This function will retrieve that conductor name that is 
        associated with the segment. This only applies to simulations
        that are electrostatic
        \sa _conductorName
        \return Returns the name of the conductor belonging to the 
                semgment
    */ 
    std::string getConductorName()
    {
        return _conductorName;
    }
    
    //! This will set the Auto Mesh State
    /*!
        The program will set the auto mesh state
        to the value provided in state for the segment
        \sa _meshSpacingIsAuto
        \param state Set to true for the mesher to automatically
                    calculate what the mesh size should be along
                    the segment. Otherwise, set to false
    */ 
    void setMeshAutoState(bool state)
    {
        _meshSpacingIsAuto = state;
    }
    
    //! Function that will get the mesh size auto state
    /*!
        This function will return the state of the 
        auto mesh boolean. This value will determine if the 
        program need to automatically compute the mesh element
        along the segment or use a user defined value
        \sa _meshSpacingIsAuto
        \return Return true if the program needs to automatically calculate
                the mesh element size along the boundary. Otherwise
                return false.
    */ 
    bool getMeshAutoState()
    {
        return _meshSpacingIsAuto;
    }
    
    //! Function that will set the element size variable to the value provided in size
    /*!
        This function will set the value of the element size to the 
        value provided in state
        \sa _elementSize
        \param size The element size that the elements along the 
                    segment should be set to when the mesher is 
                    ran
    */ 
    void setElementSizeAlongLine(double size)
    {
        _elementSize = size;
    }
    
    //! Function that will return the value of the element size along the segment
    /*!
        This function will return what the element size will be along the segment
        when the mesher is ran
        \sa _elementSize
        \return The value of the element size along the segment
    */ 
    double getElementSizeAlongLine()
    {
        return _elementSize;
    }
    
    //! Function that will set the state of the segment being hidden
    /*!
        This function will set the hidden state. The segment will be a construction
        line (or arc) if set to true.
        \sa _segmentIsHidden
        \param isHidden Boolen that is used to set the hidden state. If
                the segment is to be hidden in the post processor, then
                set to true, otherwise set to false.
    */ 
    void setHiddenState(bool isHidden)
    {
        _segmentIsHidden = isHidden;
    }
    
    //! Function that will retrieve the is hidden state
    /*!
        This function will return a boolean which describes
        if the segment is hidden in the post processor
        \sa _segmentIsHidden
        \return Returns true if the segment is hidden. Otherwise, return false.
    */ 
    bool getHiddenState()
    {
        return _segmentIsHidden;
    }
    
    //! Function that is used to set the group number of the segment
    /*!
        This function will set the group number of the segment
        \sa _groupNumber
        \param number The group number that the segment will belong to
    */ 
    void setGroupNumber(unsigned int number)
    {
        _groupNumber = number;
    }
    
    //! Function that will retrieve the group number that the segment belongs to
    /*!
        This function will return the group number that the segment is 
        associated with. 0 is the default group.
        \sa _groupNumber
        \return Returns a value representing the group number that the segment
                belongs with
    */ 
    unsigned int getGroupNumber()
    {
        return _groupNumber;
    }
	
	/**
	 * @brief Sets the electrical boundary of the property
	 * @param boundary The boundary that is to be associated with the property
	 */
	void setElectricalBoundary(electricalBoundary &boundary)
	{
		p_electricalBoundary = &boundary;
	}
	
	/**
	 * @brief Sets the electrical boundary of the property
	 * @param boundary A pointer pointing to the boundary that is to be associated with the property
	 */
	void setElectricalBoundary(electricalBoundary *boundary)
	{
		p_electricalBoundary = boundary;
	}
	
	/**
	 * @brief Retrieves the boundary porperty associated with the property
	 * @return Returns the pointer of the electrical boundary
	 */
	electricalBoundary* getElectricalBoundary()
	{
		if(p_electricalBoundary)
			return p_electricalBoundary;
		else
			return nullptr;
	}
	
	/**
	 * @brief Sets the magnetic boundary of the property
	 * @param boundary The boundary that is to be associated with the property
	 */
	void setMagneticBoundary(magneticBoundary &boundary)
	{
		p_magneticBoundary = &magneticBoundary;
	}
	
	/**
	 * @brief Sets the magnetic boundary of the property
	 * @param boundary A pointer pointing to the boundary that is to be associated with the property
	 */
	void setMagneticBoundary(magneticBoundary *boundary)
	{
		p_magneticBoundary = boundary;
	}
	
	/**
	 * @brief Retrieves the boundary porperty associated with the property
	 * @return Returns the pointer of the magnetic boundary
	 */
	magneticBoundary* getMagneticBoundary()
	{
		if(p_magneticBoundary)
			return p_magneticBoundary;
		else
			return nullptr;
	}
	
	/**
	 * @brief Sets the conductor property of the segment property
	 * @param boundary The boundary that is to be associated with the segment property
	 */
	void setConductorProperty(conductorProperty &property)
	{
		p_conductoryProperty = &property;
	}
	
	/**
	 * @brief Sets the conductor property of the segment property
	 * @param boundary A pointer pointing to the conductor property that is to be associated with the segment property
	 */
	void setConductorProperty(conductorProperty *property)
	{
		p_conductoryProperty = property;
	}
	
	/**
	 * @brief Retrieves the conductor property associated with the segment property
	 * @return Returns the pointer of the conductor property
	 */
	conductorProperty* getConductorProperty()
	{
		if(p_conductoryProperty)
			return p_conductoryProperty
		else
			return nullptr;
	}
};
#endif