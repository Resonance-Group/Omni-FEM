#ifndef ESTATICBOUNDARYPROPERTYDIALOG_H_
#define ESTATICBOUNDARYPROPERTYDIALOG_H_

#include <string>
#include <iostream>
#include <iomanip>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>
#include <wx/statbox.h>
#include <wx/sizer.h>

#include <common/enums.h>
#include <common/ElectricalBoundary.h>

class electricalStaticBoundaryDialog : public wxDialog
{
private:
    electricalBoundary _boundary;
    
    wxArrayString *BCNameArray = new wxArrayString();
    
    wxComboBox *BCComboBox = new wxComboBox();
    
    wxTextCtrl *nameTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *fixedVoltageTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *surfaceChargeTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *c0TextCtrl = new wxTextCtrl();
    
    wxTextCtrl *c1TextCtrl = new wxTextCtrl();
    
    void onComboBox(wxCommandEvent &event);
    
    void updateInterface();
    
public:
    electricalStaticBoundaryDialog(wxWindow *par);
    
    ~electricalStaticBoundaryDialog();
    
    void setBoundaryCondition(electricalBoundary &boundary);
    
    void getBoundaryCondition(electricalBoundary &boundary);
    
    void clearBoundary();
    
private:
    wxDECLARE_EVENT_TABLE();
};


#endif