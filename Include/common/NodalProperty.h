#ifndef NODALPROPERTY_H_
#define NODALPROPERTY_H_

#include <string>

using namespace std;

/*! /brief  in the E-Static sim, a node can contain certain settings that would be necessary for 
 *          running a simulation. This class contains the methods/attributes for the nodes that contain particular
 *          properties
 */
class nodalProperty
{
private:
    //! The name of the property
    string _nodalName;
    
    //! Currently, there are two options, a specified potential proper and a point charge density. This attribute combines the two into a boolean data type.
    bool _isSpecificPotential = true;
    
    //! This is the value associated with the above boolean. the units are C/m for charge density
    double _value;
    
public:
    //! This next section contains the getters and setters for the above private variables
    void setName(string name);
    string getName();
    
    void toggleSpecificPotentialState();
    bool getSpecificPotentialState();
    
    void setValue(double value);
    double getValue();
};



#endif