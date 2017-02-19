#ifndef CONDUCTORPROPERTYDIALOG_H_
#define CONDUCTORPROPERTYDIALOG_H_

#include <string>
#include <iostream>
#include <iomanip>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>
#include <wx/statbox.h>
#include <wx/sizer.h>
#include <wx/radiobut.h>

#include <common/enums.h>
#include <common/ConductorProperty.h>


class conductorPropertyDialog : public wxDialog
{
private:
    
    conductorProperty _conductorProperty;
    
    //! This is the input box for the name of the material
    wxTextCtrl *nameTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *chargeTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *voltageTextCtrl = new wxTextCtrl();
    
    wxRadioButton *radioButton1 = new wxRadioButton();
    
    wxRadioButton *radioButton2 = new wxRadioButton();
    
    void onRadioButton1Click(wxCommandEvent &event);
    
    void onRadioButton2Click(wxCommandEvent &event);
    
    void updateInterface();
    
public:

    conductorPropertyDialog();
    
    ~conductorPropertyDialog();
    
    void getNewConductor(conductorProperty &newConductor);
    
    //! This will set the private variable _circuitProperty to be equal to circuit. Useful if modifying a circuit
    void setConductor(conductorProperty &conductor);
    
    //! This will reset the variable _circuitProperty to default values. Useful if adding a new circuit
    void clearConductor();
    
private:
    wxDECLARE_EVENT_TABLE(); 
};



#endif