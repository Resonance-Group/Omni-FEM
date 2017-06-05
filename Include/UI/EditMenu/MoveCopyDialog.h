#ifndef COPYDIALOG_H_
#define COPYDIALOG_H_

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobut.h>
#include <wx/valnum.h>

#include <common/enums.h>

//! Dialog used to allow the user to move a geometry shape or to copy one
/*!
    The moving and copying dialogs are handled by the same class.
    The difference between a moving and copying dialog is the state of a boolean
    For documentation on the wxDialog class, refer to the following link:
    http://docs.wxwidgets.org/3.1.0/classwx_dialog.html
*/ 
class moveCopyDialog : public wxDialog
{
private:

    //! Boolean used to determine if the dialog is for moving or copying
    /*!
        If true, this class will function as a dialog
        for moving geometry pieces. If false this class will
        function as a copy dialog. This variable is set in the
        constructor of the class.
    */ 
    bool _isMove;
    
    //! Text box used to set the angular shift of the geometry
    /*!
        For copying, this will function as the degrees of rotation between
        each instance of the copy
    */ 
    wxTextCtrl *_angularShiftTextCtrl = new wxTextCtrl();
    
    //! Text box used to set the center X position of the rotation
    wxTextCtrl *_aboutPointXTextCtrl = new wxTextCtrl();
    
    //! Text box used to set the center Y position of the rotation
    wxTextCtrl *_aboutPointYTextCtrl = new wxTextCtrl();
    
    //! Text box used to set the amount to move a geomerty piece by in the x direction
    /*!
        For copying, this is the distance between two instances in the x-direction
    */ 
    wxTextCtrl *_horizontalShiftTextCtrl = new wxTextCtrl();
    
    //! Text box used to set the amount to move a geomerty piece by in the y-direction
    /*!
        For copying, this is the distance between two instances in the y-direction
    */
    wxTextCtrl *_verticalShiftTextCtrl = new wxTextCtrl();
    
    //! Text box used to set the number of copies that need to be created
    /*!
        This text box is only displayed if the user needs 
        to copy the geometry shapes
    */ 
    wxTextCtrl *_numberCopiesTextCtrl = new wxTextCtrl();
    
    //! Radio button used to select the rotation
    /*!
        This radio button is used to select the 
        rotation feature of the move/copy dialog.
        This will let the program know that the user 
        has selected to perform a rotation
    */ 
    wxRadioButton *_rotationCheckBox = new wxRadioButton();
    
    //! Radio button used to select the translation
    /*!
        This radio button is used to select the 
        translation feature of the move/copy dialog.
        This will let the program know that the user 
        has selected to perform a translation
    */ 
    wxRadioButton *_translationCheckBox = new wxRadioButton();
    
    //! Event procedure for when the user clicks on the rotation radio button
    /*!
        This function is executed each time the user clicks on the 
        rotation rodio button. This function will enable
        and of the text boxes that are related to the rotation 
        and disable any text boxes that are related to the 
        translation
    */ 
    void onRotationCheck(wxCommandEvent &event);
    
    //! Event procedure for when the user clicks on the translation radio button
    /*!
        This function is executed each time the user clicks on the 
        translation rodio button. This function will enable
        and of the text boxes that are related to the translation 
        and disable any text boxes that are related to the 
        rotation.
    */ 
    void onTranslationCheck(wxCommandEvent &event);
    
public:

    //! The constructor for the class
    /*!
        This constructor will create all of widgets 
        for the copy/move dialog. Depending on the
        state of the isMove, the number of copies 
        text box will be created.
        \param par The pointer to the parent window
        \param isMove Boolean used to indicate if the class should 
                        draw a dialog for moving geometry (true) or
                        for copying geometry (false)
    */
    moveCopyDialog(wxWindow *par, bool isMove);
    
    //! The destrcutor for the class
    ~moveCopyDialog();
    
    //! Retrieves whether or not the dialog was selected for rotation
    /*!
        In order to know if the user selected on the dialog to 
        perform a rotation operation, this function must be called.
        \return Returns true if the user selected to rotate. 
                Retuns false if the user selected to translate
    */ 
    bool rotationIsSelected();
    
    //! Retrieves the center point and angular shift for rotating a geomerty
    /*!
        This function is meant to be executed if the user is not
        copying geometry shapes. This function is only meant to be called
        during a move operation
        \param aboutPoint The center point of a rotation operation
        \param angularShift The angle to move the geomerty by in degrees
    */ 
    void getRotationMove(wxRealPoint &aboutPoint, double &angularShift)
    {
        double temp1;
        wxRealPoint temp2;
        unsigned int deleteMe = 0;
        getRotationCopy(temp2, temp1, deleteMe);
        aboutPoint = temp2;
        angularShift = temp1;
    }
    
    //! Retrieves the infomation needed to perform a rotation operation during a copy
    /*!
        This is the base function for both copy and moving. This function
        includes the parameters needed to grab all of the infomation
        to create copies of geometry where the angular difference
        between each copy is set by angularShift
        \param aboutPoint The center point of the rotation operation
        \param angularShift The angular difference between each copy
        \param numberOfCopies The number of copies that the program should make
    */ 
    void getRotationCopy(wxRealPoint &aboutPoint, double &angularShift, unsigned int &numberCopies);
    
    //! Retrieves the amount to move horizontally and vertically the geometry
    /*!
        This function is executed when the user is moving the geometry.
        The function will retrieve the amount to move the geometry both
        vertically and horizontally.
        \param horizontalShift The amount to move geometry horizontally
        \param veriticalShift The amount to move geometry vertically
    */ 
    void getTranslationMove(double &horizontalShift, double &veriticalShift)
    {
        double temp1, temp2;
        unsigned int deleteMe = 0;
        getTranslationCopy(temp1, temp2, deleteMe);
        horizontalShift = temp1;
        veriticalShift = temp2;
    }
    
    //! Retrieves the parameters need to perform a translation copy operation
    /*!
        This function is executed when the user is copying the geometry.
        The function will retrieve the distance between each copy (x and y)
        and the number of copies to make
        \param horizontalShift The difference between each copy in the x-direction
        \param veriticalShift The difference between each copy in the y-direction
    */
    void getTranslationCopy(double &horizontalShift, double &veriticalShift, unsigned int &numberCopies);
    
private:
    //! This is required in order to properly execute event procedures
    wxDECLARE_EVENT_TABLE();
};

#endif
