#ifndef BLOCKPROPERTYMAGNETIC_H_
#define BLOCKPROPERTYMAGNETIC_H_

#include <string>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>
#include <wx/statbox.h>
#include <wx/sizer.h>
#include <wx/valnum.h>

#include <common/enums.h>
#include <common/MaterialProperty.h>
#include <common/MagneticMaterial.h>

#include <UI/MaterialsDialog/JilesAthertonParametersDialog.h>

//! Class that is used to create the dialog for editing a magnetic material
/*! 
	This calss is for creating the dialog to edit a magnetic material when in the magnetics simualtion
	The user will have the ability to edit properties such as the 
	lamination type and the permeabiloity. If the material is a linear or non-linear
	permeability.
	For documentation on the wxDialog, refer to the following link:
	http://docs.wxwidgets.org/3.0/classwx_dialog.html
*/
class blockPropertyMagnetic : public wxDialog
{
private:
    //! This is the magnetic materail that will either be created (added to the global list) or modified
    magneticMaterial _magneticMaterial;

    //! This is the input box for the name of the material
	/*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *nameTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the relative magnetic permability of the material in the x-plane
	/*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *relativeUxTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the hystersis lag angle in the x-plane
	/*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *phiXTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the relative magnetic permability of the material in the y-plane
	/*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *relativeUyTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the hystersis lag angle in the y-plane
	/*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *phiYTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the coercivity of the material
	/*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *coercivityTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the electrical conductivity
	/*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *eConductivityTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the current density of the material
	/*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *currentDensityTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the lamination thickness
	/*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *lamThickTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the number of strands in the wire
	/*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *numStrandsTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the lamination fill factor 
	/*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *lamFFTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the diameter of the wire
	/*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *strandDiaTextCtrl = new wxTextCtrl();
    
    //! This drop-down box is created in order to give the user an option to choose from one of the values held in the LamWireSettingsArray
	/*!
        For documentation on the wxComboBox class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_combo_box.html
    */ 
    wxComboBox *specialAttriComboBox = new wxComboBox();
    
    //! This drop-down box is created in order to allow the user to choose if the magnetic mateiral is linear or not
	/*!
        For documentation on the wxComboBox class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_combo_box.html
    */ 
    wxComboBox *BHCurveComboBox = new wxComboBox();
    
    //! This is the button used to edit the Jiles-Artherton Model parameters when clicked
	/*!
		For documentation on the wxButton class, refer to
		the following link:
		http://docs.wxwidgets.org/trunk/classwx_button.html
	*/ 
    wxButton *jilesAthertonButton = new wxButton();
        
    //! This function is called when the button is pressed in order to edit the Jiles-Atherton parameters
	/**
	 * @brief 	This function is called each time the user presses on the button to edit the 
	 * 		  	Jiles-Atherton parameters of the material. This function will create the 
	 * 			dialog needed to edit the Jiles Atherton properties
	 * @param event Required argument for proper routing of the event procedure
	 */
    void onBHCurve(wxCommandEvent &event);
    
    //! This function is called in order to update the form should the user choose to change the material from linear to non-linear and vice-versa
	/**
	 * @brief 	This function will enable the user to click on the button to edite the Jiles-Atherton parameters.
	 * 			If already enabled, then this function will disable the button.
	 * @param event Required argument for proper routing of the event procedure
	 */
    void onBHCurveCombo(wxCommandEvent &event);
    
    //! THis function is called in order ot update the form when the user chooses the different options listed in the corresponding combo-box
	/**
	 * @brief 	This function will enable/disable the various text boxes based on the user
	 * 			selection.
	 * @param event Required argument for proper routing of the event procedure
	 */
    void onSpecialComboBox(wxCommandEvent &event);
    
    //! This is an internal function that gets called in order to update the fields in the text control box
	/**
	 * @brief 	This function is called in order to reset the display of the for text boxes
	 * 			with the values stored in the local material variable
	 */
    void updateInterface();
    
public:
    
	//! The constructor of the class
	/*!
		This function will setup the display and position the widgets in their
		approiate places for the user to see.
		\param par Pointer to the parent window
	*/ 
    blockPropertyMagnetic(wxWindow *par);
    
	//! The desctructor for the class
    ~blockPropertyMagnetic();
    
    /*! /brief
     *  When a new material is created, this function must be called in order to retrieve the new material
     *  Note: There is currently no checking if the number that is entered is a valid number. This is up to the user.
     *  IF a number is accidently typed as 1.5.3, then wxWidgets will automaticcaly truncate the number to 1.5
     */ 
    void getNewMaterial(magneticMaterial &newMaterial);
    
    //! This will set the private variable _magneticMaterial to be equal to matieral. Useful if modifying a material
	/**
	 * @brief This function is called when there is a need to
	 * edit the material at hand. In which case, the local material variable for the class
	 * will become whatever material that is passed into the function
	 * @param material The material that will be edited
	 */
    void setMaterial(magneticMaterial &material);
    
	/**
	 * @brief This will reset the variable _magneticMaterial to default values. Useful if adding a new material
	 */
    void clearMaterial();
    
private:
	//! This macro is required for event procedure
    wxDECLARE_EVENT_TABLE();
};



#endif
