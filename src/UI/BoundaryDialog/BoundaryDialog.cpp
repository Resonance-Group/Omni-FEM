#include <UI/BoundaryDialog/BoundaryDialog.h>

boundaryDialog::boundaryDialog(std::vector<magneticBoundary> boundaryList) : wxDialog(NULL, wxID_ANY, "Boundary Definition")
{
    _problem = physicProblems::PROB_MAGNETICS;
    
    _magneticBoundaryList = boundaryList;
    
    for(std::vector<magneticBoundary>::iterator boundaryIterator = _magneticBoundaryList.begin(); boundaryIterator != _magneticBoundaryList.end(); ++boundaryIterator)
    {
        _boundaryNameArray->Add(wxString(boundaryIterator->getBoundaryName()));
    }

    makeDialog();
}



boundaryDialog::boundaryDialog(std::vector<electricalBoundary> boundaryList) : wxDialog(NULL, wxID_ANY, "Boundary Definition")
{
    _problem = physicProblems::PROB_ELECTROSTATIC;
    
    _electricalBoundaryList = boundaryList;
    
    for(std::vector<electricalBoundary>::iterator boundaryIterator = _electricalBoundaryList.begin(); boundaryIterator != _electricalBoundaryList.end(); ++boundaryIterator)
    {
        _boundaryNameArray->Add(wxString(boundaryIterator->getBoundaryName()));
    }

    makeDialog();
}



void boundaryDialog::makeDialog()
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *propertySizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *okSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *intermediateSizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name: ", wxPoint(12, 9), wxSize(38, 13));
    name->SetFont(*font);
    
    selection->Create(this, wxID_ANY, wxEmptyString, wxPoint(56, 5), wxSize(139, 21), *_boundaryNameArray);
    selection->SetFont(*font);
    if(_boundaryNameArray->GetCount() > 0)
        selection->SetSelection(0);
    
    headerSizer->Add(name, 0, wxALIGN_CENTER | wxLEFT | wxUP, 6);
    headerSizer->Add(selection, 0, wxALIGN_CENTER | wxUP, 6);
    
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
        _magBoundaryDialog->clearBoundary();
        if(_magBoundaryDialog->ShowModal() == wxID_OK)
        {
            _magBoundaryDialog->getBoundaryCondition(magBC);
            for(std::vector<magneticBoundary>::iterator boundaryIterator = _magneticBoundaryList.begin(); boundaryIterator != _magneticBoundaryList.end(); ++boundaryIterator)
            {
                if(boundaryIterator->getBoundaryName() == magBC.getBoundaryName())
                {
                    wxMessageBox(magBC.getBoundaryName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                    break;
                }
            }
            _magneticBoundaryList.push_back(magBC);
            selection->Append(magBC.getBoundaryName());
            selection->SetSelection(0);
        }
    }
    else if(_problem == physicProblems::PROB_ELECTROSTATIC)
    {
        electricalBoundary estaticBC;
        _estaticBoundaryDialog->clearBoundary();
        if(_estaticBoundaryDialog->ShowModal() == wxID_OK)
        {
            _estaticBoundaryDialog->getBoundaryCondition(estaticBC);
            for(std::vector<electricalBoundary>::iterator boundaryIterator = _electricalBoundaryList.begin(); boundaryIterator != _electricalBoundaryList.end(); ++boundaryIterator)
            {
                if(boundaryIterator->getBoundaryName() == estaticBC.getBoundaryName())
                {
                    wxMessageBox(estaticBC.getBoundaryName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                    break;
                }
            }
            _electricalBoundaryList.push_back(estaticBC);
            selection->Append(estaticBC.getBoundaryName());
            selection->SetSelection(0);
        }
    }
} 



