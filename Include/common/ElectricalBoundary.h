#ifndef ELECTRICALBOUNDARY_H_
#define ELECTRICALBOUNDARY_H_

#include <common/BoundaryConditions.h>


/*! /brief  This class is specific for the boundary conditions of the electrostatic 
 *          solver.
 */ 
class electricalBoundary : boundaryCondition
{
private:
    //! This is the data type for the fixed votlage boundary condition
    double _fixedVoltageValue = 0;
    
    //! This is the data type for the surface charge density boundary condition
    double _surfaceChargeDensity = 0;
    
    //! This is the boundary condition for the class
    bcEnumElectroStatic _type;
public:
    void setVoltage(double value);
    double getVoltage();
    
    void setSigma(double value);
    double getSigma();
    
    void setBC(bcEnumElectroStatic BC);
    bcEnumElectroStatic getBC();
};

#endif