#ifndef MESH_ADVANCED_SETTINGS_H_
#define MESH_ADVANCED_SETTINGS_H_

#include <wx/wx.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/stattext.h>

#include <common/MeshSettings.h>

class meshAdvanced : public wxDialog
{
private:
	meshSettings *p_meshSettings;
};




#endif