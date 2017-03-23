#include <UI/GeometryDialog/SegmentPropertyDialog.h>


segmentPropertyDialog::segmentPropertyDialog(wxWindow *par, std::vector<electricalBoundary> electricalBoundaryList, std::vector<conductorProperty> conductorList ,segmentProperty property) : wxDialog(par, wxID_ANY, "Segment Property")
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
    
    _electricalBoundaryList = electricalBoundaryList;
    _conductorList = conductorList;
    
    wxArrayString *boundaryNameList = new wxArrayString();
    boundaryNameList->Add("None");
    
    wxArrayString *conductorNameList = new wxArrayString();
    conductorNameList->Add("None");
    
    _problem = physicProblems::PROB_ELECTROSTATIC;
    
    for(std::vector<electricalBoundary>::iterator boundaryNameIterator = electricalBoundaryList.begin(); boundaryNameIterator != electricalBoundaryList.end(); ++boundaryNameIterator)
    {
        boundaryNameList->Add(boundaryNameIterator->getBoundaryName());
    }
    
    for(std::vector<conductorProperty>::iterator conductorIterator = conductorList.begin(); conductorIterator != conductorList.end(); ++conductorIterator)
    {
        conductorNameList->Add(conductorIterator->getName());
    }
    
    wxStaticText *boundaryText = new wxStaticText(this, wxID_ANY, "Boundary:");
    boundaryText->SetFont(*font);
    _boundaryListCombo->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(182, 21), *boundaryNameList);
    _boundaryListCombo->SetFont(*font);
    if(property.getBoundaryName() == "None")
    {
        _boundaryListCombo->SetSelection(0);
    }
    else
    {
        for(unsigned int i = 0; i < electricalBoundaryList.size(); i++)
        {
            if(electricalBoundaryList.at(i).getBoundaryName() == property.getBoundaryName())
            {
                _boundaryListCombo->SetSelection(i + 1);
                break;
            }
        }
    }
    
    line1Sizer->Add(boundaryText, 0, wxCENTER | wxALL, 6);
    line1Sizer->Add(_boundaryListCombo, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    _meshSpacingAutoCheckbox->Create(this, generalFrameButton::ID_CHECKBOX1, "Choose Mesh Spacing Automatically");
    _meshSpacingAutoCheckbox->SetFont(*font);
    _meshSpacingAutoCheckbox->SetValue(property.getMeshAutoState());
    
    line2Sizer->Add(_meshSpacingAutoCheckbox, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    
    wxStaticText *elementSizeText = new wxStaticText(this, wxID_ANY, "Local Element Size Along Line:");
    elementSizeText->SetFont(*font);
    _elementSizeTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, 20));
    _elementSizeTextCtrl->SetFont(*font);
    _elementSizeTextCtrl->Enable(!_meshSpacingAutoCheckbox->GetValue());
    std::ostream elementSizeStream(_elementSizeTextCtrl);
    elementSizeStream << std::setprecision(4);
    elementSizeStream << property.getElementSizeAlongLine();
    
    line3Sizer->Add(elementSizeText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line3Sizer->Add(_elementSizeTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *conductorText = new wxStaticText(this, wxID_ANY, "In Conductor:");
    conductorText->SetFont(*font);
    _conductorListCombobox->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(164, 21), *conductorNameList);
    _conductorListCombobox->SetFont(*font);
    if(property.getConductorName() == "None")
    {
        _conductorListCombobox->SetSelection(0);
    }
    else
    {
        for(unsigned int i = 0; i < conductorList.size(); i++)
        {
            if(conductorList.at(i).getName() == property.getConductorName())
            {
                _conductorListCombobox->SetSelection(i + 1);
            }
        }
    }
    
    line4Sizer->Add(conductorText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line4Sizer->Add(_conductorListCombobox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _hideSegmentCheckbox->Create(this, wxID_ANY, "Hide Segment in Postprocessor");
    _hideSegmentCheckbox->SetFont(*font);
    _hideSegmentCheckbox->SetValue(property.getHiddenState());
    
    line5Sizer->Add(_hideSegmentCheckbox, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    
    wxStaticText *groupText = new wxStaticText(this, wxID_ANY, "In Group:");
    groupText->SetFont(*font);
    _groupTextCtrl->Create(this, wxID_ANY, std::to_string(property.getGroupNumber()), wxDefaultPosition, wxSize(100, 20));
    _groupTextCtrl->SetFont(*font);
    
    line6Sizer->Add(groupText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line6Sizer->Add(_groupTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
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



segmentPropertyDialog::segmentPropertyDialog(wxWindow *par, std::vector<magneticBoundary> magneticBoundayList, segmentProperty property) : wxDialog(par, wxID_ANY, "Segment Property")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *line1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line2Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line3Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line4Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line5Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    wxArrayString *boundaryNameList = new wxArrayString();
    boundaryNameList->Add("None");
    
    _magneticBoundayList = magneticBoundayList;
    
    _problem = physicProblems::PROB_MAGNETICS;
    
    for(std::vector<magneticBoundary>::iterator boundaryNameIterator = magneticBoundayList.begin(); boundaryNameIterator != magneticBoundayList.end(); ++boundaryNameIterator)
    {
        boundaryNameList->Add(boundaryNameIterator->getBoundaryName());
    }
    
    wxStaticText *boundaryText = new wxStaticText(this, wxID_ANY, "Boundary:");
    boundaryText->SetFont(*font);
    _boundaryListCombo->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(182, 21), *boundaryNameList);
    _boundaryListCombo->SetFont(*font);
    if(property.getBoundaryName() == "None")
    {
        _boundaryListCombo->SetSelection(0);
    }
    else
    {
        for(int i = 0; i < magneticBoundayList.size(); i++)
        {
            if(magneticBoundayList.at(i).getBoundaryName() == property.getBoundaryName())
            {
                _boundaryListCombo->SetSelection(i + 1);
                break;
            }
        }
    }
    
    line1Sizer->Add(boundaryText, 0, wxCENTER | wxALL, 6);
    line1Sizer->Add(_boundaryListCombo, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    _meshSpacingAutoCheckbox->Create(this, generalFrameButton::ID_CHECKBOX1, "Choose Mesh Spacing Automatically", wxDefaultPosition, wxSize(250, 17));
    _meshSpacingAutoCheckbox->SetFont(*font);
    _meshSpacingAutoCheckbox->SetValue(property.getMeshAutoState());
    
    line2Sizer->Add(_meshSpacingAutoCheckbox, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    
    wxStaticText *elementSizeText = new wxStaticText(this, wxID_ANY, "Local Element Size Along Line:");
    elementSizeText->SetFont(*font);
    _elementSizeTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, 20));
    _elementSizeTextCtrl->SetFont(*font);
    _elementSizeTextCtrl->Enable(!_meshSpacingAutoCheckbox->GetValue());
    std::ostream elementSizeStream(_elementSizeTextCtrl);
    elementSizeStream << std::setprecision(4);
    elementSizeStream << property.getElementSizeAlongLine();
    
    line3Sizer->Add(elementSizeText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line3Sizer->Add(_elementSizeTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _hideSegmentCheckbox->Create(this, wxID_ANY, "Hide Segment in Postprocessor", wxDefaultPosition, wxSize(200, 17));
    _hideSegmentCheckbox->SetFont(*font);
    _hideSegmentCheckbox->SetValue(property.getHiddenState());
    
    line4Sizer->Add(_hideSegmentCheckbox, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    
    wxStaticText *groupText = new wxStaticText(this, wxID_ANY, "In Group:");
    groupText->SetFont(*font);
    _groupTextCtrl->Create(this, wxID_ANY, std::to_string(property.getGroupNumber()), wxDefaultPosition, wxSize(100, 20));
    _groupTextCtrl->SetFont(*font);
    
    line5Sizer->Add(groupText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line5Sizer->Add(_groupTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
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
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
}


/* This needs to be tested at a later date */
void segmentPropertyDialog::getSegmentProperty(segmentProperty &property)
{
    double value;
    long value2;
    
    property.setPhysicsProblem(_problem);

    property.setBoundaryName(_boundaryListCombo->GetString(_boundaryListCombo->GetSelection()));
        
    property.setMeshAutoState(_meshSpacingAutoCheckbox->GetValue());
    
    _elementSizeTextCtrl->GetValue().ToDouble(&value);
    property.setElementSizeAlongLine(value);
        
    if(_problem == physicProblems::PROB_ELECTROSTATIC)
    {
        property.setConductorName(_conductorListCombobox->GetString(_conductorListCombobox->GetSelection()));
    }
        
    property.setHiddenState(_hideSegmentCheckbox->GetValue());
        
    _groupTextCtrl->GetValue().ToLong(&value2);
    property.setGroupNumber((unsigned int)value2);
}



void segmentPropertyDialog::onMeshCheckBox(wxCommandEvent &event)
{
    _elementSizeTextCtrl->Enable(!_meshSpacingAutoCheckbox->GetValue());
}



segmentPropertyDialog::~segmentPropertyDialog()
{
    /*
    delete _elementSizeTextCtrl;
    delete _groupTextCtrl;
    delete _boundaryListCombo;
    delete _conductorListCombobox;
    delete _meshSpacingAutoCheckbox;
    delete _hideSegmentCheckbox;
     * */
}



wxBEGIN_EVENT_TABLE(segmentPropertyDialog, wxDialog)
    EVT_CHECKBOX(generalFrameButton::ID_CHECKBOX1, segmentPropertyDialog::onMeshCheckBox)
wxEND_EVENT_TABLE()