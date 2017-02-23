#include <UI/EditMenu/OpenBoundaryDialog.h>


openBoundaryDialog::openBoundaryDialog() : wxDialog(NULL, wxID_ANY, "Open Boundary")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *line1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    wxArrayString *edgeTypeArray = new wxArrayString();
    edgeTypeArray->Add("Dirichlet");
    edgeTypeArray->Add("Neumann");
    
    wxStaticText *numLayersText = new wxStaticText(this, wxID_ANY, "Number of Layers:");
    numLayersText->SetFont(*font);
    _numberLayersTextCtrl->Create(this, wxID_ANY, "0", wxPoint(111, 12), wxSize(100, 20));
    _numberLayersTextCtrl->SetFont(*font);
    line1->Add(numLayersText, 0, wxCENTER | wxALL, 6);
    line1->Add(_numberLayersTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT | wxALIGN_RIGHT, 6);
    
    wxStaticText *radiusText = new wxStaticText(this, wxID_ANY, "Radius:");
    radiusText->SetFont(*font);
    _radiusTextCtrl->Create(this, wxID_ANY, "0", wxPoint(111, 38), wxSize(100, 20));
    _radiusTextCtrl->SetFont(*font);
    
    line2->Add(radiusText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line2->Add(59, 0, 0);
    line2->Add(_radiusTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxALIGN_RIGHT, 6);
    
    wxStaticText *horizontalCenterText = new wxStaticText(this, wxID_ANY, "Horizontal Center:");
    horizontalCenterText->SetFont(*font);
    _horizontalCenterTextCtrl->Create(this, wxID_ANY, "0", wxPoint(111, 64), wxSize(100, 20));
    _horizontalCenterTextCtrl->SetFont(*font);
    
    line3->Add(horizontalCenterText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line3->Add(1, 0, 0);
    line3->Add(_horizontalCenterTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxALIGN_RIGHT, 6);
    
    wxStaticText *verticalText = new wxStaticText(this, wxID_ANY, "Vertical Center:");
    verticalText->SetFont(*font);
    _verticalCenterTextCtrl->Create(this, wxID_ANY, "0", wxPoint(111, 90), wxSize(100, 20));
    _verticalCenterTextCtrl->SetFont(*font);
    
    line4->Add(verticalText, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    line4->Add(11, 0, 0);
    line4->Add(_verticalCenterTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT | wxALIGN_RIGHT, 6);
    
    wxStaticText *edgeTypeText = new wxStaticText(this, wxID_ANY, "Edge Type:");
    edgeTypeText->SetFont(*font);
    _edgeTypeComboBox->Create(this, wxID_ANY, wxEmptyString, wxPoint(111, 116), wxSize(100, 21), *edgeTypeArray);
    _edgeTypeComboBox->SetFont(*font);
    _edgeTypeComboBox->SetSelection(0);
    
    line5->Add(edgeTypeText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line5->Add(34, 0, 0);
    line5->Add(_edgeTypeComboBox, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT | wxALIGN_RIGHT, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxPoint(55, 143), wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_ANY, "Cancel", wxPoint(136, 143), wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    footerSizer->Add(cancelButton, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    topSizer->Add(line1);
    topSizer->Add(line2);
    topSizer->Add(line3);
    topSizer->Add(line4);
    topSizer->Add(line5);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
}



void openBoundaryDialog::getParameters(long &numberLayers, double &radius, double &horizontalCenter, double &verticalCenter, OpenBoundaryEdge &edgeType)
{
    double value1;
    long value2;
    int selection;
    
    _numberLayersTextCtrl->GetValue().ToLong(&value2);
    numberLayers = value2;
    
    _radiusTextCtrl->GetValue().ToDouble(&value1);
    radius = value1;
    
    _horizontalCenterTextCtrl->GetValue().ToDouble(&value1);
    horizontalCenter = value1;
    
    _verticalCenterTextCtrl->GetValue().ToDouble(&value1);
    verticalCenter = value1;
    
    selection = _edgeTypeComboBox->GetSelection() + 1;
    edgeType = (OpenBoundaryEdge)selection;
}



openBoundaryDialog::~openBoundaryDialog()
{
    
}