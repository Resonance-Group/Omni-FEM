/* THis file will contain all of the classes for the different custom events that 
 * Omni-FEM needs to handle
 */


#ifndef OMNIFEMEVENT_H_
#define OMNIFEMEVENT_H_

#include <wx/wx.h>

#include <common/enums.h>
#include <common/MagneticMaterial.h>


decltype void (wxEvtHandler::*MyFooEventFunction)(MagneticMaterialReturnEvent &)
#define MyFooEventHandler(func) wxEVENT_HANDLER_CAST(MyFooEventFunction, func)
#define EVT_MAGNETIC_MATERIAL_RETURN(id, func) \ wx__DECLARE_EVT1(MAGNETIC_MATERIAL_EVT_TYPE, id, MyFooEventFunction(func))

class MagneticMaterialReturnEvent;

wxDECLARE_EVENT(MAGNETIC_MATERIAL_EVT_TYPE, MagneticMaterialReturnEvent);

class MagneticMaterialReturnEvent : public wxCommandEvent
{
private:
    magneticMaterial _material;
    
public:

    void setMaterial(const magneticMaterial &mat)
    {
        _material = mat;
    }
    
    magneticMaterial getMaterial() const
    {
        return _material;
    }
    
    wxEvent *Clone() const
    {
        return new MagneticMaterialReturnEvent(*this);
    }

    MagneticMaterialReturnEvent(wxEventType commandType = MAGNETIC_MATERIAL_EVT_TYPE, int id = 0) : wxCommandEvent(commandType, id)
    {
        
    }
    
    MagneticMaterialReturnEvent(const MagneticMaterialReturnEvent &event) : wxCommandEvent(event)
    {
        this->setMaterial(event.getMaterial());
    }
    
    
};


#endif