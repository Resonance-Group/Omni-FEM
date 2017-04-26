#ifndef CREATE_FILLET_DIALOG_H_
#define CREATE_FILLET_DIALOG_H_

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/valnum.h>
#include <wx/sizer.h>



class createFilletDialog : public wxDialog
{
private:

    wxTextCtrl *_radiusTextCtrl = new wxTextCtrl();
    
public:
    createFilletDialog(wxWindow *par);
    
    double getRadius();
};





#endif