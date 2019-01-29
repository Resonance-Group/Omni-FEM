#ifndef CIRCUITPROPERTY_H_
#define CIRCUITPROPERTY_H_

#include <string>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

// Circuits on FEMM manual start at page 32
//! This class contains the properties of a circuit
/*!
    In a magnetics simulation, a block label can contain a circuit property.
    For example, when the user is simulating a DC motor, certain areas can be desigated 
    as windings for the wire. And those wires are connected in series/parallel 
    and contains a certain amount of current flowing through.
    This class is a property for that circuit.
    
    Circuits can be defined as either parallel or series circuits.
*/
class circuitProperty
{
private:

	friend class boost::serialization::access;
	
    //! The name of the circuit
    std::string p_circuitName = "None";
    
    //! Boolean that is used to determine if the circuit is series or parallel connected
    /*!
        If the circuit is connected parallel, then the current will be split
        between all of the regions that are marked with that particuler 
        circuit property. The program will ensure the the voltage drop is the 
        same across all of the areas marked when simulating. A parallel circuit
        would mean that this boolean is equal to false.
      
        For a series circuit, the current will be the same for all regions
        that have this circuit property. Series circuit will allow the user to apply 
        a number of turns to the region. This will cause the simulator to treat
        the region as a stranded conductor where the total current is the series circuit 
        current time the number of turns in the selected region. This means that to find
        the current in 1 turn where a coil has 50 turns and a total current of 10 A (the
        total current is specified by _current), the program will take 10 / 50 = 0.25 A 
        in one turn.
    */ 
    bool p_isSeries = false;
    
    //! Variable that stores how much current is flowing through the circuit
    double p_current = 0;
	
	//! The ID of the circuit property
	unsigned int p_circuitID = 0;
	
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & p_circuitName;
		ar & p_isSeries;
		ar & p_current;
		ar & p_circuitID; 
	}
public:

    //! Sets the name of the circuit
    /*!
        \param name The name of the circuit
    */ 
    void setName(std::string name)
    {
        p_circuitName = name;
    }
    
    //! Retrieves the circuit name
    /*!
        \return The name of circuit
    */ 
    std::string getName()
    {
        return p_circuitName;
    }
    
    //! Sets the state of the circuit
    /*!
        This function will set the state of the circuit
        if the circuit should be series or parallel.
        \param state The state of the circuit. If the circuit
                    should be a series circuit, set to true.
                    If a circuit should be parallel, set
                    to false.
    */ 
    void setCircuitSeriesState(bool state)
    {
        p_isSeries = state;
    }
    
    //! Retrieves whether a circuit is parallel or series
    /*!
        \return Returns true if the circuit is to be a series circuit.
                Returns false if the circuit is to be a parallel circuit.
    */ 
    bool getCircuitSeriesState()
    {
        return p_isSeries;
    }
    
    //! Sets the value of the current flowing through the circuit
    /*!
        \param currentValue The amount of current flowing through the circuit
                            in Amps
    */ 
    void setCurrent(double currentValue)
    {
        p_current = currentValue;
    }
    
    //! Retrieves the amount of current flowing through a circuit
    /*!
        \return Returns the amount of current flowing through the circuit
                in Amps.
    */ 
    double getCurrent()
    {
        return p_current;
    }
	
	/**
	 * @brief Sets the ID of the cirucit property
	 * @param ID The ID associated with the property
	 */
	void setCircuitID(unsigned int ID)
	{
		p_circuitID = ID;
	}
	
	/**
	 * @brief Retrieves the circuit ID of the property
	 * @return Returns the ID
	 */
	unsigned int getCircuitID()
	{
		return p_circuitID;
	}
};

#endif