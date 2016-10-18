#include <UI/PropertiesDialog.h>


propertiesDialog::propertiesDialog() : wxDialog()
{
    
}



void propertiesDialog::drawInitial()
{
    
    this->SetClientSize(233, 142);
    wxFont *font = new wxFont(8.25,  wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxButton *addProp = new wxButton(this, wxID_ANY, "Add Property", wxPoint(12, 49), wxSize(114, 23));
    wxButton *deleteProp = new wxButton(this, wxID_ANY, "Delete Property", wxPoint(12, 78), wxSize(114, 23));
    wxButton *modifyProp = new wxButton(this, wxID_ANY, "Modify Property", wxPoint(12, 107), wxSize(114, 23));
    wxButton *buttonOk = new wxButton(this, wxID_OK, "Ok", wxPoint(146, 107), wxSize(75, 23));
    
    wxStaticText *nameText = new wxStaticText(this, wxID_ANY, "Name: ", wxPoint(12, 9), wxSize(38, 13));
    this->Show();
}