#ifndef PROBLEM_DEFINITION_DIALOG_H_
#define PROBLEM_DEFINITION_DIALOG_H_

#include <string>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/combobox.h>
#include <wx/sizer.h>
#include <wx/valnum.h>

#include <common/enums.h>
#include <common/MagneticPreference.h>
#include <common/ElectrostaticPreference.h>


class preferencesDialog : public wxDialog
{
private:
    //! This will contain a local copy of all the setting that are to be edited for magnetic simulations 
    magneticPreference _magPreference;
    
    //! This is the local copy of the electrostatic settings that are to be edited for the electrostatic simulation
    electroStaticPreference _electrPreference;
    
    physicProblems _problem;
    
    //! The combo box for specifing the problem type for Magnetic Simulations
    wxComboBox *_problemTypeComboBox = new wxComboBox();
    
    //! The combo box for specifing the units of length for hte simulation
    wxComboBox *_lengthUnitsComboBox = new wxComboBox();
    
    //! The combo box for specifiying the AC solver of the problem
    wxComboBox *_acSolverComboBox = new wxComboBox();
    
    //! THe text box for setting the AC frequency
    wxTextCtrl *_frequencyTextCtrl = new wxTextCtrl();
    
    //! The text box for setting the depth of the problem
    wxTextCtrl *_depthTextCtrl = new wxTextCtrl();
    
    //! The text box for setting the solver precision
    wxTextCtrl *_solverPrecisionTextCtrl = new wxTextCtrl();
    
    //! The text box for specifiing the min angle of the problem
    wxTextCtrl *_minAngleTextCtrl = new wxTextCtrl();
    
    //! The text box for adding comments
    wxTextCtrl *_commentsTextCtrl = new wxTextCtrl();
    
    wxArrayString *_probTypeNameArray = new wxArrayString();
    
    wxArrayString *_lengthUnitsNameArray = new wxArrayString();
    
    wxArrayString *_acSolverNameArray = new wxArrayString();
    
    void createDialog();
    
public:

    preferencesDialog(wxWindow *par, magneticPreference pref);
    
    preferencesDialog(wxWindow *par, electroStaticPreference pref);
    
    ~preferencesDialog();
    
    void getPreferences(magneticPreference &settings);
    
    void getPreferences(electroStaticPreference &settings);

    
};


#endif