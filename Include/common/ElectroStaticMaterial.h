#ifndef ELECTROSTATICMATERIAL_H_
#define ELECTROSTATICMATERIAL_H_

#include <common/MaterialProperty.h>

/*! This class is used to create materials needed for the electrostatic simulation
 *  It inherits from the materialProperty class.
 */ 
class electrostaticMaterial : public materialProperty
{
private:
    //! This value contains the relative permittivity in the X plane 
    double _relativePermittivityX = 1;
    
    //! This value contains the relative permittivity in the Y plane
    double _relativePermittivityY = 1;
    
    
    double _chargeDensity = 0;
    
public:
    //! This section is for the getters/setters of the above private variables
    void setEpsilonX(double value);
    double getEpsilonX();
    
    void setEpsilonY(double value);
    double getEpsilonY();
    
    void setChargeDensity(double value)
    {
        _chargeDensity = value;
    }
    
    double getChargeDensity()
    {
        return _chargeDensity;
    }
};

#endif