void boundaryDialog::onDeleteProperty(wxCommandEvent &event)
{
    if(_magneticBoundaryList.size() > 0 && _problem == physicProblems::PROB_MAGNETICS)
    {
        int currentSelection = selection->GetCurrentSelection();
        _magneticBoundaryList.erase(_magneticBoundaryList.begin() + currentSelection);
        selection->Delete(currentSelection);
        selection->SetSelection(0);
    }
    else if(_electricalBoundaryList.size() > 0 && _problem == physicProblems::PROB_ELECTROSTATIC)
    {
        int currentSelection = selection->GetCurrentSelection();
        _electricalBoundaryList.erase(_electricalBoundaryList.begin() + currentSelection);
        selection->Delete(currentSelection);
        selection->SetSelection(0);
    }
}



void boundaryDialog::onModifyProperty(wxCommandEvent &event)
{
    
    if(_magneticBoundaryList.size() > 0 && _problem == physicProblems::PROB_MAGNETICS)
    {
        magneticBoundary selectedBoundary;
        int currentSelection = selection->GetSelection();
        selectedBoundary = _magneticBoundaryList.at(currentSelection);
        _magBoundaryDialog->setBoundaryCondition(selectedBoundary);
        if(_magBoundaryDialog->ShowModal() == wxID_OK)
        {
            /*
             * This is a counter. The loop is checking to see if the user accidently changed the name of the material to one that is already there.
             * However, the one that the user wants to modify is still in the list. So, the program needs to skip
             * that one. Which, this counter will assit in that
             */ 
            int i = 0;
            _magBoundaryDialog->getBoundaryCondition(selectedBoundary);
            for(std::vector<magneticBoundary>::iterator boundaryIterator = _magneticBoundaryList.begin(); boundaryIterator != _magneticBoundaryList.end(); ++boundaryIterator)
            {
                if(boundaryIterator->getBoundaryName() == selectedBoundary.getBoundaryName() && (i != currentSelection))
                {
                    wxMessageBox(selectedBoundary.getBoundaryName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                    break;
                }
                
                i++;
            } 
            _magneticBoundaryList.at(currentSelection) = selectedBoundary;
            selection->SetString(currentSelection, selectedBoundary.getBoundaryName());
        }
        selection->SetSelection(0);
    }
    else if(_electricalBoundaryList.size() > 0 && _problem == physicProblems::PROB_ELECTROSTATIC)
    {
        int currentSelection = selection->GetSelection();
        electricalBoundary selectedBoundary = _electricalBoundaryList.at(currentSelection);
        _estaticBoundaryDialog->setBoundaryCondition(selectedBoundary);
        if(_estaticBoundaryDialog->ShowModal() == wxID_OK)
        {
            /*
             * This is a counter. The loop is checking to see if the user accidently changed the name of the material to one that is already there.
             * However, the one that the user wants to modify is still in the list. So, the program needs to skip
             * that one. Which, this counter will assit in that
             */ 
            int i = 0;
            _estaticBoundaryDialog->getBoundaryCondition(selectedBoundary);
            for(std::vector<electricalBoundary>::iterator boundaryIterator = _electricalBoundaryList.begin(); boundaryIterator != _electricalBoundaryList.end(); ++boundaryIterator)
            {
                if(boundaryIterator->getBoundaryName() == selectedBoundary.getBoundaryName() && (i != currentSelection))
                {
                    wxMessageBox(selectedBoundary.getBoundaryName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                    break;
                }
                
                i++;
            } 
            _electricalBoundaryList.at(currentSelection) = selectedBoundary;
            selection->SetString(currentSelection, selectedBoundary.getBoundaryName());
        }
        selection->SetSelection(0);
    }
}



std::vector<magneticBoundary> boundaryDialog::getMagneticBoundaryList()
{
    return _magneticBoundaryList;
}



std::vector<electricalBoundary> boundaryDialog::getElectrostaticBoundaryList()
{
    return _electricalBoundaryList;
}



boundaryDialog::~boundaryDialog()
{
    
}



wxBEGIN_EVENT_TABLE(boundaryDialog, wxDialog)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonAdd, boundaryDialog::onAddProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonDelete, boundaryDialog::onDeleteProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonModify, boundaryDialog::onModifyProperty)
wxEND_EVENT_TABLE()