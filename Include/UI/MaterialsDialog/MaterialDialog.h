#ifndef MATERIALDIALOGCONTROLLER_H_
#define MATERIALDIALOGCONTROLLER_H_

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>
#include <vector>
#include <common/MaterialProperty.h>
#include <common/ElectroStaticMaterial.h>
#include <common/MagneticMaterial.h>

/*! /class materialDialog
 *  /brief
 *  This is the controller for the materials selection dialog box.
 *  PLease note that this class is different then the one for the materials libraray. This is not the material library.
 *  This is simply the class that handles the selection of the different materials for editing, deleting, or adding to the list.
 *  Due to the small size, this combines all three, controller, Aabstraction, and presentation into one class
 */
class materialDialog : public wxFrame
{
private:
//! This will contain a local copy of the materials list. This will allow for easy editing
    std:vector<materialProperty> _materialList;
    
    wxComboBox *selection = new wxComboBox();
    
    wxArrayString *materialNameArray = new wxArrayString();
    
    /*! /brief
        This function is called when the Add Property button is called.
        This fucntion will create another dialog box and add a property to the ;ist once the user is finished
    */ 
    void onAddProperty();
    
    /*! /brief
     *  This function will be called when the delete button is pressed
     *  This function will remove the selection from the list.
     */
    void onDeleteProperty();
    
    /*! /brief
     *  This function will be called when the modify button is pressed
     *  This function will create another dialog box allowing the user to modif the property
     */
    void onModifyProperty();
    
    /*! /brief
     *  This function will be called when the OK button is pressed
     *  This function will close the dialog box and save the list to the main list in the Main Frame object
     */
    void onOk();
public:
    //! This is the constructor for the class. Right now, this does not really do anything
    materialDialog(std::vector<materialProperty> materialList);
    
    //! This is the destructor for the class. This will take the material list and save it back into memory
    ~materialDialog();
    
    //! The creation of the dialog box is a two step process. This is the second step 
    void createDialog();
    
    
};

#endif