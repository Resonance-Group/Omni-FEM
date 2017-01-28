#ifndef BLOCKPROPERTYMAGNETIC_H_
#define BLOCKPROPERTYMAGNETIC_H_

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/arrstr.h>

#include <common/enums.h>
#include <common/MaterialProperty.h>
#include <common/MagneticMaterial.h>


/*! /class blockPropertMagnetic
 *  /brief
 *  This calss is for creating the Block Property dialog when in the magnetics simualtion
 *  THe dialog box is rather large however, there are only two buttons.
 *  Due to the simplicity of the dialog box, this class will be the abstraction, controller, and presentation
 */
class blockPropertyMagnetic : public wxFrame
{
private:
    magneticMaterial _magneticMaterial;

    void onOk(wxCommandEvent &event);
    
    void onCancel(wxCommandEvent &event);
    
public:
    blockPropertyMagnetic();
    
    ~blockPropertyMagnetic();

private:
    wxDECLARE_EVENT_TABLE();
};

#endif