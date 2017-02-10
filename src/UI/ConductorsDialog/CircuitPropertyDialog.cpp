#include <UI/ConductorsDialog/ConductorPropertyDialog.h>

circuitPropertyDialog::circuitPropertyDialog() : wxDialog(NULL, wxID_ANY, "Circuit Property")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxSizer *headerSizer = new wxSizer(wxHORIZONTAL);
    wxSizer *radioSizer = new wxSizer(wxVERTICAL);
    
    _circuitProperty.setCurrent(0.0);
    _circuitProperty.setName("New Circuit");
    
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name: ", wxPoint(12, 15), wxSize(38, 13));
    nameTextCtrl->Create(this, wxID_ANY, wxPoint(56, 12), wxSize(197, 20));

}


void circuitPropertyDialog::getNewCircuit(circuitProperty &newCircuit)
{
    
}



void circuitPropertyDialog::setCircuit(circuitProperty &circuit)
{
    
}



void circuitPropertyDialog::clearCircuit()
{
    
}



circuitPropertyDialog::~circuitPropertyDialog()
{
    
}

