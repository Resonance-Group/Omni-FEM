#ifndef GRIDPREFERENCES_H_
#define GRIDPREFERENCES_H_

#include <string>
#include <iostream>
#include <iomanip>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/combobox.h>
#include <wx/sizer.h>
#include <wx/arrstr.h>
#include <wx/valnum.h>

#include <common/GridPreferences.h>


/**
 * @class gridPreferencesDialog
 * @author Phillip
 * @date 12/07/17
 * @file GridPreferencesDialog.h
 * @brief Class that handles the creation of the dialog box needed 
 */
class gridPreferencesDialog : public wxDialog
{
private:
    //! Local copy of the grid preferences
    gridPreferences _preferences;
    
    //! Text box that handles the input of hte grid step size
    wxTextCtrl *_gridSizeTextCtrl = new wxTextCtrl();
    
    //! Check box that handles the state of the dispaly grid
    /*!
        If the box is checked, then the grid is dispalyed otherwise,
        the grid is not displapyed
    */ 
    wxCheckBox *_showGridCheckBox = new wxCheckBox();

    //! Check box that handles the state of snapping to the grid
    /*!
        This check box will determine if the node (block label or node or
        other functions) will be able to snap to the grid marking. The snap
        occurs when the horizontal grid marking crosses the vertical. If the
        box is checked, this means that the program will snap to the grid. Otherwise
        the program will not
    */ 
    wxCheckBox *_snapGridCheckBox = new wxCheckBox(); 
    
    //! Check box that handles that state of dispalying the origin
    /*!
        If this box is checked, then a crosshair indicating the origin will be
        drawn. Othewise, it will not be drawn
    */ 
    wxCheckBox *_showOriginCheckBox = new wxCheckBox(); 
    
    //! Check box that handles the state of displaying the block names
    /*!
        If checked, then the block label names (which is the material
        that is assigned to the block label) will be drawn. Otherwise,
        the name will be drawn. For magnetic simulations, this needs
        to be checked in order to display the circuit name that is 
        associated with the block name
    */ 
    wxCheckBox *_showBlockNameCheckBox = new wxCheckBox();
    
    //! Check box that handles the state of the dispalying the grid axis
    /*!
        If checked, then the major axis will be drawn. Otherwise, they
        will not be drawn
    */ 
    wxCheckBox *_showGridAxisCheckBox = new wxCheckBox();
    
    //! Check box that handles if the direction of the mouse wheel for zooming should be reveresed
    /*!
        If checked, then the direction will be reversed. Otherwise, the direction
        will be back to the default setting
    */ 
    wxCheckBox *_reverseMouseZoomCheckBox = new wxCheckBox();
    
    //! Combo box that is used to handle the selection of the grid
    /*!
        As of now, the grid can be understood as either a Cartesian grid
        or a Polar grid
    */ 
    wxComboBox *_coordinateComboBox = new wxComboBox();
    
    /**
     * @brief   Function that is used to update the look of the interface.
     *          This is mainly used when a set of grid preferences is passed into
     *          the class
     */
    void updateInterface();
public:

    //! The constructor for the class
    /*!
        \param par The parent window that is associated with the object
     */ 
    gridPreferencesDialog(wxWindow *par);
    
    //! The destructor for the class
    ~gridPreferencesDialog();
    
    /**
     * @brief This function will return the preferences that the user has set
     * @param preferences The object that the preferences should be saved to when the window is closed
     */
    void getParameters(gridPreferences &preferences);
    
    /**
     * @brief   This function wil update the look of the interface with new parameters and will update the
     *          local parameter object with the one passed into the function
     * @param preferences Object that the grid preferences should be stored when the dialog is closed.
     */
    void setParameters(gridPreferences &preferences);
};

#endif