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
#include <common/MeshSettings.h>
#include <common/OmniFEMMessage.h>

#include <UI/MeshAdvancedSettings.h>


//! Class that handles the creation of the dialog to edit all preferences
/*!
    This dialog is created in order to edit all of the preferences for 
    any particular simulation. This includes the simulation specific preference
    and the grid preference and any system specific preferences.
    The wxPropertySheetDialog class allows the coding of the dialog to
    contain tabs.
    For additional documentation on the wxPropertySheetDialog, refer
    to the following link:
    http://docs.wxwidgets.org/trunk/classwx_property_sheet_dialog.html
*/ 
class globalPreferencesDialog : public wxPropertySheetDialog
{
private:

    //! A local copy of the electrical preference
    /*!
        This contains a local copy of the global electrical preference
        This variable is set with the constructor and is only set when
        the user is working with an electrical simulation
    */ 
    electroStaticPreference _electricalPreference;
    
    //! A local copy of the mangetic preference
    /*!
        This contains a local copy of the global mangetic preference
        This variable is set with the constructor and is only set when
        the user is working with an mangetic simulation
    */ 
    magneticPreference _magneticPreference;
	
	meshSettings p_meshSetting;
    
    //! Pointer to the grid preferences of the simulation
    /*!
        This is a pointer pointing to the grid
        preferences of the simulation. This
        variable is set with the constructor of the class
    */ 
    gridPreferences *_preferences;

    /* This section is for creating the area for the document settings */
    
    //! Variable containing which physics problem the user selected
    /*!
        This variable will gonvern what widgets are drawn on the 
        screen since the preferences for magnetics and electrical 
        simulations are different.
    */ 
    physicProblems _problem = physicProblems::NO_PHYSICS_DEFINED;
    
    //! Text box used to modify the depth of the problem
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_depthTextCtrl = new wxTextCtrl();
    
    //! Text box used to modify the precision of the problem
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_precisionTextCtrl = new wxTextCtrl();
    
    //! Text box used to modify the minimum angle of the problem
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_minAngleTextCtrl = new wxTextCtrl();
    
    //! Text box used to modify the comments of the problem
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_commentsTextCtrl = new wxTextCtrl();
    
    //! Combo box used to select the units for the length
    /*!
        The units are also used to specify teh units for the
        depth.
        For documenation on the wxComboBox class, refer to the following
        link:
        http://docs.wxwidgets.org/trunk/classwx_combo_box.html
    */ 
    wxComboBox *_lengthComboBox = new wxComboBox();
    
    //! Combo boxused to select the problem type of the simulation
    /*!
        The selection can be either Planar or Axisymmetric
        For documenation on the wxComboBox class, refer to the following
        link:
        http://docs.wxwidgets.org/trunk/classwx_combo_box.html
    */ 
    wxComboBox *_problemTypeComboBox = new wxComboBox();
    
    /* This section are declarations for specifically the magnetic problem */
    
    //! Text box used to modify the frequency for the problem
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *_frequencyTextCtrl = new wxTextCtrl();
	
	//! The text control box that handles the smoothing steps for the mesh
	wxTextCtrl *p_smoothingStepsTextCtrl = new wxTextCtrl();
	
	//! Text control that handles settings the smallest allowable mesh size
	wxTextCtrl *p_minElementSizeTextCtrl = new wxTextCtrl();
	
	//! Text control that handles settings the largest allowable mesh size
	wxTextCtrl *p_maxElementSizeTextCtrl = new wxTextCtrl();

	
    //! Combo box used to select the AC solver of the problem
    /*!
        Can be either Succisive Approxamation or Newton.
        For documenation on the wxComboBox class, refer to the following
        link:
        http://docs.wxwidgets.org/trunk/classwx_combo_box.html
    */ 
    wxComboBox *_acSolverComboBox = new wxComboBox();
    
    /* This section is for creating the grid settings */
    
    //! Text box used to modify the grid step size
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *_gridStepTextCtrl = new wxTextCtrl();
    
    //! Combo box used to select the coordiante plane
    /*!
        Can be either Cartesian or Planar.
        For documenation on the wxComboBox class, refer to the following
        link:
        http://docs.wxwidgets.org/trunk/classwx_combo_box.html
    */ 
    wxComboBox *_coordinateComboBox = new wxComboBox();
	
	//! Combox that is used to select the mesh algorithm used to calculate the mesh
	wxComboBox *p_meshAlgothimComboBox = new wxComboBox();
	
	//! Combobox used to select the recombination algorithm GMSH uses
	wxComboBox *p_meshRecombinationComboBox = new wxComboBox();
	
	//! Combobox used to select the remesh-algorithm GMSH uses
	wxComboBox *p_remeshAlgorithmComboBox = new wxComboBox();
	
	//! Combobox used to select the remesh parameterization GMSH uses
	wxComboBox *p_remeshParamterizationComboBox = new wxComboBox();
	
	//! Combobox used to select the mesh order GMSH will use to create the mesh
	wxComboBox *p_elementOrderComboBox = new wxComboBox();
    
