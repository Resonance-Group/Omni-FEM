#ifndef CONDUCTORPROPERTY_H_
#define CONDUCTORPROPERTY_H_

#include <string>

using namespace std;

//! Class the defines the conductor that is used in an electrostatic simulation
/*!
    The main prupose of this calss is to allow the user
    to apply constraints on the total amount of charge carries
    on a conductor. Conductors can be defind as a fixed voltage.
    The program will then compute the total charge carries on the
    conductor during solving.
*/ 
class conductorProperty
{
private:
    //! This is the name of the property
    string _conductorName = "None";
    
    //! Boolean that is used to determine if the propert is a fixed voltage or total charge
    /*!
        If this bolean is true, then the value in _value is a total charge value.
        If this boolean is false, then the value in _value is a fixed voltage
    */ 
    bool _isTotalCharge = true;
    
    //! This is the value for the class.
    /*!
        Depending on the state of _isTotalCharge, this number
        has different meanings
        \sa _isTotalCharge
    */ 
    double _value = 0;
public:

    //! Sets the name of the property
    /*!
        This function will set the name of the property
        \param name The name of the property
    */ 
    void setName(string name)
    {
        _conductorName = name;
    }
    
    //! Retrieves the name of the property
    /*!
        \return Returns the name of the property
    */ 
    string getName()
    {
        return _conductorName;
    }
    
    //! Sets the state of the property
    /*!
        The state of the property can be either a fixed voltage 
        or a total charge.
        \param state Set to true if the property is a total charge.
                    If the property need to be a fixed voltage,
                    set state to false
    */ 
    void setIsTotalChargeState(bool state)
    {
        _isTotalCharge = state;
    }
    
    //! Retrieves the state of the property
    /*!
        The state of the property can be either a fixed voltage 
        or a total charge.
        \return Returns true if the property is a total charge.
                Returns false if the propert is a fixed voltage.
    */ 
    bool getIsTotalChargeState()
    {
        return _isTotalCharge;
    }
    
    //! Set the value of the property
    /*!
        The value here will have different meaning based on the 
        state of the property. If the property is a total charge,
        then the value will be charge with the units of Columb (C).
        If the state is a fixed voltage, then the value here is a 
        voltage with units of V
        \sa _isTotalCharge
        \param value The value of the property
    */ 
    void setValue(double value)
    {
        _value = value;
    }
    
    //! Retrieves the value of the property
    /*!
        The value here will have different meaning based on the 
        state of the property. If the property is a total charge,
        then the value will be charge with the units of Columb (C).
        If the state is a fixed voltage, then the value here is a 
        voltage with units of V
        \sa _isTotalCharge
        \return Returns the value of the property
    */ 
    double getValue()
    {
        return _value;
    }
};

#endif