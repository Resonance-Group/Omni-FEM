#include <UI/BoundaryDialog/MagneticBoundaryPropertyDiaglog.h>

magneticBoundaryDialog::magneticBoundaryDialog() : wxDialog(NULL, wxID_ANY, "Magnetic boundary Property", wxDefaultPosition, wxSize(376, 248))
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
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
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name:", wxPoint(12, 9), wxSize(38, 13));
    name->SetFont(*font);
    nameTextCtrl->Create(this, wxID_ANY, _magneticBoundary.getBoundaryName(),wxPoint(69, 6), wxSize(296, 20));
    nameTextCtrl->SetFont(*font);
    wxStaticText *BCTypeName = new wxStaticText(this, wxID_ANY, "BC Type:", wxPoint(12, 35), wxSize(51, 13));
    BCTypeName->SetFont(*font);
    
    BCNameArray->Add("Prescribed A");
    BCNameArray->Add("Small Skin Depth");
    BCNameArray->Add("Mixed");
    BCNameArray->Add("Strategic Dual Image");
    BCNameArray->Add("Periodic");
    BCNameArray->Add("Anti-Periodic");
    
    BCComboBox->Create(this, generalFrameButton::ID_ComboBox1, wxEmptyString, wxPoint(69, 32), wxSize(296, 20), *BCNameArray);
    BCComboBox->SetFont(*font);
    BCComboBox->SetSelection(0);
    
    /* This second part is for creating the Small skin Depth group box area */
    smallSkinDepthGroupBox->Create(this, wxID_ANY, "Small Skin Depth Parameters", wxPoint(12, 59), wxSize(188, 74));
    smallSkinDepthGroupBox->SetFont(*font);
    wxStaticText *uRelativeText = new wxStaticText(smallSkinDepthGroupBox, wxID_ANY, wxT("μ relative:"), wxPoint(6, 8), wxSize(56, 13));
    uRelativeText->SetFont(*font);
    wxStaticText *sigText = new wxStaticText(smallSkinDepthGroupBox, wxID_ANY, wxT("σ MS/m:"), wxPoint(6, 34), wxSize(55, 13));
    sigText->SetFont(*font);
    uRelativeTextCtrl->Create(smallSkinDepthGroupBox, wxID_ANY, std::to_string(_magneticBoundary.getMu()), wxPoint(86, 5), wxSize(88, 20));
    uRelativeTextCtrl-SetFont(*font);
    sigTextCtrl->Create(smallSkinDepthGroupBox, wxID_ANY, std::to_string(_magneticBoundary.getSigma()), wxPoint(86, 31), wxSize(88, 20));
    sigTextCtrl->SetFont(*font);
    
    /* The third section is for the Mixed BC Parameters */
    mixedBCGroupBox->Create(this, wxID_ANY, "Mixed BC Parameters", wxPoint(12, 139), wxSize(188, 74));
    mixedBCGroupBox->SetFont(*font);
    wxStaticText *c0Text = new wxStaticText(mixedBCGroupBox, wxID_ANY, wxT("C0 Coefficient:"), wxPoint(6, 8), wxSize(75, 13));
    c0Text->SetFont(*font);
    wxStaticText *c1Text = new wxStaticText(mixedBCGroupBox, wxID_ANY, wxT("C1 coefficient:"), wxPoint(6, 34), wxSize(75, 13));
    c1Text->SetFont(*font);
    c1TextCtrl->Create(mixedBCGroupBox, wxID_ANY, std::to_string(_magneticBoundary.getC0Value()), wxPoint(86, 5), wxSize(88, 20));
    c1TextCtrl-SetFont(*font);
    c0TextCtrl->Create(mixedBCGroupBox, wxID_ANY, std::to_string(_magneticBoundary.getC1Value()), wxPoint(86, 31), wxSize(88, 20));
    c0TextCtrl->SetFont(*font);
    
    /* This fourth section is for the PRescribed A Parameters */
    prescribedAGroupBox->Create(this, wxID_ANY, "Prescribed A Parameters", wxPoint(206, 59), wxSize(159, 154));
    prescribedAGroupBox->SetFont(*font);
    wxStaticText *A0Text = new wxStaticText(prescribedAGroupBox, wxID_ANY, wxT("A0:"), wxPoint(6, 8), wxSize(23, 13));
    A0Text->SetFont(*font);
    wxStaticText *A1Text = new wxStaticText(prescribedAGroupBox, wxID_ANY, wxT("A1:"), wxPoint(6, 43), wxSize(23, 13));
    A1Text->SetFont(*font);
    wxStaticText *A2Text = new wxStaticText(prescribedAGroupBox, wxID_ANY, wxT("A2:"), wxPoint(6, 78), wxSize(23, 13));
    A2Text->SetFont(*font);
    wxStaticText *phiText = new wxStaticText(prescribedAGroupBox, wxID_ANY, wxT("ϕ deg"), wxPoint(6, 114), wxSize(45, 13));
    phiText->SetFont(*font);
    A0TextCtrl->Create(prescribedAGroupBox, wxID_ANY, std::to_string(_magneticBoundary.getA0()), wxPoint(57, 5), wxSize(88, 20));
    A0TextCtrl-SetFont(*font);
    A1TextCtrl->Create(prescribedAGroupBox, wxID_ANY, std::to_string(_magneticBoundary.getA1()), wxPoint(57, 40), wxSize(88, 20));
    A1TextCtrl->SetFont(*font);
    A2TextCtrl->Create(prescribedAGroupBox, wxID_ANY, std::to_string(_magneticBoundary.getA2()), wxPoint(57, 75), wxSize(88, 20));
    A2TextCtrl->SetFont(*font);
    phiTextCtrl->Create(prescribedAGroupBox, wxID_ANY, std::to_string(_magneticBoundary.getPhi()), wxPoint(57, 111), wxSize(88, 20));
    phiTextCtrl->SetFont(*font);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxPoint(209, 219), wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(290, 219), wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    this->Fit();
    this->SetMinSize(this->GetSize());
    this->SetMaxSize(this->GetSize());
}



void magneticBoundaryDialog::onBCComboChange(wxCommandEvent &event)
{
    
}

magneticBoundaryDialog::~magneticBoundaryDialog()
{
    
}


wxBEGIN_EVENT_TABLE(magneticBoundaryDialog, wxDialog)
    EVT_COMBOBOX(generalFrameButton::ID_ComboBox1, magneticBoundaryDialog::onBCComboChange)
wxEND_EVENT_TABLE()