    //! Check box used to toggle the show grid state
    /*!
        For documentation on the wxCheckBox class, refer to
        the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_check_box.html
    */ 
    wxCheckBox *_showGridCheckBox = new wxCheckBox();
    
    //! Check box used to toggle the show origin state
    /*!
        For documentation on the wxCheckBox class, refer to
        the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_check_box.html
    */ 
    wxCheckBox *_showOriginCheckBox = new wxCheckBox();
    
    //! Check box used to toggle the show grid axis state
    /*!
        For documentation on the wxCheckBox class, refer to
        the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_check_box.html
    */ 
    wxCheckBox *_showGridAxisCheckBox = new wxCheckBox();
    
    //! Check box used to toggle the snap to grid state
    /*!
        For documentation on the wxCheckBox class, refer to
        the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_check_box.html
    */ 
    wxCheckBox *_snapGridCheckBox = new wxCheckBox();
    
    //! Check box used to toggle the show block names state
    /*!
        For documentation on the wxCheckBox class, refer to
        the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_check_box.html
    */ 
    wxCheckBox *_showBlockNameCheckBox = new wxCheckBox();
    
    //! Check box used to toggle the reverse mouse wheel direction for zooming state
    /*!
        For documentation on the wxCheckBox class, refer to
        the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_check_box.html
    */ 
    wxCheckBox *_reverseMouseZoomCheckBox = new wxCheckBox();
	
	wxButton *p_meshResetDefaultsButton = new wxButton();
    
    //! Function that is called to draw the screen
    /*!
        The program will setup variables within the constructor.
        After setting up in the constructor, the program will call this funciton
        to draw the correct widigets depending on the state
        of the variables
        \param par Pointer to the parent window
    */ 
    void createDialog(wxWindow *par);
    
    //! Event proceudre that is called when the user selects between Planar and Axisymmetric
    /*!
        This function is called when the user changes their selection on the 
        problem type combo box. For planar problems, the dpeth text box will be enabled.
        For axisymmetric problems, the depth text box will be disabled
    */
    void onProblemTypeComboBox(wxCommandEvent &event);
	
	/**
	 * @brief Event procedure that is called when the user changes the selection
	 * 			in the mesh algorithm combo box. This is mainly used to print debug information
	 * 			for logging.
	 * @param event Required arguement for event procedure functionality
	 */
	void onMeshAlgoComboBox(wxCommandEvent &event);
	
	/**
	 * @brief Event procedure that is called when the user changes the selection in the
	 * 			mesh recombination combo box. This is mainly used to print debug information
	 * 			for logging.
	 * @param event Required arguement for event procedure functionality
	 */
	void onMeshRecombinationComboBox(wxCommandEvent &event);
	
	/**
	 * @brief Event procedure that is called when the user changes the selection in the
	 * 			remeshing algorithm combo box. This is mainly used to print debug information
	 * 			for logging.
	 * @param event Required arguement for event procedure functionality
	 */
	void onRemeshAlgo(wxCommandEvent &event);
	
	/**
	 * @brief Event procedure that is called when the user changes the selection in the
	 * 			remesing parameterization combo box. This is mainly used to print debug information
	 * 			for logging.
	 * @param event Required arguement for event procedure functionality
	 */
	void onRemeshParam(wxCommandEvent &event);
	
	/**
	 * @brief Event procedure that is called when the user presses the reset button. This
	 * 			is used in the event that the user would like to load back the default settings
	 * @param event Required arguement for event procedure functionality
	 */
	void onMeshDefaultsReset(wxCommandEvent &event);
	
	/**
	 * @brief Event procedure that is fired when the user presses the advanced button in the mesh
	 * 			settings panel. THis will bring up another dialog with additional settings for 
	 * 			the user to select or edit
	 * @param event Required arguement for event procedure functionality
	 */
	void onMeshAdvance(wxCommandEvent &event);
    
	void onTextChange(wxCommandEvent &event);
public:

    //! Constructor for the class.
    /*!
        This cosntructor will setup the variables and draw the 
        preferences screen for a magnetic simulation
    */ 
    globalPreferencesDialog(wxWindow *par, gridPreferences *gridPref, magneticPreference pref, meshSettings settings);
    
    //! Constructor for the class.
    /*!
        This cosntructor will setup the variables and draw the 
        preferences screen for an electrostatic simulation
    */ 
    globalPreferencesDialog(wxWindow *par, gridPreferences *gridPref, electroStaticPreference pref, meshSettings settings);
    
    //! Retrieves the preferences for electrical simulations
    /*!
        This function will take an electroStaticPreference object 
        and setup the variables to what the user has set in
        the dialog
        \param electricPref The electroStaticPreference object that will take on
                            the values that the user selects in the dialog
    */ 
    void getPreferences(electroStaticPreference &electricPref, meshSettings &settings);
    
    //! Retrieves the preferences for magnetic simulations
    /*!
        This function will take an magneticPreference object 
        and setup the variables to what the user has set in
        the dialog
        \param magneticPref The magneticPreference object that will take on
                            the values that the user selects in the dialog
    */ 
    void getPreferences(magneticPreference &magneticPref, meshSettings &settings);
    
private:
    //! Required for proper event precedure working
    wxDECLARE_EVENT_TABLE();
};


#endif