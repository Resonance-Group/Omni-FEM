#include <UI/MaterialsDialog/MaterialDialog.h>

materialDialog::materialDialog(std::vector<magneticMaterial> materialList) : wxDialog(NULL, wxID_ANY, "Material Definition", wxDefaultPosition, wxSize(233, 148))
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *propertySizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *okSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *intermediateSizer = new wxBoxSizer(wxHORIZONTAL);
    
    _magneticMaterialList = materialList;
    
    for(std::vector<magneticMaterial>::iterator materialIterator = _magneticMaterialList.begin(); materialIterator != _magneticMaterialList.end(); ++materialIterator)
    {
        magneticMaterialNameArray->Add(wxString(materialIterator->getName()));
    }
    
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name: ", wxPoint(12, 9), wxSize(38, 13));
    name->SetFont(*font);
    
    selection->Create(this, wxID_ANY, wxEmptyString, wxPoint(56, 5), wxSize(139, 21), *magneticMaterialNameArray);
    selection->SetFont(*font);
    
    headerSizer->Add(name, 0, wxALIGN_CENTER | wxLEFT, 6);
    headerSizer->Add(selection, 0, wxALIGN_CENTER);
    
    wxButton *addPropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonAdd, "Add Property", wxPoint(12, 43), wxSize(102, 23));
    addPropertyButton->SetFont(*font);
    
    wxButton *deletePropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonDelete, "Delete Property", wxPoint(12, 72), wxSize(102, 23));
    deletePropertyButton->SetFont(*font);
    
    wxButton *modifyPropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonModify, "Modify Property", wxPoint(12, 101), wxSize(102, 23));
    modifyPropertyButton->SetFont(*font);
    
    propertySizer->Add(addPropertyButton, 0, wxALIGN_TOP | wxLEFT, 6);
    propertySizer->Add(0, 6, 0);
    propertySizer->Add(deletePropertyButton, 0, wxALIGN_CENTER | wxLEFT, 6);
    propertySizer->Add(0, 6, 0);
    propertySizer->Add(modifyPropertyButton, 0, wxALIGN_BOTTOM | wxDOWN | wxLEFT, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "OK", wxPoint(120, 101), wxSize(75, 23));
    okButton->SetFont(*font);
    
    okSizer->Add(0, 58, 0);
    okSizer->Add(okButton, 0, wxALIGN_BOTTOM | wxDOWN | wxRIGHT, 6);
    
    intermediateSizer->Add(propertySizer, 0, wxALIGN_LEFT);
    intermediateSizer->Add(6, 0, 0);
    intermediateSizer->Add(okSizer, 0, wxALIGN_RIGHT);
    
    
    topSizer->Add(headerSizer, 0, wxALIGN_TOP);
    topSizer->Add(0, 10, 0);
    topSizer->Add(intermediateSizer, 0, wxALIGN_BOTTOM);
    
    SetSizerAndFit(topSizer);
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