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

class materialLibraryDialog : public wxDialog
{
private:
    std::vector<electrostaticMaterial> _electricalMaterialList;
    
    std::vector<magneticMaterial> _magneticMaterialList;

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
    materialLibraryDialog(wxWindow *par, std::vector<electrostaticMaterial> &material);
    
    materialLibraryDialog(wxWindow *par, std::vector<magneticMaterial> &material);
    
    void getMagneticLocalMaterialList(std::vector<magneticMaterial> &magneticMaterialList);
    
    void getElectricalLocalMaterialList(std::vector<electrostaticMaterial> &electricalMaterialList);
    
private:
    wxDECLARE_EVENT_TABLE();
};


#endif
