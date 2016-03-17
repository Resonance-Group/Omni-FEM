/*
 * OmniFEM.h
 *
 *  Created on: Mar 15, 2016
 *      Author: phillip
 */

#ifndef OMNIFEM_H_
#define OMNIFEM_H_

#include <wx/wx.h>

class OmniFEMApp : public wxApp
{
    public:
        virtual bool OnInit();
};



class OmniFEMMainFrame : public wxFrame
{
public:
    OmniFEMMainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
private:
    /* This section is for the File menu */
    void onNewFile(wxCommandEvent &event);
    void OnSave(wxCommandEvent &event);
    void onSaveAs(wxCommandEvent &event);
    
    /* This section is for the Edit menu */
    void onPreferences(wxCommandEvent &event);
    
    /* This section is for the About menu */
    void OnAbout(wxCommandEvent &event);
    
    void OnExit(wxCommandEvent &event);
    wxDECLARE_EVENT_TABLE();
};



enum
{
    ID_New = 1,
    ID_Save = 2,
    ID_SaveAs = 3,
    ID_Preferences = 4
};



wxBEGIN_EVENT_TABLE(OmniFEMMainFrame, wxFrame)
    /* This section is for teh file menu */
    EVT_MENU(ID_New,   OmniFEMMainFrame::onNewFile)
    EVT_MENU(ID_Save, OmniFEMMainFrame::OnSave)
    EVT_MENU(ID_SaveAs, OmniFEMMainFrame::onSaveAs)
    
    /* This section is for the view menu */
    EVT_MENU(ID_Preferences, OmniFEMMainFrame::onPreferences)
    
    /* This section is for the ABOUT menu */
    EVT_MENU(wxID_ABOUT, OmniFEMMainFrame::OnAbout)
    
    EVT_MENU(wxID_EXIT,  OmniFEMMainFrame::OnExit)
    
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(OmniFEMApp);







#endif /* OMNIFEM_H_ */
