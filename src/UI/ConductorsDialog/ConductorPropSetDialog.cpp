#include <UI/ConductorsDialog/ConductorPropSetDialog.h>

conductorPropertySetDialog::conductorPropertySetDialog(std::vector<circuitProperty> circuitList) : wxDialog(NULL, wxID_ANY, "Conductor Definition")
{
    _circuitList = circuitList;
 
    _problem = physicProblems::magnetics;
   
    for(std::vector<circuitProperty>::iterator circuitIterator = _circuitList.begin(); circuitIterator != _circuitList.end(); ++circuitIterator)
    {
        conductorNameArray->Add(wxString(circuitIterator->getName()));
    }
    
    makeDialog();
}



conductorPropertySetDialog::conductorPropertySetDialog(std::vector<conductorProperty> conductorList) : wxDialog(NULL, wxID_ANY, "Conductor Definition")
{
    _conductorList = conductorList;
 
    _problem = physicProblems::electrostatics;
   
    for(std::vector<conductorProperty>::iterator conductorIterator = _conductorList.begin(); conductorIterator != _conductorList.end(); ++conductorIterator)
    {
        conductorNameArray->Add(wxString(conductorIterator->getName()));
    }
    
    makeDialog();
}


void conductorPropertySetDialog::makeDialog()
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *propertySizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *okSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *intermediateSizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name: ", wxPoint(12, 9), wxSize(38, 13));
    name->SetFont(*font);
    
    selection->Create(this, wxID_ANY, wxEmptyString, wxPoint(56, 5), wxSize(139, 21), *conductorNameArray);
    selection->SetFont(*font);
    if(conductorNameArray->GetCount() > 0)
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


void conductorPropertySetDialog::onAddProperty(wxCommandEvent &event)
{
    if(_problem == physicProblems::magnetics)
    {
        circuitPropertyDialog *circuitPropDialog = new circuitPropertyDialog();
        circuitProperty newCircuit;
        circuitPropDialog->clearCircuit();
        if(circuitPropDialog->ShowModal() == wxID_OK)
        {
            circuitPropDialog->getNewCircuit(newCircuit);
            for(std::vector<circuitProperty>::iterator circuitIterator = _circuitList.begin(); circuitIterator != _circuitList.end(); ++circuitIterator)
            {
                if(circuitIterator->getName() == newCircuit.getName())
                {
                    wxMessageBox(newCircuit.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                    break;
                }
            }
            _circuitList.push_back(newCircuit);
            selection->Append(newCircuit.getName());
            selection->SetSelection(0);
        }
    }
    else if(_problem == physicProblems::electrostatics)
    {
        conductorPropertyDialog *conductorPropDialog = new conductorPropertyDialog();
        conductorProperty newConductor;
        conductorPropDialog->clearConductor();
        if(conductorPropDialog->ShowModal() == wxID_OK)
        {
            conductorPropDialog->getNewConductor(newConductor);
            for(std::vector<conductorProperty>::iterator conductorIterator = _conductorList.begin(); conductorIterator != _conductorList.end(); ++conductorIterator)
            {
                if(conductorIterator->getName() == newConductor.getName())
                {
                    wxMessageBox(newConductor.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                    break;
                }
            }
            _conductorList.push_back(newConductor);
            selection->Append(newConductor.getName());
            selection->SetSelection(0);
        }
    }
} 



void conductorPropertySetDialog::onDeleteProperty(wxCommandEvent &event)
{
    if(_circuitList.size() > 0 && _problem == physicProblems::magnetics)
    {
        int currentSelection = selection->GetCurrentSelection();
        _circuitList.erase(_circuitList.begin() + currentSelection);
        selection->Delete(currentSelection);
        selection->SetSelection(0);
    }
    else if(_conductorList.size() > 0 && _problem == physicProblems::electrostatics)
    {
        int currentSelection = selection->GetCurrentSelection();
        _conductorList.erase(_conductorList.begin() + currentSelection);
        selection->Delete(currentSelection);
        selection->SetSelection(0);
    }
}



void conductorPropertySetDialog::onModifyProperty(wxCommandEvent &event)
{
    
    if(_circuitList.size() > 0 && _problem == physicProblems::magnetics)
    {
        circuitProperty selectedCircuitProperty;
        circuitPropertyDialog *circuitPropDialog = new circuitPropertyDialog();
        int currentSelection = selection->GetSelection();
        selectedCircuitProperty = _circuitList.at(currentSelection);
        circuitPropDialog->setCircuit(selectedCircuitProperty);
        if(circuitPropDialog->ShowModal() == wxID_OK)
        {
            /*
             * This is a counter. The loop is checking to see if the user accidently changed the name of the material to one that is already there.
             * However, the one that the user wants to modify is still in the list. So, the program needs to skip
             * that one. Which, this counter will assist in that
             */
            int i = 0;
            circuitPropDialog->getNewCircuit(selectedCircuitProperty);
            for(std::vector<circuitProperty>::iterator circuitIterator = _circuitList.begin(); circuitIterator != _circuitList.end(); ++circuitIterator)
            {
                if(circuitIterator->getName() == selectedCircuitProperty.getName() && (i != currentSelection))
                {
                    wxMessageBox(selectedCircuitProperty.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                    break;
                }
                
                i++;
            } 
            _circuitList.at(currentSelection) = selectedCircuitProperty;
            selection->SetString(currentSelection, selectedCircuitProperty.getName());
            selection->SetSelection(0);
        }
    }
    else if(_conductorList.size() > 0 && _problem == physicProblems::electrostatics)
    {
        conductorProperty selectedConductor;
        conductorPropertyDialog *conductorPropDialog = new conductorPropertyDialog();
        int currentSelection = selection->GetSelection();
        selectedConductor = _conductorList.at(currentSelection);
        conductorPropDialog->setConductor(selectedConductor);
        if(conductorPropDialog->ShowModal() == wxID_OK)
        {
            int i = 0;
            conductorPropDialog->getNewConductor(selectedConductor);
            for(std::vector<conductorProperty>::iterator conductorIterator = _conductorList.begin(); conductorIterator != _conductorList.end(); ++conductorIterator)
            {
                if(conductorIterator->getName() == selectedConductor.getName() && i != currentSelection)
                {
                    wxMessageBox(selectedConductor.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                    break;
                }
                i++;
            }
            _conductorList.at(currentSelection) = selectedConductor;
            selection->SetString(currentSelection, selectedConductor.getName());
            selection->SetSelection(0);
        }
    }
}



std::vector<conductorProperty> conductorPropertySetDialog::getConductorList()
{
    return _conductorList;
}



std::vector<circuitProperty> conductorPropertySetDialog::getCircuitList()
{
    return _circuitList;
}



conductorPropertySetDialog::~conductorPropertySetDialog()
{
    
}



wxBEGIN_EVENT_TABLE(conductorPropertySetDialog, wxDialog)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonAdd, conductorPropertySetDialog::onAddProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonDelete, conductorPropertySetDialog::onDeleteProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonModify, conductorPropertySetDialog::onModifyProperty)
wxEND_EVENT_TABLE()