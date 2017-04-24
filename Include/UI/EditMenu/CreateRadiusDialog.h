#ifndef CREATE_RADIUS_DIALOG_H_
#define CREATE_RADIUS_DIALOG_H_

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/valnum.h>
#include <wx/sizer.h>



class createRadiusDialog : public wxDialog
{
private:

    wxTextCtrl *_radiusTextCtrl = new wxTextCtrl();
    
public:
    createRadiusDialog(wxWindow *par);
    
    double getRadius();
};





#endif