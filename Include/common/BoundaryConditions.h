#ifndef BOUNDARYCONDITIONS_H_
#define BOUNDARYCONDITIONS_H_

#include <common/enums.h>
#include <string>

using namespace std;

/*! /brief This class is the general BC class that is used to */
class boundaryCondition
{
private:
    //! The name of the boundary
    string _boundaryName;
    double _c0 = 0;
    double _c1 = 0;
public:
    //! This function will set the name of the boundary
    void setBoundaryName(string name);
    
    //! This function will return the name of boundary
    string getBoundaryName();
    
    void setC0(double value);
    double getC0Value();
    
    void setC1(double value);
    double getC1Value();
};


#endif