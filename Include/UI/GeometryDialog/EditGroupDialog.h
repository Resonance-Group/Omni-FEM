#ifndef EDIT_GROUP_DIALOG_H_
#define EDIT_GROUP_DIALOG_H_

#include <string>

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/valnum.h>

class editGroupNumberDialog : public wxDialog
{
private:
    
    wxTextCtrl *_groupNumberTextCtrl = new wxTextCtrl();

public:
    editGroupNumberDialog(wxWindow *par, unsigned int groupNumber);
    
    unsigned int getGroupNumber();
};





#endif