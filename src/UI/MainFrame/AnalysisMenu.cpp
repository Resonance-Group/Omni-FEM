
#include "UI/OmniFEMFrame.h"



void OmniFEMMainFrame::onViewResults(wxCommandEvent &event)
{
//	wxMessageBox("You are viewing results!", "Results", wxOK | wxCANCEL | wxICON_INFORMATION);

	p_test = new paraviewInitilizer();
	p_test->loadData();
}



void OmniFEMMainFrame::onAnalyze(wxCommandEvent &event)
{
    
}
