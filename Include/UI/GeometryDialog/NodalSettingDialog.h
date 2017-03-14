#ifndef SET_NODAL_PROPERTY_H_
#define SET_NODAL_PROPERTY_H_

#include <vector>

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/arrstr.h>

#include <common/NodalProperty.h>
#include <common/GeometryProperties/NodeSettings.h>
#include <common/ConductorProperty.h>

class setNodalPropertyDialog : public wxDialog
{
private:
    physicProblems _problem = physicProblems::NO_PHYSICS_DEFINED;

    std::vector<nodalProperty> _nodalList;
    
    std::vector<conductorProperty> _conductorList;
    
    nodeSetting _nodeSetting;
    
    wxComboBox *_nodePropertyComboBox = new wxComboBox();
    
    wxTextCtrl *_groupTextCtrl = new wxTextCtrl();
    
    wxComboBox *_conductorsComboBox = new wxComboBox();
public:
    setNodalPropertyDialog(wxWindow *par, std::vector<nodalProperty> &nodePropertyList, nodeSetting &nodeSettings, std::vector<conductorProperty> &conductorPropertyList);
    
    setNodalPropertyDialog(wxWindow *par, std::vector<nodalProperty> &nodePropertyList, nodeSetting &nodeSettings);
    
    void getNodalSettings(nodeSetting &settings);
    
    ~setNodalPropertyDialog();
};



#endif