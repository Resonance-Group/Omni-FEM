#ifndef MAGNETICMATERIAL_H_
#define MAGNETICMATERIAL_H_

#include <common/MaterialProperty.h>
#include <common/enums.h>

/*! /brief
 *  This is the class that is specific to the properties for the magnetic materials
 */ 
class magneticMaterial : materialProperty
{
private:
    //! This data type will indicate if a Linear or non-linear BH curve should be used for the material
    bool _isLinear = true;
    
    //! For the linear BH curve, this variable holds the relative permeability of the material in the X-plane
    double _relativePermeabilityX = 0;
    
    //! For the linear BH curve, this variable holds the relative permeability of the material in the Y-Plane
    double _relativePermeabilityY = 0;
    
    //! 
    double _phiHX = 0;
    
    //!
    double _phiHY = 0;
    
    //!
    double _coercivity = 0;
    double _electricalConductivity = 0;
    double _currentDensity = 0;
    lamWireEnum _attribute = NOT_LAMINATED_OR_STRANDED;
    double _lamThickness = 0;
    double _numStrands = 0;
    double _lamFF = 0;
    double _strandDia = 0;
public:
    void toggleLienarBH();
    bool getBHState();
    
    void setMUrX(double value);
    double getMUrX();
    
    void setMUrY(double value);
    double getMUrY();
    
    void setPhiX(double value);
    double getPhiX();
    
    void setPhiY(double value);
    double getPhiY();
    
    void setCoercivity(double value);
    double getCoercivity();
    
    void setRho(double value);
    double getRho();
    
    void setCurrentDensity(double value);
    double getCurrentDensity();
    
    void setSpecialAttribute(lamWireEnum value);
    lamWireEnum getSpecialAttribute();
    
    void setLaminationThickness(double value);
    double getLaminationThickness();
    
    void setNumberStrands(double value);
    double getNumberStrands();
    
    void setLaminationFillFactor(double value);
    double getLaminationFillFactor();
    
    void setStrandDiameter(double value);
    double getStrandDiameter();
};


#endif