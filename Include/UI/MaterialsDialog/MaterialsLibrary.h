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
    std::vector<electrostaticMaterial> *_electricalMaterialList;
    
    std::vector<magneticMaterial> *_magneticMaterialList;

    wxTreeCtrl *_masterLibraryTreeCtrl = new wxTreeCtrl();
    
    wxTreeCtrl *_localLibraryTreeCtrl = new wxTreeCtrl();
    
    void onEditMaterial(wxCommandEvent &event);
    
    void onAddMaterialToLocal(wxCommandEvent &event);
    
    void onAddMaterialToMaster(wxCommandEvent &event);
    
    void onRemoveMaterial(wxCommandEvent &event);
    
    void onAddFolder(wxCommandEvent &event);
    
    void onClickEditMaterial(wxTreeEvent &event);
    
    void onLocalDrag(wxTreeEvent &event);

public:
    materialLibraryDialog(wxWindow *par, std::vector<electrostaticMaterial> *material);
    
    materialLibraryDialog(wxWindow *par, std::vector<magneticMaterial> *material);
    
    void getMagneticLocalMaterialList(std::vector<magneticMaterial> &magneticMaterialList);
    
    void getElectricalLocalMaterialList(std::vector<electrostaticMaterial> &electricalMaterialList);
    
private:
    wxDECLARE_EVENT_TABLE();
};


#endif
