#ifndef MAGNETICMATERIAL_H_
#define MAGNETICMATERIAL_H_

#include <common/MaterialProperty.h>
#include <common/enums.h>
#include <common/JilesAthertonParameters.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


//! Class that is used to handle all of the material properties for a magnetic simulation
/*!
    This class is used to define the properties associated with teh block
    label. The class contains all of the properties that are used for
    the material of a block label
*/ 
class magneticMaterial : public materialProperty
{
private:
	friend class boost::serialization::access;
	
    //! Boolean used to indicate if a Linear or non-linear BH curve should be used for the material
    bool _isLinear = true;
    
    //! For the linear BH curve, this variable holds the relative permeability of the material in the X-plane.
    double _relativePermeabilityX = 0;
    
    //! For the linear BH curve, this variable holds the relative permeability of the material in the Y-Plane
    double _relativePermeabilityY = 0;
    
    //! The hystersis lag angle in the X-direction
    /*!
        A simple model for the hysteresis in harmonic problems is to assume that 
        hysteresis creates a constant phase lag between B an H that is
        independent of frequency. Since the loop is not exactly elliptical,
        the perceived hystersis angle will vary for different amplitudes of excitiation.
        Note that the angle is not parameter that is defined on many materials. To find the angle for a material,
        the user needs to perform a frequency sweep on a coil with a core composed of the material of interest.
    */ 
    double _phiHX = 0;
    
    //! The hysteresis lag angle in the Y-direction
    /*!
        A simple model for the hysteresis in harmonic problems is to assume that 
        hysteresis creates a constant phase lag between B an H that is
        independent of frequency. Since the loop is not exactly elliptical,
        the perceived hystersis angle will vary for different amplitudes of excitiation.
        Note that the angle is not parameter that is defined on many materials. To find the angle for a material,
        the user needs to perform a frequency sweep on a coil with a core composed of the material of interest.
    */ 
    double _phiHY = 0;
    
    //! This is the properties for the Jiles-Atherton Model
    jilesAthertonParameters _nonLinearParameters;
    
    //! The coercivity of the material. Units are in A/m.
    double _coercivity = 0;
    
    //! The electrical conductivity of the material (units are in MS/m)
    /*!
        This value is typically used in simulations that deal with eddy currents.
        There is a strong dependence of temperature on the conductivity of a material
    */ 
    double _electricalConductivity = 0;
    
    //! The current density of the material (units are in MA/m2).
    /*!
        This denotes the source current density at DC. At frequencies other
        then DC, eddy currents will be induced and this will prevent the total
        current in the region from being eaul to this value.
        In the case of eddy current, the circuit property must be imposed in order to limit
        the total current
    */ 
    double _currentDensity = 0;
    
    //! This is the lamination and wire type for the material
    /*!
        For the laminations, there are are different configurations 
        that can be taken. If a lamination configuration is selected,
        then the user will need to select a lamination
        thickness and fill factor.
      
        If the object represents a coil, then the user will
        need to enter parameters related to strands. For 
        magnet wire or square type wire, there is only 1 strand.
        For stranded and Litz wire, the user will need to enter the 
        number of strands and the diameter.
      
        The simulator simulates the wire in bulk. This means that the 
        program does not simulate each strand but rather the whole coil
    */
    lamWireEnum _attribute = NOT_LAMINATED_OR_STRANDED;
    
    //! The lamination thickness of the material
    double _lamThickness = 0;
    
    //! The number of strands for the wire
    unsigned int _numStrands = 0;
    
    //! The lamination fill factor for the material
    double _lamFF = 0;
    
    //! The strand Diameter
    double _strandDia = 0;
	
	//! The Identification Number for the material
	unsigned int p_materialID = 0;
	
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<materialProperty>(*this);
		ar & _isLinear;
		ar & _attribute;
		ar & _coercivity;
		ar & _currentDensity;
		ar & _electricalConductivity;
		ar & _lamFF;
		ar & _lamThickness;
		ar & _nonLinearParameters;
		ar & _numStrands;
		ar & _phiHX;
		ar & _phiHY;
		ar & _relativePermeabilityX;
		ar & _relativePermeabilityY;
		ar & _strandDia;
		ar & p_materialID;
	}
