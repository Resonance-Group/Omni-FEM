#ifndef BLOCKPROPERTYDIALOG_H_
#define BLOCKPROPERTYDIALOG_H_

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>
#include <wx/valnum.h>

#include <common/ElectroStaticMaterial.h>
#include <common/MagneticMaterial.h>
#include <common/enums.h>
#include <common/GeometryProperties/BlockProperty.h>


//! Class that draws the dialog for editing block labels
/*!
    This class handles the drawing of the dialog
    that allows the user to edit the properties
    of a block label. After clicking on the ok button,
    this class will generate a wxID_OK event which will allow the 
    program to grab the parameters of the block property
*/ 
class blockPropertyDialog : public wxDialog
{
private:

    //! Physics problem that the user selected
    /*!
        The physics problem that the user has selected.
        This variable is set in the constructor and 
        depends on which material list was passed into
        the constructor.
    */
    physicProblems _problem;
    
    //! Pointer to the global magnetic material list
    std::vector<magneticMaterial> *_magneticMaterialList;
    
    //! Pointer to the global electrical material list
    std::vector<electrostaticMaterial> *_electricalMaterialList;
    
    //! Pointer to the global circuit list
    std::vector<circuitProperty> *_circuitList;

    //! Combo box used to select the material for the block label
    /*!
        For documentation on the wxComboBox class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_combo_box.html
    */ 
    wxComboBox *_materialComboBox = new wxComboBox();
    
    //! Combo box used toselect pre-determined mesh sizes
    /*!
        For documentation on the wxComboBox class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_combo_box.html
    */ 
    wxComboBox *_meshSizeComboBox = new wxComboBox();
    
    //! Check box used to select the auto mesh feature
    /*!
        For documentation on the wxCheckBox class, refer to
        the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_check_box.html
    */
    wxCheckBox *_autoMeshCheckBox = new wxCheckBox();
    
    //! Text box used to edit the mesh size
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */
    wxTextCtrl *_meshSizeTextCtrl = new wxTextCtrl();
    
    //! Combo box used to select the circuit for the block label
    /*!
        This only applies to magnetic simulations
        For documentation on the wxComboBox class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_combo_box.html
    */ 
    wxComboBox *_circuitComboBox = new wxComboBox();
    
    //! Text box used to edit the number of turns for the block label
    /*!
        This only applies to magnetic simulations
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_numberOfTurnsTextCtrl = new wxTextCtrl();
    
    //! Text box used to edit the number of turns for the block label
    /*!
        This only applies to magnetic simulations
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_magnetizationTextCtrl = new wxTextCtrl();
    
    //! Text box used to edit the group number for the block label
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_groupTextCtrl = new wxTextCtrl();
    
    //! Check box used to set that the block label is within an external region
    /*!
        This option is only possible if the user set the problem
        type to Axisymmetric. Otherwise, the user has the option
        to specify this parameter
        For documentation on the wxCheckBox class, refer to
        the following link:
        http://docs.wxwidgets.org/3.1.0/classwx_check_box.html
    */ 
    wxCheckBox *_externalRegionCheckbox = new wxCheckBox();
    
    //! Check box used to set that this block label is the default
    /*!
        For defualt block labels, all subsequent block labels will contain
        the properties set by the one with the default checked
    */ 
    wxCheckBox *_defaultCheckBox = new wxCheckBox();
    
    //! Event procedure for when the user clicks on the auto mesh check box
    /*!
        This function will toggle the enable state of both the 
        combo box for the pre-defined mesh sizes and the 
        mesh size text box. The enable state will always be opposite of
        the checked state for the auto mesh check box
        \param event Required parameter for proper functionality of the event procedure
    */ 
    void onCheckAutoMesh(wxCommandEvent &event);
    
    //! Event procedure that is fired when the user changes the value in the mesh size text control box
    /*!
        This function will update the selection in the 
        mesh size combo box to be custom
        \param event Required parameter for proper functionality of the event procedure
    */ 
    void onTextEdit(wxCommandEvent &event);
    
    //! Combo box event procedure for when the user selects a pre-defined mesh size
    /*!
        This event procedure is fired each time the user changes the value for
        the mesh size combo box. THis function will determine what the selection
        should be in the mesh size combo box. This function will then call teh 
        setMeshSizeTextCtrl function in order to change the value 
        displayed in the text box.
        \param event Required parameter for proper functionality of the event procedure
    */ 
    void onComboBoxSelection(wxCommandEvent &event);
    
    //! Function that changes the value displayed in the mesh size text control
    /*!
        This function will change the value in the mesh text control 
        to display the value of the mesh size that corresponds 
        with their selection
        \param meshType The mesh size type that the user selected
    */ 
    void setMeshSizeTextCtrl(meshSize meshType);
    
public:

    //! Constructor for the class
    /*!
        This constructor will create the dialog for the magnetic simulation.
        \param par Pointer to the parent window. For a selected block label
        \param material Pointer to the global magnetic material list
        \param circuit pointer to the global circuit list
        \param property A block property that will be edited.
                        For a selected block label the program will 
                        display the properties in text, combo, and 
                        check boxes
        \param isAxisymmetric Boolean used to enable/disable the external region check box.
                            Set to true to enable it. Otherwise, set to false
    */ 
    blockPropertyDialog(wxWindow *par, std::vector<magneticMaterial> *material, std::vector<circuitProperty> *circuit, blockProperty property, bool isAxisymmetric);
    
    //! Constructor for the class
    /*!
        This constructor will create the dialog for the electrical simulation.
        \param par Pointer to the parent window.                       
        \param material Pointer to the global electrical material list.             
        \param property A block property that will be edited.
                        For a selected block label the program will 
                        display the properties in text, combo, and 
                        check boxes
        \param isAxisymmetric Boolean used to enable/disable the external region check box.
                            Set to true to enable it. Otherwise, set to false
    */ 
    blockPropertyDialog(wxWindow *par, std::vector<electrostaticMaterial> *material, blockProperty property, bool isAxisymmetric);
    
    //! Retrieves the properties for the edit block label
    /*!
        This function will take all of the setting that the
        user edited and save them into a program supplied 
        block label object
        \param property The block label that will save the 
                        properties set by the user
    */ 
    void getBlockProperty(blockProperty &property);
    
    //! Destructor for the class
    ~blockPropertyDialog();
    
private:

    //! Required for the event table to work properly
    wxDECLARE_EVENT_TABLE();
};


#endif