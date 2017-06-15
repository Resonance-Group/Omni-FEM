#ifndef MATERIALSLIBRARY_H_
#define MATERIALSLIBRARY_H_

#include <vector>

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/treectrl.h>

#include <common/ElectroStaticMaterial.h>
#include <common/MagneticMaterial.h>
#include <common/enums.h>

#include <UI/MaterialsDialog/BlockPropertyMagnetics.h>
#include <UI/MaterialsDialog/BlockPropertyDialogElectrostatic.h>

/**
 * @class materialLibraryDialog
 * @author phillip
 * @date 14/06/17
 * @file MaterialsLibrary.h
 * @brief Class that handles the creation of the material libaray
 * 			dialog. The material library will allow the user to hand 
 * 			pick some preset materials. The library is also able to allow the
 * 			user to add to it. Once the user clicks ok on the interface,
 * 			the class will generate a wkID_OK event. 
 * 			For documentation on the wxDialog class, refer
 * 			to the following link:
 * 			http://docs.wxwidgets.org/3.0/classwx_dialog.html
 */
class materialLibraryDialog : public wxDialog
{
private:
    //! Pointer pointing to the global electrical material list
    std::vector<electrostaticMaterial> *_electricalMaterialList;
    
    //! Pointer pointing to the global magnetic material list
    std::vector<magneticMaterial> *_magneticMaterialList;
    
    //! Tree control for the master library list
    /*!
        The master library will be the list that contains all of the different
        types of materials for use. The tree control will display the listing and
        organize everything.
    */ 
    wxTreeCtrl *_masterLibraryTreeCtrl = new wxTreeCtrl();
    
    //! Tree control for the local library list
    /*!
        The local library will be the list that contains what the user
        has choosen to use in the problem. The tree control will display the listing and
        organize everything.
    */ 
    wxTreeCtrl *_localLibraryTreeCtrl = new wxTreeCtrl();
    
    /**
     * @brief   This function will be called when the user presses the Edit button on the
     *          library menu. This will bring up the approiate dialog in order to edit the
     *          properties of the selected material
     * @param event A required param in order for the event procedure to work properly
     */
    void onEditMaterial(wxCommandEvent &event);
    
    /**
     * @brief   This function is executed when the user clicks on the right pointing arrow on the 
     *          the library dialog. This will add the material to the local (global) list
     * @param event A required param in order for the event procedure to work properly
     */
    void onAddMaterialToLocal(wxCommandEvent &event);
    
    /**
     * @brief   This function is executed when the user clicks on the left pointing arrow on the
     *          material dialog. This will add the selected material on the local list side to
     *          the master list if hte material does not already exist. There cannot be 
     *          2 materials with the same name within each simulation.
     * @param event A required param in order for the event procedure to work properly
     */
    void onAddMaterialToMaster(wxCommandEvent &event);
    
    /**
     * @brief   Function that is executed when the user clicks on the delete button. This
     *          function will remove the material from the local list.
     * @param event A required param in order for the event procedure to work properly
     */
    void onRemoveMaterial(wxCommandEvent &event);
    
    /**
     * @brief   Function that is executed when the user clicks on the Add Folder button. This
     *          function will add a new folder to the material library on the master list
     * @param event A required param in order for the event procedure to work properly
     */
    void onAddFolder(wxCommandEvent &event);
    
    /**
     * @brief   This function is executed when the user double click on a selection. This 
     *          will also create the dialog box to edit the selected material.
     * @param event A required param in order for the event procedure to work properly
     */
    void onClickEditMaterial(wxTreeEvent &event);
    
    /**
     * @brief   This function is executed when the user drags a selection from the 
     *          master list to the local list. This will add the dragged material to the
     *          local list.
     * @param event A required param in order for the event procedure to work properly
     */
    void onLocalDrag(wxTreeEvent &event);

public:
    //! Constructor for the class
    /*!
        This constructor is the electrical constructor and will create the dialog
        for the electrical simulation in order to allow the edit of electrical materials
        \param par Pointer pointing to the parent window of the dialog
        \param material Pointer pointing to the global electrical material list
    */ 
    materialLibraryDialog(wxWindow *par, std::vector<electrostaticMaterial> *material);
    
    //! Constructor for the class
    /*!
        This constructor is the magnetic constructor and will create the dialog
        for the magnetic simulation in order to allow the edit of magnetic materials
        \param par Pointer pointing to the parent window of the dialog
        \param material Pointer pointing to the global magnetic material list
    */ 
    materialLibraryDialog(wxWindow *par, std::vector<magneticMaterial> *material);
    
    /**
     * @brief   Retrieves the local magnetic list. This function will copy the local list into
     *          the global magetic material list.
     * @param magneticMaterialList The global magnetic material list
     */
    void getMagneticLocalMaterialList(std::vector<magneticMaterial> &magneticMaterialList);
    
    /**
     * @brief   Retrieves the local magnetic list. This function will copy the local list into
     *          the global magetic material list.
     * @param electricalMaterialList The global electrical material list
     */
    void getElectricalLocalMaterialList(std::vector<electrostaticMaterial> &electricalMaterialList);
    
private:
    //! Required macro for the event procedure to work properly
    wxDECLARE_EVENT_TABLE();
};


#endif
