#ifndef GLOBAL_PREFERENCES_DIALOG_H_
#define GLOBAL_PREFERENCES_DIALOG_H_

#include <string>
#include <iostream>
#include <iomanip>

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/combobox.h>
#include <wx/string.h>
#include <wx/checkbox.h>
#include <wx/propdlg.h>
#include <wx/bookctrl.h>
#include <wx/validate.h>
#include <wx/valnum.h>

#include <common/enums.h>
#include <common/GridPreferences.h>
#include <common/MagneticPreference.h>
#include <common/ElectrostaticPreference.h>

class globalPreferencesDialog : public wxPropertySheetDialog
{
private:
    electroStaticPreference _electricalPreference;
    
    magneticPreference _magneticPreference;
    
    gridPreferences *_preferences;

/* This section is for creating the area for the document settings */
    physicProblems _problem = physicProblems::NO_PHYSICS_DEFINED;

    wxTextCtrl *_depthTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_precisionTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_minAngleTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_commentsTextCtrl = new wxTextCtrl();
    
    wxComboBox *_lengthComboBox = new wxComboBox();
    
    wxComboBox *_problemTypeComboBox = new wxComboBox();
    
    /* This section are declarations for specifically the magnetic problem */
    wxTextCtrl *_frequencyTextCtrl = new wxTextCtrl();
    
    wxComboBox *_acSolverComboBox = new wxComboBox();
    
/* This section is for creating the grid settings */
    wxTextCtrl *_gridStepTextCtrl = new wxTextCtrl();
    
    wxComboBox *_coordinateComboBox = new wxComboBox();
    
    wxCheckBox *_showGridCheckBox = new wxCheckBox();
    
    wxCheckBox *_showOriginCheckBox = new wxCheckBox();
    
    wxCheckBox *_showGridAxisCheckBox = new wxCheckBox();
    
    wxCheckBox *_snapGridCheckBox = new wxCheckBox();
    
    wxCheckBox *_showBlockNameCheckBox = new wxCheckBox();
    
    wxCheckBox *_reverseMouseZoomCheckBox = new wxCheckBox();
    
    void updateInterface();
    
    void createDialog(wxWindow *par);
    
public:
    globalPreferencesDialog(wxWindow *par, gridPreferences *gridPref, magneticPreference pref);
    
    globalPreferencesDialog(wxWindow *par, gridPreferences *gridPref, electroStaticPreference pref);
    
    void getPreferences(electroStaticPreference &electricPref);
    
    void getPreferences(magneticPreference &magneticPref);
};


#endif