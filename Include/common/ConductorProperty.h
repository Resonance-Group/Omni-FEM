#ifndef CONDUCTORPROPERTY_H_
#define CONDUCTORPROPERTY_H_

#include <string>

using namespace std;

/*! /brief This class is the conductors class. when the simulator
 *          is running the E-stat portion, conductor properties will need to be
 *          set. This class contains the properties of a condutor
 */ 
class conductorProperty
{
private:
    //! This is the name of the property
    string _conductorName;
    
    //! Set to True if the conductor is suppose to have a charge value False will be that the COnductor is a Prescribed Voltage
    bool _isTotalCharge = true;
    
    //! The value of the object. The meaning of value is determined by the above boolean
    double _value = 0;
    
    //! The value of the charge
    double _charge = 0;
public:
    //! This next sections are the getters/setters for the private variables
    void setName(string name);
    
    string getName();
    
    //! This function will set the conductor to be either a total charge or prescribed voltage
    void setIsTotalChargeState(bool state);
    
    //! This function will return true if the conductor is a total charge property
    bool getIsTotalChargeState();
    
    //! This will set the value to be either total charge or prescibe voltage
    void setValue(double value);
    
    //! This will return either the total charge or prescibed voltage
    double getValue();
};





#endif