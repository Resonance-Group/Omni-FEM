#ifndef SELECT_GROUP_DIALOG_H_
#define SELECT_GROUP_DIALOG_H_

#include <wx/wx.h>
#include <wx/radiobut.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/valnum.h>

#include <common/enums.h>

class selectGroupDialog : public wxDialog
{
private:

    wxRadioButton *_nodeRadioButton = new wxRadioButton();
    
    wxRadioButton *_lineRadioButton = new wxRadioButton();
    
    wxRadioButton *_arcRadioButton = new wxRadioButton();
    
    wxRadioButton *_labelRadioButton = new wxRadioButton();
    
    wxRadioButton *_allRadioButton = new wxRadioButton();
    
    wxTextCtrl *_groupNumberSelect = new wxTextCtrl();
public:
    selectGroupDialog(wxWindow *par);
    
    EditGeometry getGroupNumber(unsigned int &groupNumber);
};


#endif