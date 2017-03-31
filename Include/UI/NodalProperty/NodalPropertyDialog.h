#ifndef NODALPROPERTYDIALOG_H_
#define NODALPROPERTYDIALOG_H_

#include <string>
#include <iostream>
#include <iomanip>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>
#include <wx/statbox.h>
#include <wx/radiobut.h>
#include <wx/sizer.h>

#include <common/NodalProperty.h>
#include <common/enums.h>

/*! /class blockPropertMagnetic
 *  /brief
 *  This calss is for creating the Block Property dialog when in the magnetics simualtion
 *  THe dialog box is rather large however, there are only two buttons.
 *  Due to the simplicity of the dialog box, this class will be the abstraction, controller, and presentation
 * 
 * Because the difference between dialog boxes for eletctrostatic and magnetics are similair, this class
 * will be handling both cases.
 */
class nodalPropertyDialog : public wxDialog
{
private:
    physicProblems _problem;

    //! This is the nodal property that will either be created (added to the global list) or modified
    nodalProperty _nodalProperty;

    //! This is the input box for the name of the nodal Property
    wxTextCtrl *nameTextCtrl = new wxTextCtrl();
    
    /*! /brief
     *  Since this class will handle two different sims (electrostatic/magnetics) and the form is the same for the both of them, generic names will be used to name some of the items for easy portablility
     *  For the magnetics solver, this is the text control box for Specific Vector Potential
     *  For the electrostatics solver, this is the text contrl box for
     */
    wxTextCtrl *textCtrl1 = new wxTextCtrl();
    
    /*! /brief
     *  Since this class will handle two different sims (electrostatic/magnetics) and the form is the same for the both of them, generic names will be used to name some of the items for easy portablility
     *  For the magnetics solver, this is the text control box for Point Current
     *  For the electrostatics solver, this is the text contrl box for
     */
    wxTextCtrl *textCtrl2 = new wxTextCtrl();
    
    /*! /brief
     *  Since this class will handle two different sims (electrostatic/magnetics) and the form is the same for the both of them, generic names will be used to name some of the items for easy portablility
     *  For the magnetics solver, this is the text control box for Specific Vector Potential
     *  For the electrostatics solver, this is the text contrl box for
     */
    wxRadioButton *radioButton1 = new wxRadioButton();
    
    /*! /brief
     *  Since this class will handle two different sims (electrostatic/magnetics) and the form is the same for the both of them, generic names will be used to name some of the items for easy portablility
     *  For the magnetics solver, this is the text control box for Specific Vector Potential
     *  For the electrostatics solver, this is the text contrl box for
     */
    wxRadioButton *radioButton2 = new wxRadioButton();
    
    void onRadioButton1Cllick(wxCommandEvent &event);
    
    void onRadioButton2Cllick(wxCommandEvent &event);
    
    void updateInterface();
    
public:
    
    nodalPropertyDialog(wxWindow *par, physicProblems problem);
    
    nodalPropertyDialog(wxWindow *par);
    
    ~nodalPropertyDialog();
    
    /*! /brief
     *  When a new nodal Property is created, this function must be called in order to retrieve the new nodal Property
     *  Note: There is currently no checking if the number that is entered is a valid number. This is up to the user.
     *  IF a number is accidently typed as 1.5.3, then wxWidgets will automaticcaly truncate the number to 1.5
     */ 
    void getNodalProperty(nodalProperty &nodalProp);
    
    //! This will set the private variable _nodalProperty to be equal to nodalProp. Useful if modifying a nodal Property
    void setNodalProperty(nodalProperty &nodalProp);
    
    //! This will reset the variable _nodalProperty to default values. Useful if adding a new nodal Property
    void clearNodalProperty();
    
    //! This is mainly for two step creation
    void createDialog(physicProblems problem);
    
private:
    wxDECLARE_EVENT_TABLE();
};


#endif