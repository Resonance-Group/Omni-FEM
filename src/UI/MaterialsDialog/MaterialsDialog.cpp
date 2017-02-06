#include <UI/MaterialsDialog/MaterialDialog.h>

materialDialog::materialDialog(std::vector<magneticMaterial> materialList) : wxFrame(NULL, wxID_ANY, "Material Definition", wxDefaultPosition, wxSize(233, 148))
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
    
    wxButton *okButton = new wxButton(this, propertiesDialogEnum::ID_ButtonOk, "OK", wxPoint(146, 107), wxSize(75, 23));
    
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name: ", wxPoint(12, 9), wxSize(38, 13));
    name->SetFont(*font);
    
    selection->Create(this, wxID_ANY, wxEmptyString, wxPoint(56, 6), wxSize(165, 21), *magneticMaterialNameArray);
    selection->SetFont(*font);
    
    this->FitInside();
    this->SetMinSize(this->GetSize());
    this->SetMaxSize(this->GetSize());
}



void materialDialog::onOk(wxCommandEvent &event)
{
    // Fire an event in order to save the local list into the global list
}



void materialDialog::onAddProperty(wxCommandEvent &event)
{
    magneticMaterial newMat;
    magneticMaterialPropertyDialog->clearMaterial();
    if(magneticMaterialPropertyDialog->ShowModal() == wxID_OK)
    {
        magneticMaterialPropertyDialog->getNewMaterial(newMat);
        _magneticMaterialList.push_back(newMat);
        selection->Append(newMat.getName());
        selection->SetSelection(0);
    }
} 



void materialDialog::onDeleteProperty(wxCommandEvent &event)
{
    
}



void materialDialog::onModifyProperty(wxCommandEvent &event)
{
    magneticMaterial selectedMaterial;
    //magneticMaterial test;
    if(_magneticMaterialList.size() > 0)
    {
        int currentSelection = selection->GetSelection();
        selectedMaterial = _magneticMaterialList.at(currentSelection);
        magneticMaterialPropertyDialog->setMaterial(selectedMaterial);
        if(magneticMaterialPropertyDialog->ShowModal() == wxID_OK)
        {
            // Do some stuff
        }
    }
}



void materialDialog::updateComboBox()
{
    
}

materialDialog::~materialDialog()
{
    
}

wxBEGIN_EVENT_TABLE(materialDialog, wxFrame)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonOk, materialDialog::onOk)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonAdd, materialDialog::onAddProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonDelete, materialDialog::onDeleteProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonModify, materialDialog::onModifyProperty)
wxEND_EVENT_TABLE()