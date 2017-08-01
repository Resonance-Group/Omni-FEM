#ifndef MATERIALPROPERTY_H_
#define MATERIALPROPERTY_H_

#include <string>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

//! Base class for all of the material property classes
/*!
    This class handles any properties that are common to the other classes
*/ 
class materialProperty
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & _propertyName;
	}
private:
    //! The name of the material
    std::string _propertyName;
    
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