#ifndef EXTERIORREGION_H_
#define EXTERIORREGION_H

#include <string>
#include <iostream>
#include <iomanip>

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/sizer.h>


class exteriorRegionDialog : public wxDialog
{
private:
    wxTextCtrl *_centerExteriorTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_radiusExteriorTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_radiusInteriorTextCtrl = new wxTextCtrl();
    
public:
    exteriorRegionDialog(wxWindow *par);
    
    ~exteriorRegionDialog();
    
    void setParameters(double &centerOfExterior, double &radiusExterior, double &radiusInterior);
    
    void getParameters(double &centerOfExterior, double &radiusExterior, double &radiusInterior);
};

#endif