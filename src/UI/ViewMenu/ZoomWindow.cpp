#include <UI/ViewMenu/ZoomWindow.h>

zoomWindow::zoomWindow() : wxDialog(NULL, wxID_ANY, "Zoom Window")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *line1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line2Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line3Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line4Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    wxStaticText *topText = new wxStaticText(this, wxID_ANY, "Top:");
    topText->SetFont(*font);
    _topTextCtrl->Create(this, wxID_ANY, "10", wxPoint(76, 12), wxSize(100, 20));
    _topTextCtrl->SetFont(*font);
    
    line1Sizer->Add(topText, 0, wxCENTER | wxALL, 6);
    line1Sizer->Add(32, 0, 0);
    line1Sizer->Add(_topTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *bottomText = new wxStaticText(this, wxID_ANY, "Bottom:");
    bottomText->SetFont(*font);
    _bottomTextCtrl->Create(this, wxID_ANY, "10", wxPoint(76, 38), wxSize(100, 20));
    _bottomTextCtrl->SetFont(*font);
    
    line2Sizer->Add(bottomText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line2Sizer->Add(12, 0, 0);
    line2Sizer->Add(_bottomTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *leftText = new wxStaticText(this, wxID_ANY, "Left:");
    leftText->SetFont(*font);
    _leftTextCtrl->Create(this, wxID_ANY, "10", wxPoint(76, 64), wxSize(100, 20));
    _leftTextCtrl->SetFont(*font);
    
    line3Sizer->Add(leftText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line3Sizer->Add(30, 0, 0);
    line3Sizer->Add(_leftTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *rightText = new wxStaticText(this, wxID_ANY, "Right:");
    rightText->SetFont(*font);
    _rightTextCtrl->Create(this, wxID_ANY, "10", wxPoint(76, 90), wxSize(100, 20));
    _rightTextCtrl->SetFont(*font);
    
    line4Sizer->Add(rightText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line4Sizer->Add(23, 0, 0);
    line4Sizer->Add(_rightTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxPoint(20, 116), wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_ANY, "Cancel", wxPoint(101, 116), wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    footerSizer->Add(cancelButton, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    topSizer->Add(line1Sizer);
    topSizer->Add(line2Sizer);
    topSizer->Add(line3Sizer);
    topSizer->Add(line4Sizer);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
}



void zoomWindow::getParameters(double &topValue, double &bottomValue, double &leftValue, double &rightValue)
{
    double value;
    
    _topTextCtrl->GetValue().ToDouble(&value);
    topValue = value;
    
    _bottomTextCtrl->GetValue().ToDouble(&value);
    bottomValue = value;
    
    _leftTextCtrl->GetValue().ToDouble(&value);
    leftValue = value;
    
    _rightTextCtrl->GetValue().ToDouble(&value);
    rightValue = value;
}



zoomWindow::~zoomWindow()
{
    
}