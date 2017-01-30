#ifndef BLOCKPROPERTYMAGNETIC_H_
#define BLOCKPROPERTYMAGNETIC_H_

#include <string>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>

#include <common/enums.h>
#include <common/MaterialProperty.h>
#include <common/MagneticMaterial.h>
#include <common/omniFEMEvent.h>


/*! /class blockPropertMagnetic
 *  /brief
 *  This calss is for creating the Block Property dialog when in the magnetics simualtion
 *  THe dialog box is rather large however, there are only two buttons.
 *  Due to the simplicity of the dialog box, this class will be the abstraction, controller, and presentation
 */
class blockPropertyMagnetic : public wxFrame
{
private:

  //  MagneticMaterialReturnEvent magneticEvent(MAGNETIC_MATERIAL_EVT_TYPE, CustomEvent::MagneticMaterial);
    wxTextCtrl *nameTextCtrl = new wxTextCtrl();
    wxTextCtrl *relativeUxTextCtrl = new wxTextCtrl();
    wxTextCtrl *phiXTextCtrl = new wxTextCtrl();
    wxTextCtrl *relativeUyTextCtrl = new wxTextCtrl();
    wxTextCtrl *phiYTextCtrl = new wxTextCtrl();
    wxTextCtrl *phiMaxTextCtrl = new wxTextCtrl();
    wxTextCtrl *coercivityTextCtrl = new wxTextCtrl();
    wxTextCtrl *eConductivityTextCtrl = new wxTextCtrl();
    wxTextCtrl *currentDesnityTextCtrl = new wxTextCtrl();
    wxTextCtrl *lamThickTextCtrl = new wxTextCtrl();
    wxTextCtrl *numStrandsTextCtrl = new wxTextCtrl();
    wxTextCtrl *lamFFTextCtrl = new wxTextCtrl();
    wxTextCtrl *strandDiaTextCtrl = new wxTextCtrl();
    
    wxArrayString *BHSettingsArray = new wxArrayString();
    
    wxArrayString *LamWireSettingsArray = new wxArrayString();
    
    wxComboBox *specialAttriComboBox = new wxComboBox();
    
    wxComboBox *BHCurveComboBox = new wxComboBox();
    
    wxButton *editBHCurve = new wxButton();

    magneticMaterial _magneticMaterial;

    void onOk(wxCommandEvent &event);
    
    void onCancel(wxCommandEvent &event);
    
    void onBHCurve(wxCommandEvent &event);
    
    void onBHCurveCombo(wxCommandEvent &event);
    
    void onSpecialComboBox(wxCommandEvent &event);
    
  //  wxEvtHandler *pdest;
    
public:
    blockPropertyMagnetic(magneticMaterial material);
    
    blockPropertyMagnetic();
    
    ~blockPropertyMagnetic();

private:
    wxDECLARE_EVENT_TABLE();
    wxDEFINE_EVENT(MAGNETIC_MATERIAL_EVT_TYPE, MagneticMaterialReturnEvent);
};



#endif