#include <UI/MaterialsDialog/BlockPropertyMagnetics.h>


blockPropertyMagnetic::blockPropertyMagnetic(magneticMaterial material) : wxFrame(NULL, wxID_ANY, "Magnetic Block Property", wxDefaultPosition, wxSize(416, 486))
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name:", wxPoint(21, 15), wxSize(38, 13));
    name->SetFont(*font);
    wxStaticText *BHCurve = new wxStaticText(this, wxID_ANY, "B-H Curve", wxPoint(21, 45), wxSize(56, 13));
    BHCurve->SetFont(*font);
    wxStaticText *linearMaterial = new wxStaticText(this, wxID_ANY, "Linear Material Properties", wxPoint(2, 85), wxSize(129, 13));
    linearMaterial->SetFont(*font);
    wxStaticText *relativeUx = new wxStaticText(this, wxID_ANY, "Relative ux:", wxPoint(21, 104), wxSize(63,13));
    relativeUx->SetFont(*font);
    wxStaticText *relativeUy = new wxStaticText(this, wxID_ANY, "Relative uy:", wxPoint(233, 104), wxSize(63, 13));
    relativeUy->SetFont(*font);
    wxStaticText *phiX = new wxStaticText(this, wxID_ANY, "Phi hx:", wxPoint(21, 130), wxSize(38, 13));
    phiX->SetFont(*font);
    wxStaticText *phiY = new wxStaticText(this, wxID_ANY, "Phi hy:", wxPoint(233, 130), wxSize(38, 13));
    phiY->SetFont(*font);
    wxStaticText *deg1 = new wxStaticText(this, wxID_ANY, "deg", wxPoint(187, 130), wxSize(25, 13));
    deg1->SetFont(*font);
    wxStaticText *deg2 = new wxStaticText(this, wxID_ANY, "deg", wxPoint(383, 130), wxSize(25, 13));
    deg2->SetFont(*font);
    wxStaticText *deg3 = new wxStaticText(this, wxID_ANY, "deg", wxPoint(385, 183), wxSize(25, 13));
    deg3->SetFont(*font);
    wxStaticText *nonlinearMatLabel = new wxStaticText(this, wxID_ANY, "Nonlinear Material Properties:", wxPoint(2, 162), wxSize(145, 13));
    nonlinearMatLabel->SetFont(*font);
    wxStaticText *phiMaxLabel = new wxStaticText(this, wxID_ANY, "Phi hmax:", wxPoint(233, 183), wxSize(52, 13));
    phiMaxLabel->SetFont(*font);
    wxStaticText *coercivityLabel = new wxStaticText(this, wxID_ANY, "Coercivity:", wxPoint(2, 214), wxSize(56, 13));
    coercivityLabel->SetFont(*font);
    wxStaticText *eConductivityLabel = new wxStaticText(this, wxID_ANY, "Electrical Conductivity:", wxPoint(209, 214), wxSize(114, 13));
    eConductivityLabel->SetFont(*font);
    wxStaticText *HcLabel = new wxStaticText(this, wxID_ANY, "Hc, A/m2", wxPoint(24, 236), wxSize(56, 13));
    HcLabel->SetFont(*font);
    wxStaticText *sigLabel = new wxStaticText(this, wxID_ANY, "sig. MS/m:", wxPoint(233, 236), wxSize(55, 13));
    sigLabel->SetFont(*font);
    wxStaticText *specialAttrLabel = new wxStaticText(this, wxID_ANY, "Special Attributes: Lamination and Wire Type", wxPoint(2, 322), wxSize(219, 13));
    specialAttrLabel->SetFont(*font);
    wxStaticText *lamThickLabel = new wxStaticText(this, wxID_ANY, "Lam. Thickness:", wxPoint(5, 375), wxSize(82, 13));
    lamThickLabel->SetFont(*font);
    wxStaticText *numTurnsLabel = new wxStaticText(this, wxID_ANY, "Number of Turns:", wxPoint(5, 408), wxSize(89, 13));
    numTurnsLabel->SetFont(*font);
    wxStaticText *lamFillLabel = new wxStaticText(this, wxID_ANY, "Lam. Fill Factor:", wxPoint(221, 375), wxSize(78, 13));
    lamFillLabel->SetFont(*font);
    wxStaticText *strandDiaLabel = new wxStaticText(this, wxID_ANY, "Strand Dia:", wxPoint(221, 411), wxSize(60,13));
    strandDiaLabel->SetFont(*font);
    wxStaticText *mmLabel1 = new wxStaticText(this, wxID_ANY, "mm", wxPoint(187, 375), wxSize(23, 13));
    mmLabel1->SetFont(*font);
    wxStaticText *mmLabel2 = new wxStaticText(this, wxID_ANY, "mm", wxPoint(385, 411), wxSize(23, 13));
    mmLabel2->SetFont(*font);
    wxStaticText *sourceCurrentLabel = new wxStaticText(this, wxID_ANY, "Source Current Density:", wxPoint(2, 274), wxSize(119, 13));
    sourceCurrentLabel->SetFont(*font);
    wxStaticText *currentDesnityLabel = new wxStaticText(this, wxID_ANY, "J MA/m2:", wxPoint(24, 293), wxSize(56, 13));
    currentDesnityLabel->SetFont(*font);
    
    editBHCurve->Create(this, wxID_EDIT, "Edit B-H Curve", wxPoint(24, 178), wxSize(157, 23));
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxPoint(248, 449), wxSize(75, 23));
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(329, 449), wxSize(75, 23));
    
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
    
    specialAttriComboBox->Create(this, generalFrameButton::ID_ComboBox2, wxEmptyString, wxPoint(24, 338), wxSize(355, 21), *LamWireSettingsArray);
    specialAttriComboBox->SetFont(*font);
    BHCurveComboBox->Create(this, generalFrameButton::ID_ComboBox1, wxEmptyString, wxPoint(95, 42), wxSize(165, 21), *BHSettingsArray);
    BHCurveComboBox->SetFont(*font);
    
    _magneticMaterial = material;
        
    nameTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl1, _magneticMaterial.getName(), wxPoint(95, 12), wxSize(251, 20));
    relativeUxTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl2, std::to_string(_magneticMaterial.getMUrX()), wxPoint(104, 101), wxSize(77, 20));
    phiXTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl3, std::to_string(_magneticMaterial.getPhiX()), wxPoint(104, 127), wxSize(77, 20));
    relativeUyTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl4, std::to_string(_magneticMaterial.getMUrY()), wxPoint(302, 101), wxSize(77, 20));
    phiYTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl5, std::to_string(_magneticMaterial.getPhiY()), wxPoint(302, 127), wxSize(77, 20));
    phiMaxTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl6, std::to_string(_magneticMaterial.getPhiMax()), wxPoint(302, 180), wxSize(77, 20));
    coercivityTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl7, std::to_string(_magneticMaterial.getCoercivity()), wxPoint(104, 233), wxSize(77, 20));
    eConductivityTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl8, std::to_string(_magneticMaterial.getSigma()), wxPoint(302, 233), wxSize(77, 20));
    currentDesnityTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl9, std::to_string(_magneticMaterial.getCurrentDensity()), wxPoint(104, 290), wxSize(249, 20));
    lamThickTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl10, std::to_string(_magneticMaterial.getLaminationThickness()), wxPoint(104, 372), wxSize(77, 20));
    numStrandsTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl11, std::to_string(_magneticMaterial.getNumberStrands()), wxPoint(104, 408), wxSize(77, 20));
    lamFFTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl12, std::to_string(_magneticMaterial.getLaminationFillFactor()), wxPoint(302, 372), wxSize(77, 20));
    strandDiaTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl13, std::to_string(_magneticMaterial.getStrandDiameter()), wxPoint(302, 408), wxSize(77, 20));
    
    if(_magneticMaterial.getBHState())
    {
        BHCurveComboBox->SetSelection(0);
        phiMaxTextCtrl->Enable(false);
        relativeUxTextCtrl->Enable(true);
        phiXTextCtrl->Enable(true);
        relativeUyTextCtrl->Enable(true);
        phiYTextCtrl->Enable(true);
        editBHCurve->Enable(false);
    }
    else
    {
        BHCurveComboBox->SetSelection(1);
        relativeUxTextCtrl->Enable(false);
        phiXTextCtrl->Enable(false);
        relativeUyTextCtrl->Enable(false);
        phiYTextCtrl->Enable(false);
        phiMaxTextCtrl->Enable(true);
        editBHCurve->Enable(true);
    }
        
    specialAttriComboBox->SetSelection((int)_magneticMaterial.getSpecialAttribute());
    
    lamWireEnum result = _magneticMaterial.getSpecialAttribute();
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

    this->Fit();
    this->SetMinSize(this->GetSize());
    this->SetMaxSize(this->GetSize());
}



