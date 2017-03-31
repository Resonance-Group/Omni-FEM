#include <UI/ConductorsDialog/ConductorPropertyDialog.h>


conductorPropertyDialog::conductorPropertyDialog(wxWindow *par) : wxDialog(par, wxID_ANY, "Conductor Property")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *totalChargeSize = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *voltageSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *intermediateSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    _conductorProperty.setValue(0);
    _conductorProperty.setIsTotalChargeState(true);
    _conductorProperty.setName("New Conductor");
    
    /* Creating the header of the windows */
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name: ");
    name->SetFont(*font);
    nameTextCtrl->Create(this, wxID_ANY, _conductorProperty.getName(), wxDefaultPosition, wxSize(226, 20));
    nameTextCtrl->SetFont(*font);
    
    headerSizer->Add(name, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 6);
    headerSizer->Add(nameTextCtrl, 0, wxALIGN_CENTER | wxTOP | wxRIGHT, 6);
    
    radioButton1->Create(this, generalFrameButton::ID_RadioButton1, "Total Charge (C):");
    radioButton1->SetFont(*font);
    radioButton1->SetValue(true);
    radioButton2->Create(this, generalFrameButton::ID_RadioButton2, "Prescribed Voltage (V):");
    radioButton2->SetFont(*font);
    radioButton2->SetValue(false);
    
    chargeTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(116, 20));
    chargeTextCtrl->SetFont(*font);
    voltageTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(116, 20));
    voltageTextCtrl->SetFont(*font);
    
    totalChargeSize->Add(radioButton1, 0, wxCENTER | wxALL, 6);
    totalChargeSize->Add(33, 0, 0);
    totalChargeSize->Add(chargeTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    voltageSizer->Add(radioButton2, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    voltageSizer->Add(voltageTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxDefaultPosition, wxSize(75, 23));
    okButton->SetFont(*font);
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxLEFT, 6);
    footerSizer->Add(cancelButton);
    
    topSizer->Add(headerSizer);
    topSizer->Add(totalChargeSize);
    topSizer->Add(voltageSizer);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    
    updateInterface();
    
    SetSizerAndFit(topSizer);
}



void conductorPropertyDialog::getNewConductor(conductorProperty &newConductor)
{
    double value = 0;
    
    newConductor.setName(nameTextCtrl->GetValue().ToStdString());
    
    if(radioButton1->GetValue())
    {
        chargeTextCtrl->GetValue().ToDouble(&value);
        newConductor.setValue(value);
    }
    else
    {
        voltageTextCtrl->GetValue().ToDouble(&value);
        newConductor.setValue(value);
    }
    
    newConductor.setIsTotalChargeState(radioButton1->GetValue());
}


void conductorPropertyDialog::setConductor(conductorProperty &conductor)
{
    _conductorProperty = conductor;
    updateInterface();
}



void conductorPropertyDialog::clearConductor()
{
    _conductorProperty.setValue(0);
    _conductorProperty.setIsTotalChargeState(true);
    _conductorProperty.setName("New Conductor");
    updateInterface();
}



void conductorPropertyDialog::updateInterface()
{
    std::ostream chargeStream(chargeTextCtrl);
    std::ostream voltageStream(voltageTextCtrl);
    
    nameTextCtrl->SetValue(_conductorProperty.getName());
    chargeTextCtrl->SetValue(wxEmptyString);
    voltageTextCtrl->SetValue(wxEmptyString);
    
    if(_conductorProperty.getIsTotalChargeState())
    {
        radioButton1->SetValue(true);
        radioButton2->SetValue(false);
        chargeTextCtrl->Enable(true);
        voltageTextCtrl->Enable(false);
        chargeStream << std::setprecision(5);
        voltageStream << std::setprecision(5);
        chargeStream << _conductorProperty.getValue();
        voltageStream << 0;
    }
    else
    {
        radioButton1->SetValue(false);
        radioButton2->SetValue(true);
        chargeTextCtrl->Enable(false);
        voltageTextCtrl->Enable(true);
        chargeStream << std::setprecision(5);
        voltageStream << std::setprecision(5);
        chargeStream << 0;
        voltageStream << _conductorProperty.getValue();
    }
}



void conductorPropertyDialog::onRadioButton1Click(wxCommandEvent &event)
{
    chargeTextCtrl->Enable(true);
    voltageTextCtrl->Enable(false);
}



void conductorPropertyDialog::onRadioButton2Click(wxCommandEvent &event)
{
    chargeTextCtrl->Enable(false);
    voltageTextCtrl->Enable(true);
}



conductorPropertyDialog::~conductorPropertyDialog()
{
    
}




wxBEGIN_EVENT_TABLE(conductorPropertyDialog, wxDialog)
    EVT_RADIOBUTTON(generalFrameButton::ID_RadioButton1, conductorPropertyDialog::onRadioButton1Click)
    EVT_RADIOBUTTON(generalFrameButton::ID_RadioButton2, conductorPropertyDialog::onRadioButton2Click)
wxEND_EVENT_TABLE()