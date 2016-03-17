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
    void onNewFile(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnSave(wxCommandEvent &event);
    void onSaveAs(wxCommandEvent &event);
    wxDECLARE_EVENT_TABLE();
};



enum
{
    ID_New = 1,
    ID_Save = 2,
    ID_SaveAs = 3
};



wxBEGIN_EVENT_TABLE(OmniFEMMainFrame, wxFrame)
    EVT_MENU(ID_New,   OmniFEMMainFrame::onNewFile)
    EVT_MENU(ID_Save, OmniFEMMainFrame::OnSave)
    EVT_MENU(ID_SaveAs, OmniFEMMainFrame::onSaveAs)
    EVT_MENU(wxID_EXIT,  OmniFEMMainFrame::OnExit)
    EVT_MENU(wxID_ABOUT, OmniFEMMainFrame::OnAbout)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(OmniFEMApp);







#endif /* OMNIFEM_H_ */
