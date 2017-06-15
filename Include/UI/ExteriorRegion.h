#ifndef EXTERIORREGION_H_
#define EXTERIORREGION_H

#include <string>
#include <iostream>
#include <iomanip>

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/sizer.h>

/**
 * @class exteriorRegionDialog
 * @author Phillip
 * @date 15/06/17
 * @file ExteriorRegion.h
 * @brief   Class that handles the creation of the exterior region dialog
 *          This dialog will allow the user to create an exterior region
 *          when the user needs to solve a problem that is an unbounded domain
 *          This dialog is only accessible when the user needs to solve an axisymmetric
 *          problem.
 *          For documentation on the wxDialogClass, refer to the following link:
 *          http://docs.wxwidgets.org/3.0/classwx_dialog.html
 */
class exteriorRegionDialog : public wxDialog
{
private:
    //! Text control for entering in the center of the exterior region
    /*!
        The location along the z-axis of the axisymmetric problem
        where the center of the external region is located.
    */ 
    wxTextCtrl *_centerExteriorTextCtrl = new wxTextCtrl();
    
    //! The radius of the exterior region
    /*!
        This is the radius of the sphere representing the exterior region
    */ 
    wxTextCtrl *_radiusExteriorTextCtrl = new wxTextCtrl();
    
    //! The radius of the interior region
    /*!
        The radius of hte sphere that contains the model of the problem
    */ 
    wxTextCtrl *_radiusInteriorTextCtrl = new wxTextCtrl();
    
public:
    //! The constructor of the class
    /*!
        This function will create the dialog and place
        all of the widgets in their approiate positions
        \param par pointer to the parent window
    */ 
    exteriorRegionDialog(wxWindow *par);
    
    //! Deconstructor of the class
    ~exteriorRegionDialog();
    
    /**
     * @brief   This function will take inputs of the center, and radius of the interior/exterior region
                These values will then be displayed to the user
     * @param centerOfExterior A value representing the center along the z-axis of the problem
     * @param radiusExterior A value reprenting the radius of the exterior region
     * @param radiusInterior A value represnting the radius of the interior region
     */
    void setParameters(double &centerOfExterior, double &radiusExterior, double &radiusInterior);
    
    /**
     * @brief   This function will retrieve the parameters that the user placed in. 
     *          This function will typically be called after the user clicked on the 
     *          ok button generating a wxID_OK event
     * @param centerOfExterior Variable to store the center of the region
     * @param radiusExterior Variable to store the radius of the exterior region
     * @param radiusInterior Variable to store the radius of the interior region
     */
    void getParameters(double &centerOfExterior, double &radiusExterior, double &radiusInterior);
};

#endif