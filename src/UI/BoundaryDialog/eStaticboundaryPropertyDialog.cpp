#include <UI/BoundaryDialog/EstaticboundaryPropertyDialog.h>


electricalStaticBoundaryDialog::electricalStaticBoundaryDialog() : wxDialog(NULL, wxID_ANY, "Boundary Property")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *bcSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer *fixedVoltageSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Fixed Voltage");
    fixedVoltageSizer->GetStaticBox()->SetFont(*font);
    wxStaticBoxSizer *surfaceChargeSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Surface Charge Density");
    surfaceChargeSizer->GetStaticBox()->SetFont(*font);
    wxStaticBoxSizer *mixedBCSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Mixed BC Parameters");
    mixedBCSizer->GetStaticBox()->SetFont(*font);
    wxBoxSizer *c0Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *c1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    BCNameArray->Add("Fixed Voltage");
    BCNameArray->Add("Surface Charge Density");
    BCNameArray->Add("Mixed");
    BCNameArray->Add("Periodic");
    BCNameArray->Add("Anti-Periodic");
    
    _boundary.setBoundaryName("New Boundary");
    _boundary.setBC(bcEnumElectroStatic::FIXED_VOLTAGE);
    _boundary.setC0(0);
    _boundary.setC1(0);
    _boundary.setSigma(0);
    _boundary.setVoltage(0);
    
    wxStaticText *nameText = new wxStaticText(this, wxID_ANY, "Name:", wxPoint(12, 15), wxSize(38, 13));
    nameText->SetFont(*font);
    nameTextCtrl->Create(this, wxID_ANY, "New Boundary", wxPoint(69, 12), wxSize(168, 20));
    nameTextCtrl->SetFont(*font);
    headerSizer->Add(nameText, 0, wxCENTER | wxALL, 6);
    headerSizer->Add(14, 0, 0);
    headerSizer->Add(nameTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *bcName = new wxStaticText(this, wxID_ANY, "BC Type:", wxPoint(12, 41), wxSize(51, 13));
    bcName->SetFont(*font);
    BCComboBox->Create(this, generalFrameButton::ID_ComboBox1, wxEmptyString, wxPoint(69, 38), wxSize(170, 21), *BCNameArray);
    BCComboBox->SetFont(*font);
    BCComboBox->SetSelection(0);
    bcSizer->Add(bcName, 0, wxCENTER | wxRIGHT | wxBOTTOM | wxLEFT, 6);
    bcSizer->Add(BCComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    fixedVoltageTextCtrl->Create(fixedVoltageSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxPoint(6, 19), wxSize(210, 20));
    fixedVoltageTextCtrl->SetFont(*font);
    fixedVoltageSizer->Add(fixedVoltageTextCtrl, 0, wxCENTER | wxALL, 6);
    
    surfaceChargeTextCtrl->Create(surfaceChargeSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxPoint(6, 19), wxSize(210, 20));
    surfaceChargeTextCtrl->SetFont(*font);
    surfaceChargeSizer->Add(surfaceChargeTextCtrl, 0, wxCENTER | wxALL, 6);
    
    wxStaticText *c0Name = new wxStaticText(mixedBCSizer->GetStaticBox(), wxID_ANY, "C0 Coefficient:", wxPoint(6, 25), wxSize(82, 13));
    c0Name->SetFont(*font);
    c0TextCtrl->Create(mixedBCSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxPoint(90, 22), wxSize(122, 20));
    c0TextCtrl->SetFont(*font);
    c0Sizer->Add(c0Name, 0, wxCENTER | wxALL, 6);
    c0Sizer->Add(c0TextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *c1Name = new wxStaticText(mixedBCSizer->GetStaticBox(), wxID_ANY, "C1 Coefficient:", wxPoint(6, 51), wxSize(82, 13));
    c1Name->SetFont(*font);
    c1TextCtrl->Create(mixedBCSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxPoint(90, 48), wxSize(122, 20));
    c1TextCtrl->SetFont(*font);
    c1Sizer->Add(c1Name, 0, wxCENTER | wxALL, 6);
    c1Sizer->Add(c1TextCtrl, 0, wxCENTER | wxBOTTOM | wxTOP | wxRIGHT, 6);
    
    mixedBCSizer->Add(c0Sizer);
    mixedBCSizer->Add(c1Sizer);
    
    wxButton *okButton  = new wxButton(this, wxID_OK, "Ok", wxPoint(59, 278), wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(140, 278), wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxALL, 6);
    footerSizer->Add(cancelButton, 0, wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    topSizer->Add(headerSizer);
    topSizer->Add(bcSizer);
    topSizer->Add(fixedVoltageSizer, 0, wxLEFT | wxRIGHT | wxBOTTOM, 6);
    topSizer->Add(surfaceChargeSizer, 0, wxLEFT | wxRIGHT | wxBOTTOM, 6);
    topSizer->Add(mixedBCSizer, 0, wxLEFT | wxRIGHT, 6);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT, 6);
    
    updateInterface();
    
    SetSizerAndFit(topSizer);
}



void electricalStaticBoundaryDialog::setBoundaryCondition(electricalBoundary &boundary)
{
    _boundary = boundary;
    
    updateInterface();
}



void electricalStaticBoundaryDialog::getBoundaryCondition(electricalBoundary &boundary)
{
    double value;
    
    boundary.setBoundaryName(nameTextCtrl->GetValue().ToStdString());
    
    boundary.setBC((bcEnumElectroStatic)BCComboBox->GetSelection());
    
    fixedVoltageTextCtrl->GetValue().ToDouble(&value);
    boundary.setVoltage(value);
    
    surfaceChargeTextCtrl->GetValue().ToDouble(&value);
    boundary.setSigma(value);
    
    c0TextCtrl->GetValue().ToDouble(&value);
    boundary.setC0(value);
    
    c1TextCtrl->GetValue().ToDouble(&value);
    boundary.setC1(value);
}



void electricalStaticBoundaryDialog::clearBoundary()
{
    _boundary.setBoundaryName("New Boundary");
    _boundary.setBC(bcEnumElectroStatic::FIXED_VOLTAGE);
    _boundary.setC0(0);
    _boundary.setC1(0);
    _boundary.setSigma(0);
    _boundary.setVoltage(0);
    
    updateInterface();
}



void electricalStaticBoundaryDialog::onComboBox(wxCommandEvent &event)
{
    bcEnumElectroStatic selection = (bcEnumElectroStatic)BCComboBox->GetSelection();
    
    if(selection == bcEnumElectroStatic::FIXED_VOLTAGE)
    {
        fixedVoltageTextCtrl->Enable(true);
        surfaceChargeTextCtrl->Enable(false);
        c0TextCtrl->Enable(false);
        c1TextCtrl->Enable(false);
    }
    else if(selection == bcEnumElectroStatic::SURFACE_CHARGE_DENSITY)
    {
        fixedVoltageTextCtrl->Enable(false);
        surfaceChargeTextCtrl->Enable(true);
        c0TextCtrl->Enable(false);
        c1TextCtrl->Enable(false);
    }
    else if(selection == bcEnumElectroStatic::E_STATIC_MIXED)
    {
        fixedVoltageTextCtrl->Enable(false);
        surfaceChargeTextCtrl->Enable(false);
        c0TextCtrl->Enable(true);
        c1TextCtrl->Enable(true);
    }
    else
    {
        fixedVoltageTextCtrl->Enable(false);
        surfaceChargeTextCtrl->Enable(false);
        c0TextCtrl->Enable(false);
        c1TextCtrl->Enable(false); 
    }
}



void electricalStaticBoundaryDialog::updateInterface()
{
    std::ostream fixedVoltageStream(fixedVoltageTextCtrl);
    std::ostream surfaceChargeStream(surfaceChargeTextCtrl);
    std::ostream c0Stream(c0TextCtrl);
    std::ostream c1Stream(c1TextCtrl);
    
    nameTextCtrl->SetValue(_boundary.getBoundaryName());
    
    BCComboBox->SetSelection((int)_boundary.getBC());
    
    fixedVoltageTextCtrl->SetValue(wxEmptyString);
    fixedVoltageStream << std::setprecision(7);
    fixedVoltageStream << _boundary.getVoltage();
    
    surfaceChargeTextCtrl->SetValue(wxEmptyString);
    surfaceChargeStream << std::setprecision(7);
    surfaceChargeStream << _boundary.getSigma();
    
    c0TextCtrl->SetValue(wxEmptyString);
    c0Stream << std::setprecision(7);
    c0Stream << _boundary.getC0Value();
    
    c1TextCtrl->SetValue(wxEmptyString);
    c1Stream << std::setprecision(7);
    c1Stream << _boundary.getC1Value();
    
    if(_boundary.getBC() == bcEnumElectroStatic::FIXED_VOLTAGE)
    {
        fixedVoltageTextCtrl->Enable(true);
        surfaceChargeTextCtrl->Enable(false);
        c0TextCtrl->Enable(false);
        c1TextCtrl->Enable(false);
    }
    else if(_boundary.getBC() == bcEnumElectroStatic::SURFACE_CHARGE_DENSITY)
    {
        fixedVoltageTextCtrl->Enable(false);
        surfaceChargeTextCtrl->Enable(true);
        c0TextCtrl->Enable(false);
        c1TextCtrl->Enable(false);
    }
    else if(_boundary.getBC() == bcEnumElectroStatic::E_STATIC_MIXED)
    {
        fixedVoltageTextCtrl->Enable(false);
        surfaceChargeTextCtrl->Enable(false);
        c0TextCtrl->Enable(true);
        c1TextCtrl->Enable(true);
    }
    else
    {
        fixedVoltageTextCtrl->Enable(false);
        surfaceChargeTextCtrl->Enable(false);
        c0TextCtrl->Enable(false);
        c1TextCtrl->Enable(false); 
    }
}



electricalStaticBoundaryDialog::~electricalStaticBoundaryDialog()
{
    
}


wxBEGIN_EVENT_TABLE(electricalStaticBoundaryDialog, wxDialog)
    EVT_COMBOBOX(generalFrameButton::ID_ComboBox1, electricalStaticBoundaryDialog::onComboBox)
wxEND_EVENT_TABLE()