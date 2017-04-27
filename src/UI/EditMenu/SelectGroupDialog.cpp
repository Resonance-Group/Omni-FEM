#include <UI/EditMenu/SelectGroupDialog.h>


selectGroupDialog::selectGroupDialog(wxWindow *par) : wxDialog(par, wxID_ANY, "Select Group")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *line1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line2Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    wxIntegerValidator<unsigned int> groupValidator;
    groupValidator.SetMin(0);
    groupValidator.SetMax(65535);
    
    _nodeRadioButton->Create(this, wxID_ANY, "Node");
    _nodeRadioButton->SetFont(*font);
    _lineRadioButton->Create(this, wxID_ANY, "Line");
    _lineRadioButton->SetFont(*font);
    _arcRadioButton->Create(this, wxID_ANY, "Arcs");
    _arcRadioButton->SetFont(*font);
    _labelRadioButton->Create(this, wxID_ANY, "Block Labels");
    _labelRadioButton->SetFont(*font);
    _allRadioButton->Create(this, wxID_ANY, "All Geometry");
    _allRadioButton->SetFont(*font);
    
    line1Sizer->Add(_nodeRadioButton, 0, wxCENTER | wxALL, 6);
    line1Sizer->Add(_lineRadioButton, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    line1Sizer->Add(_arcRadioButton, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    line1Sizer->Add(_labelRadioButton, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    line1Sizer->Add(_allRadioButton, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *groupText = new wxStaticText(this, wxID_ANY, "Group Number:");
    groupText->SetFont(*font);
    _groupNumberSelect->Create(this, wxID_ANY, "0", wxDefaultPosition, wxSize(100, 20), 0, groupValidator);
    _groupNumberSelect->SetFont(*font);
    
    line2Sizer->Add(groupText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line2Sizer->Add(_groupNumberSelect, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxDefaultPosition, wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    footerSizer->Add(cancelButton, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    topSizer->Add(line1Sizer, 0, wxLEFT | wxRIGHT | wxTOP, 6);
    topSizer->Add(line2Sizer, 0, wxALL , 6);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
}


EditGeometry selectGroupDialog::getGroupNumber(unsigned int &groupNumber)
{
    long value;
    
    _groupNumberSelect->GetValue().ToLong(&value);
    groupNumber = (unsigned int)value;
    
    if(_nodeRadioButton->GetValue())
        return EditGeometry::EDIT_NODES;
    else if(_lineRadioButton->GetValue())
        return EditGeometry::EDIT_LINES;
    else if(_arcRadioButton->GetValue())
        return EditGeometry::EDIT_ARCS;
    else if(_labelRadioButton->GetValue())
        return EditGeometry::EDIT_LABELS;
    else if(_allRadioButton->GetValue())
        return EditGeometry::EDIT_ALL;
    
    return EditGeometry::EDIT_NONE;
}