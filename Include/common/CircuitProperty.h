#ifndef CIRCUITPROPERTY_H_
#define CIRCUITPROPERTY_H_

#include <string>

using namespace std;

/*! /brief  In a magnetics simulation, ablock label can contain a circuit property.
 *          For example, the user is simulating a DC motor. Certain areas can be desigated 
 *          as windings for the wire. And those wires are connected in series/parallel 
 *          and contains a certain amount of current flowing through.
 *          This class is a property for that circuit
 */
class circuitProperty
{
private:
    //! The name of the circuit
    string _circuitName;
    
    //! The wire is in series or parallel with each other.
    bool _isSeries = false;
    
    //! How much current is flowing through the circuit
    double _current = 0;
public:
    //! The next section are the getters/setters for the above private variables
    void setName(string name);
    string getName();
    
    void toggleSeriesCircuit();
    bool getCircuitState();
    
    void setCurrent(double currentValue);
    double getCurrent();
};

#endif