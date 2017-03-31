#include <UI/GeometryDialog/ArcSegmentDialog.h>



arcSegmentDialog::arcSegmentDialog(wxWindow *par, std::vector<electricalBoundary> list) : wxDialog(par, wxID_ANY, "Arc Segment")
{
    _problem = physicProblems::PROB_ELECTROSTATIC;
    
    _localElectricalBoundaryList = list;
    
    _nameArray.Add("None");
    
    for(std::vector<electricalBoundary>::iterator electricalIterator = _localElectricalBoundaryList.begin(); electricalIterator != _localElectricalBoundaryList.end(); ++electricalIterator)
    {
        _nameArray.Add(electricalIterator->getBoundaryName());
    }
    
    createDialog();
}



arcSegmentDialog::arcSegmentDialog(wxWindow *par, std::vector<magneticBoundary> list) : wxDialog(par, wxID_ANY, "Arc Segment")
{
    _problem = physicProblems::PROB_MAGNETICS;
    
    _localMagneticBoundaryList = list;
    
    _nameArray.Add("None");
    
    for(std::vector<magneticBoundary>::iterator magneticIterator = _localMagneticBoundaryList.begin(); magneticIterator != _localMagneticBoundaryList.end(); ++magneticIterator)
    {
        _nameArray.Add(magneticIterator->getBoundaryName());
    }
    
    createDialog();
}



void arcSegmentDialog::updateInterface()
{
    std::ostream arcAngleStream(_arcAngleTextCtrl);
    
    _arcAngleTextCtrl->SetValue(wxEmptyString);
    _segmentTextCtrl->SetValue(wxEmptyString);
    
    arcAngleStream << std::setprecision(3);
    arcAngleStream << _localArcShape.getArcAngle();
    
    _segmentTextCtrl->SetValue(std::to_string(_localArcShape.getnumSegments()));
    
    _boundaryComboBox->SetSelection(0);
}



void arcSegmentDialog::createDialog()
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *line1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line2Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line3Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    wxFloatingPointValidator<double> angleValidator(3, NULL, wxNUM_VAL_NO_TRAILING_ZEROES);
    angleValidator.SetRange(-360, 360);
    
    wxIntegerValidator<int> segmentValidator;
    segmentValidator.SetMax(100);
    segmentValidator.SetMin(3);
    
    wxStaticText *arcAngleText = new wxStaticText(this, wxID_ANY, "Arc Angle (deg):");
    arcAngleText->SetFont(*font);
    _arcAngleTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20), 0, angleValidator);
    _arcAngleTextCtrl->SetFont(*font);
    
    line1Sizer->Add(arcAngleText, 0, wxCENTER | wxALL, 6);
    line1Sizer->Add(18, 0, 0);
    line1Sizer->Add(_arcAngleTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *maxSegmentText = new wxStaticText(this, wxID_ANY, "Number Segments:");
    maxSegmentText->SetFont(*font);
    _segmentTextCtrl->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20), 0, segmentValidator);
    _segmentTextCtrl->SetFont(*font);
    
    line2Sizer->Add(maxSegmentText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line2Sizer->Add(_segmentTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *boundaryText = new wxStaticText(this, wxID_ANY, "Set Boundary:");
    boundaryText->SetFont(*font);
    _boundaryComboBox->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 21), _nameArray);
    _boundaryComboBox->SetFont(*font);
    
    line3Sizer->Add(boundaryText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line3Sizer->Add(29, 0, 0);
    line3Sizer->Add(_boundaryComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxDefaultPosition, wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    footerSizer->Add(cancelButton, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    topSizer->Add(line1Sizer);
    topSizer->Add(line2Sizer);
    topSizer->Add(line3Sizer);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
    
    updateInterface();
}



void arcSegmentDialog::clearParameter()
{
    _localArcShape.setArcAngle(0);
    _localArcShape.setNumSegments(3);
    updateInterface();
}



void arcSegmentDialog::setArcParameter(arcShape shape)
{
    _localArcShape = shape;
    updateInterface();
}



void arcSegmentDialog::getArcParameter(arcShape &shape)
{
    double value;
    long value2;
    
    _arcAngleTextCtrl->GetValue().ToDouble(&value);
    shape.setArcAngle(value);
    
    _segmentTextCtrl->GetValue().ToLong(&value2);
    shape.setNumSegments(value2);
    
    shape.getSegmentProperty()->setBoundaryName(_boundaryComboBox->GetString(_boundaryComboBox->GetSelection()));
}