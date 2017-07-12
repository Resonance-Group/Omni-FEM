#ifndef MIRRORDIALOG_H_
#define MIRRORDIALOG_H_

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>


//! Dialog used to perform a mirror operation
/*!
    This dialog is used in order to 
    enter in two points to create a mirror line.
    For documentation regarding the wxDialog class, refer to 
    the following link:
    http://docs.wxwidgets.org/3.1.0/classwx_dialog.html
*/ 
class mirrorDialog : public wxDialog
{
private:
    //! Text box used to enter in the first coordinate point in the X-plane
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_firstPointXTextCtrl = new wxTextCtrl();
    
    //! Text box used to enter in the first coordinate point in the Y-plane
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_firstPointYTextCtrl = new wxTextCtrl();
    
    //! Text box used to enter in the second coordinate point in the X-plane
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_secondPointXTextCtrl = new wxTextCtrl();
    
    //! Text box used to enter in the second coordinate point in the Y-plane
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_secondPointYTextCtrl = new wxTextCtrl();
    
public:
    //! Constructor for the class
    /*!
        Draws the widgets in the correct locations
        \param par Pointer to the parent window
    */ 
    mirrorDialog(wxWindow *par);

    //! Retrieves the two points that the user enters
    /*!
        This function will return the points that the user entered into the dialog
        \param firstPoint The first point for the mirror line
        \param secondPoint The second point for the mirror line
    */ 
    void getPoints(wxRealPoint &firstPoint, wxRealPoint &secondPoint);
    
    //! Destrcutor for the class
    ~mirrorDialog();
};


#endif