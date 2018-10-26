#include <UI/BoundaryDialog/BoundaryDialog.h>

boundaryDialog::boundaryDialog(wxWindow *par, std::vector<magneticBoundary> *boundaryList) : wxDialog(par, wxID_ANY, "Boundary Definition")
{
    _problem = physicProblems::PROB_MAGNETICS;
    
    _magneticBoundaryList = boundaryList;
    
    makeDialog();
}



boundaryDialog::boundaryDialog(wxWindow *par, std::vector<electricalBoundary> *boundaryList) : wxDialog(par, wxID_ANY, "Boundary Definition")
{
    _problem = physicProblems::PROB_ELECTROSTATIC;
    
    _electricalBoundaryList = boundaryList;
    
    makeDialog();
}



void boundaryDialog::makeDialog()
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxArrayString boundaryNameArray;

    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *propertySizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *okSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *intermediateSizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name: ", wxPoint(12, 9), wxSize(38, 13));
    name->SetFont(*font);
    
    if(_problem == physicProblems::PROB_ELECTROSTATIC)
    {
        for(std::vector<electricalBoundary>::iterator boundaryIterator = _electricalBoundaryList->begin(); boundaryIterator != _electricalBoundaryList->end(); ++boundaryIterator)
        {
            boundaryNameArray.Add(wxString(boundaryIterator->getBoundaryName()));
        }
    }
    else if(_problem == physicProblems::PROB_MAGNETICS)
    {
        for(std::vector<magneticBoundary>::iterator boundaryIterator = _magneticBoundaryList->begin(); boundaryIterator != _magneticBoundaryList->end(); ++boundaryIterator)
        {
            boundaryNameArray.Add(wxString(boundaryIterator->getBoundaryName()));
        }
    }
    
    _selection->Create(this, wxID_ANY, wxEmptyString, wxPoint(56, 5), wxSize(139, 21), boundaryNameArray);
    _selection->SetFont(*font);
    if(boundaryNameArray.GetCount() > 0)
        _selection->SetSelection(0);
    
    headerSizer->Add(name, 0, wxALIGN_CENTER | wxLEFT | wxUP, 6);
    headerSizer->Add(_selection, 0, wxALIGN_CENTER | wxUP, 6);
    
    wxButton *addPropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonAdd, "Add Property", wxPoint(12, 43), wxSize(102, 23));
    addPropertyButton->SetFont(*font);
    
    wxButton *deletePropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonDelete, "Delete Property", wxPoint(12, 72), wxSize(102, 23));
    deletePropertyButton->SetFont(*font);
    
    wxButton *modifyPropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonModify, "Modify Property", wxPoint(12, 101), wxSize(102, 23));
    modifyPropertyButton->SetFont(*font);
    
    propertySizer->Add(0, 10, 0);
    propertySizer->Add(addPropertyButton, 0, wxLEFT, 6);
    propertySizer->Add(0, 6, 0);
    propertySizer->Add(deletePropertyButton, 0, wxALIGN_CENTER | wxLEFT, 6);
    propertySizer->Add(0, 6, 0);
    propertySizer->Add(modifyPropertyButton, 0, wxDOWN | wxLEFT, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "OK", wxPoint(120, 101), wxSize(75, 23));
    okButton->SetFont(*font);
    
    okSizer->Add(0, 68, 0);
    okSizer->Add(okButton, 0, wxDOWN | wxRIGHT, 6);
    
    intermediateSizer->Add(propertySizer, 0, wxALIGN_LEFT);
    intermediateSizer->Add(6, 0, 0);
    intermediateSizer->Add(okSizer);
    
    topSizer->Add(headerSizer, 0, wxALIGN_TOP);
    topSizer->Add(0, 10, 0);
    topSizer->Add(intermediateSizer);
    
    SetSizerAndFit(topSizer);
}