public:

    //! Sets if the material is linear or non-linear
    /*!
        \param isLinear Set to true if the material is linear
                        Set to false if hte material is non-linear
    */ 
    void setBHCurveLinearity(bool isLinear)
    {
        _isLinear = isLinear;
    }
    
    //! Retrieves if the material is linear or not
    /*!
        \return Returns true if hte material is linear. Otherwise, returns false
    */ 
    bool getBHState()
    {
        return _isLinear;
    }
    
    //! Sets the relative permeability of the material in the x-direction.
    /*!
        \param value The value of the relative permeability in the x-plane
    */ 
    void setMUrX(double value)
    {
        _relativePermeabilityX = value;
    }
    
    //! Retrieves the relative permeability of the material in the x-direction.
    /*!
        \return Returns a value representing the relative permeability in the x-plane
    */ 
    double getMUrX()
    {
        return _relativePermeabilityX;
    }
    
    //! Sets the relative permeability of the material in the y-direction.
    /*!
        \param value The value of the relative permeability in the y-plane
    */
    void setMUrY(double value)
    {
        _relativePermeabilityY = value;
    }
    
    //! Retrieves the relative permeability of the material in the y-direction.
    /*!
        \return Returns a value representing the relative permeability in the y-plane
    */
    double getMUrY()
    {
        return _relativePermeabilityY;
    }
    
    //! Sets the hystersis lag angle in the x-direction.
    /*! 
        Note that this parameter is only used for the linear approximation
        \param value A value that represents the hystersis lag angle in the x-plane in degs.
    */ 
    void setPhiX(double value)
    {
        _phiHX = value;
    }
    
    //! Retrieves the hystersis lag angle in the x-direction. 
    /*!
        Note that this parameter is only used for the linear approximation
        \return Returns a value representing the hystersis lag angle in the x-plane in degs
    */ 
    double getPhiX()
    {
        return _phiHX;
    }
    
    /**
     * @brief   Sets the hystersis lag angle in the y-direction.
     *          Note that this parameter is only used for the linear approximation
     * @param value A value that represents the hystersis lag angle in the y-plane in degs.
     */
    void setPhiY(double value)
    {
        _phiHY = value;
    }

    /**
     * @brief   Retrieves the hystersis lag angle in the y-direction. 
     *          Note that this parameter is only used for the linear approximation
     * @return Returns a value representing the hystersis lag angle in the y-plane in degs
     */
    double getPhiY()
    {
        return _phiHY;
    }
    
    //! Sets the Jiles Atherton model parameters.
    /*!
        The Jiles Atherton model is for nonlinear magnetic materials
        \param parameter The Jile Atherton parameters that the material needs to have
    */ 
    void setJilesAtherton(jilesAthertonParameters parameter)
    {
        _nonLinearParameters = parameter;
    }
    
    //! Retrieves the Jiles-Artherton model parameters
    /*!
        \return Returns an object that contains the Jiles Atherton parameters for the material
    */ 
    jilesAthertonParameters getJilesAtherton()
    {
        return _nonLinearParameters;
    }
    
    //! Sets the coercivity for the material. 
    /*!
        The unit for the coercivity are in A/m.
        This is usually applied to if the material is a permanent magnet
        \param value The value representing the coercivity of the material
    */ 
    void setCoercivity(double value)
    {
        _coercivity = value;
    }
    
    //! Retrieves the coercivity for the material. 
    /*!
        The unit for the coercivity are in A/m.
        \return Returns a value representing the coercivity of the material
    */ 
    double getCoercivity()
    {
        return _coercivity;
    }
    
    //! This will set the electrical conductivity of the material. 
    /*! 
        The units are in MS/m. This is usually used in time-harmonic (eddy-current)
        problems. Commodity-grade transformer laminations have a conductivity of 9 MS/m
        \param value the value of the electrical conductivity of the material.
    */ 
    void setSigma(double value)
    {
        _electricalConductivity = value;
    }
    
    //! Retrieves the electrical conductivity of the material. 
    /*!
        The units are in MS/m.
        \return Returns a value representing the electrical conductivity of the material.
    */ 
    double getSigma()
    {
        return _electricalConductivity;
    }
    
    //! This will set the current density of the material. 
    /*!
        Units are in MA/m2.
        \sa _currentDensity
        \param value The value for the current density in the block
    */ 
    void setCurrentDensity(double value)
    {
        _currentDensity = value;
    }
    
    //! Retrieves the current density of the material. 
    /*!
        Units are in MA/m2.
        \return Returns a value representing the current density in the block
    */ 
    double getCurrentDensity()
    {
        return _currentDensity;
    }
    
    //! This will set the lamination and wire type of the material
    /*!
        Depending on the value set here, the user will need to input different
        parameters such as lamination thickness or strand diameter
        \param value The lamination or wire type that the block belongs to
    */ 
    void setSpecialAttribute(lamWireEnum value)
    {
        _attribute = value;
    }
    
    //! Retrieves the lamination and wire type of the material.
    /*!
        \return Returns a value representing what the wire type or lamination
                type is of the material.
    */ 
    lamWireEnum getSpecialAttribute()
    {
        return _attribute;
    }
    
    //! Set the lamination thickness (if any) of the material. 
    /*!
        Units are in mm
        \param value The lamination thickness of the material
    */ 
    void setLaminationThickness(double value)
    {
        _lamThickness = value;
    }
    
    //! Retrieves the lamination thickness (if any) of the material.
    /*!
        \return Returns a value representing the lamination thickness of the material in mm.
    */ 
    double getLaminationThickness()
    {
        return _lamThickness;
    }
    
    //! Sets the number of strands in the wire.
    /*!
        For Magnet or Square wire, this value should be 1
        \param value The number of strands bundled in the wire
    */
    void setNumberStrands(unsigned int value)
    {
        _numStrands = value;
    }
    
    //! Retrieves the number of strands bundled in the wire.
    /*!
        \return Returns a number representing the number of strands
                bundled in the wire
    */ 
    unsigned int getNumberStrands()
    {
        return _numStrands;
    }
    
    //! Sets the lamination fill factor (if any) of the material.
    /*!
        The fraction of the core that is filled with the material.
        For exmaple, if the lamination is 12.8 mil thick and the insulation between
        each is 1.2 mil thick, then the fill factor is:
        12.8 / (1.2 + 12.8) = 0.914
        \param value The fill factor for the material
    */ 
    void setLaminationFillFactor(double value)
    {
        _lamFF = value;
    }
    
    //! Retrieves the lamination fill factor (if any) of the material.
    /*!
        \returns Returns a value representing the fill factor of the material
    */ 
    double getLaminationFillFactor()
    {
        return _lamFF;
    }
    
    //! Sets the strand diameter of the material (if any). 
    /*!
        Units are in mm.
        \param value The diameter of the wire that is used.
                    This does nto include the insulation (maybe)
    */ 
    void setStrandDiameter(double value)
    {
        _strandDia = value;
    }
    
    //! Retrieves the strand diameter of the material (if any).
    /*!
        Units are in mm.
        \return Returns a value representing the diameter of the wire. This does
                not include the insulation
    */ 
    double getStrandDiameter()
    {
        return _strandDia;
    }
    
    //! Clears out the Jiles Atherton parameters
    void clearJilesAtherton()
    {
        _nonLinearParameters.clear();
    }
	
	/**
	 * @brief Function that is used to set the material ID. This is not something that the user
	 * 			is allowed to edit. This is for internal purposes only.
	 * @param ID The ID of the material
	 */
	void setMaterialID(unsigned int ID)
	{
		p_materialID = ID;
	}
	
	unsigned int getMaterialID()
	{
		return p_materialID;
	}
};


#endif