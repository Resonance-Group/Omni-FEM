#include <UI/MaterialsDialog/BlockPropertyMagnetics.h>



blockPropertyMagnetic::blockPropertyMagnetic() : wxDialog(NULL, wxID_ANY, "Magnetic Block Property", wxDefaultPosition, wxSize(416, 465))
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
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
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name:", wxPoint(21, 15), wxSize(38, 13));
    name->SetFont(*font);
    wxStaticText *BHCurve = new wxStaticText(this, wxID_ANY, "B-H Curve", wxPoint(21, 45), wxSize(56, 13));
    BHCurve->SetFont(*font);
    BHCurveComboBox->Create(this, generalFrameButton::ID_ComboBox1, wxEmptyString, wxPoint(95, 42), wxSize(165, 21), *BHSettingsArray);
    BHCurveComboBox->SetFont(*font);
    nameTextCtrl->Create(this, magneticBlockPropertyDiag::ID_TextControl1, _magneticMaterial.getName(), wxPoint(95, 12), wxSize(251, 20));
    nameTextCtrl->SetFont(*font);
    
    /* This first part is for the Linear Properties */
    linearMatPropGroupBox->SetFont(*font);
    linearMatPropGroupBox->Create(this, wxID_ANY, "Linear Material Properties", wxPoint(5, 69), wxSize(409, 74));
    wxStaticText *relativeUx = new wxStaticText(linearMatPropGroupBox, wxID_ANY, wxT("Relative μx:"), wxPoint(6, 4), wxSize(63,13));
    relativeUx->SetFont(*font);
    wxStaticText *relativeUy = new wxStaticText(linearMatPropGroupBox, wxID_ANY, wxT("Relative μy:"), wxPoint(214, 4), wxSize(63, 13));
    relativeUy->SetFont(*font);
    wxStaticText *phiX = new wxStaticText(linearMatPropGroupBox, wxID_ANY, wxT("ϕ hx:"), wxPoint(7, 30), wxSize(38, 13));
    phiX->SetFont(*font);
    wxStaticText *phiY = new wxStaticText(linearMatPropGroupBox, wxID_ANY, wxT("ϕ hy:"), wxPoint(214, 30), wxSize(38, 13));
    phiY->SetFont(*font);
    wxStaticText *deg1 = new wxStaticText(linearMatPropGroupBox, wxID_ANY, "deg", wxPoint(158, 30), wxSize(25, 13));
    deg1->SetFont(*font);
    wxStaticText *deg2 = new wxStaticText(linearMatPropGroupBox, wxID_ANY, "deg", wxPoint(376, 30), wxSize(25, 13));
    deg2->SetFont(*font);
    relativeUxTextCtrl->Create(linearMatPropGroupBox, magneticBlockPropertyDiag::ID_TextControl2, std::to_string(_magneticMaterial.getMUrX()), wxPoint(75, 0), wxSize(77, 20));
    relativeUxTextCtrl->SetFont(*font);
    phiXTextCtrl->Create(linearMatPropGroupBox, magneticBlockPropertyDiag::ID_TextControl3, std::to_string(_magneticMaterial.getPhiX()), wxPoint(75, 27), wxSize(77, 20));
    phiXTextCtrl->SetFont(*font);
    relativeUyTextCtrl->Create(linearMatPropGroupBox, magneticBlockPropertyDiag::ID_TextControl4, std::to_string(_magneticMaterial.getMUrY()), wxPoint(293, 0), wxSize(77, 20));
    relativeUyTextCtrl->SetFont(*font);
    phiYTextCtrl->Create(linearMatPropGroupBox, magneticBlockPropertyDiag::ID_TextControl5, std::to_string(_magneticMaterial.getPhiY()), wxPoint(293, 27), wxSize(77, 20));
    phiYTextCtrl->SetFont(*font);
    
    /* This second part is for the nonlinear properties */
    nonlinearGroupBox->SetFont(*font);
    nonlinearGroupBox->Create(this, wxID_ANY, "Nonlinear Material Properties", wxPoint(5, 149), wxSize(409, 49));
    wxStaticText *phiMaxLabel = new wxStaticText(nonlinearGroupBox, wxID_ANY, wxT("ϕ hmax:"), wxPoint(214, 5), wxSize(52, 13));
    phiMaxLabel->SetFont(*font);
    wxStaticText *deg3 = new wxStaticText(nonlinearGroupBox, wxID_ANY, "deg", wxPoint(376, 5), wxSize(25, 13));
    deg3->SetFont(*font);
    editBHCurve->Create(nonlinearGroupBox, wxID_EDIT, "Edit B-H Curve", wxPoint(6, 0), wxSize(157, 23));
    editBHCurve->SetFont(*font);
    phiMaxTextCtrl->Create(nonlinearGroupBox, magneticBlockPropertyDiag::ID_TextControl6, std::to_string(_magneticMaterial.getPhiMax()), wxPoint(293, 0), wxSize(77, 20));
    phiMaxTextCtrl->SetFont(*font);
    
    /* This part is for the coercivity section */
    coercivityGroupBox->SetFont(*font);
    coercivityGroupBox->Create(this, wxID_ANY, "Coercivity", wxPoint(5, 204), wxSize(176, 40));
    coercivityTextCtrl->Create(coercivityGroupBox, magneticBlockPropertyDiag::ID_TextControl7, std::to_string(_magneticMaterial.getCoercivity()), wxPoint(75, 0), wxSize(77, 20));
    coercivityTextCtrl->SetFont(*font);
    wxStaticText *HcLabel = new wxStaticText(coercivityGroupBox, wxID_ANY, "Hc, A/m2", wxPoint(6, 4), wxSize(56, 13));
    HcLabel->SetFont(*font);
    
    /* This part is for the electrical conductivity */
    eConductivityGroupBox->SetFont(*font);
    eConductivityGroupBox->Create(this, wxID_ANY, "Electrical Conductivity", wxPoint(204, 204), wxSize(210, 40));
    wxStaticText *sigLabel = new wxStaticText(eConductivityGroupBox, wxID_ANY, wxT("σ MS/m:"), wxPoint(15, 4), wxSize(55, 13));
    sigLabel->SetFont(*font);
    eConductivityTextCtrl->Create(eConductivityGroupBox, magneticBlockPropertyDiag::ID_TextControl8, std::to_string(_magneticMaterial.getSigma()), wxPoint(94, 0), wxSize(77, 20));
    eConductivityTextCtrl->SetFont(*font);
    
    /* This part is for the source current density */
    sourceCurrentGroupBox->SetFont(*font);
    sourceCurrentGroupBox->Create(this, wxID_ANY, "Source Current Density", wxPoint(5, 250), wxSize(409, 45));
    wxStaticText *currentDesnityLabel = new wxStaticText(sourceCurrentGroupBox, wxID_ANY, "J MA/m2:", wxPoint(7, 4), wxSize(56, 13));
    currentDesnityLabel->SetFont(*font);
    currentDesnityTextCtrl->Create(sourceCurrentGroupBox, magneticBlockPropertyDiag::ID_TextControl9, std::to_string(_magneticMaterial.getCurrentDensity()), wxPoint(75, 0), wxSize(295, 20));
    currentDesnityTextCtrl->SetFont(*font);
    
    /* This part is for the Special Attributes */
    specialAttriGroupBox->SetFont(*font);
    specialAttriGroupBox->Create(this, wxID_ANY, "Special Attributes: Lamination and Wire Type", wxPoint(5, 301), wxSize(410, 100));
    specialAttriComboBox->Create(specialAttriGroupBox,  generalFrameButton::ID_ComboBox2, wxEmptyString, wxPoint(10, 0), wxSize(361, 21), *LamWireSettingsArray);
    specialAttriComboBox->SetFont(*font);
    wxStaticText *lamThickLabel = new wxStaticText(specialAttriGroupBox, wxID_ANY, "Lam. Thickness:", wxPoint(6, 34), wxSize(82, 13));
    lamThickLabel->SetFont(*font);
    wxStaticText *numTurnsLabel = new wxStaticText(specialAttriGroupBox, wxID_ANY, "Number of Turns:", wxPoint(6, 60), wxSize(89, 13));
    numTurnsLabel->SetFont(*font);
    wxStaticText *lamFillLabel = new wxStaticText(specialAttriGroupBox, wxID_ANY, "Lam. Fill Factor:", wxPoint(209, 34), wxSize(78, 13));
    lamFillLabel->SetFont(*font);
    wxStaticText *strandDiaLabel = new wxStaticText(specialAttriGroupBox, wxID_ANY, "Strand Dia:", wxPoint(210, 60), wxSize(60,13));
    strandDiaLabel->SetFont(*font);
    wxStaticText *mmLabel1 = new wxStaticText(specialAttriGroupBox, wxID_ANY, "mm", wxPoint(184, 34), wxSize(23, 13));
    mmLabel1->SetFont(*font);
    wxStaticText *mmLabel2 = new wxStaticText(specialAttriGroupBox, wxID_ANY, "mm", wxPoint(374, 60), wxSize(23, 13));
    mmLabel2->SetFont(*font);
    lamThickTextCtrl->Create(specialAttriGroupBox, magneticBlockPropertyDiag::ID_TextControl10, std::to_string(_magneticMaterial.getLaminationThickness()), wxPoint(101, 31), wxSize(77, 20));
    lamThickTextCtrl->SetFont(*font);
    numStrandsTextCtrl->Create(specialAttriGroupBox, magneticBlockPropertyDiag::ID_TextControl11, std::to_string(_magneticMaterial.getNumberStrands()), wxPoint(101, 56), wxSize(77, 20));
    numStrandsTextCtrl->SetFont(*font);
    lamFFTextCtrl->Create(specialAttriGroupBox, magneticBlockPropertyDiag::ID_TextControl12, std::to_string(_magneticMaterial.getLaminationFillFactor()), wxPoint(293, 31), wxSize(77, 20));
    lamFFTextCtrl->SetFont(*font);
    strandDiaTextCtrl->Create(specialAttriGroupBox, magneticBlockPropertyDiag::ID_TextControl13, std::to_string(_magneticMaterial.getStrandDiameter()), wxPoint(293, 56), wxSize(77, 20));
    strandDiaTextCtrl->SetFont(*font);

    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxPoint(258, 407), wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(339, 407), wxSize(75, 23));
    cancelButton->SetFont(*font);

    this->SetMinSize(this->GetSize());
    this->SetMaxSize(this->GetSize());
}



