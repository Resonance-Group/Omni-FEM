#ifndef SCALINGDIALOG_H_
#define SCALINGDIALOG_H_

#include <string>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>

class scaleDialog : public wxDialog
{
private:
    wxTextCtrl *_scalingFactorTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_baseFactorXTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_baseFactorYTextCtrl = new wxTextCtrl();
    
public:
    scaleDialog(wxWindow *par, wxRealPoint &selectedPoint);
    
    ~scaleDialog();
    
    void getScalingParameters(double &scalingFactor, wxRealPoint &baseFactor);
};

#endif