#ifndef COPYDIALOG_H_
#define COPYDIALOG_H_

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobut.h>
#include <wx/valnum.h>

#include <common/enums.h>


class moveCopyDialog : public wxDialog
{
private:
    //! This boolean keeps track of if the dialog box is to be a move or copy dialog
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
    moveCopyDialog(wxWindow *par, bool isMove);
    
    ~moveCopyDialog();

    bool rotationIsSelected();
    
    void getRotationMove(wxPoint &aboutPoint, double &angularShift)
    {
        double temp1;
        wxPoint temp2;
        unsigned int deleteMe = 0;
        getRotationCopy(temp2, temp1, deleteMe);
        aboutPoint = temp2;
        angularShift = temp1;
    }
    
    void getRotationCopy(wxPoint &aboutPoint, double &angularShift, unsigned int &numberCopies);
    
    void getTranslationMove(double &horizontalShift, double &veriticalShift)
    {
        double temp1, temp2;
        unsigned int deleteMe = 0;
        getTranslationCopy(temp1, temp2, deleteMe);
        horizontalShift = temp1;
        veriticalShift = temp2;
    }
    
    void getTranslationCopy(double &horizontalShift, double &veriticalShift, unsigned int &numberCopies);
    
private:
    wxDECLARE_EVENT_TABLE();
};

#endif
