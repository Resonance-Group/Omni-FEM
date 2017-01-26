#include <UI/MaterialsDialog/MaterialDialog.h>

materialDialog::materialDialog(std::vector<materialProperty> materialList) : wxFrame(NULL, wxID_ANY, "Material Definition", wxDefaultPosition, wxSize(233, 142))
{
    _materialList = materialList;
    
    for(std::vector<materialProperty>::iterator materialIterator = _materialList.begin(); materialIterator != _materialList.end(); ++materialIterator)
    {
        materialNameArray->Add(wxString(materialIterator->getName()));
    }
    
    wxButton *addPropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonAdd, "Add Property", wxPoint(12, 49), wxSize(114, 23));
    
    wxButton *deletePropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonDelete, "Delete Property", wxPoint(12, 78), wxSize(114, 23));
    
    wxButton *modifyPropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonModify, "Modify Property", wxPoint(12, 107), wxSize(114, 23));
    
    wxButton *okButton = new wxButton(this, propertiesDialogEnum::ID_ButtonOk, "OK", wxPoint(146, 107), wxSize(75, 23));
    
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name: ", wxPoint(12, 9), wxSize(38, 13));
    
    selection->Create(this, wxID_ANY, wxEmptyString, wxPoint(56, 6), wxSize(165, 21), *materialNameArray);
    
}

void materialDialog::onOk(wxCommandEvent &event)
{
    wxMessageBox("Success");
}

materialDialog::~materialDialog()
{
    
}

wxBEGIN_EVENT_TABLE(materialDialog, wxFrame)

    EVT_BUTTON(propertiesDialogEnum::ID_ButtonOk, materialDialog::onOk)

wxEND_EVENT_TABLE()