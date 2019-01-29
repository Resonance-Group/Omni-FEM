#ifndef MAGNETICBOUNDARY_H_
#define MAGNETICBOUNDARY_H_

#include <common/BoundaryConditions.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

//! Class that is used to handle the specific values for the magnetic boundary conditions
/*!
    The first mangetic boundary condition is the prescribed A boundary. With this boundary,
    the vector potential, A, is fixed along a given boundary. This can be used to
    prescribe the flux passing normal to a boundary sicne the normal flux is equal to the 
    tangential derivative of A along the boundary. The form for A along the bonudary
    is specified by 3 different parameters: A0, A1, A2, and phi. If the problem is planar:
    then the forumal for A is as follows:

    \f[ A=(A_0+A_1x+A_2y)e^{j\phi} \f]
    
    or A = (A0 + A1 * x + A2 * y)^(j * phi).
    For axisymmetruc problems, A corresponds to the following equation:

    \f[ A=(A_0+A_1r+A_2z)e^{j\phi} \f]
    
    or A = (A0 + A1 * r + A2 * z)^(j * phi).
  
    For the small skin depth boundary condition, this boundary condition denotes an interface
    with a material subject to eddy currents at frequencies that are high enough such that the 
    skin depth in the material is very small. Teh boundary condition for the small skin depth
    is a Robin boundary condition:

    \f[ \frac{\partial A}{\partial n} + (\frac{1+j}{\delta })A=0 \f]
    
    or dA/dn + ((1 + j)/(delta)) * A = 0 where n is the direction
    of the outward normal to the bounday and \f[ \delta \f] denotes the skin deth
    of the material at the frequency of interest. The skin depth is defined as:

    \f[ \sqrt{\frac{2}{\omega \mu_{r} \mu_o \sigma}}=\delta \f]
    
    or sqrt(2 / (ω * μr * μo * σ)) = δ where ω = 2 * π * f.
    μr and σ are defined as the relative permeability and conductivity of the skin depth
    eddy current material. At 0 Hz, the boundary condition becomes \f[ \frac{\partial A}{\partial n} = 0 \f]
    or dA/dn = 0.

    The strategic dual image bonudary condition is experiemntal. This boundary condition mimics
    an open boundary condition by solving the problem twice, once with a homogeneous Dirichlet
    on the SDI boudnary and once with a Newmann on the SDI boundary. The results are then averaged to
    get the open boundary result. This boundary should be applied to the outer boudnary of a circular domain
    in 2D planar problems.
  
    For the periodic boundary condition, this type is applied to two different segments and causes
    the magnetic vector potential to be identical along each boundary. Useful for boundaries that are 
    contain some symmetry. This is alos useful for domains that are open bonudaries. 
    A different periodic condition must be defined for each section of the boundary since each periodic
    boundary condition can only be applied to a line or arc and another corresponding line or arc.

    For antiperiodic boundary condition,this is implemented in a similair manner
    as the periodic boundary condition. The only expection is that instead of the 
    two segments being identicial to each other, they are now the negative of another. 
*/ 
class magneticBoundary : public boundaryCondition
{
private:

    friend class boost::serialization::access;
	
    //! The A0 parameter in a Prescribed A boundary condition
    double _A0 = 0;
    
    //! The A1 parameter in a Prescribed A boundary condition
    double _A1 = 0;
    
    //! The A2 parameter in a Prescribed A boundary condition
    double _A2 = 0;
    
    //! The φ parameter in a Prescribed A boundary condition
    double _phi = 0;
    
    //! The relative conductivity used in the small skin depth boundary condition
    double _sigma = 0;
    
    //! The relative permeability used in the calculation of the small skin depth boundary condition
    double _mur = 0;
    
    //! This is the type of boundary condition that belongs to the class
    bcEnumMagnetic _type;
	
	//! The boundary ID associated with the boundary. This is used in the solver primarly
	unsigned int p_boundaryID = 0;
	
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<boundaryCondition>(*this);
		ar & _A0;
		ar & _A1;
		ar & _A2;
		ar & _phi;
		ar & _sigma;
		ar & _mur;
		ar & _type;
		ar & p_boundaryID;
	}
public:
    
    //! Sets the value for the A0 parameter
    /*!
        \param value The value for the A0 parameter
    */ 
    void setA0(double value)
    {
        _A0 = value;
    }
    
    //! Retrieves the A0 value
    /*!
        \return Returns a number representing the value for the
                A0 parameter
     */ 
    double getA0()
    {
        return _A0;
    }
    
    //! Sets the value for the A1 parameter
    /*!
        \param value The value for the A0 parameter
    */ 
    void setA1(double value)
    {
        _A1 = value;
    }
    
    //! Retrieves the A1 value
    /*!
        \return Returns a number representing the value for the
                A1 parameter
     */ 
    double getA1()
    {
        return _A1;
    }
    
    //! Sets the value for the A2 parameter
    /*!
        \param value The value for the A2 parameter
    */ 
    void setA2(double value)
    {
        _A2 = value;
    }
    
    //! Retrieves the A2 value
    /*!
        \return Returns a number representing the value for the
                A2 parameter
     */ 
    double getA2()
    {
        return _A2;
    }
    
    //! Sets the value for the φ parameter
    /*!
        \param value The value for the φ parameter
    */ 
    void setPhi(double value)
    {
        _phi = value;
    }
    
    //! Retrieves the φ value
    /*!
        \return Returns a number representing the value for the
                φ parameter
    */ 
    double getPhi()
    {
        return _phi;
    }
    
    //! Sets the sigma value for the small skin depth boundary condition
    /*!
        Sigma here is the conductivity of the material
        \param value The value for the conductivity of the eddy current
                     material
    */ 
    void setSigma(double value)
    {
        _sigma = value;
    }
    
    //! Retrieves the conductivity of the material
    /*!
        \return Returns a value representing the 
                conductivity of the material
    */ 
    double getSigma()
    {
        return _sigma;
    }
    
    //! Sets the μr value for the small skin depth boundary condition
    /*!
        μr here is the relative permeability of the material
        \param value The value for the relative permeability of the eddy current
                     material
    */
    void setMu(double value)
    {
        _mur = value;
    }
    
    //! Retrieves the relative permeability of the material
    /*!
        \return Returns a value representing the 
                relative permeability of the material
    */ 
    double getMu()
    {
        return _mur;
    }
    
    //! Sets the specific bonudary condition of the material
    /*!
        The boundary condition for the magnetostatic simulation can be:
        Prescribed A
        Small Skin Depth
        Mixed
        Strategic Dual Image
        Periodic
        Anti-periodic
        \param BC The boundary condition that belongs to the property
    */ 
    void setBC(bcEnumMagnetic BC)
    {
        _type = BC;
    }
    
    //! Retrieves the boundary condition of the property
    /*!
        \return Returns a value representing the specific boundary condition
    */ 
    bcEnumMagnetic getBC()
    {
        return _type;
    }
	
	/**
	 * @brief Function that is used in order to set the boudary ID of the boundary
	 * 			This is for internal purposes only and the user will not eb able to
	 * 			edit this property
	 * @param ID The ID of the boundary
	 */
	void setBoundaryID(unsigned int ID)
	{
		p_boundaryID = ID;
	}
	
	/**
	 * @brief Retrieves the boundary ID of the boundary
	 * @return Returns the boundary ID
	 */
	unsigned int getBoundaryID()
	{
		return p_boundaryID;
	}
};


#endif