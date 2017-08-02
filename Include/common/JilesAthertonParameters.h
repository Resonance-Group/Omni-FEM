#ifndef JILESARTHERTONPARAMETER_H_
#define JILESARTHERTONPARAMETER_H_

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


//! Class that handles the parameters for Jiles-Artherton
/*!
    This class was created in order to handle all of the parameters for the Jiles-Artherton model.
    Currently, this calss only deals with the parameters in one-plane. More research needs to be
    done in order to vectorize the parameters
*/ 
class jilesAthertonParameters
{
private:
	friend class boost::serialization::access;
    
    //! Boolean to state if the material is an anisotropy material
    bool _isAnisotropy = false;

    //! Boolean used to determine if Y parameters need to be used in the simulation
    bool _useYParameters = false;
    
    //! This is the interdomain coupling in the magnetic material in the X-direction
    double _alpha = 0;
    
    //! This is the domain wall density in the magnetic material in the X direction
    double _aParamX = 0;
    
    //! This is the Saturation magnetiztion of the material in the X-direction
    double _MsParamX = 0;
    
    //! This is the average energy required to break the pinning site in the magnetic material in the X-direction
    double _kParamX = 0;
    
    //! This is the magnetization reversibility in the X-direction
    double _cParamX = 0;
    
    //! For anisotropy materials, this is the average anisotropy evergy density in the X-direction
    double _KanParamX = 0;
    
    //! For anisotropy materials, this si teh angle between direction of magnetizing field H and the direction of anisotropy easy axis (The unit are in radians)
    double _psiParamX = 0;
    
    //! For anisotropy materials, this is the participation of anisotropic phase in the magnetic material
    double _tParamX = 0;
/* 
    Below are repeats of the above parameters in the Y direction
    These have the same meaning except in the y-plane. 
    For now, these will not be commented as I am still learning
    how to do the vectorizes Jiles-atherton model. It is unkonwn if 
    these parameters are needed 
 */
    double _aParamY = 0;
    
    double _MsParamY = 0;
    
    double _kParamY = 0;
    
    double _cParamY = 0;
    
    double _KanParamY = 0;
    
    double _psiParamY = 0;
    
    double _tParamY = 0;
	
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & _isAnisotropy;
		ar & _alpha;
		ar & _aParamX;
		ar & _MsParamX;
		ar & _MsParamX;
		ar & _kParamX;
		ar & _cParamX;
		ar & _KanParamX;
		ar & _psiParamX;
		ar & _tParamX;
	}
    
