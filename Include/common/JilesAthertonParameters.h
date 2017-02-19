#ifndef JILESARTHERTONPARAMETER_H_
#define JILESARTHERTONPARAMETER_H_

class jilesAthertonParameters
{
private:
    
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
/* Below are repeats of the above parameters in the Y direction */
    double _aParamY = 0;
    
    double _MsParamY = 0;
    
    double _kParamY = 0;
    
    double _cParamY = 0;
    
    double _KanParamY = 0;
    
    double _psiParamY = 0;
    
    double _tParamY = 0;
    
public:

    //! This function will set whether or not the material is anisotropy
    void setIsAnisotropyMaterial(bool isAnisotropy)
    {
        _isAnisotropy = isAnisotropy;
    }
    
    //! This function will return true if the material is anisotropy
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
    
    //! This function will set the alpha parameter or the interdomain coupoling in the magnetic material
    void setAlpha(double alpha)
    {
        _alpha = alpha;
    }
    
    
    //! This function will return the alpha parameter.
    double getAlpha()
    {
        return _alpha;
    }
    
    //! This function will set the a parameter or the quantity of the domain wall density in the magnetic material
    void setAParam(double aParam)
    {
        _aParamX = aParam;
    }

    //! This function will return the a parameter
    double getAParam()
    {
        return _aParamX;
    }
    
    //! This function will set the saturation magnetization of the material
    void setSaturationMagnetization(double value)
    {
        _MsParamX = value;
    }
    
    //! This function will return the saturation magnetization of the material
    double getSaturationMagnetization()
    {
        return _MsParamX;
    }
    
    //! This function will set the k parameter which is teh average energy required to break the pinning site in the magnetic material
    void setKParam(double value)
    {
        _kParamX = value;
    }
    
    //! This function will return the value of the k parameter
    double getKParam()
    {
        return _kParamX;
    }
    
    //! This function will set the magnetization reversibility of the material
    void setMagnetizationReversibility(double value)
    {
        _cParamX = value;
    }
    
    //! This function will return the magnetization reversibility of the material
    double getMagnetizationReversibility()
    {
        return _cParamX;
    }
    
    //! For anisotropy materials, this function will set the Average ansotropy energy density
    void setEnergyDensity(double value)
    {
        _KanParamX = value;
    }
    
    //! This function will return the average anisotropy energy density if enables for the material. IF the function returns 0, then the material is not anisotropy.
    double getEnergyDensity()
    {

        return _KanParamX;
    }
    
    //!  For anisotropy materials, this function will set the Psi Parameter
    void setPsi(double value)
    {
        _psiParamX = value;
    }
    
    //! For anisotropy materials, this function will return the psi Parameter. IF the function returns a 0, then it could mean that the material is not anisotropy
    double getPsi()
    {
        return _psiParamX;
    }
    
    //! For anisotropy materials, this function will set the participation of anistropic phase in the magnetic material
    void setTParameter(double value)
    {
        _tParamX = value;
    }
    
    //! For anisotropy materials, this function will return the t parameter. If the function returns 0, it could mean that the material is not anisotropy
    double getTParameter()
    {
        return _tParamX;
    }
    
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
    