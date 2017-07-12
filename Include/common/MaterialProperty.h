#ifndef MATERIALPROPERTY_H_
#define MATERIALPROPERTY_H_

#include <string>

using namespace std;



//! Base class for all of the material property classes
/*!
    This class handles any properties that are common to the other classes
*/ 
class materialProperty
{
private:
    //! The name of the material
    string _propertyName;
    
public:
    //! Sets the name of the material
    /*!
        \param name The name of the material
    */ 
    void setName(std::string name)
    {
        _propertyName = name;
    }
    
    //! Retrieves the name of the material
    /*!
        \return Returns a name representing the name of the material
    */ 
    std::string getName()
    {
        return _propertyName;
    }
};

#endif