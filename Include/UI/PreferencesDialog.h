#ifndef PROBLEM_DEFINITION_DIALOG_H_
#define PROBLEM_DEFINITION_DIALOG_H_

#include <string>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/combobox.h>
#include <wx/sizer.h>

#include <common/enums.h>
#include <common/MagneticPreference.h>
#include <common/ElectrostaticPreference.h>


class preferencesDialog : public wxDialog
{
private:
    //! This will contain a local copy of all the setting that are to be edited for magnetic simulations 
    magneticPreference _magPreference;
    
    //! The combo box for specifing the problem type for Magnetic Simulations
    wxComboBox *problemTypeComboBox = new wxComboBox();
    
    //! The combo box for specifing the units of length for hte simulation
    wxComboBox *lengthUnitsComboBox = new wxComboBox();
    
    //! The combo box for specifiying the AC solver of the problem
    wxComboBox *acSolverComboBox = new wxComboBox();
    
    //! THe text box for setting the AC frequency
    wxTextCtrl *frequencyTextCtrl = new wxTextCtrl();
    
    //! The text box for setting the depth of the problem
    wxTextCtrl *depthTextCtrl = new wxTextCtrl();
    
    //! The text box for setting the solver precision
    wxTextCtrl *solverPrecisionTextCtrl = new wxTextCtrl();
    
    //! The text box for specifiing the min angle of the problem
    wxTextCtrl *minAngleTextCtrl = new wxTextCtrl();
    
    //! The text box for adding comments
    wxTextCtrl *commentsTextCtrl = new wxTextCtrl();
    
    wxArrayString *probTypeNameArray = new wxArrayString();
    
    wxArrayString *lengthUnitsNameArray = new wxArrayString();
    
    wxArrayString *acSolverNameArray = new wxArrayString();
    
public:

    preferencesDialog(magneticPreference &pref);
    
    preferencesDialog(electroStaticPref &pref);
    
    ~preferencesDialog();
    
    void getPreferences(magneticPreference &settings);
    
    void getPreferences(electroStaticPref &settigns);

    
};


#endif