#include <UI/MaterialsDialog/BlockPropertyDialogElectrostatic.h>

blockPropertyDialogElectrostatic::blockPropertyDialogElectrostatic() : wxDialog(NULL, wxID_ANY, "Electrostatic Material")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *relativeXSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *relativeYSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *chargeDensitySizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name:", wxPoint(12, 15), wxSize(38, 13));
    name->SetFont(*font);
    _name->Create(this, wxID_ANY, _material.getName(), wxPoint(56, 12), wxSize(165, 20));
    _name->SetFont(*font);
    
    headerSizer->Add(name, 0, wxCENTER | wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 6);
    headerSizer->Add(_name, 0, wxCENTER | wxRIGHT | wxTOP | wxBOTTOM, 6);
    
    wxStaticText *relativeXText = new wxStaticText(this, wxID_ANY, wxT("Relative εx:"), wxPoint(12, 50), wxSize(66, 13));
    relativeXText->SetFont(*font);
    _relativeEpiXTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxPoint(100, 47), wxSize(106, 20));
    std::ostream relativeXStream(_relativeEpiXTextCtrl);
    relativeXStream << std::setprecision(3);
    relativeXStream << _material.getEpsilonX();
    _relativeEpiXTextCtrl->SetFont(*font);
    relativeXSizer->Add(relativeXText, 0, wxLEFT | wxTOP | wxBOTTOM | wxRIGHT | wxCENTER, 6);
    relativeXSizer->Add(24, 0, 0);
    relativeXSizer->Add(_relativeEpiXTextCtrl, 0, wxLEFT | wxTOP | wxBOTTOM | wxRIGHT | wxCENTER, 6);
    
    wxStaticText *relativeYText = new wxStaticText(this, wxID_ANY, wxT("Relative εy:"), wxPoint(12, 76), wxSize(66, 13));
    relativeYText->SetFont(*font);
    _relativeEpiYTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxPoint(100, 73), wxSize(106, 20));
    std::ostream relativeYStream(_relativeEpiYTextCtrl);
    relativeYStream << std::setprecision(3);
    relativeYStream << _material.getEpsilonY();
    _relativeEpiYTextCtrl->SetFont(*font);
    relativeYSizer->Add(relativeYText, 0, wxLEFT | wxBOTTOM | wxRIGHT | wxCENTER, 6);
    relativeYSizer->Add(29, 0, 0);
    relativeYSizer->Add(_relativeEpiYTextCtrl, 0, wxBOTTOM | wxRIGHT | wxCENTER, 6);
    
    wxStaticText *chargeDensityName = new wxStaticText(this, wxID_ANY, "Charge Density:", wxPoint(12, 102), wxSize(95, 13));
    chargeDensityName->SetFont(*font);
    _chargeDensityTextCtrl->Create(this, wxID_ANY, std::to_string(_material.getChargeDensity()), wxPoint(100, 99), wxSize(106, 20));
    std::ostream chargeStream(_chargeDensityTextCtrl);
    chargeStream << std::setprecision(3);
    chargeStream << _material.getChargeDensity();
    _chargeDensityTextCtrl->SetFont(*font);
    chargeDensitySizer->Add(chargeDensityName, 0, wxLEFT | wxRIGHT | wxCENTER, 6);
    chargeDensitySizer->Add(_chargeDensityTextCtrl, 0, wxRIGHT | wxCENTER, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxPoint(52, 136), wxSize(75, 23));
    okButton->SetFont(*font);
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(133, 136), wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxRIGHT | wxLEFT | wxTOP | wxBOTTOM, 6);
    footerSizer->Add(cancelButton, 0, wxRIGHT | wxBOTTOM | wxTOP, 6);
    
    topSizer->Add(headerSizer);
    topSizer->Add(relativeXSizer);
    topSizer->Add(relativeYSizer);
    topSizer->Add(chargeDensitySizer);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);

    SetSizerAndFit(topSizer);
}



void blockPropertyDialogElectrostatic::getMaterial(electrostaticMaterial &material)
{
    double value;
    
    material.setName(_name->GetValue().ToStdString());
    
    _relativeEpiXTextCtrl->GetValue().ToDouble(&value);
    material.setEpsilonX(value);
    
    _relativeEpiYTextCtrl->GetValue().ToDouble(&value);
    material.setEpsilonY(value);
    
    _chargeDensityTextCtrl->GetValue().ToDouble(&value);
    material.setChargeDensity(value);
}



void blockPropertyDialogElectrostatic::clearMaterial()
{
    _material.setEpsilonX(1);
    _material.setEpsilonY(1);
    _material.setName("New Material");
    _material.setChargeDensity(0);
    
    setTextBox();
}




void blockPropertyDialogElectrostatic::setMaterial(electrostaticMaterial &material)
{
    _material = material;
    setTextBox();
}



void blockPropertyDialogElectrostatic::setTextBox()
{
    std::ostream relativeXStream(_relativeEpiXTextCtrl);
    std::ostream relativeYStream(_relativeEpiYTextCtrl);
    std::ostream chargeStream(_chargeDensityTextCtrl);
    
    _name->SetValue(_material.getName());
    
    _relativeEpiXTextCtrl->SetValue(wxEmptyString);
    relativeXStream << std::setprecision(3);
    relativeXStream << _material.getEpsilonX();
    
    _relativeEpiYTextCtrl->SetValue(wxEmptyString);
    relativeYStream << std::setprecision(3);
    relativeYStream << _material.getEpsilonY();
    
    _chargeDensityTextCtrl->SetValue(wxEmptyString);
    chargeStream << std::setprecision(3);
    chargeStream << _material.getChargeDensity();
}



blockPropertyDialogElectrostatic::~blockPropertyDialogElectrostatic()
{
    
}