#ifndef MAGNETICBOUNDARY_H_
#define MAGNETICBOUNDARY_H_

#include <common/BoundaryConditions.h>

/*! /brief  This class is specifically set for the boundary
 *          conditions of the magnetic solver
 */ 
class magneticBoundary : boundaryCondition
{
private:
    /*!
     *  Prescribe A is the vector potential A that is presribed along a given boundary.
     *  The form for A along the boundary is specified by the parameters of
     *  A0, A1, and A2. These are coefficients which if the problem is planar, the 
     *  formula takes the form of:
     *  A = (A0 + A1 * x + A2 * y) * e ^ (j * phi)
     *  For axisymmetric, the forumla is:
     *  A = (A0 + A1 * r + A2 * z) * e ^ (j * phi)
     *  For the mathmaticians (or other folks), j = i
     * 
     *  A0 is the constant coefficient.
     */ 
    double _A0 = 0;
    
    //! A1 is the coefficient related to the x term (or r term)
    double _A1 = 0;
    
    //! A2 is the coefficient related to the y term (or the z term)
    double _A2 = 0;
    
    //! This is the coefficient that is related to the imaginary number 
    double _phi = 0;
    
    //! The relative conductivity used in the small skin depth boundary condition
    double _sigma = 0;
    
    //! The relative permeability used in the calculation of the small skin depth boundary condition
    double _mur = 0;
public:
    //! This section is for the getters/setters of the private variables
    void setA0(double value);
    double getA0();
    
    void setA1(double value);
    double getA1();
    
    void setA2(double value);
    double getA2();
    
    void setPhi(double value);
    double getPhi();
    
    void setSigma(double value)
    double getSigma();
    
    void setMu(double value);
    double getMu();
};


#endif