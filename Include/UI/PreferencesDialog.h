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

/**
 * @class preferencesDialog
 * @author Phillip
 * @date 12/07/17
 * @file PreferencesDialog.h
 * @brief   Dialog that is used to handle any of the problem 
 *          preferences that the user can set. This will include
 *          the comments, if there is a frequency component,
 *          the length of the problem, the precision of the 
 *          problem, etc. When the user accepts the changes, this class will
 *          generate a wxID_OK event which the program can then pull for the
 *          preferences and update the program accordingly.
 */
class preferencesDialog : public wxDialog
{
private:
    //! This will contain a local copy of all the setting that are to be edited for magnetic simulations 
    magneticPreference _magPreference;
    
    //! This is the local copy of the electrostatic settings that are to be edited for the electrostatic simulation
    electroStaticPreference _electrPreference;
    
    //! The physics problem that the user is simulating
    /*!
        The value here will determine what items are drawn on the screen.
        For example, the acSolverComboBox object does not need to be drawn 
        on the screen when the problem is an electrostatic
    */ 
    physicProblems _problem;
    
    //! The combo box for specifing the problem type
    /*!
        Currently, this can either be planar or axisymmetric
    */ 
    wxComboBox *_problemTypeComboBox = new wxComboBox();
    
    //! The combo box for specifing the units of length for the simulation
    /*!
        Currently, Omni-FEM supports:
        Inches
        Millimeters
        Centimeters
        Meters
        Mils
        Micrometers
    */ 
    wxComboBox *_lengthUnitsComboBox = new wxComboBox();
    
    //! The combo box for specifiying the AC solver of the problem
    /*!
        This can either be successive approximatation or Newton
    */ 
    wxComboBox *_acSolverComboBox = new wxComboBox();
    
    //! The text box for setting the AC frequency. Units are in Hz
    wxTextCtrl *_frequencyTextCtrl = new wxTextCtrl();
    
    //! The text box for setting the depth of the problem
    /*!
        The units for the depth are the units that are selected in the
        lenghUnitsComboBox
    */ 
    wxTextCtrl *_depthTextCtrl = new wxTextCtrl();
    
    //! The text box for setting the solver precision
    wxTextCtrl *_solverPrecisionTextCtrl = new wxTextCtrl();
    
    //! The text box for specifiing the min angle of the problem
    wxTextCtrl *_minAngleTextCtrl = new wxTextCtrl();
    
    //! The text box for adding comments
    wxTextCtrl *_commentsTextCtrl = new wxTextCtrl();
    
    /**
     * @brief   Function that is called in order to actually create the dialog.
     *          The constructors simply set up the different variables and then 
     *          this function is called in order to setup the interface and to utilize
     *          the initilized variables.
     */
    void createDialog();
    
    /**
     * @brief   Event Procedure that is called allowing the user to specify a depth parameter
     *          when the user selects the planar selection
     * @param event Standard object in order to route the event procedure to the proper function
     */
    void onComboBox(wxCommandEvent &event);
    
public:

    //! Constructor for the class
    /*!
        This is the constructor for magnetics. The program will setup the 
        dialog for a magnetic simulation
        \param par  A pointer to the parent window associated with the dialog
        \param pref A copy of the current magnetic preferences.
                    This copy is used to display the current selected settings
                    to the user for editing.
    */ 
    preferencesDialog(wxWindow *par, magneticPreference pref);
    
    //! Constructor for the class
    /*!
        This is the constructor for electrostatics. The program will setup the 
        dialog for an electrostatics simulation
        \param par  A pointer to the parent window associated with the dialog
        \param pref A copy of the current electrostatic preferences.
                    This copy is used to display the current selected settings
                    to the user for editing.
    */ 
    preferencesDialog(wxWindow *par, electroStaticPreference pref);
    
    //! The destructor for the class
    ~preferencesDialog();
    
    /**
     * @brief   When the class generates a wxID_OK event, then the program will need to pull the 
     *          settings and update the simulator as necessary. 
     * @param settings THe magnetic preference settings that the class should save the selected settings to
     */
    void getPreferences(magneticPreference &settings);
    
    /**
     * @brief   When the class generates a wxID_OK event, then the program will need to pull the setting 
     *          and update the simulator as necessary
     * @param settings The electrical settings that the class should save the editted settings to
     */
    void getPreferences(electroStaticPreference &settings);

private:
    //! Macro that is needed in order to implement the event procedures
    wxDECLARE_EVENT_TABLE();
};


#endif