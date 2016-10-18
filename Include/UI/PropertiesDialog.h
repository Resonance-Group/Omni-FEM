#ifndef PROPERTIESDIALOG_H_
#define PROPERTIESDIALOG_H_

#include <wx/wx.h>
#include <string>
//#include <UI/problemDefinition.h>

class propertiesDialog : wxDialog
{
private:
//    physicProblems _physProb;

    
    
    void drawMaterialPropEStat();
    void drawMaterialPropMagnetic();
    
    void drawBoundaryPropEStat();
    void drawboundaryPropMagnetics();
    
    void drawNodalPropEStat();
    void drawNodalPropMagnetic();
    
    void drawCircuitsProp();
    void drawConductorProp();

public:
    propertiesDialog();
    void drawInitial();
};



#endif