blockPropertyMagnetic::blockPropertyMagnetic() : wxFrame(NULL, wxID_ANY, "Magnetic Block Property", wxDefaultPosition, wxSize(416, 488))
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name:", wxPoint(21, 15), wxSize(38, 13));
    name->SetFont(*font);
    wxStaticText *BHCurve = new wxStaticText(this, wxID_ANY, "B-H Curve", wxPoint(21, 45), wxSize(56, 13));
    BHCurve->SetFont(*font);
    wxStaticText *linearMaterial = new wxStaticText(this, wxID_ANY, "Linear Material Properties", wxPoint(2, 85), wxSize(129, 13));
    linearMaterial->SetFont(*font);
    wxStaticText *relativeUx = new wxStaticText(this, wxID_ANY, "Relative ux:", wxPoint(21, 104), wxSize(63,13));
    relativeUx->SetFont(*font);
    wxStaticText *relativeUy = new wxStaticText(this, wxID_ANY, "Relative uy:", wxPoint(233, 104), wxSize(63, 13));
    relativeUy->SetFont(*font);
    wxStaticText *phiX = new wxStaticText(this, wxID_ANY, "Phi hx:", wxPoint(21, 130), wxSize(38, 13));
    phiX->SetFont(*font);
    wxStaticText *phiY = new wxStaticText(this, wxID_ANY, "Phi hy:", wxPoint(233, 130), wxSize(38, 13));
    phiY->SetFont(*font);
    wxStaticText *deg1 = new wxStaticText(this, wxID_ANY, "deg", wxPoint(187, 130), wxSize(25, 13));
    deg1->SetFont(*font);
    wxStaticText *deg2 = new wxStaticText(this, wxID_ANY, "deg", wxPoint(383, 130), wxSize(25, 13));
    deg2->SetFont(*font);
    wxStaticText *deg3 = new wxStaticText(this, wxID_ANY, "deg", wxPoint(385, 183), wxSize(25, 13));
    deg3->SetFont(*font);
    wxStaticText *nonlinearMatLabel = new wxStaticText(this, wxID_ANY, "Nonlinear Material Properties:", wxPoint(2, 162), wxSize(145, 13));
    nonlinearMatLabel->SetFont(*font);
    wxStaticText *phiMaxLabel = new wxStaticText(this, wxID_ANY, "Phi hmax:", wxPoint(233, 183), wxSize(52, 13));
    phiMaxLabel->SetFont(*font);
    wxStaticText *coercivityLabel = new wxStaticText(this, wxID_ANY, "Coercivity:", wxPoint(2, 214), wxSize(56, 13));
    coercivityLabel->SetFont(*font);
    wxStaticText *eConductivityLabel = new wxStaticText(this, wxID_ANY, "Electrical Conductivity:", wxPoint(209, 214), wxSize(114, 13));
    eConductivityLabel->SetFont(*font);
    wxStaticText *HcLabel = new wxStaticText(this, wxID_ANY, "Hc, A/m2", wxPoint(24, 236), wxSize(56, 13));
    HcLabel->SetFont(*font);
    wxStaticText *sigLabel = new wxStaticText(this, wxID_ANY, "sig. MS/m:", wxPoint(233, 236), wxSize(55, 13));
    sigLabel->SetFont(*font);
    wxStaticText *specialAttrLabel = new wxStaticText(this, wxID_ANY, "Special Attributes: Lamination and Wire Type", wxPoint(2, 322), wxSize(219, 13));
    specialAttrLabel->SetFont(*font);
    wxStaticText *lamThickLabel = new wxStaticText(this, wxID_ANY, "Lam. Thickness:", wxPoint(5, 375), wxSize(82, 13));
    lamThickLabel->SetFont(*font);
    wxStaticText *numTurnsLabel = new wxStaticText(this, wxID_ANY, "Number of Turns:", wxPoint(5, 408), wxSize(89, 13));
    numTurnsLabel->SetFont(*font);
    wxStaticText *lamFillLabel = new wxStaticText(this, wxID_ANY, "Lam. Fill Factor:", wxPoint(221, 375), wxSize(78, 13));
    lamFillLabel->SetFont(*font);
    wxStaticText *strandDiaLabel = new wxStaticText(this, wxID_ANY, "Strand Dia:", wxPoint(221, 411), wxSize(60,13));
    strandDiaLabel->SetFont(*font);
    wxStaticText *mmLabel1 = new wxStaticText(this, wxID_ANY, "mm", wxPoint(187, 375), wxSize(23, 13));
    mmLabel1->SetFont(*font);
    wxStaticText *mmLabel2 = new wxStaticText(this, wxID_ANY, "mm", wxPoint(385, 411), wxSize(23, 13));
    mmLabel2->SetFont(*font);
    wxStaticText *sourceCurrentLabel = new wxStaticText(this, wxID_ANY, "Source Current Density:", wxPoint(2, 274), wxSize(119, 13));
    sourceCurrentLabel->SetFont(*font);
    wxStaticText *currentDesnityLabel = new wxStaticText(this, wxID_ANY, "J MA/m2:", wxPoint(24, 293), wxSize(56, 13));
    currentDesnityLabel->SetFont(*font);
    
    editBHCurve->Create(this, wxID_EDIT, "Edit B-H Curve", wxPoint(24, 178), wxSize(157, 23));
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxPoint(248, 449), wxSize(75, 23));
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(329, 449), wxSize(75, 23));
    
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
    
    specialAttriComboBox->Create(this,  generalFrameButton::ID_ComboBox2, wxEmptyString, wxPoint(24, 338), wxSize(355, 21), *LamWireSettingsArray);
    specialAttriComboBox->SetFont(*font);
    BHCurveComboBox->Create(this, generalFrameButton::ID_ComboBox1, wxEmptyString, wxPoint(95, 42), wxSize(165, 21), *BHSettingsArray);
    BHCurveComboBox->SetFont(*font);
    
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
    
    // This is primarly for the function above. If the function needs to be edited, this will be the first one to edit
    //_magneticMaterial = material;
    
    nameTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl1, _magneticMaterial.getName(), wxPoint(95, 12), wxSize(251, 20));
    relativeUxTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl2, std::to_string(_magneticMaterial.getMUrX()), wxPoint(104, 101), wxSize(77, 20));
    phiXTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl3, std::to_string(_magneticMaterial.getPhiX()), wxPoint(104, 127), wxSize(77, 20));
    relativeUyTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl4, std::to_string(_magneticMaterial.getMUrY()), wxPoint(302, 101), wxSize(77, 20));
    phiYTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl5, std::to_string(_magneticMaterial.getPhiY()), wxPoint(302, 127), wxSize(77, 20));
    phiMaxTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl6, std::to_string(_magneticMaterial.getPhiMax()), wxPoint(302, 180), wxSize(77, 20));
    coercivityTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl7, std::to_string(_magneticMaterial.getCoercivity()), wxPoint(104, 233), wxSize(77, 20));
    eConductivityTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl8, std::to_string(_magneticMaterial.getSigma()), wxPoint(302, 233), wxSize(77, 20));
    currentDesnityTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl9, std::to_string(_magneticMaterial.getCurrentDensity()), wxPoint(104, 290), wxSize(249, 20));
    lamThickTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl10, std::to_string(_magneticMaterial.getLaminationThickness()), wxPoint(104, 372), wxSize(77, 20));
    numStrandsTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl11, std::to_string(_magneticMaterial.getNumberStrands()), wxPoint(104, 408), wxSize(77, 20));
    lamFFTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl12, std::to_string(_magneticMaterial.getLaminationFillFactor()), wxPoint(302, 372), wxSize(77, 20));
    strandDiaTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl13, std::to_string(_magneticMaterial.getStrandDiameter()), wxPoint(302, 408), wxSize(77, 20));
    
    if(_magneticMaterial.getBHState())
    {
        BHCurveComboBox->SetSelection(0);
        phiMaxTextCtrl->Enable(false);
        relativeUxTextCtrl->Enable(true);
        phiXTextCtrl->Enable(true);
        relativeUyTextCtrl->Enable(true);
        phiYTextCtrl->Enable(true);
        editBHCurve->Enable(false);
    }
    else
    {
        BHCurveComboBox->SetSelection(1);
        relativeUxTextCtrl->Enable(false);
        phiXTextCtrl->Enable(false);
        relativeUyTextCtrl->Enable(false);
        phiYTextCtrl->Enable(false);
        phiMaxTextCtrl->Enable(true);
        editBHCurve->Enable(true);
    }
        
    specialAttriComboBox->SetSelection((int)_magneticMaterial.getSpecialAttribute());
    
    lamWireEnum result = _magneticMaterial.getSpecialAttribute();
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

    this->Fit();
    this->SetMinSize(this->GetSize());
    this->SetMaxSize(this->GetSize());
}



