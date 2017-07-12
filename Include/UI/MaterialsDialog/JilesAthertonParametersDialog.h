#ifndef jilesAthertonParametersDIALOG_H_
#define jilesAthertonParametersDIALOG_H_

#include <string>
#include <iostream>
#include <iomanip>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>
#include <wx/statbox.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>

#include <common/JilesAthertonParameters.h>
#include <common/enums.h>

/**
 * @class jilesAthertonParameterDialog
 * @author phillip
 * @date 13/06/17
 * @file JilesAthertonParametersDialog.h
 * @brief 	Class that is used to handle the dialog for editing the 
 * 			Jiles-Atherton parameters for a particular magnetic material.
 * 			until further notice, This dialog is for the x-plane only.
 * 			For documentation on the wxDialog class, refer to the following link:
 * 			http://docs.wxwidgets.org/3.0/classwx_dialog.html
 */
class jilesAthertonParameterDialog : public wxDialog
{
private:

    //! This is the class that stores a local copy of the Jiles Artheron parameters
    jilesAthertonParameters _parameter;
    
	//! Text box used to edit the alpha parameter
	/*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *_alphaParamTextCtrl = new wxTextCtrl();
    
	//! Text box used to edit the a parameter
	/*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *_aParamTextCtrl = new wxTextCtrl();
    
	//! Text box used to edit the Ms parameter
	/*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *_satMagnetizationParamTextCtrl = new wxTextCtrl();
    
	//! Text box used to edit the k parameter
	/*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *_kParamTextCtrl = new wxTextCtrl();
    
	//! Text box used to edit the c parameter
	/*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *_cParamTextCtrl = new wxTextCtrl();
    
	//! Text box used to edit the kan parameter
	/*!
		This is enabled when the material is an anistropy material.
		Otherwise, this text box is disabled.
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *_KanParamTextCtrl = new wxTextCtrl();
    
	//! Text box used to edit the psi parameter
	/*!
		This is enabled when the material is an anistropy material.
		Otherwise, this text box is disabled.
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *_psiParamTextCtrl = new wxTextCtrl();
    
	//! Text box used to edit the t parameter
	/*!
		This is enabled when the material is an anistropy material.
		Otherwise, this text box is disabled.
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *_tParamTextCtrl = new wxTextCtrl();
    
	//! Check box used to indicate if the material is an anistropy material
	/*!
		This check box has an event procedure tied to it in which 
		certain text boxes will be enabled/disabled 
		For documentation on the wxCheckBox class, refer to
        the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_check_box.html
	*/ 
    wxCheckBox *_isAnisotropyCheckBox = new wxCheckBox();
    
	/**
	 * @brief 	Event procedure used to enable/disable text boxes when the is Anisotropy
	 * 			check box is true/false respectively.
	 * @param event A required argument for proper functionality of the event procedure
	 */
    void onCheckBox(wxCommandEvent &event);
    
	/**
	 * @brief 	Function that is used to update the values of the 
	 * 			text boxes with those stored in the local
	 * 			property variable
	 */
    void updateInterface();
    
public:
	//! The constructor of the class
	/*!
		This funciton will create the dialog and position all of
		the widgets in the correct places
		\param par Pointer to the parent window
	*/ 
    jilesAthertonParameterDialog(wxWindow *par);
    
	//! The desctructor for the class
    ~jilesAthertonParameterDialog();
    
	/**
	 * @brief 	This function will set the local parameters object to what
	 * 			is passed into the function. This function is useful when the user
	 * 			needs to edite the parameters of a particule magnetic material.
	 * @param param The Jile-Atherton parameters that are to be edited
	 */
    void setJilesAthertonParameter(jilesAthertonParameters param);
    
	/**
	 * @brief 	This function will retrieve the values stored within the text boxes
	 * 			and save these values into the variable that is passed into the function
	 * @param param The variable that is to contain all of the saved values from the 
	 * 				text boxes
	 */
    void getJilesAthertonParameter(jilesAthertonParameters &param);
    
private:
	//! This macro is required for proper functionality of the event procedure
    wxDECLARE_EVENT_TABLE();
};


#endif