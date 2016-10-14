#ifndef BOUNDARYCONDITIONS_H_
#define BOUNDARYCONDITIONS_H_

#include <common/enums.h>

using namespace std;

/*! /brief This class is the general BC class that is used to */
class boundaryCondition
{
private:
    string _boundaryName;
    double _c0 = 0;
    double _c1 = 0;
    
    bcEnum _bcType;
public:
    void setBoundaryName(string name);
    string getBoundaryName();
    
    void setC0(double value);
    double getC0Value();
    
    void setC1(double value);
    double getC1Value();
    
    void setBC(bcEnum BC);
    bcEnum getBC();
}


#endif