blockPropertyMagnetic::~blockPropertyMagnetic()
{
    
}



void blockPropertyMagnetic::onOk(wxCommandEvent &event)
{
    
    double value;
    
    coercivityTextCtrl->GetValue().ToDouble(&value);
    _magneticMaterial.setCoercivity(value);
    
    _magneticMaterial.setName(nameTextCtrl->GetValue().ToStdString());
    
    currentDesnityTextCtrl->GetValue().ToDouble(&value);
    _magneticMaterial.setCurrentDensity(value);
    
    lamFFTextCtrl->GetValue().ToDouble(&value);
    _magneticMaterial.setLaminationFillFactor(value);
    
    lamThickTextCtrl->GetValue().ToDouble(&value);
    _magneticMaterial.setLaminationThickness(value);
    
    relativeUxTextCtrl->GetValue().ToDouble(&value);
    _magneticMaterial.setMUrX(value);
    
    relativeUyTextCtrl->GetValue().ToDouble(&value);
    _magneticMaterial.setMUrY(value);
    
    numStrandsTextCtrl->GetValue().ToDouble(&value);
    _magneticMaterial.setNumberStrands(value);
    
    phiXTextCtrl->GetValue().ToDouble(&value);
    _magneticMaterial.setPhiX(value);
    
    phiYTextCtrl->GetValue().ToDouble(&value);
    _magneticMaterial.setPhiY(0);
    
    eConductivityTextCtrl->GetValue().ToDouble(&value);
    _magneticMaterial.setSigma(0);
    
    _magneticMaterial.setSpecialAttribute((lamWireEnum)specialAttriComboBox->GetSelection());

    if(BHCurveComboBox->GetSelection() == 0)
        _magneticMaterial.setBHCurveLinearity(true);
    else
        _magneticMaterial.setBHCurveLinearity(false);

    strandDiaTextCtrl->GetValue().ToDouble(&value);
    _magneticMaterial.setStrandDiameter(value);
    
    magneticEvent.setMaterial(_magneticMaterial);
    
    wxQueueEvent(pdest, &magneticEvent);
}



