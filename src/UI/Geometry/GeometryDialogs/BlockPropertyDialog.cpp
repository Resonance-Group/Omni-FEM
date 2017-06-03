//#include <UI/BlockPropertyDialog.h>
#include <UI/GeometryDialog/BlockPropertyDialog.h>


blockPropertyDialog::blockPropertyDialog(wxWindow *par, std::vector<magneticMaterial> material, std::vector<circuitProperty> circuit, blockProperty property, bool isAxisymmetric) : wxDialog(par, wxID_ANY, "Block Property")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *line1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line2Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line3Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *meshSizeSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line4Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line5Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line6Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line7Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line8Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line9Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    wxFloatingPointValidator<double> numberValidator(6);
    numberValidator.SetMin(0);
    
    wxIntegerValidator<unsigned int> groupValidator;
    groupValidator.SetMin(0);
    
    _problem = physicProblems::PROB_MAGNETICS;
    
    _magneticMaterialList = material;
    _circuitList = circuit;
    
    wxArrayString *materialNameList = new wxArrayString();
    materialNameList->Add("None");
    materialNameList->Add("No Mesh");
    
    wxArrayString *circuitNameList = new wxArrayString();
    circuitNameList->Add("None");
    
    wxArrayString meshSettingArray;
    meshSettingArray.Add("Extremely Fine");
    meshSettingArray.Add("Extra Fine");
    meshSettingArray.Add("Finer");
    meshSettingArray.Add("Fine");
    meshSettingArray.Add("Normal");
    meshSettingArray.Add("Coarse");
    meshSettingArray.Add("Coarser");
    meshSettingArray.Add("Extra Coarse");
    meshSettingArray.Add("Extremely Coarse");
    meshSettingArray.Add("Custom");
    
    for(std::vector<magneticMaterial>::iterator materialIterator = _magneticMaterialList.begin(); materialIterator != _magneticMaterialList.end(); ++materialIterator)
    {
        materialNameList->Add(materialIterator->getName());
    }
    
    for(std::vector<circuitProperty>::iterator circuitIterator = _circuitList.begin(); circuitIterator != _circuitList.end(); ++circuitIterator)
    {
        circuitNameList->Add(circuitIterator->getName());
    }
    
    wxStaticText *materialText = new wxStaticText(this, wxID_ANY, "Material:");
    materialText->SetFont(*font);
    _materialComboBox->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(207, 21), *materialNameList);
    _materialComboBox->SetFont(*font);
    if(property.getMaterialName() == "None")
    {
        _materialComboBox->SetSelection(0);
    }
    else
    {
        for(unsigned int i = 0; i < _magneticMaterialList.size(); i++)
        {
            if(_magneticMaterialList.at(i).getName() == property.getMaterialName())
            {
                _materialComboBox->SetSelection(i + 2);
                break;
            }
        }
    }
    
    line1Sizer->Add(materialText, 0, wxCENTER | wxALL, 6);
    line1Sizer->Add(_materialComboBox, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    _autoMeshCheckBox->Create(this, generalFrameButton::ID_CHECKBOX1, "Let DealII Choose Mesh Size");
    _autoMeshCheckBox->SetValue(property.getAutoMeshState());
    _autoMeshCheckBox->SetFont(*font);
    
    line2Sizer->Add(_autoMeshCheckBox, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    
    wxStaticText *meshText = new wxStaticText(this, wxID_ANY, "Mesh Size:");
    meshText->SetFont(*font);
    _meshSizeTextCtrl->Create(this, wxID_EDIT, wxEmptyString, wxDefaultPosition, wxSize(121, 20), 0, numberValidator);
    _meshSizeTextCtrl->SetFont(*font);
    _meshSizeTextCtrl->Enable(!property.getAutoMeshState());
    std::ostream meshSizeStream(_meshSizeTextCtrl);
    meshSizeStream << std::fixed << std::setprecision(6) << property.getMeshSize();
    
    line3Sizer->Add(meshText, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    line3Sizer->Add(75, 0, 0);
    line3Sizer->Add(_meshSizeTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _meshSizeComboBox->Create(this, wxID_APPLY, wxEmptyString, wxDefaultPosition, wxSize(121, 21), meshSettingArray);
    _meshSizeComboBox->SetSelection((int)property.getMeshsizeType() - 1);
    _meshSizeComboBox->SetFont(*font);
    _meshSizeComboBox->Enable(!property.getAutoMeshState());
    
    setMeshSizeTextCtrl(property.getMeshsizeType());
    
    meshSizeSizer->Add(_meshSizeComboBox, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    
    wxStaticText *circuitText = new wxStaticText(this, wxID_ANY, "In Circuit:");
    circuitText->SetFont(*font);
    _circuitComboBox->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 23), *circuitNameList);
    _circuitComboBox->SetFont(*font);
    if(property.getCircuitName() == "None")
    {
        _circuitComboBox->SetSelection(0);
    }
    else
    {
        for(unsigned int i = 0; i < _circuitList.size(); i++)
        {
            if(_circuitList.at(i).getName() == property.getCircuitName())
            {
                _circuitComboBox->SetSelection(i + 1);
                break;
            }
        }
    }
    
    line4Sizer->Add(circuitText, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    line4Sizer->Add(83, 0, 0);
    line4Sizer->Add(_circuitComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *numberofTurnsText = new wxStaticText(this, wxID_ANY, "Number of Turns:");
    numberofTurnsText->SetFont(*font);
    _numberOfTurnsTextCtrl->Create(this, wxID_ANY, std::to_string(property.getNumberOfTurns()), wxDefaultPosition, wxSize(121, 20), 0, numberValidator);
    _numberOfTurnsTextCtrl->SetFont(*font);
    
    line5Sizer->Add(numberofTurnsText, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    line5Sizer->Add(41, 0, 0);
    line5Sizer->Add(_numberOfTurnsTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *magnetizationDirectionText = new wxStaticText(this, wxID_ANY, "Magnetization Direction:");
    magnetizationDirectionText->SetFont(*font);
    _magnetizationTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20));
    _magnetizationTextCtrl->SetFont(*font);
    std::ostream magnetStream(_magnetizationTextCtrl);
    magnetStream << std::setprecision(4);
    magnetStream << property.getMagnetization();
    
    line6Sizer->Add(magnetizationDirectionText, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    line6Sizer->Add(_magnetizationTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *groupText = new wxStaticText(this, wxID_ANY, "In Group:");
    groupText->SetFont(*font);
    _groupTextCtrl->Create(this, wxID_ANY, std::to_string(property.getGroupNumber()), wxDefaultPosition, wxSize(121, 20), 0, groupValidator);
    _groupTextCtrl->SetFont(*font);
    
    line7Sizer->Add(groupText, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    line7Sizer->Add(84, 0, 0);
    line7Sizer->Add(_groupTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _externalRegionCheckbox->Create(this, wxID_ANY, "Block Label Located in an External Region");
    _externalRegionCheckbox->SetFont(*font);
    if(isAxisymmetric)
    {
        _externalRegionCheckbox->Enable();
        _externalRegionCheckbox->SetValue(property.getIsExternalState());
    }
    else
    {
        _externalRegionCheckbox->Enable(false);
        _externalRegionCheckbox->SetValue(false);
    }
    
    line8Sizer->Add(_externalRegionCheckbox, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    
    _defaultCheckBox->Create(this, wxID_ANY, "Set as Default Block Label");
    _defaultCheckBox->SetValue(property.getDefaultState());
    _defaultCheckBox->SetFont(*font);
    
    line9Sizer->Add(_defaultCheckBox, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxDefaultPosition, wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    footerSizer->Add(cancelButton, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    topSizer->Add(line1Sizer);
    topSizer->Add(line2Sizer);
    topSizer->Add(line3Sizer);
    topSizer->Add(meshSizeSizer, 0, wxALIGN_RIGHT);
    topSizer->Add(line4Sizer);
    topSizer->Add(line5Sizer);
    topSizer->Add(line6Sizer);
    topSizer->Add(line7Sizer);
    topSizer->Add(line8Sizer);
    topSizer->Add(line9Sizer);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
}



blockPropertyDialog::blockPropertyDialog(wxWindow *par, std::vector<electrostaticMaterial> material, blockProperty property, bool isAxisymmetric) : wxDialog(par, wxID_ANY, "Block Property")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *line1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line2Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line3Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *meshSizeSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line4Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line5Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line6Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    wxFloatingPointValidator<double> numberValidator(6);
    numberValidator.SetMin(0);
    
    wxIntegerValidator<unsigned int> groupValidator;
    groupValidator.SetMin(0);
    
    _problem = physicProblems::PROB_ELECTROSTATIC;
    
    _electricalMaterialList = material;
    
    wxArrayString *materialNameList = new wxArrayString();
    materialNameList->Add("None");
    materialNameList->Add("No Mesh");
    
    wxArrayString meshSettingArray;
    meshSettingArray.Add("Extremely Fine");
    meshSettingArray.Add("Extra Fine");
    meshSettingArray.Add("Finer");
    meshSettingArray.Add("Fine");
    meshSettingArray.Add("Normal");
    meshSettingArray.Add("Coarse");
    meshSettingArray.Add("Coarser");
    meshSettingArray.Add("Extra Coarse");
    meshSettingArray.Add("Extremely Coarse");
    meshSettingArray.Add("Custom");
    
    for(std::vector<electrostaticMaterial>::iterator materialIterator = _electricalMaterialList.begin(); materialIterator != _electricalMaterialList.end(); ++materialIterator)
    {
        materialNameList->Add(materialIterator->getName());
    }
    
    wxStaticText *materialText = new wxStaticText(this, wxID_ANY, "Material:");
    materialText->SetFont(*font);
    _materialComboBox->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(207, 21), *materialNameList);
    _materialComboBox->SetFont(*font);
    if(property.getMaterialName() == "None")
    {
        _materialComboBox->SetSelection(0);
    }
    else
    {
        for(unsigned int i = 0; i < _electricalMaterialList.size(); i++)
        {
            if(_electricalMaterialList.at(i).getName() == property.getMaterialName())
            {
                _materialComboBox->SetSelection(i + 2);
                break;
            }
        }
    }
    
    line1Sizer->Add(materialText, 0, wxCENTER | wxALL, 6);
    line1Sizer->Add(_materialComboBox, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    _autoMeshCheckBox->Create(this, generalFrameButton::ID_CHECKBOX1, "Let DealII Choose Mesh Size");
    _autoMeshCheckBox->SetValue(property.getAutoMeshState());
    _autoMeshCheckBox->SetFont(*font);
    
    line2Sizer->Add(_autoMeshCheckBox, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    
    wxStaticText *meshText = new wxStaticText(this, wxID_ANY, "Mesh Size:");
    meshText->SetFont(*font);
    _meshSizeTextCtrl->Create(this, wxID_EDIT, wxEmptyString, wxDefaultPosition, wxSize(121, 20), wxTE_PROCESS_ENTER, numberValidator);
    _meshSizeTextCtrl->SetFont(*font);
    _meshSizeTextCtrl->Enable(!property.getAutoMeshState());
    std::ostream meshSizeStream(_meshSizeTextCtrl);
    meshSizeStream << std::fixed << std::setprecision(4) << property.getMeshSize();
    
    line3Sizer->Add(meshText, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    line3Sizer->Add(75, 0, 0);
    line3Sizer->Add(_meshSizeTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _meshSizeComboBox->Create(this, wxID_APPLY, wxEmptyString, wxDefaultPosition, wxSize(121, 21), meshSettingArray);
    _meshSizeComboBox->SetSelection((int)property.getMeshsizeType() - 1);
    _meshSizeComboBox->SetFont(*font);
    _meshSizeComboBox->Enable(!property.getAutoMeshState());
    
    setMeshSizeTextCtrl(property.getMeshsizeType());
    
    meshSizeSizer->Add(_meshSizeComboBox, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    
    wxStaticText *groupText = new wxStaticText(this, wxID_ANY, "In Group:");
    groupText->SetFont(*font);
    _groupTextCtrl->Create(this, wxID_ANY, std::to_string(property.getGroupNumber()), wxDefaultPosition, wxSize(121, 20), 0, groupValidator);
    _groupTextCtrl->SetFont(*font);
    
    line4Sizer->Add(groupText, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    line4Sizer->Add(84, 0, 0);
    line4Sizer->Add(_groupTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _externalRegionCheckbox->Create(this, wxID_ANY, "Block Label Located in an External Region");
    _externalRegionCheckbox->SetFont(*font);
    if(isAxisymmetric)
    {
        _externalRegionCheckbox->Enable();
        _externalRegionCheckbox->SetValue(property.getIsExternalState());
    }
    else
    {
        _externalRegionCheckbox->Enable(false);
        _externalRegionCheckbox->SetValue(false);
    }
    
    line5Sizer->Add(_externalRegionCheckbox, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    
    _defaultCheckBox->Create(this, wxID_ANY, "Set as Default Block Label");
    _defaultCheckBox->SetValue(property.getDefaultState());
    _defaultCheckBox->SetFont(*font);
    
    line6Sizer->Add(_defaultCheckBox, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxDefaultPosition, wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    footerSizer->Add(cancelButton, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    topSizer->Add(line1Sizer);
    topSizer->Add(line2Sizer);
    topSizer->Add(line3Sizer);
    topSizer->Add(meshSizeSizer, 0, wxALIGN_RIGHT);
    topSizer->Add(line4Sizer);
    topSizer->Add(line5Sizer);
    topSizer->Add(line6Sizer);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
}



void blockPropertyDialog::getBlockProperty(blockProperty &property)
{
    double value;
    long value2;
    
    property.setMaterialName(_materialComboBox->GetString(_materialComboBox->GetSelection()));
    
    property.setAutoMeshState(_autoMeshCheckBox->GetValue());
    
    if(!_autoMeshCheckBox->GetValue())
    {
        _meshSizeTextCtrl->GetValue().ToDouble(&value);
        property.setMeshSize(value);
        property.setMeshSizeType((meshSize)(_meshSizeComboBox->GetSelection() + 1));
    }
    
    if(_problem == physicProblems::PROB_MAGNETICS)
    {
        property.setCircuitName(_circuitComboBox->GetString(_circuitComboBox->GetSelection()));
        
        _numberOfTurnsTextCtrl->GetValue().ToLong(&value2);
        property.setNumberOfTurns(value2);
        
        property.setMagnetization(_magnetizationTextCtrl->GetValue());
    }
    
    _groupTextCtrl->GetValue().ToLong(&value2);
    property.setGroupNumber((unsigned int)value2);
    
    property.setIsExternalState(_externalRegionCheckbox->GetValue());
    property.setDefaultState(_defaultCheckBox->GetValue());
}



void blockPropertyDialog::onCheckAutoMesh(wxCommandEvent &event)
{
    _meshSizeTextCtrl->Enable(!_autoMeshCheckBox->GetValue());
    _meshSizeComboBox->Enable(!_autoMeshCheckBox->GetValue());
}



void blockPropertyDialog::onTextEdit(wxCommandEvent &event)
{
    double value;
    
    _meshSizeTextCtrl->GetValue().ToDouble(&value);
    _meshSizeTextCtrl->SetValue(wxEmptyString);
    std::ostream meshSizeStream(_meshSizeTextCtrl);
    meshSizeStream << fixed << std::setprecision(4) << value;
    
    _meshSizeComboBox->SetSelection(9);
}



void blockPropertyDialog::onComboBoxSelection(wxCommandEvent &event)
{
    meshSize selection = (meshSize)(_meshSizeComboBox->GetSelection() + 1);
    
    setMeshSizeTextCtrl(selection);
}



void blockPropertyDialog::setMeshSizeTextCtrl(meshSize meshType)
{
    switch(meshType)
    {
        case(meshSize::MESH_EXTREMELY_FINE):
            _meshSizeTextCtrl->SetValue("0.0001");
            break;
        case(meshSize::MESH_EXTRA_FINE):
            _meshSizeTextCtrl->SetValue("0.001");
            break;
        case(meshSize::MESH_FINER):
            _meshSizeTextCtrl->SetValue("0.01");
            break;
        case(meshSize::MESH_FINE):
            _meshSizeTextCtrl->SetValue("0.1");
            break;
        case(meshSize::MESH_NORMAL):
            _meshSizeTextCtrl->SetValue("1");
            break;
        case(meshSize::MESH_COARSE):
            _meshSizeTextCtrl->SetValue("10");
            break;
        case(meshSize::MESH_COARSER):
            _meshSizeTextCtrl->SetValue("100");
            break;
        case(meshSize::MESH_EXTRA_COARSE):
            _meshSizeTextCtrl->SetValue("1000");
            break;
        case(meshSize::MESH_EXTREMELY_COARSE):
            _meshSizeTextCtrl->SetValue("10000");
            break;
        case(meshSize::MESH_CUSTOM):
            break;
        default:
            _meshSizeTextCtrl->SetValue("1");
    }
}



blockPropertyDialog::~blockPropertyDialog()
{
    
}



wxBEGIN_EVENT_TABLE(blockPropertyDialog, wxDialog)
    EVT_CHECKBOX(generalFrameButton::ID_CHECKBOX1, blockPropertyDialog::onCheckAutoMesh)
    EVT_TEXT_ENTER(wxID_EDIT, blockPropertyDialog::onTextEdit)
    EVT_COMBOBOX(wxID_APPLY, blockPropertyDialog::onComboBoxSelection)
wxEND_EVENT_TABLE()