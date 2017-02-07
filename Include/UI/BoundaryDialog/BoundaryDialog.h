#ifndef BOUNDARY_DIALOG_H_
#define BOUNDARY_DIALOG_H_


#include <vector>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>

#include <common/BoundaryConditions.h>
#include <common/ElectricalBoundary.h>
#include <common/MagneticBoundary.h>
#include <common/enums.h>

#include <UI/BoundaryDialog/MagneticBoundaryPropertyDiaglog.h>


/*! /class materialDialog
 *  /brief
 *  This is the controller for the materials selection dialog box.
 *  PLease note that this class is different then the one for the materials libraray. This is not the material library.
 *  This is simply the class that handles the selection of the different materials for editing, deleting, or adding to the list.
 *  Due to the small size, this combines all three, controller, Aabstraction, and presentation into one class
 */
class boundaryDialog : public wxDialog
{
private:
//! This will contain a local copy of the materials list. This will allow for easy editing
    std::vector<magneticBoundary> _magneticBoundaryList;
    
    //! This is the combo box containing the current avaiable magnetic materials
    wxComboBox *selection = new wxComboBox();
    
    /*! /brief 
     *  The string array containing the names of the different magnetic materials
     *  This variable is actually used once to load the initial state of the names into the combo box.
     *  Once the forum is loaded, this variable is no longer used as the combo box list can be directly edited.
     */ 
    wxArrayString *magneticBoundaryNameArray = new wxArrayString();
    
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
    magneticBoundaryDialog *_magBoundaryDialog = new magneticBoundaryDialog();
    
public:
    //! This is the constructor for the class. This constructor is for a magnetic material
    boundaryDialog(std::vector<magneticBoundary> boundaryList);
    
    //! This is the destructor for the class. This will take the material list and save it back into memory
    ~boundaryDialog();
    
    //! This function needs to be called in order to retrieve the editted list once the dialog is closed
    std::vector<magneticBoundary> getBoundaryList();
    
private:
    wxDECLARE_EVENT_TABLE();
};


#endif