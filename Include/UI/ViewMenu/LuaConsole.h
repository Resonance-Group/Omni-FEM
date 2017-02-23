#ifndef LUA_CONSOLE_H_
#define LUA_CONSOLE_H_

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/string.h>

#include <common/enums.h>

class luaConsole : public wxDialog
{
private:

    wxTextCtrl *_outputConsole = new wxTextCtrl();
    
    wxTextCtrl *_inputConsole = new wxTextCtrl();
    
    void onClearInput(wxCommandEvent &event);
    
    void onClearOutput(wxCommandEvent &event);
    
    void clearOutput();
    
    void clearInput();
    
public:

    luaConsole();
    
    ~luaConsole();
    
    void appendOutput(wxString &outputText);
    
    void getInput(wxString &inputText);
    
private:
    wxDECLARE_EVENT_TABLE();
};

#endif