#ifndef BOUNDARYCONDITIONS_H_
#define BOUNDARYCONDITIONS_H_

#include <string>

#include <common/enums.h>


// As a side note, FEMM documentation for the magnetic boundary begins on PDF page 25
// page 50 for electrostatic

//! Base class for boundary conditions
/*!
    This class is the base class for the boundary conditions.
    This contains any properties that are similiar to the different
    bonudary conditions. Since we are dealing with electrostatic and magnetostatic
    simulations, the properties for boundary conditions
    that are similiar between the two are the name of the boundary condition
    and the mixed parameter boundary conditions.
  
    The mixed boundary condition has different meanings depending on the physics simulation.
    For electrostatics, the mixed boundary condition is of the form:
    \f[\varepsilon _{r}\varepsilon _{o}\frac{\partial V}{\partial n}+c_{o}V+c_{1}=0 \f]
    Depending on the vvalues of c1 and c0, the boundary can either be a Robin or Neumann
    boundary condition. If c1 = 0, then careful selection of the c0 coefficient
    will allow the boundary condition to be applied to the outer boundary
    which would approximate an unbounded solution region.
  
    For magnetiostatics, the mixed boundary condition is in the form of:
    \f[ (\frac{1}{\mu_{r}*\mu_{0}})*\frac{\delta A}{\delta n}+c_{o}*A+c_{1}=0 \f].
    Depending on the values of c1 and c0, the boundary condition can be either 
    a Neumann boundary condition or a Robin bonudary condition. For this, there are 
    2 cases for a mixed boundary condition:
    
    1) Much like the electrostatic, the mixed boundary can be used to approximate
    an unboundaed solution region.
  
    2) The mixed boundary conditoin can be used to set the field intensity H that flows
    parallel to a boundary. c0 would need to be set to 0 and c1 set to the desired
    H value in A/M. This boundary condition can also be used to prescribe 
    dA/dn=0 at the boundary. 
*/ 
class boundaryCondition
{
private:
    //! The name of the boundary condition
    std::string _boundaryName;
    
    //! This is the c0 coefficient in both BC for electrostatic and magnetics
    double _c0 = 0;
    
    //! This is the c1 coefficient in both BC for electrostatic and magnetics
    double _c1 = 0;
public:

    //! This function will set the name of the boundary
    /*!
        This parameter is for all types of boundary conditions. This will
        set the name of the boundary condition to the name parameter
        \sa _boundaryName
        \param name The name of the boundary condition
    */ 
    void setBoundaryName(std::string name)
    {
        _boundaryName = name;
    }
    
    //! Retrieves the name of the boundary condition
    /*!
        This function will return the name of the boundary condition
        \sa _boundaryName
        \return The name of the boundary condition
    */ 
    std::string getBoundaryName()
    {
        return _boundaryName;
    }
    
    //! Set the value of the c0 coefficient
    /*!
        This function will set the value of the c0 
        coefficient in both equations for the boundary condition
        \sa _c0
        \param value The value that c0 should be set to
    */ 
    void setC0(double value)
    {
        _c0 = value;
    }
    
    //! Get the value of the c0 coefficient
    /*!
        This function will get the value of the c0
        coefficient.
        \sa _c0
        \return Returns that value of the c0 coefficient
    */ 
    double getC0Value()
    {
        return _c0;
    }
    
    //! Set the value of the c1 coefficient
    /*!
        This function will set the value of the c1 coefficient
        in both equations for the boundary conditions
        \sa _c1
        \param value The value that c1 should be set to
    */ 
    void setC1(double value)
    {
        _c1 = value;
    }
    
    //! Retrieves the value of the c1 coefficient
    /*!
        This function will get the value of the c1 coefficient
        \sa _c1
        \return Returns the value of the c1 coefficient
    */
    double getC1Value()
    {
        return _c1;
    }
};


#endif