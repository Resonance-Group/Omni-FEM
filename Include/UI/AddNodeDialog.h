#ifndef ADD_NODE_DIALOG_H_
#define ADD_NODE_DIALOG_H_

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>

class addNodeDialog : public wxDialog
{
private:
	wxTextCtrl *p_setXValueCtrl = new wxTextCtrl();
	
	wxTextCtrl *p_setYValueCtrl = new wxTextCtrl();
	
public:

	addNodeDialog(wxWindow *par) : wxDialog(par, wxID_ANY, "Add Node")
	{
		wxFont font = wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
		
		wxBoxSizer *xValueSizer = new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer *yValueSizer = new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
		
		wxStaticText *xText = new wxStaticText(this, wxID_ANY, "X-Value: ");
		xText->SetFont(font);
		
		p_setXValueCtrl->Create(this, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize);
		p_setXValueCtrl->SetValidator(wxTextValidator(wxFILTER_NUMERIC));
		
		xValueSizer->Add(xText, 0, wxCENTER | wxALL, 6);
		xValueSizer->Add(p_setXValueCtrl, 0, wxTOP | wxBOTTOM | wxRIGHT, 6);
		
		wxStaticText *yText = new wxStaticText(this, wxID_ANY, "Y-Value: ");
		yText->SetFont(font);
		
		p_setYValueCtrl->Create(this, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize);
		p_setYValueCtrl->SetValidator(wxTextValidator(wxFILTER_NUMERIC));
		
		yValueSizer->Add(yText,0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
		yValueSizer->Add(p_setYValueCtrl,0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
		
		wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxDefaultPosition, wxSize(75, 23));
		okButton->SetFont(font);
		
		wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(75, 23));
		cancelButton->SetFont(font);
		
		footerSizer->Add(okButton, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
		footerSizer->Add(cancelButton, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
		
		topSizer->Add(xValueSizer);
		topSizer->Add(yValueSizer);
		topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
		
		SetSizerAndFit(topSizer);
	}
	
	wxRealPoint getPoint()
	{
		double xValue = 0;
		double yValue = 0;
		
		p_setXValueCtrl->GetValue().ToDouble(&xValue);
		p_setYValueCtrl->GetValue().ToDouble(&yValue);
		
		return wxRealPoint(xValue, yValue);
	}
};


#endif