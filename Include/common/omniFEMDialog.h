#ifndef OMNIFEMDLG_H_
#define OMNIFEMDLG_H_

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/treectrl.h>


/*! /brief This class is a custom class that will be used for creating any dialog boxes within OmniFEM */
class OmniFEMDialog : public wxDialog
{
public:
	OmniFEMDialog(wxWindow *parent, wxWindowID windowID, const wxString &title);
	void addComponent(wxControl *controlComponent);
	
private:
		wxPanel *windowPanel;

};

#endif