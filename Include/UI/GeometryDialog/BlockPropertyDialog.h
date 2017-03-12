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

#include <common/ElectroStaticMaterial.h>
#include <common/MagneticMaterial.h>
#include <common/enums.h>
#include <common/GeometryProperties/BlockProperty.h>



class blockPropertyDialog : public wxDialog
{
private:
    physicProblems _problem;
    
    std::vector<magneticMaterial> _magneticMaterialList;
    
    std::vector<electrostaticMaterial> _electricalMaterialList;
    
    std::vector<circuitProperty> _circuitList;

    wxComboBox *_materialComboBox = new wxComboBox();
    
    wxCheckBox *_autoMeshCheckBox = new wxCheckBox();
    
    wxTextCtrl *_meshSizeTextCtrl = new wxTextCtrl();
    
    wxComboBox *_circuitComboBox = new wxComboBox();
    
    wxTextCtrl *_numberOfTurnsTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_magnetizationTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_groupTextCtrl = new wxTextCtrl();
    
    wxCheckBox *_externalRegionCheckbox = new wxCheckBox();
    
    wxCheckBox *_defaultCheckBox = new wxCheckBox();
    
    void onCheckAutoMesh(wxCommandEvent &event);
    
public:
    blockPropertyDialog(std::vector<magneticMaterial> material, std::vector<circuitProperty> circuit, blockProperty property, bool isAxisymmetric);
    
    blockPropertyDialog(std::vector<electrostaticMaterial> material, blockProperty property, bool isAxisymmetric);
    
    void getBlockProperty(blockProperty &property);
    
    ~blockPropertyDialog();
    
private:
    wxDECLARE_EVENT_TABLE();
};


#endif