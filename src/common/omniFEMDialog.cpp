#include <common/omniFEMDialog.h>

OmniFEMDialog::OmniFEMDialog(wxWindow *parent, wxWindowID windowID, const wxString &title) : wxDialog(parent, windowID, title)
{
	windowPanel = new wxPanel(this);
}