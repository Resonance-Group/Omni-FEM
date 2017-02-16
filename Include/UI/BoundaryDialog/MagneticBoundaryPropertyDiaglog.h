#ifndef MAGNETIC_BOUNDARY_PROPERTY_DIALOG_H_
#define MAGNETIC_BOUNDARY_PROPERTY_DIALOG_H_

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
#include <common/BoundaryConditions.h>
#include <common/MagneticBoundary.h>

/*! /class magneticBoundaryDialog
 *  /brief
 *  This class handles all of the interaction in order to add/modify a boundary condition for
 *  a mangetic boundary
 */
class magneticBoundaryDialog : public wxDialog
{
private:
    //! This is a local copy of the new or modified magnetic boundary
    magneticBoundary _magneticBoundary;
    
    wxArrayString *BCNameArray = new wxArrayString();
    
    wxComboBox *BCComboBox = new wxComboBox();
    
    wxTextCtrl *nameTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *uRelativeTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *sigTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *c0TextCtrl = new wxTextCtrl();
    
    wxTextCtrl *c1TextCtrl = new wxTextCtrl();
    
    wxTextCtrl *A0TextCtrl = new wxTextCtrl();
    
    wxTextCtrl *A1TextCtrl = new wxTextCtrl();
    
    wxTextCtrl *A2TextCtrl = new wxTextCtrl();
    
    wxTextCtrl *phiTextCtrl = new wxTextCtrl();
    
    void onBCComboChange(wxCommandEvent &event);
    
    void setTextBox();
    
public:
    //! The constructor for the class
    magneticBoundaryDialog();
    
    //! The desctrutor for the class
    ~magneticBoundaryDialog();
    
    //! This function will set the boundary condition of the local boundary condition. Useful for when modifying a BC
    void setBoundaryCondition(magneticBoundary &boundary);
    
    //! This will retireive the boundary condition. THis function is needed when modifying a BC or adding a new one in order to pull for the updated/new parameters. This function should be called after the Modal return wxID_OK
    void getBoundaryCondition(magneticBoundary &boundary);
    
    //! This will restore the local boundary condition back to default values. This is useful when adding a new boundary condition
    void clearBoundary();
    
private:
   wxDECLARE_EVENT_TABLE();
};

#endif