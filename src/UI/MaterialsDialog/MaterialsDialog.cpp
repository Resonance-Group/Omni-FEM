#include <UI/MaterialsDialog/MaterialDialog.h>

materialDialog::materialDialog(std::vector<magneticMaterial> materialList) : wxDialog(NULL, wxID_ANY, "Material Definition", wxDefaultPosition, wxSize(233, 148))
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    _magneticMaterialList = materialList;
    
    for(std::vector<magneticMaterial>::iterator materialIterator = _magneticMaterialList.begin(); materialIterator != _magneticMaterialList.end(); ++materialIterator)
    {
        magneticMaterialNameArray->Add(wxString(materialIterator->getName()));
    }
    
    wxButton *addPropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonAdd, "Add Property", wxPoint(12, 49), wxSize(125, 26));
    
    wxButton *deletePropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonDelete, "Delete Property", wxPoint(12, 78), wxSize(125, 26));
    
    wxButton *modifyPropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonModify, "Modify Property", wxPoint(12, 107), wxSize(125, 26));
    
    wxButton *okButton = new wxButton(this, wxID_OK, "OK", wxPoint(146, 107), wxSize(75, 23));
    
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name: ", wxPoint(12, 9), wxSize(38, 13));
    name->SetFont(*font);
    
    selection->Create(this, wxID_ANY, wxEmptyString, wxPoint(56, 6), wxSize(165, 21), *magneticMaterialNameArray);
    selection->SetFont(*font);
    
    this->FitInside();
    this->SetMinSize(this->GetSize());
    this->SetMaxSize(this->GetSize());
}



void materialDialog::onAddProperty(wxCommandEvent &event)
{
    magneticMaterial newMat;
    magneticMaterialPropertyDialog->clearMaterial();
    if(magneticMaterialPropertyDialog->ShowModal() == wxID_OK)
    {
        magneticMaterialPropertyDialog->getNewMaterial(newMat);
        for(std::vector<magneticMaterial>::iterator materialIterator = _magneticMaterialList.begin();  materialIterator != _magneticMaterialList.end(); ++materialIterator)
        {
            if(materialIterator->getName() == newMat.getName())
            {
                wxMessageBox(newMat.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER); 
                break;
            }
        }
        _magneticMaterialList.push_back(newMat);
        selection->Append(newMat.getName());
        selection->SetSelection(0);
    }
} 



void materialDialog::onDeleteProperty(wxCommandEvent &event)
{
    if(_magneticMaterialList.size() > 0)
    {
        int currentSelection = selection->GetCurrentSelection();
        _magneticMaterialList.erase(_magneticMaterialList.begin() + currentSelection);
        selection->Delete(currentSelection);
        selection->SetSelection(0);
    }
}



void materialDialog::onModifyProperty(wxCommandEvent &event)
{
    magneticMaterial selectedMaterial;
    if(_magneticMaterialList.size() > 0)
    {
        int currentSelection = selection->GetSelection();
        selectedMaterial = _magneticMaterialList.at(currentSelection);
        magneticMaterialPropertyDialog->setMaterial(selectedMaterial);
        if(magneticMaterialPropertyDialog->ShowModal() == wxID_OK)
        {
            int i = 0;
            magneticMaterialPropertyDialog->getNewMaterial(selectedMaterial);
            for(std::vector<magneticMaterial>::iterator materialIterator = _magneticMaterialList.begin();  materialIterator != _magneticMaterialList.end();++materialIterator)
            {
                if(materialIterator->getName() == selectedMaterial.getName() && (i != currentSelection))
                {
                    wxMessageBox(selectedMaterial.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER); 
                    break;
                }
                i++;
            }
            _magneticMaterialList.at(currentSelection) = selectedMaterial;
            selection->SetString(currentSelection, selectedMaterial.getName());
            
        }
    }
}



std::vector<magneticMaterial> materialDialog::getMaterialList()
{
    return _magneticMaterialList;
}



materialDialog::~materialDialog()
{
    
}



wxBEGIN_EVENT_TABLE(materialDialog, wxDialog)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonAdd, materialDialog::onAddProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonDelete, materialDialog::onDeleteProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonModify, materialDialog::onModifyProperty)
wxEND_EVENT_TABLE()