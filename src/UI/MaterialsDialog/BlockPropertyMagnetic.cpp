#include <UI/MaterialsDialog/BlockPropertyMagnetics.h>



blockPropertyMagnetic::blockPropertyMagnetic() : wxDialog(NULL, wxID_ANY, "Magnetic Block Property")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *BHCurveSizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxStaticBoxSizer *linearPropertiesSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Linear Material Properties");
    linearPropertiesSizer->GetStaticBox()->SetFont(*font);
    wxBoxSizer *lpLine1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *lpLine2 = new wxBoxSizer(wxHORIZONTAL);
    
    wxStaticBoxSizer *coercivitySizer = new wxStaticBoxSizer(wxHORIZONTAL, this, "Coercivity");
    coercivitySizer->GetStaticBox()->SetFont(*font);
    
    wxStaticBoxSizer *eConductivitySizer = new wxStaticBoxSizer(wxHORIZONTAL, this, "Electrical Conductivity");
    eConductivitySizer->GetStaticBox()->SetFont(*font);
    
    wxBoxSizer *intermediateSizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxStaticBoxSizer *currentDensitySizer = new wxStaticBoxSizer(wxHORIZONTAL, this, "Source Current Density");
    currentDensitySizer->GetStaticBox()->SetFont(*font);
    
    wxStaticBoxSizer *specialAttriSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Special Attributes: Lamination and Wire Type");
    specialAttriSizer->GetStaticBox()->SetFont(*font);
    wxBoxSizer *specialAttriLine1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *specialAttriLine2Sizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxBoxSizer *footSizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    _magneticMaterial.setCoercivity(0);
    _magneticMaterial.setName("New Material");
    _magneticMaterial.setCurrentDensity(0);
    _magneticMaterial.setLaminationFillFactor(1);
    _magneticMaterial.setLaminationThickness(0);
    _magneticMaterial.setMUrX(1);
    _magneticMaterial.setMUrY(1);
    _magneticMaterial.setNumberStrands(1);
    _magneticMaterial.setPhiX(0);
    _magneticMaterial.setPhiY(0);
    _magneticMaterial.setSigma(0);
    _magneticMaterial.setSpecialAttribute(lamWireEnum::NOT_LAMINATED_OR_STRANDED);
    _magneticMaterial.setStrandDiameter(0);
    
    BHSettingsArray->Add("Linear B-H Curve");
    BHSettingsArray->Add("Nonlinear B-H Curve");
    
    LamWireSettingsArray->Add("Not Laminated or Stranded");
    LamWireSettingsArray->Add("Laminated In-Plane");
    LamWireSettingsArray->Add("Laminated Parallel to x (Planar) or r (Axisymmetric)");
    LamWireSettingsArray->Add("Laminated Parallel to y (Planar) or z (Axisymmetric)");
    LamWireSettingsArray->Add("Magnet Wire");
    LamWireSettingsArray->Add("Plain Stranded Wire");
    LamWireSettingsArray->Add("Litz Wire");
    LamWireSettingsArray->Add("Square Wire");
    LamWireSettingsArray->Add("10% CCA");
    LamWireSettingsArray->Add("15% CCA");
    
    /* This section is for the header */
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name:");
    name->SetFont(*font);
    nameTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl1, _magneticMaterial.getName(), wxPoint(86, 12), wxSize(373, 20));
    nameTextCtrl->SetFont(*font);
    headerSizer->Add(name, 0, wxCENTER | wxALL, 6);
    headerSizer->Add(23, 0, 0);
    headerSizer->Add(nameTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM , 6);
    
    /* This section is for the BH Curve infomation */
    wxStaticText *BHCurve = new wxStaticText(this, wxID_ANY, "B-H Curve", wxPoint(12, 41), wxSize(60, 13));
    BHCurve->SetFont(*font);
    BHCurveComboBox->Create(this, generalFrameButton::ID_ComboBox1, wxEmptyString, wxPoint(86, 38), wxSize(165, 21), *BHSettingsArray);
    BHCurveComboBox->SetFont(*font);
    jilesAthertonButton->Create(this, wxID_EDIT, "Edit Jiles-Atherton Parameters", wxPoint(262, 38), wxSize(202, 23));
    jilesAthertonButton->SetFont(*font);
    BHCurveSizer->Add(BHCurve, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    BHCurveSizer->Add(BHCurveComboBox, 0, wxCENTER | wxRIGHT | wxBOTTOM, 6);
    BHCurveSizer->Add(jilesAthertonButton, 0, wxCENTER | wxBOTTOM, 6);
    
    /* This first part is for the Linear Properties */
    wxStaticText *relativeUx = new wxStaticText(linearPropertiesSizer->GetStaticBox(), wxID_ANY, wxT("Relative μx:"), wxPoint(6, 4), wxSize(70,13));
    relativeUx->SetFont(*font);
    relativeUxTextCtrl->Create(linearPropertiesSizer->GetStaticBox(), magneticBlockPropertyDiag::ID_TextControl2, wxEmptyString, wxPoint(75, 0), wxSize(87, 20));
    relativeUxTextCtrl->SetFont(*font);
    
    wxStaticText *relativeUy = new wxStaticText(linearPropertiesSizer->GetStaticBox(), wxID_ANY, wxT("Relative μy:"));
    relativeUy->SetFont(*font);
    relativeUyTextCtrl->Create(linearPropertiesSizer->GetStaticBox(), magneticBlockPropertyDiag::ID_TextControl4, wxEmptyString, wxPoint(293, 0), wxSize(87, 20));
    relativeUyTextCtrl->SetFont(*font);
    
    wxStaticText *phiX = new wxStaticText(linearPropertiesSizer->GetStaticBox(), wxID_ANY, wxT("ϕ hx:"), wxPoint(7, 30), wxSize(38, 13));
    phiX->SetFont(*font);
    phiXTextCtrl->Create(linearPropertiesSizer->GetStaticBox(), magneticBlockPropertyDiag::ID_TextControl3, wxEmptyString, wxPoint(75, 27), wxSize(87, 20));
    phiXTextCtrl->SetFont(*font);
    
    wxStaticText *phiY = new wxStaticText(linearPropertiesSizer->GetStaticBox(), wxID_ANY, wxT("ϕ hy:"), wxPoint(214, 30), wxSize(38, 13));
    phiY->SetFont(*font);
    phiYTextCtrl->Create(linearPropertiesSizer->GetStaticBox(), magneticBlockPropertyDiag::ID_TextControl5, wxEmptyString, wxPoint(293, 27), wxSize(87, 20));
    phiYTextCtrl->SetFont(*font);
    
    wxStaticText *deg1 = new wxStaticText(linearPropertiesSizer->GetStaticBox(), wxID_ANY, "deg", wxPoint(158, 30), wxSize(25, 13));
    deg1->SetFont(*font);
    wxStaticText *deg2 = new wxStaticText(linearPropertiesSizer->GetStaticBox(), wxID_ANY, "deg", wxPoint(376, 30), wxSize(25, 13));
    deg2->SetFont(*font);
    
    lpLine1->Add(relativeUx, 0, wxCENTER | wxALL, 6);
    lpLine1->Add(relativeUxTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    lpLine1->Add(60, 0, 0);
    lpLine1->Add(relativeUy, 0, wxCENTER | wxALL, 6);
    lpLine1->Add(12, 0, 0);
    lpLine1->Add(relativeUyTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    lpLine2->Add(phiX, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    lpLine2->Add(31, 0, 0);
    lpLine2->Add(phiXTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    lpLine2->Add(deg1, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    lpLine2->Add(35, 0, 0);
    lpLine2->Add(phiY, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    lpLine2->Add(39, 0, 0);
    lpLine2->Add(phiYTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    lpLine2->Add(deg2, 0, wxCENTER | wxBOTTOM, 6);
    
    linearPropertiesSizer->Add(lpLine1);
    linearPropertiesSizer->Add(lpLine2);
    
    /* This part is for the coercivity section */
    wxStaticText *HcLabel = new wxStaticText(coercivitySizer->GetStaticBox(), wxID_ANY, "Hc (A/m2):", wxPoint(6, 4), wxSize(65, 13));
    HcLabel->SetFont(*font);
    coercivityTextCtrl->Create(coercivitySizer->GetStaticBox(), magneticBlockPropertyDiag::ID_TextControl7, wxEmptyString, wxPoint(75, 0), wxSize(120, 20));
    coercivityTextCtrl->SetFont(*font);
    coercivitySizer->Add(HcLabel, 0, wxCENTER | wxALL, 6);
    coercivitySizer->Add(coercivityTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    /* This part is for the electrical conductivity */
    wxStaticText *sigLabel = new wxStaticText(eConductivitySizer->GetStaticBox(), wxID_ANY, wxT("σ MS/m:"), wxPoint(15, 4), wxSize(55, 13));
    sigLabel->SetFont(*font);
    eConductivityTextCtrl->Create(eConductivitySizer->GetStaticBox(), magneticBlockPropertyDiag::ID_TextControl8, wxEmptyString, wxPoint(75, 0), wxSize(120, 20));
    eConductivityTextCtrl->SetFont(*font);
    eConductivitySizer->Add(sigLabel, 0, wxCENTER | wxALL, 6);
    eConductivitySizer->Add(eConductivityTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    intermediateSizer->Add(coercivitySizer);
    intermediateSizer->Add(40, 0, 0);
    intermediateSizer->Add(eConductivitySizer);
    
    /* This part is for the source current density */
    wxStaticText *currentDesnityLabel = new wxStaticText(currentDensitySizer->GetStaticBox(), wxID_ANY, "J (MA/m2):", wxPoint(7, 4), wxSize(65, 13));
    currentDesnityLabel->SetFont(*font);
    currentDensityTextCtrl->Create(currentDensitySizer->GetStaticBox(), magneticBlockPropertyDiag::ID_TextControl9, wxEmptyString, wxPoint(75, 0), wxSize(358, 20));
    currentDensityTextCtrl->SetFont(*font);
    currentDensitySizer->Add(currentDesnityLabel, 0, wxCENTER | wxALL, 6);
    currentDensitySizer->Add(currentDensityTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    /* This part is for the Special Attributes */
    specialAttriComboBox->Create(specialAttriSizer->GetStaticBox(),  generalFrameButton::ID_ComboBox2, wxEmptyString, wxPoint(10, 0), wxSize(361, 21), *LamWireSettingsArray);
    specialAttriComboBox->SetFont(*font);
    
    wxStaticText *lamThickLabel = new wxStaticText(specialAttriSizer->GetStaticBox(), wxID_ANY, "Lam. Thickness:", wxPoint(6, 34), wxSize(95, 13));
    lamThickLabel->SetFont(*font);
    lamThickTextCtrl->Create(specialAttriSizer->GetStaticBox(), magneticBlockPropertyDiag::ID_TextControl10, wxEmptyString, wxPoint(101, 31), wxSize(77, 20));
    lamThickTextCtrl->SetFont(*font);
    
    wxStaticText *numStrandsLabel = new wxStaticText(specialAttriSizer->GetStaticBox(), wxID_ANY, "Number of Strands:", wxPoint(6, 60), wxSize(110, 13));
    numStrandsLabel->SetFont(*font);
    numStrandsTextCtrl->Create(specialAttriSizer->GetStaticBox(), magneticBlockPropertyDiag::ID_TextControl11, wxEmptyString, wxPoint(101, 56), wxSize(77, 20));
    numStrandsTextCtrl->SetFont(*font);
    
    wxStaticText *lamFillLabel = new wxStaticText(specialAttriSizer->GetStaticBox(), wxID_ANY, "Lam. Fill Factor:", wxPoint(209, 34), wxSize(90, 13));
    lamFillLabel->SetFont(*font);
    lamFFTextCtrl->Create(specialAttriSizer->GetStaticBox(), magneticBlockPropertyDiag::ID_TextControl12, wxEmptyString, wxPoint(293, 31), wxSize(77, 20));
    lamFFTextCtrl->SetFont(*font);
    
    wxStaticText *strandDiaLabel = new wxStaticText(specialAttriSizer->GetStaticBox(), wxID_ANY, "Strand Dia:", wxPoint(210, 60), wxSize(65,13));
    strandDiaLabel->SetFont(*font);
    strandDiaTextCtrl->Create(specialAttriSizer->GetStaticBox(), magneticBlockPropertyDiag::ID_TextControl13, wxEmptyString, wxPoint(293, 56), wxSize(77, 20));
    strandDiaTextCtrl->SetFont(*font);
    
    wxStaticText *mmLabel1 = new wxStaticText(specialAttriSizer->GetStaticBox(), wxID_ANY, "mm", wxPoint(184, 34), wxSize(23, 13));
    mmLabel1->SetFont(*font);
    
    wxStaticText *mmLabel2 = new wxStaticText(specialAttriSizer->GetStaticBox(), wxID_ANY, "mm", wxPoint(374, 60), wxSize(23, 13));
    mmLabel2->SetFont(*font);
    
    specialAttriLine1Sizer->Add(lamThickLabel, 0, wxCENTER | wxALL, 6);
    specialAttriLine1Sizer->Add(15, 0, 0);
    specialAttriLine1Sizer->Add(lamThickTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    specialAttriLine1Sizer->Add(mmLabel1, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    specialAttriLine1Sizer->Add(lamFillLabel, 0, wxCENTER | wxBOTTOM | wxTOP | wxRIGHT, 6);
    specialAttriLine1Sizer->Add(lamFFTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    specialAttriLine2Sizer->Add(numStrandsLabel, 0, wxCENTER | wxALL, 6);
    specialAttriLine2Sizer->Add(numStrandsTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    specialAttriLine2Sizer->Add(25, 0, 0);
    specialAttriLine2Sizer->Add(strandDiaLabel, 0, wxCENTER | wxALL, 6);
    specialAttriLine2Sizer->Add(22, 0, 0);
    specialAttriLine2Sizer->Add(strandDiaTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    specialAttriLine2Sizer->Add(mmLabel2, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    specialAttriSizer->Add(specialAttriComboBox, 0, wxCENTER | wxALL, 6);
    specialAttriSizer->Add(specialAttriLine1Sizer);
    specialAttriSizer->Add(specialAttriLine2Sizer);

    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxPoint(258, 407), wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(339, 407), wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footSizer->Add(okButton, 0, wxCENTER | wxTOP | wxRIGHT, 6);
    footSizer->Add(cancelButton, 0, wxCENTER | wxTOP | wxTOP | wxRIGHT, 6);

    topSizer->Add(headerSizer, 0, wxLEFT | wxRIGHT, 6);
    topSizer->Add(BHCurveSizer, 0, wxLEFT | wxRIGHT, 6);
    topSizer->Add(linearPropertiesSizer, 0, wxALL, 6);
    topSizer->Add(intermediateSizer, 0, wxLEFT | wxRIGHT, 6);
    topSizer->Add(currentDensitySizer, 0, wxALL, 6);
    topSizer->Add(specialAttriSizer, 0, wxLEFT | wxRIGHT, 6);
    topSizer->Add(footSizer, 0, wxALIGN_RIGHT | wxBOTTOM, 6);
    
    updateInterface();
    
    SetSizerAndFit(topSizer);
}



void blockPropertyMagnetic::getNewMaterial(magneticMaterial &newMaterial)
{
    double value;
    
    coercivityTextCtrl->GetValue().ToDouble(&value);
    newMaterial.setCoercivity(value); 
    
    newMaterial.setName(nameTextCtrl->GetValue().ToStdString());
    
    currentDensityTextCtrl->GetValue().ToDouble(&value);
    newMaterial.setCurrentDensity(value);

    lamFFTextCtrl->GetValue().ToDouble(&value);
    newMaterial.setLaminationFillFactor(value);
    
    lamThickTextCtrl->GetValue().ToDouble(&value);
    newMaterial.setLaminationThickness(value);
    
    relativeUxTextCtrl->GetValue().ToDouble(&value);
    newMaterial.setMUrX(value);
    
    relativeUyTextCtrl->GetValue().ToDouble(&value);
    newMaterial.setMUrY(value);
    
    numStrandsTextCtrl->GetValue().ToDouble(&value);
    newMaterial.setNumberStrands(value);
    
    phiXTextCtrl->GetValue().ToDouble(&value);
    newMaterial.setPhiX(value);
    
    phiYTextCtrl->GetValue().ToDouble(&value);
    newMaterial.setPhiY(value);
    
    eConductivityTextCtrl->GetValue().ToDouble(&value);
    newMaterial.setSigma(value);
    
    newMaterial.setSpecialAttribute((lamWireEnum)specialAttriComboBox->GetSelection());

    if(BHCurveComboBox->GetSelection() == 0)
        newMaterial.setBHCurveLinearity(true);
    else
        newMaterial.setBHCurveLinearity(false);

    strandDiaTextCtrl->GetValue().ToDouble(&value);
    newMaterial.setStrandDiameter(value);
    newMaterial.setJilesAtherton(_magneticMaterial.getJilesAtherton());
}



void blockPropertyMagnetic::onBHCurve(wxCommandEvent &event)
{
    jilesAthertonParameterDialog *dialog = new jilesAthertonParameterDialog();
    dialog->setJilesAthertonParameter(_magneticMaterial.getJilesAtherton());
    if(dialog->ShowModal() == wxID_OK)
    {
        jilesAthertonParameters newParameters;
        dialog->getJilesAthertonParameter(newParameters);
        _magneticMaterial.setJilesAtherton(newParameters);
    }
}



void blockPropertyMagnetic::onBHCurveCombo(wxCommandEvent &event)
{
    if(BHCurveComboBox->GetSelection() == 0)
    {
        BHCurveComboBox->SetSelection(0);
        relativeUxTextCtrl->Enable(true);
        phiXTextCtrl->Enable(true);
        relativeUyTextCtrl->Enable(true);
        phiYTextCtrl->Enable(true);
        jilesAthertonButton->Enable(false);
    }
    else
    {
        BHCurveComboBox->SetSelection(1);
        relativeUxTextCtrl->Enable(false);
        phiXTextCtrl->Enable(false);
        relativeUyTextCtrl->Enable(false);
        phiYTextCtrl->Enable(false);
        jilesAthertonButton->Enable(true);
    }
}



void blockPropertyMagnetic::onSpecialComboBox(wxCommandEvent &event)
{
    lamWireEnum result = (lamWireEnum)specialAttriComboBox->GetSelection();
    
    if(result == lamWireEnum::NOT_LAMINATED_OR_STRANDED)
    {
        coercivityTextCtrl->Enable(true);
        lamFFTextCtrl->Enable(false);
        lamThickTextCtrl->Enable(false);
        numStrandsTextCtrl->Enable(false);
        strandDiaTextCtrl->Enable(false);
    }
    else if(result == lamWireEnum::LAMINATED_IN_PLANE || result == lamWireEnum::LAMINATED_PARALLEL_X_OR_R_AXISYMMETRIC || result == lamWireEnum::LAMINATED_PARALLEL_Y_OR_Z_AXISYMMETRIC)
    {
        coercivityTextCtrl->Enable(false);
        lamFFTextCtrl->Enable(true);
        lamThickTextCtrl->Enable(true);
        numStrandsTextCtrl->Enable(false);
        strandDiaTextCtrl->Enable(false);
    }
    else if(result == lamWireEnum::MAGNET_WIRE || result == lamWireEnum::SQUARE_WIRE)
    {
        coercivityTextCtrl->Enable(false);
        lamFFTextCtrl->Enable(false);
        lamThickTextCtrl->Enable(false);
        numStrandsTextCtrl->Enable(false);
        strandDiaTextCtrl->Enable(true);
    }
    else if(result == lamWireEnum::PLAIN_STRANDED_WIRE || result == lamWireEnum::LITZ_WIRE || result == lamWireEnum::CCA_10 || result == lamWireEnum::CCA_15)
    {
        coercivityTextCtrl->Enable(false);
        lamFFTextCtrl->Enable(false);
        lamThickTextCtrl->Enable(false);
        numStrandsTextCtrl->Enable(true);
        strandDiaTextCtrl->Enable(true);
    } 
}



void blockPropertyMagnetic::setMaterial(magneticMaterial &material)
{
    _magneticMaterial = material;
    updateInterface();
}



void blockPropertyMagnetic::clearMaterial()
{
    _magneticMaterial.setCoercivity(0);
    _magneticMaterial.setName("New Material");
    _magneticMaterial.setBHCurveLinearity(true);
    _magneticMaterial.setCurrentDensity(0);
    _magneticMaterial.setLaminationFillFactor(1);
    _magneticMaterial.setLaminationThickness(0);
    _magneticMaterial.setMUrX(1);
    _magneticMaterial.setMUrY(1);
    _magneticMaterial.setNumberStrands(1);
    _magneticMaterial.setPhiX(0);
    _magneticMaterial.setPhiY(0);
    _magneticMaterial.setSigma(0);
    _magneticMaterial.setSpecialAttribute(lamWireEnum::NOT_LAMINATED_OR_STRANDED);
    _magneticMaterial.setStrandDiameter(0);
    _magneticMaterial.clearJilesAtherton();
    
    updateInterface();
}



void blockPropertyMagnetic::updateInterface()
{
    std::ostream relativeUxStream(relativeUxTextCtrl);
    std::ostream phiXStream(phiXTextCtrl);
    std::ostream relativeUyStream(relativeUyTextCtrl);
    std::ostream phiYStream(phiYTextCtrl);
    std::ostream coercivityStream(coercivityTextCtrl);
    std::ostream eConductivityStream(eConductivityTextCtrl);
    std::ostream currentDensityStream(currentDensityTextCtrl);
    std::ostream lamThickStream(lamThickTextCtrl);
    std::ostream numStrandsStream(numStrandsTextCtrl);
    std::ostream lamFFStream(lamFFTextCtrl);
    std::ostream strandDiaStream(strandDiaTextCtrl);
    
    nameTextCtrl->SetValue(_magneticMaterial.getName());
    
    relativeUxTextCtrl->SetValue(wxEmptyString);
    relativeUxStream << std::setprecision(3);
    relativeUxStream << _magneticMaterial.getMUrX();
    
    phiXTextCtrl->SetValue(wxEmptyString);
    phiXStream << std::setprecision(3);
    phiXStream << _magneticMaterial.getPhiX();
    
    relativeUyTextCtrl->SetValue(wxEmptyString);
    relativeUyStream << std::setprecision(3);
    relativeUyStream << _magneticMaterial.getMUrY();
    
    phiYTextCtrl->SetValue(wxEmptyString);
    phiYStream << std::setprecision(3);
    phiYStream << _magneticMaterial.getPhiY();
    
    coercivityTextCtrl->SetValue(wxEmptyString);
    coercivityStream << std::setprecision(3);
    coercivityStream << _magneticMaterial.getCoercivity();
    
    eConductivityTextCtrl->SetValue(wxEmptyString);
    eConductivityStream << std::setprecision(3);
    eConductivityStream << _magneticMaterial.getSigma();
    
    currentDensityTextCtrl->SetValue(wxEmptyString);
    currentDensityStream << std::setprecision(30);
    currentDensityStream << _magneticMaterial.getCurrentDensity();
    
    lamThickTextCtrl->SetValue(wxEmptyString);
    lamThickStream << std::setprecision(3);
    lamThickStream << _magneticMaterial.getLaminationThickness();
    
    numStrandsTextCtrl->SetValue(wxEmptyString);
    numStrandsStream << std::setprecision(3);
    numStrandsStream << _magneticMaterial.getNumberStrands();
    
    lamFFTextCtrl->SetValue(wxEmptyString);
    lamFFStream << std::setprecision(3);
    lamFFStream << _magneticMaterial.getLaminationFillFactor();
    
    strandDiaTextCtrl->SetValue(wxEmptyString);
    strandDiaStream << std::setprecision(3);
    strandDiaStream << _magneticMaterial.getStrandDiameter();
    

    if(_magneticMaterial.getBHState())
    {
        BHCurveComboBox->SetSelection(0);
        relativeUxTextCtrl->Enable(true);
        phiXTextCtrl->Enable(true);
        relativeUyTextCtrl->Enable(true);
        phiYTextCtrl->Enable(true);
        jilesAthertonButton->Enable(false);
    }
    else
    {
        BHCurveComboBox->SetSelection(1);
        relativeUxTextCtrl->Enable(false);
        phiXTextCtrl->Enable(false);
        relativeUyTextCtrl->Enable(false);
        phiYTextCtrl->Enable(false);
        jilesAthertonButton->Enable(true);
    }
        
    specialAttriComboBox->SetSelection((int)_magneticMaterial.getSpecialAttribute());
    
    if(_magneticMaterial.getSpecialAttribute() == lamWireEnum::NOT_LAMINATED_OR_STRANDED)
    {
        coercivityTextCtrl->Enable(true);
        lamFFTextCtrl->Enable(false);
        lamThickTextCtrl->Enable(false);
        numStrandsTextCtrl->Enable(false);
        strandDiaTextCtrl->Enable(false);
    }
    else if(_magneticMaterial.getSpecialAttribute() == lamWireEnum::LAMINATED_IN_PLANE || _magneticMaterial.getSpecialAttribute() == lamWireEnum::LAMINATED_PARALLEL_X_OR_R_AXISYMMETRIC || _magneticMaterial.getSpecialAttribute() == lamWireEnum::LAMINATED_PARALLEL_Y_OR_Z_AXISYMMETRIC)
    {
        coercivityTextCtrl->Enable(false);
        lamFFTextCtrl->Enable(true);
        lamThickTextCtrl->Enable(true);
        numStrandsTextCtrl->Enable(false);
        strandDiaTextCtrl->Enable(false);
    }
    else if(_magneticMaterial.getSpecialAttribute() == lamWireEnum::MAGNET_WIRE || _magneticMaterial.getSpecialAttribute() == lamWireEnum::SQUARE_WIRE)
    {
        coercivityTextCtrl->Enable(false);
        lamFFTextCtrl->Enable(false);
        lamThickTextCtrl->Enable(false);
        numStrandsTextCtrl->Enable(false);
        strandDiaTextCtrl->Enable(true);
    }
    else if(_magneticMaterial.getSpecialAttribute() == lamWireEnum::PLAIN_STRANDED_WIRE || _magneticMaterial.getSpecialAttribute() == lamWireEnum::LITZ_WIRE || _magneticMaterial.getSpecialAttribute() == lamWireEnum::CCA_10 || _magneticMaterial.getSpecialAttribute() == lamWireEnum::CCA_15)
    {
        coercivityTextCtrl->Enable(false);
        lamFFTextCtrl->Enable(false);
        lamThickTextCtrl->Enable(false);
        numStrandsTextCtrl->Enable(true);
        strandDiaTextCtrl->Enable(true);
    }  
}



blockPropertyMagnetic::~blockPropertyMagnetic()
{
    
}



wxBEGIN_EVENT_TABLE(blockPropertyMagnetic, wxDialog)
    EVT_BUTTON(wxID_EDIT, blockPropertyMagnetic::onBHCurve)
    EVT_COMBOBOX(generalFrameButton::ID_ComboBox1, blockPropertyMagnetic::onBHCurveCombo)
    EVT_COMBOBOX(generalFrameButton::ID_ComboBox2, blockPropertyMagnetic::onSpecialComboBox)
wxEND_EVENT_TABLE()