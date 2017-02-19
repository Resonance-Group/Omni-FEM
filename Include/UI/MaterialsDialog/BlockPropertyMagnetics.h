#ifndef BLOCKPROPERTYMAGNETIC_H_
#define BLOCKPROPERTYMAGNETIC_H_

#include <string>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>
#include <wx/statbox.h>
#include <wx/sizer.h>

#include <common/enums.h>
#include <common/MaterialProperty.h>
#include <common/MagneticMaterial.h>

#include <UI/MaterialsDialog/JilesAthertonParametersDialog.h>


/*! /class blockPropertMagnetic
 *  /brief
 *  This calss is for creating the Block Property dialog when in the magnetics simualtion
 *  THe dialog box is rather large however, there are only two buttons.
 *  Due to the simplicity of the dialog box, this class will be the abstraction, controller, and presentation
 */
class blockPropertyMagnetic : public wxDialog
{
private:
    //! This is the magnetic materail that will either be created (added to the global list) or modified
    magneticMaterial _magneticMaterial;

    //! This is the input box for the name of the material
    wxTextCtrl *nameTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the relative magnetic permability of the material in the x-plane
    wxTextCtrl *relativeUxTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the hystersis lag angle in the x-plane
    wxTextCtrl *phiXTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the relative magnetic permability of the material in the y-plane
    wxTextCtrl *relativeUyTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the hystersis lag angle in the y-plane
    wxTextCtrl *phiYTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the coercivity of the material
    wxTextCtrl *coercivityTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the electrical conductivity
    wxTextCtrl *eConductivityTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the current density of the material
    wxTextCtrl *currentDensityTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the lamination thickness
    wxTextCtrl *lamThickTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the number of strands in the wire
    wxTextCtrl *numStrandsTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the lamination fill factor 
    wxTextCtrl *lamFFTextCtrl = new wxTextCtrl();
    
    //! This box is created for inputting a value for the diameter of the wire
    wxTextCtrl *strandDiaTextCtrl = new wxTextCtrl();
    
    //! This string array is created for holding the options to indicate if the material is linear or not
    wxArrayString *BHSettingsArray = new wxArrayString();
    
    //! This string array is created for listing the different lamination and wire settings
    wxArrayString *LamWireSettingsArray = new wxArrayString();
    
    //! This drop-down box is created in order to give the user an option to choose from one of the values held in the LamWireSettingsArray
    wxComboBox *specialAttriComboBox = new wxComboBox();
    
    //! This drop-down box is created in order to allow the user to choose if the magnetic mateiral is linear or not
    wxComboBox *BHCurveComboBox = new wxComboBox();
    
    //! This is the button used to edit the Jiles-Artherton Model parameters when clicked
    wxButton *jilesAthertonButton = new wxButton();
        
    //! This function is called when the button is pressed in order to edit the Jiles-Atherton parameters
    void onBHCurve(wxCommandEvent &event);
    
    //! This function is called in order to update the form should the user choose to change the material from linear to non-linear and vice-versa
    void onBHCurveCombo(wxCommandEvent &event);
    
    //! THis function is called in order ot update the form when the user chooses the different options listed in the corresponding combo-box
    void onSpecialComboBox(wxCommandEvent &event);
    
    //! This is an internal function that gets called in order to update the fields in the text control box
    void updateInterface();
    
public:
    
    blockPropertyMagnetic();
    
    ~blockPropertyMagnetic();
    
    /*! /brief
     *  When a new material is created, this function must be called in order to retrieve the new material
     *  Note: There is currently no checking if the number that is entered is a valid number. This is up to the user.
     *  IF a number is accidently typed as 1.5.3, then wxWidgets will automaticcaly truncate the number to 1.5
     */ 
    void getNewMaterial(magneticMaterial &newMaterial);
    
    //! This will set the private variable _magneticMaterial to be equal to matieral. Useful if modifying a material
    void setMaterial(magneticMaterial &material);
    
    //! This will reset the variable _magneticMaterial to default values. Useful if adding a new material
    void clearMaterial();
    
private:
    wxDECLARE_EVENT_TABLE();
};



#endif
