#ifndef NODAL_PROPERTY_DIALOG_H_
#define NODAL_PROPERTY_DIALOG_H_

#include <vector>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>
#include <wx/sizer.h>

#include <common/NodalProperty.h>
#include <common/enums.h>

#include <UI/NodalProperty/NodalPropertyDialog.h>

class nodalPropertiesDialog : public wxDialog
{
private:
//! This will contain a local copy of the boundary list. This will allow for easy editing
    std::vector<nodalProperty> _nodalPropertyList;
    
    //! This is the combo box containing the current avaiable magnetic boundary
    wxComboBox *selection = new wxComboBox();
    
    /*! /brief 
     *  The string array containing the names of the different magnetic boundary
     *  This variable is actually used once to load the initial state of the names into the combo box.
     *  Once the forum is loaded, this variable is no longer used as the combo box list can be directly edited.
     */ 
    wxArrayString *nodalPropertyNameArray = new wxArrayString();
    
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
    
    //! This contains the dialog that is used to edit and add the magnetic boundary to/from the list
    nodalPropertyDialog *_nodalPropertyDialog = new nodalPropertyDialog();
    
public:
    //! This is the constructor for the class. This constructor is for a magnetic material
    nodalPropertiesDialog(std::vector<nodalProperty> nodalPropertyList);
    
    //! This is the destructor for the class. This will take the material list and save it back into memory
    ~nodalPropertiesDialog();
    
    //! This function needs to be called in order to retrieve the editted list once the dialog is closed
    std::vector<nodalProperty> getNodalPropertyList();
    
private:
    wxDECLARE_EVENT_TABLE();  
};

#endif