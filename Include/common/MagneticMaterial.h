#ifndef MAGNETICMATERIAL_H_
#define MAGNETICMATERIAL_H_

#include <common/MaterialProperty.h>
#include <common/enums.h>

/*! /class magneticMaterial 
 *  /brief
 *  This is the class that is specific to the properties for the magnetic materials
 */ 
class magneticMaterial : public materialProperty
{
private:
    //! This data type will indicate if a Linear or non-linear BH curve should be used for the material
    bool _isLinear = true;
    
    //! For the linear BH curve, this variable holds the relative permeability of the material in the X-plane
    double _relativePermeabilityX = 0;
    
    //! For the linear BH curve, this variable holds the relative permeability of the material in the Y-Plane
    double _relativePermeabilityY = 0;
    
    //! The hystersis lag angle in the X-direction
    double _phiHX = 0;
    
    //! The hysteresis lag angle in the Y-direction
    double _phiHY = 0;
    
    //! The max hystersis lag angle. Used in calculations for the non-linear B-H curve
    double _phiMax = 0;
    
    //! The coercivity of the material. Units are in A/m.
    double _coercivity = 0;
    
    //! The electrical conductivity of the material (units are in MS/m)
    double _electricalConductivity = 0;
    
    //! The current density of the material (units are in MA/m2).
    double _currentDensity = 0;
    
    //! This is the lamination and wire type for the material
    lamWireEnum _attribute = NOT_LAMINATED_OR_STRANDED;
    
    //! The lamination thickness of the material
    double _lamThickness = 0;
    
    //! The number of strands for the wire
    double _numStrands = 0;
    
    //! The lamination fill factor for the material
    double _lamFF = 0;
    
    //! The strand Diameter
    double _strandDia = 0;
public:
    //! This will toggle the status of the isLinear boolean to indicate if the material is linear/nonlinear. The default value is that the material is linear
    void setBHCurveLinearity(bool isLinear);
    
    //! This will get the state of the isLinear boolean
    bool getBHState();
    
    //! This will set the relative permeability of the material in the x-direction.
    void setMUrX(double value);
    
    //! This will get the relative permeability of the material in the x-direction.
    double getMUrX();
    
    //! This will set the relative permeability of the material in the y-direction.
    void setMUrY(double value);
    
    //! This will get the relative permeability of the material in the y-direction.
    double getMUrY();
    
    //! This will set the hystersis lag angle in the x-direction. Note that this parameter is only used for the linear approximation
    void setPhiX(double value);
    
    //! This will get the hystersis lag angle in the x-direction. Note that this parameter is only used for the linear approximation
    double getPhiX();
    
    //! This will set the hystersis lag angle in the y-direction. Note that this parameter is only used for the linear approximation
    void setPhiY(double value);
    
    //! This will get the hystersis lag angle in the y-direction. Note that this parameter is only used for the linear approximation
    double getPhiY();
    
    //! This will set the max hystersis lag angle. Note: This is only used during a nonlinear B-H curve
    void setPhiMax(double value);
    
    //! This will get the max hystersis lag angle. Note: This is only used during a nonlinear B-H curve
    double getPhiMax();
    
    //! This will set the coercivity for the material. Units are in A/m.
    void setCoercivity(double value);
    
    //! This will get the coercivity for the material. Units are in A/m.
    double getCoercivity();
    
    //! This will set the electrical conductivity of the material. Units are in MS/m.
    void setSigma(double value);
    
    //! This will get the electrical conductivity of the material. Units are in MS/m.
    double getSigma();
    
    //! This will set the current density of the material. Units are in MA/m2.
    void setCurrentDensity(double value);
    
    //! This will get the current density of the material. Units are in MA/m2.
    double getCurrentDensity();
    
    //! This will set the lamination and wire type of the material.
    void setSpecialAttribute(lamWireEnum value);
    
    //! This will get the lamination and wire type of the material.
    lamWireEnum getSpecialAttribute();
    
    //! This will set the lamination thickness (if any) of the material. Units are in mm
    void setLaminationThickness(double value);
    
    //! This will get the lamination thickness (if any) of the material.Units are in mm.
    double getLaminationThickness();
    
    //! This will set the number of strands in the wire.
    void setNumberStrands(double value);
    
    //! This will get the number of strands in the wire.
    double getNumberStrands();
    
    //! This will set the lamination fill factor (if any) of the material.
    void setLaminationFillFactor(double value);
    
    //! This will get the lamination fill factor (if any) of the material.
    double getLaminationFillFactor();
    
    //! This will set the strand diameter of the material (if any). Units are in mm.
    void setStrandDiameter(double value);
    
    //! This will get hte strand diameter of the material (if any). Units are in mm.
    double getStrandDiameter();
};


#endif