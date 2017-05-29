#ifndef MATERIALPROPERTY_H_
#define MATERIALPROPERTY_H_

#include <string>

using namespace std;


/*! This is the general class for the material properties. 
 *  Instead of having two different classes and two different data structures in each
 *  block label for the materials, a general one was created.
 */
class materialProperty
{
private:
    //! The name of the material
    string _propertyName;
    
public:
    //! The getter/setter for the name
    void setName(std::string name)
    {
        _propertyName = name;
    }
    
    std::string getName()
    {
        return _propertyName;
    }
};

#endif