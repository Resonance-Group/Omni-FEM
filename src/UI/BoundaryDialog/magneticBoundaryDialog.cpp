#include <UI/BoundaryDialog/MagneticBoundaryPropertyDiaglog.h>



magneticBoundaryDialog::magneticBoundaryDialog(wxWindow *par) : wxDialog(par, wxID_ANY, "Magnetic Boundary Property")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *bcTypeSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer *ssdpSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Small Skin Depth Parameters");
    ssdpSizer->GetStaticBox()->SetFont(*font);
    wxStaticBoxSizer *mixedBCSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Mixed BC Parameters");
    mixedBCSizer->GetStaticBox()->SetFont(*font);
    wxStaticBoxSizer *prescribedASizer = new wxStaticBoxSizer(wxVERTICAL, this, "Prescribed A Parameters");
    prescribedASizer->GetStaticBox()->SetFont(*font);
    wxBoxSizer *intermediateSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *allBCSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    _magneticBoundary.setA0(0);
    _magneticBoundary.setA1(0);
    _magneticBoundary.setA2(0);
    _magneticBoundary.setBC(bcEnumMagnetic::PRESCRIBE_A);
    _magneticBoundary.setBoundaryName("New Boundary");
    _magneticBoundary.setC0(0);
    _magneticBoundary.setC1(0);
    _magneticBoundary.setMu(0);
    _magneticBoundary.setPhi(0);
    _magneticBoundary.setSigma(0);
    
    /* This first section is for the header of the dialog */
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name:");
    name->SetFont(*font);
    nameTextCtrl->Create(this, wxID_ANY, _magneticBoundary.getBoundaryName(), wxDefaultPosition, wxSize(289, 20));
    nameTextCtrl->SetFont(*font);
    headerSizer->Add(name, 0, wxCENTER | wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 6);
    headerSizer->Add(10, 0, 0);
    headerSizer->Add(nameTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *BCTypeName = new wxStaticText(this, wxID_ANY, "BC Type:");
    BCTypeName->SetFont(*font);
    
    BCNameArray->Add("Prescribed A");
    BCNameArray->Add("Small Skin Depth");
    BCNameArray->Add("Mixed");
    BCNameArray->Add("Strategic Dual Image");
    BCNameArray->Add("Periodic");
    BCNameArray->Add("Anti-Periodic");
    
    BCComboBox->Create(this, generalFrameButton::ID_ComboBox1, wxEmptyString, wxDefaultPosition, wxSize(289, 22), *BCNameArray);
    BCComboBox->SetFont(*font);
    BCComboBox->SetSelection(0);
    bcTypeSizer->Add(BCTypeName, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    bcTypeSizer->Add(BCComboBox, 0, wxCENTER | wxRIGHT | wxBOTTOM, 6);
    
    /* This second part is for creating the Small skin Depth group box area */
    wxBoxSizer *uRelativeSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *sigSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *uRelativeText = new wxStaticText(ssdpSizer->GetStaticBox(), wxID_ANY, wxT("μ relative:"));
    uRelativeText->SetFont(*font);
    wxStaticText *sigText = new wxStaticText(ssdpSizer->GetStaticBox(), wxID_ANY, wxT("σ MS/m:"));
    sigText->SetFont(*font);
    uRelativeTextCtrl->Create(ssdpSizer->GetStaticBox(), wxID_ANY, std::to_string(_magneticBoundary.getMu()), wxDefaultPosition, wxSize(88, 20));
    uRelativeTextCtrl-SetFont(*font);
    sigTextCtrl->Create(ssdpSizer->GetStaticBox(), wxID_ANY, std::to_string(_magneticBoundary.getSigma()), wxDefaultPosition, wxSize(88, 20));
    sigTextCtrl->SetFont(*font);
    uRelativeSizer->Add(uRelativeText, 0, wxCENTER | wxALL, 6);
    uRelativeSizer->Add(24, 0, 0);
    uRelativeSizer->Add(uRelativeTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    sigSizer->Add(sigText, 0, wxCENTER | wxRIGHT | wxBOTTOM | wxLEFT, 6);
    sigSizer->Add(35, 0, 0);
    sigSizer->Add(sigTextCtrl, 0, wxBOTTOM | wxCENTER | wxRIGHT, 6);
    ssdpSizer->Add(uRelativeSizer);
    ssdpSizer->Add(sigSizer);
    
    /* The third section is for the Mixed BC Parameters */
    wxBoxSizer *c0Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *c1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *c0Text = new wxStaticText(mixedBCSizer->GetStaticBox(), wxID_ANY, wxT("C0 Coefficient:"));
    c0Text->SetFont(*font);
    wxStaticText *c1Text = new wxStaticText(mixedBCSizer->GetStaticBox(), wxID_ANY, wxT("C1 Coefficient:"));
    c1Text->SetFont(*font);
    c1TextCtrl->Create(mixedBCSizer->GetStaticBox(), wxID_ANY, std::to_string(_magneticBoundary.getC0Value()), wxDefaultPosition, wxSize(88, 20));
    c1TextCtrl-SetFont(*font);
    c0TextCtrl->Create(mixedBCSizer->GetStaticBox(), wxID_ANY, std::to_string(_magneticBoundary.getC1Value()), wxDefaultPosition, wxSize(88, 20));
    c0TextCtrl->SetFont(*font);
    c0Sizer->Add(c0Text, 0, wxCENTER | wxALL, 6);
    c0Sizer->Add(c0TextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    c1Sizer->Add(c1Text, 0, wxCENTER | wxRIGHT | wxBOTTOM | wxLEFT , 6);
    c1Sizer->Add(c1TextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    mixedBCSizer->Add(c0Sizer);
    mixedBCSizer->Add(c1Sizer);
    
    intermediateSizer->Add(ssdpSizer);
    intermediateSizer->Add(mixedBCSizer);
    
    /* This fourth section is for the Prescribed A Parameters */
    wxBoxSizer *A0Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *A1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *A2Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *phiSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *A0Text = new wxStaticText(prescribedASizer->GetStaticBox(), wxID_ANY, wxT("A0:"));
    A0Text->SetFont(*font);
    wxStaticText *A1Text = new wxStaticText(prescribedASizer->GetStaticBox(), wxID_ANY, wxT("A1:"));
    A1Text->SetFont(*font);
    wxStaticText *A2Text = new wxStaticText(prescribedASizer->GetStaticBox(), wxID_ANY, wxT("A2:"));
    A2Text->SetFont(*font);
    wxStaticText *phiText = new wxStaticText(prescribedASizer->GetStaticBox(), wxID_ANY, wxT("ϕ deg:"));
    phiText->SetFont(*font);
    A0TextCtrl->Create(prescribedASizer->GetStaticBox(), wxID_ANY, std::to_string(_magneticBoundary.getA0()), wxDefaultPosition, wxSize(88, 20));
    A0TextCtrl-SetFont(*font);
    A1TextCtrl->Create(prescribedASizer->GetStaticBox(), wxID_ANY, std::to_string(_magneticBoundary.getA1()), wxDefaultPosition, wxSize(88, 20));
    A1TextCtrl->SetFont(*font);
    A2TextCtrl->Create(prescribedASizer->GetStaticBox(), wxID_ANY, std::to_string(_magneticBoundary.getA2()), wxDefaultPosition, wxSize(88, 20));
    A2TextCtrl->SetFont(*font);
    phiTextCtrl->Create(prescribedASizer->GetStaticBox(), wxID_ANY, std::to_string(_magneticBoundary.getPhi()), wxDefaultPosition, wxSize(88, 20));
    phiTextCtrl->SetFont(*font);
    
    A0Sizer->Add(A0Text, 0, wxCENTER | wxALL, 6);
    A0Sizer->Add(17, 0, 0);
    A0Sizer->Add(A0TextCtrl, 0, wxCENTER | wxRIGHT | wxBOTTOM | wxTOP, 6);
    
    A1Sizer->Add(A1Text, 0, wxCENTER | wxALL, 6);
    A1Sizer->Add(17, 0, 0);
    A1Sizer->Add(A1TextCtrl, 0, wxCENTER | wxRIGHT | wxBOTTOM | wxTOP, 6);
    
    A2Sizer->Add(A2Text, 0, wxCENTER | wxALL, 6);
    A2Sizer->Add(17, 0, 0);
    A2Sizer->Add(A2TextCtrl, 0, wxCENTER | wxRIGHT | wxBOTTOM | wxTOP, 6);
    
    phiSizer->Add(phiText, 0, wxCENTER | wxALL, 6);
    phiSizer->Add(phiTextCtrl, 0, wxCENTER | wxRIGHT | wxBOTTOM | wxTOP, 6);
    
    prescribedASizer->Add(A0Sizer);
    prescribedASizer->Add(0, 2, 0);
    prescribedASizer->Add(A1Sizer);
    prescribedASizer->Add(0, 2, 0);
    prescribedASizer->Add(A2Sizer);
    prescribedASizer->Add(0, 2, 0);
    prescribedASizer->Add(phiSizer);
    prescribedASizer->Add(0, 1, 0);
    
    allBCSizer->Add(intermediateSizer, 0, wxRIGHT | wxLEFT, 6);
    allBCSizer->Add(prescribedASizer, 0, wxRIGHT, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxDefaultPosition, wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxTOP | wxBOTTOM | wxRIGHT, 6);
    footerSizer->Add(cancelButton, 0, wxRIGHT | wxBOTTOM | wxTOP, 6);
    
    topSizer->Add(headerSizer);
    topSizer->Add(bcTypeSizer);
    topSizer->Add(allBCSizer);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    uRelativeTextCtrl->Enable(false);
    sigTextCtrl->Enable(false);
    c0TextCtrl->Enable(false);
    c1TextCtrl->Enable(false);
    A0TextCtrl->Enable(true);
    A1TextCtrl->Enable(true);
    A2TextCtrl->Enable(true);
    phiTextCtrl->Enable(true);
    
    SetSizerAndFit(topSizer);
}



void magneticBoundaryDialog::onBCComboChange(wxCommandEvent &event)
{
    if(BCComboBox->GetSelection() == (int)bcEnumMagnetic::PRESCRIBE_A)
    {
        uRelativeTextCtrl->Enable(false);
        sigTextCtrl->Enable(false);
        c0TextCtrl->Enable(false);
        c1TextCtrl->Enable(false);
        A0TextCtrl->Enable(true);
        A1TextCtrl->Enable(true);
        A2TextCtrl->Enable(true);
        phiTextCtrl->Enable(true);
    }
    else if(BCComboBox->GetSelection() == (int)bcEnumMagnetic::SMALL_SKIN_DEPTH)
    {
        uRelativeTextCtrl->Enable(true);
        sigTextCtrl->Enable(true);
        c0TextCtrl->Enable(false);
        c1TextCtrl->Enable(false);
        A0TextCtrl->Enable(false);
        A1TextCtrl->Enable(false);
        A2TextCtrl->Enable(false);
        phiTextCtrl->Enable(false);
    }
    else if(BCComboBox->GetSelection() == (int)bcEnumMagnetic::MIXED)
    {
        uRelativeTextCtrl->Enable(false);
        sigTextCtrl->Enable(false);
        c0TextCtrl->Enable(true);
        c1TextCtrl->Enable(true);
        A0TextCtrl->Enable(false);
        A1TextCtrl->Enable(false);
        A2TextCtrl->Enable(false);
        phiTextCtrl->Enable(false);
    }
    else
    {
        uRelativeTextCtrl->Enable(false);
        sigTextCtrl->Enable(false);
        c0TextCtrl->Enable(false);
        c1TextCtrl->Enable(false);
        A0TextCtrl->Enable(false);
        A1TextCtrl->Enable(false);
        A2TextCtrl->Enable(false);
        phiTextCtrl->Enable(false);
    }
}



void magneticBoundaryDialog::getBoundaryCondition(magneticBoundary &boundary)
{
    double value;
    boundary.setBoundaryName(nameTextCtrl->GetValue().ToStdString());
    
    boundary.setBC((bcEnumMagnetic)BCComboBox->GetSelection());
    
    uRelativeTextCtrl->GetValue().ToDouble(&value);
    boundary.setMu(value);
    
    sigTextCtrl->GetValue().ToDouble(&value);
    boundary.setSigma(value);
    
    c0TextCtrl->GetValue().ToDouble(&value);
    boundary.setC0(value);
    
    c1TextCtrl->GetValue().ToDouble(&value);
    boundary.setC1(value);
    
    A0TextCtrl->GetValue().ToDouble(&value);
    boundary.setA0(value);
    
    A1TextCtrl->GetValue().ToDouble(&value);
    boundary.setA1(value);
    
    A2TextCtrl->GetValue().ToDouble(&value);
    boundary.setA2(value);
    
    phiTextCtrl->GetValue().ToDouble(&value);
    boundary.setPhi(value);
    
}



void magneticBoundaryDialog::clearBoundary()
{
    _magneticBoundary.setA0(0);
    _magneticBoundary.setA1(0);
    _magneticBoundary.setA2(0);
    _magneticBoundary.setBC(bcEnumMagnetic::PRESCRIBE_A);
    _magneticBoundary.setBoundaryName("New Boundary");
    _magneticBoundary.setC0(0);
    _magneticBoundary.setC1(0);
    _magneticBoundary.setMu(0);
    _magneticBoundary.setPhi(0);
    _magneticBoundary.setSigma(0);
    
    updateInterface();
}



void magneticBoundaryDialog::setBoundaryCondition(magneticBoundary &boundary)
{
    _magneticBoundary = boundary;
    
    updateInterface();
}



void magneticBoundaryDialog::updateInterface()
{
    std::ostream relativeStream(uRelativeTextCtrl);
    std::ostream sigStream(sigTextCtrl);
    std::ostream c0Stream(c0TextCtrl);
    std::ostream c1Stream(c1TextCtrl);
    std::ostream A0Stream(A0TextCtrl);
    std::ostream A1Stream(A1TextCtrl);
    std::ostream A2Stream(A2TextCtrl);
    std::ostream phiStream(phiTextCtrl);
    
    nameTextCtrl->SetValue(_magneticBoundary.getBoundaryName());
    
    uRelativeTextCtrl->SetValue(wxEmptyString);
    relativeStream << setprecision(3);
    relativeStream << _magneticBoundary.getMu();
    
    sigTextCtrl->SetValue(wxEmptyString);
    sigStream << setprecision(3);
    sigStream << _magneticBoundary.getSigma();
    
    c0TextCtrl->SetValue(wxEmptyString);
    c0Stream << setprecision(3);
    c0Stream << _magneticBoundary.getC0Value();
    
    c1TextCtrl->SetValue(wxEmptyString);
    c1Stream << setprecision(3);
    c1Stream << _magneticBoundary.getC1Value();
    
    A0TextCtrl->SetValue(wxEmptyString);
    A0Stream << setprecision(3);
    A0Stream << _magneticBoundary.getA0();
    
    A1TextCtrl->SetValue(wxEmptyString);
    A1Stream << setprecision(3);
    A1Stream << _magneticBoundary.getA1();
    
    A2TextCtrl->SetValue(wxEmptyString);
    A2Stream << setprecision(3);
    A2Stream << _magneticBoundary.getA2();
    
    phiTextCtrl->SetValue(wxEmptyString);
    phiStream << setprecision(3);
    phiStream << _magneticBoundary.getPhi();
    
    BCComboBox->SetSelection((int)_magneticBoundary.getBC());
    
    if(BCComboBox->GetSelection() == (int)bcEnumMagnetic::PRESCRIBE_A)
    {
        uRelativeTextCtrl->Enable(false);
        sigTextCtrl->Enable(false);
        c0TextCtrl->Enable(false);
        c1TextCtrl->Enable(false);
        A0TextCtrl->Enable(true);
        A1TextCtrl->Enable(true);
        A2TextCtrl->Enable(true);
        phiTextCtrl->Enable(true);
    }
    else if(BCComboBox->GetSelection() == (int)bcEnumMagnetic::SMALL_SKIN_DEPTH)
    {
        uRelativeTextCtrl->Enable(true);
        sigTextCtrl->Enable(true);
        c0TextCtrl->Enable(false);
        c1TextCtrl->Enable(false);
        A0TextCtrl->Enable(false);
        A1TextCtrl->Enable(false);
        A2TextCtrl->Enable(false);
        phiTextCtrl->Enable(false);
    }
    else if(BCComboBox->GetSelection() == (int)bcEnumMagnetic::MIXED)
    {
        uRelativeTextCtrl->Enable(false);
        sigTextCtrl->Enable(false);
        c0TextCtrl->Enable(true);
        c1TextCtrl->Enable(true);
        A0TextCtrl->Enable(false);
        A1TextCtrl->Enable(false);
        A2TextCtrl->Enable(false);
        phiTextCtrl->Enable(false);
    }
    else
    {
        uRelativeTextCtrl->Enable(false);
        sigTextCtrl->Enable(false);
        c0TextCtrl->Enable(false);
        c1TextCtrl->Enable(false);
        A0TextCtrl->Enable(false);
        A1TextCtrl->Enable(false);
        A2TextCtrl->Enable(false);
        phiTextCtrl->Enable(false);
    }
}



magneticBoundaryDialog::~magneticBoundaryDialog()
{
    this->Close();
}



wxBEGIN_EVENT_TABLE(magneticBoundaryDialog, wxDialog)
    EVT_COMBOBOX(generalFrameButton::ID_ComboBox1, magneticBoundaryDialog::onBCComboChange)
wxEND_EVENT_TABLE()