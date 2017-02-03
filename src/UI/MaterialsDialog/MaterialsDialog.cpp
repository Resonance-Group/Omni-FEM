#include <UI/MaterialsDialog/MaterialDialog.h>

materialDialog::materialDialog(std::vector<materialProperty> materialList) : wxFrame(NULL, wxID_ANY, "Material Definition", wxDefaultPosition, wxSize(233, 148))
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    _materialList = materialList;
    
    for(std::vector<materialProperty>::iterator materialIterator = _materialList.begin(); materialIterator != _materialList.end(); ++materialIterator)
    {
        materialNameArray->Add(wxString(materialIterator->getName()));
    }
    
    wxButton *addPropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonAdd, "Add Property", wxPoint(12, 49), wxSize(125, 26));
    
    wxButton *deletePropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonDelete, "Delete Property", wxPoint(12, 78), wxSize(125, 26));
    
    wxButton *modifyPropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonModify, "Modify Property", wxPoint(12, 107), wxSize(125, 26));
    
    wxButton *okButton = new wxButton(this, propertiesDialogEnum::ID_ButtonOk, "OK", wxPoint(146, 107), wxSize(75, 23));
    
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name: ", wxPoint(12, 9), wxSize(38, 13));
    name->SetFont(*font);
    
    selection->Create(this, wxID_ANY, wxEmptyString, wxPoint(56, 6), wxSize(165, 21), *materialNameArray);
    selection->SetFont(*font);
    
    this->FitInside();
    this->SetMinSize(this->GetSize());
    this->SetMaxSize(this->GetSize());
    
 //   Bind(MAGNETIC_MATERIAL_EVT_TYPE, &materialDialog::onAddMaterialEvent, this, CustomEvent::MagneticMaterial);
}



void materialDialog::onOk(wxCommandEvent &event)
{
    // Fire an event in order to save the local list into the global list
}



void materialDialog::onAddProperty(wxCommandEvent &event)
{
    magneticMaterial newMat;
    if(newMaterial->ShowModal() == wxID_OK)
    {
        newMaterial->getNewMaterial(newMat);
        _materialList.push_back(newMat);
        selection->Append(newMat.getName());
    }
} 



void materialDialog::onDeleteProperty(wxCommandEvent &event)
{
    
}



void materialDialog::onModifyProperty(wxCommandEvent &event)
{
    if(_materialList.size() > 0)
    {
        // show some stuff
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