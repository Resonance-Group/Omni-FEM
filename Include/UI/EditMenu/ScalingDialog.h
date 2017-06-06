#ifndef SCALINGDIALOG_H_
#define SCALINGDIALOG_H_

#include <string>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>

//! Class that handles the dialog creation of the scale geometry dialog
/*!
    This class will create a dialog allowing the user
    to enter the parameters for scaling geometry.
    The parameters that the user needs to enter in
    are the scaling factor and the base point of the scaling.
    When the user clicks on the ok button, this class will generate a 
    wxID_OK event. For additional documentation on the wxDialog
    class, refer to the following link:
    http://docs.wxwidgets.org/3.1.0/classwx_dialog.html
*/ 
class scaleDialog : public wxDialog
{
private:
    
    //! Text box for allowing the user to enter the scaling factor
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_scalingFactorTextCtrl = new wxTextCtrl();
    
    //! Text box used to enter in the x-point for the base point of the scale operation
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_baseFactorXTextCtrl = new wxTextCtrl();
    
    //! Text box used to enter in the y-point for the base point of the scale operation
    /*!
        For documentation on the wxTextCtrl class, refer to
        the following link:
        http://docs.wxwidgets.org/trunk/classwx_text_ctrl.html
    */ 
    wxTextCtrl *_baseFactorYTextCtrl = new wxTextCtrl();
    
public:

    //! Constructor for the class
    /*!
     * This constructor will create the dialog that the user
     * will see in order to enter the parameters of the scale
     * geometry operation. The constructor can take on a pre
     * selected point and display this accordingly on the dialog
     * when it it first created
     * \param par Pointer to the parent window
     * \param selectedPoint THe point that will be first display to the user
     */ 
    scaleDialog(wxWindow *par, wxRealPoint &selectedPoint);
    
    //! Retrieves the parameters that the user entered
    /*!
        This function is called when the user clicks on the ok button and a
        wxID_OK event is generated. This function will retrieve the 
        parameters that the user entered into the dialog
        \param scalingFactor The factor by which to scale the geometry
        \param baseFactor The base point of the scaling operation
    */ 
    void getScalingParameters(double &scalingFactor, wxRealPoint &baseFactor);
    
    //1 The destructor of the class
    ~scaleDialog();
};

#endif