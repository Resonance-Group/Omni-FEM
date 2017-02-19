#ifndef CIRCUITPROPERTYDIALOG_H_
#define CIRCUITPROPERTYDIALOG_H_

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
#include <common/CircuitProperty.h>


class circuitPropertyDialog : public wxDialog
{
private:
    circuitProperty _circuitProperty;
    
    //! This is the input box for the name of the material
    wxTextCtrl *nameTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the circuit current of the property
    wxTextCtrl *circuitCurrentTextCtrl = new wxTextCtrl();
    
    wxRadioButton *radioButton1 = new wxRadioButton();
    
    wxRadioButton *radioButton2 = new wxRadioButton();
    
    void onRadioButton1Click(wxCommandEvent &event);
    
    void onRadioButton2Click(wxCommandEvent &event);
    
    void setTextBox();
public:
    
    circuitPropertyDialog();
    
    ~circuitPropertyDialog();
    
    /*! /brief
     *  When a new circuit is created, this function must be called in order to retrieve the new circuit
     *  Note: There is currently no checking if the number that is entered is a valid number. This is up to the user.
     *  IF a number is accidently typed as 1.5.3, then wxWidgets will automaticcaly truncate the number to 1.5
     */ 
    void getNewCircuit(circuitProperty &newCircuit);
    
    //! This will set the private variable _circuitProperty to be equal to circuit. Useful if modifying a circuit
    void setCircuit(circuitProperty &circuit);
    
    //! This will reset the variable _circuitProperty to default values. Useful if adding a new circuit
    void clearCircuit();
    
    
private:
    wxDECLARE_EVENT_TABLE();  
};




#endif