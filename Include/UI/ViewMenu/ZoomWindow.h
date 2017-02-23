#ifndef ZOOMWINDOW_H_
#define ZOOMWINDOW_H_

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>


class zoomWindow : public wxDialog
{
private:
    wxTextCtrl *_topTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_bottomTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_leftTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_rightTextCtrl = new wxTextCtrl();
    
public:
    zoomWindow();
    
    ~zoomWindow();
    
    void getParameters(double &topValue, double &bottomValue, double &leftValue, double &rightValue);
};


#endif