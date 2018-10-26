#ifndef ELECTRICALBOUNDARY_H_
#define ELECTRICALBOUNDARY_H_

#include <common/BoundaryConditions.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


//! Boundary condition class that is specific for electrostatic simulations
/*!
    This class handles all of the boundary conditions
    that is specific to electrostatic simulations.
    Specifically, this class will handle the boundary conditions
    that are fixed voltage, surface charge density, periodic, and 
    antiperiodic. 

    With fixed voltage, the voltage is set to a prescribed 
    value along a given segment. 

    With a surface charge density, this will apply a distrubtion
    of line charge to a segment. This boundary condition
    is usually used on internal boundaries where a segment is
    between materials or on isolated segments. The other
    boundary conditions are used on exterior segments.

    For a periodic boundary condition, this type is
    applied when it is required that the potential on two segments
    be identical to each other. This is useful in order to exploit the 
    symmetry of some problems. Another use is for open boundary applications.
    Many times, a periodic boundary is made up of several different segments.
    A different periodic condition must be defined for each section of the boundary
    since each periodic boundary condition can only
    be applied to a line or arc and another corresponding line or arc.

    For antiperiodic boundary condition,this is implemented in a similair manner
    as the periodic boundary condition. The only expection is that instead of the 
    two segments being identicial to each other, they are now the negative of another. 
*/ 
class electricalBoundary : public boundaryCondition
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<boundaryCondition>(*this);
		ar & _fixedVoltageValue;
		ar & _surfaceChargeDensity;
		ar & _type;
		ar & p_boundaryID;
	}
private:
    //! This variable stores the voltage value in a fixed voltage boundary condition
    double _fixedVoltageValue = 0;
    
    //! This variable stores the charge density value in a surface charge density boundary condition
    double _surfaceChargeDensity = 0;
	
	//! The boundary ID associated with the boundary. This is used in the solver primarly
	unsigned int p_boundaryID = 0;
    
    //! This variable identifies what boundary condition this property is
    bcEnumElectroStatic _type;
public:

    //! Sets the voltage for a fixed voltage boundary condition
    /*!
        \param value The voltage value of the voltage in a fixed
                    voltage boundary condition. The units are V
    */ 
    void setVoltage(double value)
    {
        _fixedVoltageValue = value;
    }
    
    //! Retreives the voltage value
    /*!
        \return Returns the voltage value in V
    */ 
    double getVoltage()
    {
        return _fixedVoltageValue;
    }
    
    //! Sets the charge density in a surface charge density boundary condition
    /*!
        This function will set the surface charge density parameter
        \param value The surface charge density in units of columb (C)
    */ 
    void setSigma(double value)
    {
        _surfaceChargeDensity = value;
    }
    
    //! Retrieves the surface charge density value 
    /*!
        \return Returns the surface charge density in units of C
    */ 
    double getSigma()
    {
        return _surfaceChargeDensity;
    }
    
    //! Sets the boundary condition of the property
    /*!
        \param BC The boundary condition that the property will be
    */ 
    void setBC(bcEnumElectroStatic BC)
    {
        _type = BC;
    }
    
    //! Retrieves the boundary condition of the property
    /*!
        \return Returns a value indicating what boundary condition that the
                property is
    */ 
    bcEnumElectroStatic getBC()
    {
        return _type;
    }
	
	/**
	 * @brief Function that is used in order to set the boudary ID of the boundary
	 * 			This is for internal purposes only and the user will not eb able to
	 * 			edit this property
	 * @param ID The ID of the boundary
	 */
	void setBoundaryID(unsigned int ID)
	{
		p_boundaryID = ID;
	}
	
	/**
	 * @brief Retrieves the boundary ID of the boundary
	 * @return Returns the boundary ID
	 */
	unsigned int getBoundaryID()
	{
		return p_boundaryID;
	}
};

#endif