void blockPropertyMagnetic::getNewMaterial(magneticMaterial &newMaterial)
{
    double value;
    
    coercivityTextCtrl->GetValue().ToDouble(&value);
    newMaterial.setCoercivity(value); 
    
    newMaterial.setName(nameTextCtrl->GetValue().ToStdString());
    
    currentDesnityTextCtrl->GetValue().ToDouble(&value);
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



void blockPropertyMagnetic::setMaterial(magneticMaterial &material)
{
    _magneticMaterial = material;
    
    setTextControlValues();
    
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



void blockPropertyMagnetic::clearMaterial()
{
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
    
    setTextControlValues();
    
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
}



void blockPropertyMagnetic::setTextControlValues()
{
    nameTextCtrl->SetValue(_magneticMaterial.getName());
    relativeUxTextCtrl->SetValue(std::to_string(_magneticMaterial.getMUrX()));
    phiXTextCtrl->SetValue(std::to_string(_magneticMaterial.getPhiX()));
    relativeUyTextCtrl->SetValue(std::to_string(_magneticMaterial.getMUrY()));
    phiYTextCtrl->SetValue(std::to_string(_magneticMaterial.getPhiY()));
    
    phiMaxTextCtrl->SetValue(std::to_string(_magneticMaterial.getPhiMax()));
    
    coercivityTextCtrl->SetValue(std::to_string(_magneticMaterial.getCoercivity()));
    
    eConductivityTextCtrl->SetValue(std::to_string(_magneticMaterial.getSigma()));
    
    currentDesnityTextCtrl->SetValue(std::to_string(_magneticMaterial.getCurrentDensity()));
    
    lamThickTextCtrl->SetValue(std::to_string(_magneticMaterial.getLaminationThickness()));
    numStrandsTextCtrl->SetValue(std::to_string(_magneticMaterial.getNumberStrands()));
    lamFFTextCtrl->SetValue(std::to_string(_magneticMaterial.getLaminationFillFactor()));
    strandDiaTextCtrl->SetValue(std::to_string(_magneticMaterial.getStrandDiameter())); 
}



blockPropertyMagnetic::~blockPropertyMagnetic()
{
    
}



wxBEGIN_EVENT_TABLE(blockPropertyMagnetic, wxDialog)
    EVT_BUTTON(wxID_EDIT, blockPropertyMagnetic::onBHCurve)
    EVT_COMBOBOX(generalFrameButton::ID_ComboBox1, blockPropertyMagnetic::onBHCurveCombo)
    EVT_COMBOBOX(generalFrameButton::ID_ComboBox2, blockPropertyMagnetic::onSpecialComboBox)
wxEND_EVENT_TABLE()