public:

    //! Sets that state of material
    /*!
        The material can either be anisotropy or not.
        This is the state of the material
        \param isAnisotropy Set to true if the material is anisotropy.
                            Otherwise, set to false.
    */ 
    void setIsAnisotropyMaterial(bool isAnisotropy)
    {
        _isAnisotropy = isAnisotropy;
    }
    
    //! Retrieves if the material is anisotropy or not
    /*!
        \return Returns true if the material is anisotropy.
                Otherwise, returns false.
    */ 
    bool getIsAnisotropyMaterial()
    {
        return _isAnisotropy;
    }
    
    //!This function will set whether or not to use the Y Parameters
    void setUseYParameter(bool state)
    {
       _useYParameters = state; 
    }
    
    //! This function will return true if we are to use the Y Parameters
    bool getUseYUseYParameter()
    {
        return _useYParameters;
    }
    
    //! Sets the interdomain coupling for the magnetic material
    /*!
        The interdomain coupling is the alpha parameter in the 
        Jiles-Atherton model.
        \param alpha The value of the interdomain coupling
    */ 
    void setAlpha(double alpha)
    {
        _alpha = alpha;
    }
    
    
    //! Retrieves the value of the interdomain coupling for the magnetic material
    /*!
        \return Returns a value representing the interdomain coupling (or alpha value)
                of the magnetic material
    */ 
    double getAlpha()
    {
        return _alpha;
    }
    
    //! Sets the value for the quantity of the domain wall density in the magnetic material.
    /*!
        This is the a parameter in the Jiles-atherton model. This parameter is represents
        the quantity of the domain wall density in the magnetic material.
        \param aParam The value for the quantity of the domain wall density in the magnetic material
    */ 
    void setAParam(double aParam)
    {
        _aParamX = aParam;
    }

    //! Retrieves the quantity of the domain wall density in the magnetic material
    /*!
        \return Returns a value representing the quantity of the domain wall density in the magnetic material or
                the a parameter.
    */ 
    double getAParam()
    {
        return _aParamX;
    }
    
    //! This function will set the 
    //! Sets the value for the saturation magnetization of the material
    /*!
        The saturation magnetization of the material is the Ms parameter of the Jiles-Atherton model
        \param value The value of the saturation magnetization of the material
    */ 
    void setSaturationMagnetization(double value)
    {
        _MsParamX = value;
    }
    
    //! Retrieves the saturation magnetization of the magnetic material
    /*!
        \return Returns the saturation magnetization of the magnetic material. 
                This is the Ms parameter
    */ 
    double getSaturationMagnetization()
    {
        return _MsParamX;
    }
    
    //! Sets the average energy required to break the pinning site in the magnetic material
    /*!
        This is also the k parameter
        \param value The average energy required to break the pinning site in the magnetic material
    */ 
    void setKParam(double value)
    {
        _kParamX = value;
    }
    
    //! Retrieves the k parameter of the magnetic material
    /*!
        \return Returns a value representing the average energy required to break the pinning site in the magnetic material.
		 		This is the k parameter.
    */ 
    double getKParam()
    {
        return _kParamX;
    }
    
    //! Sets the magnetization reversibility of the material
    /*!
        \param value The value for the magnetization reversibility of the material
                    or the c parameter
    */ 
    void setMagnetizationReversibility(double value)
    {
        _cParamX = value;
    }
    
    //! Retrieves the magnetization reversibility of the material
    /*!
        \return Returns a value representing the magnetization reversibility
                of the material. This is the c parameter.
    */ 
    double getMagnetizationReversibility()
    {
        return _cParamX;
    }
    
    //! Sets the average anisotropy energy density
    /*!
        This parameter only applies if the material
        is designated as anisotropy.
        \param value The average anisotropy energy density. This is also the 
                    k parameter.
    */ 
    void setEnergyDensity(double value)
    {
        _KanParamX = value;
    }
    
    //! Retrieves the average anisotropy energy density of the material.
    /*!
        This only applies to materials that are anisotropy.
        \return Returns a value representing the average anisotropy energy density of the material.
                If the material is not designated as anisotropy, this function will return 0.
    */ 
    double getEnergyDensity()
    {
        if(!_isAnisotropy)
            return 0;
        else
            return _KanParamX;
    }
    
    //TODO: Determine what the Psi parameter actually is
    //! Sets the Psi parameter of the material
    /*!
        This only applies to materials that are designated as anisotropy.
        \param value The value for the psi parameter
    */ 
    void setPsi(double value)
    {
        _psiParamX = value;
    }
    
    //! Retrieves the Psi parameter of the magnetic material.
    /*!
        \return Returns a value representing the Psi parameter. 
                If the material is not anisotropy, then this function will return 0.
    */ 
    double getPsi()
    {
        if(!_isAnisotropy)
            return 0;
        else
            return _psiParamX;
    }
    
    //! Sets the participation of anistropic phase in the magnetic material.
    /*!
        This function only pertains to materials that are desginated as anisotropy.
        The participation of anistropic phase is known as the T parameter.
        \param value The value for the participation of anistropic phase in the magnetic material.
    */ 
    void setTParameter(double value)
    {
        _tParamX = value;
    }
    
    //! Retrieves the T parameter of the magnetic material.
    /*!
        \return Returns a value representing the participation of anistropic phase in the magnetic material.
                If the material is not designated as anisotropy, this function will return 0.
    */ 
    double getTParameter()
    {
        if(!_isAnisotropy)
            return 0;
        else
            return _tParamX;
    }
    
    //! Resets all of the parameters back to 0
    /*!
        This function will also set the material to not anisotropy
    */ 
    void clear()
    {
        _isAnisotropy = false;
        _useYParameters = false;
        _alpha = 0;
        _aParamX = 0;
        _MsParamX = 0;
        _kParamX = 0;
        _cParamX = 0;
        _KanParamX = 0;
        _psiParamX = 0;
        _tParamX = 0;
    }
};

#endif
    