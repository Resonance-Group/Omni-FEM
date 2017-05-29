#ifndef NODALPROPERTY_H_
#define NODALPROPERTY_H_

#include <string>

using namespace std;

/*! /brief  in the E-Static sim, a node can contain certain settings that would be necessary for 
 *          running a simulation. This class contains the methods/attributes for the nodes that contain particular
 *          properties.
 * 
 *          This class is the point property. This class differs from the nodeSettings class in that this class
 *          will be used during the FEM calculations
 */
class nodalProperty
{
private:
    //! The name of the property
    string _nodalName = "None";
    
    //! Currently, there are two options, a specified potential property and a point current. This attribute combines the two into a boolean data type.
    bool _isSpecificPotential = true;
    
    //! This is the value associated with the above boolean. the units are C/m for charge density
    double _value = 0;
    
public:
    nodalProperty()
    {
        _nodalName = "None";
        _isSpecificPotential = true;
        _value = 0;
    }

    //! This next section contains the getters and setters for the above private variables
    void setName(string name)
    {
        _nodalName = name;
    }
    
    string getName()
    {
        return _nodalName;
    }
    
    /*! /brief 
     * This function will set the state of the property which determined if the property is a specific potential or point current for magnetics
     * For electrostatics, this function will change the state to be either a Specific Potential or a POint Charge Dnesity value
     */ 
    void setState(bool state)
    {
        _isSpecificPotential = state;
    }
    
    //! This function will get the state of the property. Function returns true to indicate that the value in the class is for a specificed potential
    bool getState()
    {
        return _isSpecificPotential;
    }
    
    void setValue(double value)
    {
        _value = value;
    }
    
    double getValue()
    {
        return _value;
    }
};





#endif