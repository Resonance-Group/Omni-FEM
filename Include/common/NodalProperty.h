#ifndef NODALPROPERTY_H_
#define NODALPROPERTY_H_

#include <string>

using namespace std;


//! Class that is created in order to handle the nodal properties of the simulations
/*!
    This class handles the nodal properties for both the electrostatic and mangeticostatic simulations
  
    For the magnetic simulation, the user can define the vector potential, A, at a given point
    or can define a point current, J, at a given point. These two values are mutullay exlsive and
    the meaning of the value variable within the class is governed by a boolean.
  
    The vector potential A can be defined as a complex value. The units are Wbber/meter. Typically, A us
    defined as some particular value at some point in the solution domain for 
    problems with derivative boundary conditions on all sides. For the point current J, this can
    also be defined as a complex number.
  
    For electrostatic simulations, the value can be defined as either a specific voltage
    at a particular point or a pont charge density at a given point. The voltage is in units of V 
    and the point charge in units of C/m
*/ 
class nodalProperty
{
private:
    //! The name of the property
    string _nodalName = "None";
    
    //! Boolean that is used to define the meaning of the value variable within the class
    /*!
        This boolean is used to specify the meaning of the value variable.
        For magnetic simulations, this boolean changes the meaning of the value variable from
        a specific vector potential value (set to true) to a point current density value (set to false)
      
        For electrostatics, this boolean changes the value variable from a specific voltage value (set to true)
        to a specific point charge density (set to false)
        
        In both cases, if this variable is true, then the value is a specific potential value (volts or vector potential).
        If the variable is false, then the value is some sort of density (current or charge density).
    */ 
    bool _isSpecificPotential = true;
    
    //! This is the value associated with the above boolean. the units are C/m for charge density
    double _value = 0;
    
public:

    //! Sets the name of the property
    /*!
        \param name The name of the point property
    */ 
    void setName(string name)
    {
        _nodalName = name;
    }
    
    //! Retrieves the name of the property
    /*!
        \return Returns a string representing the name of the property
    */ 
    string getName()
    {
        return _nodalName;
    }
    
    //! Sets the meaning of the value variable
    /*!
        For magnetic simulations, setting the state to true will define the value variable as
        a specific vector potential at a point. Setting state to false will define the 
        value variable as a current density.
      
        For electrostatics, setting the state to true will define the value variable as 
        a specific voltage as a point. Setting to false will define the value variable as a 
        charge density value.
        \param state Boolean used to switch the meaning of the value variable. Set to true
                    if the value parameter is a specific potential. Set to false if the 
                    value is a density value.
     */ 
    void setState(bool state)
    {
        _isSpecificPotential = state;
    }
    
    //! Retrieves the state of the value parameter
    /*!
        \return Returns true if the value variable is a specific potential (vector potential or voltage).
                Returns false if the value variable is a density value (current or charge).
    */ 
    bool getState()
    {
        return _isSpecificPotential;
    }
    
    //! Sets the value of the property
    /*!
        The meaning of this value is defined by the setState function
        For magnetics, this value is either a vector potential or current density (A/m).
        For electrostatics, this value can mean either a specific voltage potential (V) 
        or a point charge density (C/m).
        \param value The value of the nodal property
    */ 
    void setValue(double value)
    {
        _value = value;
    }
    
    //! Retreives the value stored in the value variable
    /*!
        The meaning of this value is defined by the setState function
        For magnetics, this value is either a vector potential or current density (A/m).
        For electrostatics, this value can mean either a specific voltage potential (V) 
        or a point charge density (C/m).
        \return Returns a value representign the value of the nodal property
    */ 
    double getValue()
    {
        return _value;
    }
};





#endif