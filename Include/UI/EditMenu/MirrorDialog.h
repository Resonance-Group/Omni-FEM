#ifndef MIRRORDIALOG_H_
#define MIRRORDIALOG_H_

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>


class mirrorDialog : public wxDialog
{
private:
    wxTextCtrl *_firstPointXTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_firstPointYTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_secondPointXTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_secondPointYTextCtrl = new wxTextCtrl();
    
public:
    mirrorDialog(wxWindow *par);

    ~mirrorDialog();
    
    void getPoints(wxPoint &firstPoint, wxPoint &secondPoint);
};


#endif