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
    
    //! Set to true if the conductor is suppose to have a prescribed voltage value
    bool _isPrescribeVoltage = false;
    
    //! Set to True if the conductor is suppose to have a charge value
    bool _isTotalCharge = false;
    
    //! The value of the prescribed voltage
    double _voltageValue = 0;
    
    //! The value of the charge
    double _charge = 0;
public:
    conductorProperty();
    //! This next sections are the getters/setters for the private variables
    void setName(string name);
    string getName();
    
    //! Toggle the total prescribed voltage state from true -> false or false -> true. Technically, only one should be active at a time. Checks are in place to ensure this.
    void togglePrescribeVoltage();
    bool getPrescribeVoltageState();
    
    //! Toggle the total charge state from true -> false or false -> true
    void toggleTotalCharge();
    bool getTotalChargeState();
    
    void setVoltage(double value);
    double getVoltage();
    
    void setCharge(double value);
    double getCharge();
};





#endif