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

//! Class that handles the dialog for editing the material lists
/*!
    This class does not handle the creation/modifying of individual material objects that 
    the user selects. Rather, this class handles the editing of the list as a whole.
    This dialog will allow the user to add an item to the list, modify an existing item,
    or remove an item from the list. For modifying or adding the elements in the list,
    this class will call the approiate dialog in order to perform this action.
    This class inherits from the dialog class because it allows for the easy creation
    of ok/cancel buttons. This class is intended to be created in order to operate as
    modal.
    For additional documentation for the wxDialog class, refer to the following link:
    http://docs.wxwidgets.org/3.1.0/classwx_dialog.html
*/
class materialDialog : public wxDialog
{
private:

    //! Variable that keeps track of the simulation problem the user selected
    /*!
        This variable is set when the material list is passed into the constructor.
        If a circuit list is passed, then this variable will be set for
        magnetics simulation. Likewise, if a conductor list is passed, this variable
        will be set to electrostic.THis will effect whcih property dialog is drawn next
    */ 
    physicProblems _problem;
    
    //! Pointer pointing to the global list of the electrical materials. 
    /*!
        This is mainly used for electrostatic simulations
    */
    std::vector<electrostaticMaterial> *_electroStaticMaterialList;

    //! Pointer pointing to the global list of the magnetic materials. 
    /*!
        This is mainly used for magnetic simulations
    */
    std::vector<magneticMaterial> *_magneticMaterialList;
    
    
    //! Combo box that contains the listing of all of the names of the materials.
    wxComboBox *_selection = new wxComboBox();
    
    //! Event procedure that is called when the user presses the Add Property button
    /*!
        This function will create the appropriate dialog box in order to add a material
        to the list. The dialog box that gets created is dependent on the problem variable.
        Once the user is finished on adding the property, the function will add the 
        property to the global list. This function will also alert the user
        if they created a property with the same name already. This is not preventing the 
        creation of the property as the user can go and modify the name of the property.
        If there are two properties with the same name, this can cause the program to 
        operate in an unknown state.
        \param event A required parameter in order to properly route the event procedure
    */
    void onAddProperty(wxCommandEvent &event);
    
    //! Event Procedure that is called when the user clicks on the Delete Property button
    /*!
        This function will remove the property that is selected in the combo box from the
        the list. This will only occur if there are more then 1 elements within the list
        \param event A required parameter in order to properly route the event procedure
    */
    void onDeleteProperty(wxCommandEvent &event);
    
    //! Event procedure that is called when the user clicks on the Modify Property button
    /*!
        This function will bring up the appropriate dialog box in order to modify the settings
        of the property that is selected in the combo box. This will only occur if there is more
        then 1 element within the list
        \param event A required parameter in order to properly route the event procedure
    */
    void onModifyProperty(wxCommandEvent &event);
    
    //! Creates the actual dialog
    /*!
        The constructors of the class sets up the different variables that are necessary 
        before the dialog is created. This function actually creates the dialog
        utilizing the variables that we just setup in the constructor
    */
    void makeDialog();
    
public:

    //! This is the constructor for the class. 
    /*!
        This constructor is for a material list used in the magnetic simulation
        \param par A pointer to the parent window
        \param materialList A pointer to the global magnetic material list
    */
    materialDialog(wxWindow *par, std::vector<magneticMaterial> *materialList);
    
    //! This is the constructor for the class. 
    /*!
        This constructor is for a material list used in the electrostatic simulation
        \param par A pointer to the parent window
        \param electroStaticMaterialList A pointer to the global electricla material list
    */
    materialDialog(wxWindow *par, std::vector<electrostaticMaterial> *electroStaticMaterialList);
    
    //! This is the destructor for the class.
    ~materialDialog();
    
private:
    //! Required function for the event procedures to work properly
    wxDECLARE_EVENT_TABLE();
};

#endif