void blockPropertyMagnetic::onCancel(wxCommandEvent &event)
{
    this->Close();
}



void blockPropertyMagnetic::onBHCurve(wxCommandEvent &event)
{
    wxMessageBox("This is going to work for the Jiles-Artherton Model");
}



void blockPropertyMagnetic::onBHCurveCombo(wxCommandEvent &event)
{
    if(BHCurveComboBox->GetSelection() == 0)
    {
        BHCurveComboBox->SetSelection(0);
        phiMaxTextCtrl->Enable(false);
        relativeUxTextCtrl->Enable(true);
        phiXTextCtrl->Enable(true);
        relativeUyTextCtrl->Enable(true);
        phiYTextCtrl->Enable(true);
        editBHCurve->Enable(false);
    }
    else
    {
        BHCurveComboBox->SetSelection(1);
        relativeUxTextCtrl->Enable(false);
        phiXTextCtrl->Enable(false);
        relativeUyTextCtrl->Enable(false);
        phiYTextCtrl->Enable(false);
        phiMaxTextCtrl->Enable(true);
        editBHCurve->Enable(true);
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



wxBEGIN_EVENT_TABLE(blockPropertyMagnetic, wxFrame)
    EVT_BUTTON(wxID_OK, blockPropertyMagnetic::onOk)
    EVT_BUTTON(wxID_CANCEL, blockPropertyMagnetic::onCancel)
    EVT_BUTTON(wxID_EDIT, blockPropertyMagnetic::onBHCurve)
    EVT_COMBOBOX(generalFrameButton::ID_ComboBox1, blockPropertyMagnetic::onBHCurveCombo)
    EVT_COMBOBOX(generalFrameButton::ID_ComboBox2, blockPropertyMagnetic::onSpecialComboBox)
wxEND_EVENT_TABLE()