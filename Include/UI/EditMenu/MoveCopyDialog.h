#ifndef COPYDIALOG_H_
#define COPYDIALOG_H_

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobut.h>

#include <common/enums.h>


class moveCopyDialog : public wxDialog
{
private:
    bool _isMove;

    wxTextCtrl *_angularShiftTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_aboutPointXTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_aboutPointYTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_horizontalShiftTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_verticalShiftTextCtrl = new wxTextCtrl();
    
    wxTextCtrl *_numberCopiesTextCtrl = new wxTextCtrl();
    
    wxRadioButton *_rotationCheckBox = new wxRadioButton();
    
    wxRadioButton *_translationCheckBox = new wxRadioButton();
    
    void onRotationCheck(wxCommandEvent &event);
    
    void onTranslationCheck(wxCommandEvent &event);
    
public:
    moveCopyDialog(bool isMove);
    
    ~moveCopyDialog();

    bool rotationIsSelected();
    
    void getRotationCopy(wxPoint &aboutPoint, double &angularShift, long &numberCopies);
    
    void getTranslationCopy(double &horizontalShift, double &veriticalShift, long &numberCopies);
    
private:
    wxDECLARE_EVENT_TABLE();
};

#endif
