#ifndef BLOCKPROPERTYDIALOGELECTROSTATIC_H_
#define BLOCKPROPERTYDIALOGELECTROSTATIC_H_

#include <string>
#include <iostream>
#include <iomanip>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/arrstr.h>
#include <wx/statbox.h>
#include <wx/sizer.h>

#include <common/enums.h>
#include <common/ElectroStaticMaterial.h>

//! Class that handles the creating/editing dialog for electrical materials
/*!
    This class was created so that it is able to handle the 
    dialog for creating or editing the electrical materials.
    The class will create a dialog with text boxes allowing 
    the user to enter in parameters for the charge density
    and the relative permittivity
    For documentation on the wxDialog class, refer to the 
    following link:
    http://docs.wxwidgets.org/3.1.0/classwx_dialog.html
*/ 
class blockPropertyDialogElectrostatic : public wxDialog
{
private:

    //! A local copy of the material
    /*!
        This variable is only used when the user is
        editing the material. This will store a 
        local copy of the material and all
        of the text boxes will be updated with the values stored
        in this variable. When creating a new material,
        this variable is reset back to default
        values
    */ 
    electrostaticMaterial _material;
    
    //! Text box that is created for editing the name of the material
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_name = new wxTextCtrl();
    
    //! Text box used to edit the relative permittivity in the x-plane
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_relativeEpiXTextCtrl = new wxTextCtrl();
    
    //! Text box used to edit the relative permittivity in the y-plane
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_relativeEpiYTextCtrl = new wxTextCtrl();
    
    //! Text box used to edit the charge density of the material
    /*!
        This is actually a volume charge denisty in units of C/m^3
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_chargeDensityTextCtrl = new wxTextCtrl();
    
    //! Function called to update the interface
    /*!
        The interface is updated by updating the values
        displayed in the text boxex
    */ 
    void updateInterface();

public:

    //! Constructor of the class
    /*!
        This is the constructor of the class. This function
        draws the dialog and places the widgets in the approiate 
        position.
        \param par A pointer pointing to the parent window
    */ 
    blockPropertyDialogElectrostatic(wxWindow *par);
    
    //! Destructor of the class
    ~blockPropertyDialogElectrostatic();
    
    //! Retrieves the values entered into the text box
    /*!
        \param material The variable that will store the 
                        retrieved values
    */ 
    void getMaterial(electrostaticMaterial &material);
    
    //! Resets the local material variable back to defaults
    void clearMaterial();
    
    //! Sets the local material to the variable material
    /*!
        \param material The material whos values will be 
                        displayed when the dialog is displayed
    */ 
    void setMaterial(electrostaticMaterial &material);
};



#endif