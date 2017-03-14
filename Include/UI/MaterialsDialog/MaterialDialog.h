#ifndef MATERIALDIALOGCONTROLLER_H_
#define MATERIALDIALOGCONTROLLER_H_

#include <vector>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>
#include <wx/sizer.h>

#include <common/MaterialProperty.h>
#include <common/ElectroStaticMaterial.h>
#include <common/MagneticMaterial.h>
#include <common/enums.h>

#include <UI/MaterialsDialog/BlockPropertyMagnetics.h>
#include <UI/MaterialsDialog/BlockPropertyDialogElectrostatic.h>

using namespace std;

/*! /class materialDialog
 *  /brief
 *  This is the controller for the materials selection dialog box.
 *  PLease note that this class is different then the one for the materials libraray. This is not the material library.
 *  This is simply the class that handles the selection of the different materials for editing, deleting, or adding to the list.
 *  Due to the small size, this combines all three, controller, Aabstraction, and presentation into one class
 */
class materialDialog : public wxDialog
{
private:
    //! This data will hold what phyics problem the user watns to simulate. This is useful for teh add, mody and delete buttons so that the function knows which vector to modify.
    physicProblems _problem;
    
    std::vector<electrostaticMaterial> _electroStaticMaterialList;

//! This will contain a local copy of the materials list. This will allow for easy editing
    std::vector<magneticMaterial> _magneticMaterialList;
    
    
    //! This is the combo box containing the current avaiable magnetic materials
    wxComboBox *selection = new wxComboBox();
    
    /*! /brief 
     *  The string array containing the names of the different magnetic materials and electrostatic materials
     *  This variable is actually used once to load the initial state of the names into the combo box.
     *  Once the forum is loaded, this variable is no longer used as the combo box list can be directly edited.
     */ 
    wxArrayString *materialNameArray = new wxArrayString();
    
    /*! /brief
        This function is called when the Add Property button is called.
        This fucntion will create another dialog box and add a property to the ;ist once the user is finished
    */ 
    void onAddProperty(wxCommandEvent &event);
    
    /*! /brief
     *  This function will be called when the delete button is pressed
     *  This function will remove the selection from the list.
     */
    void onDeleteProperty(wxCommandEvent &event);
    
    /*! /brief
     *  This function will be called when the modify button is pressed
     *  This function will create another dialog box allowing the user to modif the property
     */
    void onModifyProperty(wxCommandEvent &event);
    
    //! This contains the dialog that is used to edit and add the magnetic materials to/from the list
    
    
    blockPropertyDialogElectrostatic *_eStaticMaterialDialog = new blockPropertyDialogElectrostatic();
    
    void makeDialog();
    
public:
    //! This is the constructor for the class. This constructor is for a magnetic material
    materialDialog(wxWindow *par, std::vector<magneticMaterial> materialList);
    
    materialDialog(wxWindow *par, std::vector<electrostaticMaterial> electroStaticMaterialList);
    
    //! This is the destructor for the class. This will take the material list and save it back into memory
    ~materialDialog();
    
    //! This function needs to be called in order to retrieve the editted list once the dialog is closed
    std::vector<magneticMaterial> getMagenticMaterialList();
    
    std::vector<electrostaticMaterial> getElectroMaterialList();
    
private:
    wxDECLARE_EVENT_TABLE();
};

#endif