void boundaryDialog::onAddProperty(wxCommandEvent &event)
{
    if(_problem == physicProblems::PROB_MAGNETICS)
    {
        magneticBoundary magBC;
        magneticBoundaryDialog *magBoundaryDialog = new magneticBoundaryDialog(this);
        magBoundaryDialog->clearBoundary();
        if(magBoundaryDialog->ShowModal() == wxID_OK)
        {
            magBoundaryDialog->getBoundaryCondition(magBC);
            for(std::vector<magneticBoundary>::iterator boundaryIterator = _magneticBoundaryList->begin(); boundaryIterator != _magneticBoundaryList->end(); ++boundaryIterator)
            {
                if(boundaryIterator->getBoundaryName() == magBC.getBoundaryName())
                {
                    wxMessageBox(magBC.getBoundaryName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                    break;
                }
            }
			magBC.setBoundaryID(_magneticBoundaryList->size() + 1);
            _magneticBoundaryList->push_back(magBC);
            _selection->Append(magBC.getBoundaryName());
            _selection->SetSelection(0);
        }
    }
    else if(_problem == physicProblems::PROB_ELECTROSTATIC)
    {
        electricalBoundary estaticBC;
        electricalStaticBoundaryDialog *estaticBoundaryDialog = new electricalStaticBoundaryDialog(this);
        estaticBoundaryDialog->clearBoundary();
        if(estaticBoundaryDialog->ShowModal() == wxID_OK)
        {
            estaticBoundaryDialog->getBoundaryCondition(estaticBC);
            for(std::vector<electricalBoundary>::iterator boundaryIterator = _electricalBoundaryList->begin(); boundaryIterator != _electricalBoundaryList->end(); ++boundaryIterator)
            {
                if(boundaryIterator->getBoundaryName() == estaticBC.getBoundaryName())
                {
                    wxMessageBox(estaticBC.getBoundaryName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                    break;
                }
            }
			estaticBC.setBoundaryID(_electricalBoundaryList->size() + 1);
            _electricalBoundaryList->push_back(estaticBC);
            _selection->Append(estaticBC.getBoundaryName());
            _selection->SetSelection(0);
        }
    }
} 



void boundaryDialog::onDeleteProperty(wxCommandEvent &event)
{
    if((_magneticBoundaryList != nullptr) && _problem == physicProblems::PROB_MAGNETICS)
    {
        if(!_magneticBoundaryList->empty())
        {
            int currentSelection = _selection->GetCurrentSelection();
			unsigned int boundaryIDCounter = 1;
			
            _magneticBoundaryList->erase(_magneticBoundaryList->begin() + currentSelection);
            _selection->Delete(currentSelection);
            _selection->SetSelection(0);
			
			for(auto boundaryIterator = _magneticBoundaryList->begin(); boundaryIterator != _magneticBoundaryList->end(); boundaryIterator++)
			{
				boundaryIterator->setBoundaryID(boundaryIDCounter++);
			}
			
            if(_magneticBoundaryList->empty())
                _selection->SetValue(wxEmptyString);
        }
    }
    else if((_electricalBoundaryList != nullptr) && _problem == physicProblems::PROB_ELECTROSTATIC)
    {
        if(!_electricalBoundaryList->empty())
        {
            int currentSelection = _selection->GetCurrentSelection();
			unsigned int boundaryIDCounter = 1;
			
            _electricalBoundaryList->erase(_electricalBoundaryList->begin() + currentSelection);
            _selection->Delete(currentSelection);
            _selection->SetSelection(0);
			
			for(auto boundaryIterator = _electricalBoundaryList->begin(); boundaryIterator != _electricalBoundaryList->end(); boundaryIterator++)
			{
				boundaryIterator->setBoundaryID(boundaryIDCounter++);
			}
			
            if(_electricalBoundaryList->empty())
                _selection->SetValue(wxEmptyString);
        }
    }
}



void boundaryDialog::onModifyProperty(wxCommandEvent &event)
{
    if((_magneticBoundaryList != nullptr) && _problem == physicProblems::PROB_MAGNETICS)
    {
        if(!_magneticBoundaryList->empty())
        {
            magneticBoundary selectedBoundary;
            magneticBoundaryDialog *magBoundaryDialog = new magneticBoundaryDialog(this);
            int currentSelection = _selection->GetSelection();
            selectedBoundary = _magneticBoundaryList->at(currentSelection);
            magBoundaryDialog->setBoundaryCondition(selectedBoundary);
            if(magBoundaryDialog->ShowModal() == wxID_OK)
            {
                /*
                 * This is a counter. The loop is checking to see if the user accidently changed the name of the material to one that is already there.
                 * However, the one that the user wants to modify is still in the list. So, the program needs to skip
                 * that one. Which, this counter will assit in that
                 */ 
                int i = 0;
                magBoundaryDialog->getBoundaryCondition(selectedBoundary);
                for(std::vector<magneticBoundary>::iterator boundaryIterator = _magneticBoundaryList->begin(); boundaryIterator != _magneticBoundaryList->end(); ++boundaryIterator)
                {
                    if(boundaryIterator->getBoundaryName() == selectedBoundary.getBoundaryName() && (i != currentSelection))
                    {
                        wxMessageBox(selectedBoundary.getBoundaryName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                        break;
                    }
                    
                    i++;
                } 
                _magneticBoundaryList->at(currentSelection) = selectedBoundary;
                _selection->SetString(currentSelection, selectedBoundary.getBoundaryName());
            }
            _selection->SetSelection(0);
        }
    }
    else if((_electricalBoundaryList != nullptr) && _problem == physicProblems::PROB_ELECTROSTATIC)
    {
        if(!_electricalBoundaryList->empty())
        {
            int currentSelection = _selection->GetSelection();
            electricalStaticBoundaryDialog *estaticBoundaryDialog = new electricalStaticBoundaryDialog(this);
            electricalBoundary selectedBoundary = _electricalBoundaryList->at(currentSelection);
            estaticBoundaryDialog->setBoundaryCondition(selectedBoundary);
            if(estaticBoundaryDialog->ShowModal() == wxID_OK)
            {
                /*
                 * This is a counter. The loop is checking to see if the user accidently changed the name of the material to one that is already there.
                 * However, the one that the user wants to modify is still in the list. So, the program needs to skip
                 * that one. Which, this counter will assit in that
                 */ 
                int i = 0;
                estaticBoundaryDialog->getBoundaryCondition(selectedBoundary);
                for(std::vector<electricalBoundary>::iterator boundaryIterator = _electricalBoundaryList->begin(); boundaryIterator != _electricalBoundaryList->end(); ++boundaryIterator)
                {
                    if(boundaryIterator->getBoundaryName() == selectedBoundary.getBoundaryName() && (i != currentSelection))
                    {
                        wxMessageBox(selectedBoundary.getBoundaryName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                        break;
                    }
                    
                    i++;
                } 
                _electricalBoundaryList->at(currentSelection) = selectedBoundary;
                _selection->SetString(currentSelection, selectedBoundary.getBoundaryName());
            }
            _selection->SetSelection(0);
        }
    }
}



boundaryDialog::~boundaryDialog()
{
    
}



wxBEGIN_EVENT_TABLE(boundaryDialog, wxDialog)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonAdd, boundaryDialog::onAddProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonDelete, boundaryDialog::onDeleteProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonModify, boundaryDialog::onModifyProperty)
wxEND_EVENT_TABLE()