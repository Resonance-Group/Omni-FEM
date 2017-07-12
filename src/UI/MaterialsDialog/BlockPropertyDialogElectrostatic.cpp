#include <UI/MaterialsDialog/BlockPropertyDialogElectrostatic.h>

blockPropertyDialogElectrostatic::blockPropertyDialogElectrostatic(wxWindow *par) : wxDialog(par, wxID_ANY, "Electrostatic Material")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *relativeXSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *relativeYSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *chargeDensitySizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name:");
    name->SetFont(*font);
    _name->Create(this, wxID_ANY, _material.getName(), wxPoint(56, 12), wxSize(156, 20));
    _name->SetFont(*font);
    
    headerSizer->Add(name, 0, wxCENTER | wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 6);
    headerSizer->Add(_name, 0, wxCENTER | wxRIGHT | wxTOP | wxBOTTOM, 6);
    
    wxStaticText *relativeXText = new wxStaticText(this, wxID_ANY, wxT("Relative εx:"));
    relativeXText->SetFont(*font);
    _relativeEpiXTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(106, 20));
    std::ostream relativeXStream(_relativeEpiXTextCtrl);
    relativeXStream << std::setprecision(3);
    relativeXStream << _material.getEpsilonX();
    _relativeEpiXTextCtrl->SetFont(*font);
    relativeXSizer->Add(relativeXText, 0, wxLEFT | wxTOP | wxBOTTOM | wxRIGHT | wxCENTER, 6);
    relativeXSizer->Add(17, 0, 0);
    relativeXSizer->Add(_relativeEpiXTextCtrl, 0, wxLEFT | wxTOP | wxBOTTOM | wxRIGHT | wxCENTER, 6);
    
    wxStaticText *relativeYText = new wxStaticText(this, wxID_ANY, wxT("Relative εy:"));
    relativeYText->SetFont(*font);
    _relativeEpiYTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(106, 20));
    std::ostream relativeYStream(_relativeEpiYTextCtrl);
    relativeYStream << std::setprecision(3);
    relativeYStream << _material.getEpsilonY();
    _relativeEpiYTextCtrl->SetFont(*font);
    relativeYSizer->Add(relativeYText, 0, wxLEFT | wxBOTTOM | wxRIGHT | wxCENTER, 6);
    relativeYSizer->Add(24, 0, 0);
    relativeYSizer->Add(_relativeEpiYTextCtrl, 0, wxBOTTOM | wxRIGHT | wxCENTER, 6);
    
    wxStaticText *chargeDensityName = new wxStaticText(this, wxID_ANY, "Charge Density:");
    chargeDensityName->SetFont(*font);
    _chargeDensityTextCtrl->Create(this, wxID_ANY, std::to_string(_material.getChargeDensity()), wxDefaultPosition, wxSize(106, 20));
    std::ostream chargeStream(_chargeDensityTextCtrl);
    chargeStream << std::setprecision(3);
    chargeStream << _material.getChargeDensity();
    _chargeDensityTextCtrl->SetFont(*font);
    chargeDensitySizer->Add(chargeDensityName, 0, wxLEFT | wxRIGHT | wxCENTER, 6);
    chargeDensitySizer->Add(_chargeDensityTextCtrl, 0, wxRIGHT | wxCENTER, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxDefaultPosition, wxSize(75, 23));
    okButton->SetFont(*font);
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(75, 23));
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
    
    updateInterface();
}




void blockPropertyDialogElectrostatic::setMaterial(electrostaticMaterial &material)
{
    _material = material;
    updateInterface();
}



void blockPropertyDialogElectrostatic::updateInterface()
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