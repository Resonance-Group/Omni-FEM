//#include <UI/BlockPropertyDialog.h>
#include <UI/GeometryDialog/BlockPropertyDialog.h>


blockPropertyDialog::blockPropertyDialog(wxWindow *par, std::vector<magneticMaterial> material, std::vector<circuitProperty> circuit, blockProperty property, bool isAxisymmetric) : wxDialog(par, wxID_ANY, "Block Property")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *line1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line2Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line3Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line4Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line5Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line6Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line7Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line8Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line9Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    _problem = physicProblems::PROB_MAGNETICS;
    
    _magneticMaterialList = material;
    _circuitList = circuit;
    
    wxArrayString *materialNameList = new wxArrayString();
    materialNameList->Add("None");
    
    wxArrayString *circuitNameList = new wxArrayString();
    circuitNameList->Add("None");
    
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
    if(!property.getMagneticMaterialSetState())
    {
        _materialComboBox->SetSelection(0);
    }
    else
    {
        for(unsigned int i = 0; i < _magneticMaterialList.size(); i++)
        {
            if(_magneticMaterialList.at(i).getName() == property.getMagneticMaterial().getName())
            {
                _materialComboBox->SetSelection(i + 1);
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
    _meshSizeTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20));
    _meshSizeTextCtrl->SetFont(*font);
    _meshSizeTextCtrl->Enable(!property.getAutoMeshState());
    std::ostream meshSizeStream(_meshSizeTextCtrl);
    meshSizeStream << std::setprecision(4);
    meshSizeStream << property.getMeshSize();
    
    line3Sizer->Add(meshText, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    line3Sizer->Add(75, 0, 0);
    line3Sizer->Add(_meshSizeTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *circuitText = new wxStaticText(this, wxID_ANY, "In Circuit:");
    circuitText->SetFont(*font);
    _circuitComboBox->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 23), *circuitNameList);
    _circuitComboBox->SetFont(*font);
    if(!property.getCircuitSetState())
    {
        _circuitComboBox->SetSelection(0);
    }
    else
    {
        for(unsigned int i = 0; i < _circuitList.size(); i++)
        {
            if(_circuitList.at(i).getName() == property.getCircuit().getName())
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
    _numberOfTurnsTextCtrl->Create(this, wxID_ANY, std::to_string(property.getNumberOfTurns()), wxDefaultPosition, wxSize(121, 20));
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
    _groupTextCtrl->Create(this, wxID_ANY, std::to_string(property.getGroupNumber()), wxDefaultPosition, wxSize(121, 20));
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
    wxBoxSizer *line4Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line5Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line6Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    _problem = physicProblems::PROB_MAGNETICS;
    
    _electricalMaterialList = material;
    
    wxArrayString *materialNameList = new wxArrayString();
    materialNameList->Add("None");
    
    for(std::vector<electrostaticMaterial>::iterator materialIterator = _electricalMaterialList.begin(); materialIterator != _electricalMaterialList.end(); ++materialIterator)
    {
        materialNameList->Add(materialIterator->getName());
    }
    
    wxStaticText *materialText = new wxStaticText(this, wxID_ANY, "Material:");
    materialText->SetFont(*font);
    _materialComboBox->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(207, 21), *materialNameList);
    _materialComboBox->SetFont(*font);
    if(!property.getElectricMaterialSetState())
    {
        _materialComboBox->SetSelection(0);
    }
    else
    {
        for(unsigned int i = 0; i < _electricalMaterialList.size(); i++)
        {
            if(_electricalMaterialList.at(i).getName() == property.getElectricMaterial().getName())
            {
                _materialComboBox->SetSelection(i + 1);
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
    _meshSizeTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20));
    _meshSizeTextCtrl->SetFont(*font);
    _meshSizeTextCtrl->Enable(!property.getAutoMeshState());
    std::ostream meshSizeStream(_meshSizeTextCtrl);
    meshSizeStream << std::setprecision(4);
    meshSizeStream << property.getMeshSize();
    
    line3Sizer->Add(meshText, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    line3Sizer->Add(75, 0, 0);
    line3Sizer->Add(_meshSizeTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *groupText = new wxStaticText(this, wxID_ANY, "In Group:");
    groupText->SetFont(*font);
    _groupTextCtrl->Create(this, wxID_ANY, std::to_string(property.getGroupNumber()), wxDefaultPosition, wxSize(121, 20));
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
    
    if(_problem == physicProblems::PROB_ELECTROSTATIC)
    {
        property.setPhysicsProblem(physicProblems::PROB_ELECTROSTATIC);
    }
    else
        property.setPhysicsProblem(physicProblems::PROB_MAGNETICS);
    
    if(_materialComboBox->GetSelection() != 0)
    {
        for(int i = 1; i < _materialComboBox->GetCount(); i++)
        {
            if(_problem == physicProblems::PROB_ELECTROSTATIC)
            {
                if(_electricalMaterialList.at(i - 1).getName() == _materialComboBox->GetString(_materialComboBox->GetSelection()))
                {
                    property.setElectricMaterial(_electricalMaterialList.at(i - 1));
                    break;
                }
            }
            else if(_problem == physicProblems::PROB_MAGNETICS)
            {
                if(_magneticMaterialList.at(i - 1).getName() == _materialComboBox->GetString(_materialComboBox->GetSelection()))
                {
                    property.setMagneticMaterial(_magneticMaterialList.at(i - 1));
                    break;
                }
            }
        }
    }
    
    property.setAutoMeshState(_autoMeshCheckBox->GetValue());
    
    if(!_autoMeshCheckBox->GetValue())
    {
        _meshSizeTextCtrl->GetValue().ToDouble(&value);
        property.setMeshSize(value);  
    }
    
    if(_problem == physicProblems::PROB_MAGNETICS)
    {
        if(_circuitComboBox->GetSelection() != 0)
        {
            for(int i = 1; i < _circuitComboBox->GetCount(); i++)
            {
                if(_circuitList.at(i - 1).getName() == _circuitComboBox->GetString(i))
                {
                    property.setCircuit(_circuitList.at(i - 1));
                    break;
                }
            }  
        }
        
        _numberOfTurnsTextCtrl->GetValue().ToLong(&value2);
        property.setNumberOfTurns(value2);
        
        _magnetizationTextCtrl->GetValue().ToDouble(&value);
        property.setMagnetization(value);
    }
    
    _groupTextCtrl->GetValue().ToLong(&value2);
    property.setGroupNumber((unsigned int)value2);
    
    property.setIsExternalState(_externalRegionCheckbox->GetValue());
    property.setDefaultState(_defaultCheckBox->GetValue());
}



void blockPropertyDialog::onCheckAutoMesh(wxCommandEvent &event)
{
    _meshSizeTextCtrl->Enable(!_autoMeshCheckBox->GetValue());
}



blockPropertyDialog::~blockPropertyDialog()
{
    
}



wxBEGIN_EVENT_TABLE(blockPropertyDialog, wxDialog)
    EVT_CHECKBOX(generalFrameButton::ID_CHECKBOX1, blockPropertyDialog::onCheckAutoMesh)
wxEND_EVENT_TABLE()