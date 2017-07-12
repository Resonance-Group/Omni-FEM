#include <UI/ConductorsDialog/ConductorPropSetDialog.h>

conductorPropertySetDialog::conductorPropertySetDialog(wxWindow *par, std::vector<circuitProperty> *circuitList) : wxDialog(par, wxID_ANY, "Conductor Definition")
{
    _circuitList = circuitList;
 
    _problem = physicProblems::PROB_MAGNETICS;
   
    makeDialog();
}



conductorPropertySetDialog::conductorPropertySetDialog(wxWindow *par, std::vector<conductorProperty> *conductorList) : wxDialog(par, wxID_ANY, "Conductor Definition")
{
    _conductorList = conductorList;
 
    _problem = physicProblems::PROB_ELECTROSTATIC;
   
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
    
    wxArrayString conductorNameArray;
    
    
    switch(_problem)
    {
        case physicProblems::PROB_ELECTROSTATIC:
        {
            for(std::vector<conductorProperty>::iterator conductorIterator = _conductorList->begin(); conductorIterator != _conductorList->end(); ++conductorIterator)
            {
                conductorNameArray.Add(wxString(conductorIterator->getName()));
            }
        }
        break;
        case physicProblems::PROB_MAGNETICS:
        {
           for(std::vector<circuitProperty>::iterator circuitIterator = _circuitList->begin(); circuitIterator != _circuitList->end(); ++circuitIterator)
            {
                conductorNameArray.Add(wxString(circuitIterator->getName()));
            } 
        }
        break;
        default:
            return;
    }
    
    _selection->Create(this, wxID_ANY, wxEmptyString, wxPoint(56, 5), wxSize(139, 21), conductorNameArray);
    _selection->SetFont(*font);
    if(conductorNameArray.GetCount() > 0)
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


void conductorPropertySetDialog::onAddProperty(wxCommandEvent &event)
{
    if(_problem == physicProblems::PROB_MAGNETICS)
    {
        circuitPropertyDialog *circuitPropDialog = new circuitPropertyDialog(this);
        circuitProperty newCircuit;
        circuitPropDialog->clearCircuit();
        if(circuitPropDialog->ShowModal() == wxID_OK)
        {
            circuitPropDialog->getNewCircuit(newCircuit);
            for(std::vector<circuitProperty>::iterator circuitIterator = _circuitList->begin(); circuitIterator != _circuitList->end(); ++circuitIterator)
            {
                if(circuitIterator->getName() == newCircuit.getName())
                {
                    wxMessageBox(newCircuit.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                    break;
                }
            }
            _circuitList->push_back(newCircuit);
            _selection->Append(newCircuit.getName());
            _selection->SetSelection(0);
        }
    }
    else if(_problem == physicProblems::PROB_ELECTROSTATIC)
    {
        conductorPropertyDialog *conductorPropDialog = new conductorPropertyDialog(this);
        conductorProperty newConductor;
        conductorPropDialog->clearConductor();
        if(conductorPropDialog->ShowModal() == wxID_OK)
        {
            conductorPropDialog->getNewConductor(newConductor);
            for(std::vector<conductorProperty>::iterator conductorIterator = _conductorList->begin(); conductorIterator != _conductorList->end(); ++conductorIterator)
            {
                if(conductorIterator->getName() == newConductor.getName())
                {
                    wxMessageBox(newConductor.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                    break;
                }
            }
            _conductorList->push_back(newConductor);
            _selection->Append(newConductor.getName());
            _selection->SetSelection(0);
        }
    }
} 



void conductorPropertySetDialog::onDeleteProperty(wxCommandEvent &event)
{
    if(_circuitList != nullptr && _problem == physicProblems::PROB_MAGNETICS)
    {
        if(!_circuitList->empty())
        {
            int currentSelection = _selection->GetCurrentSelection();
            _circuitList->erase(_circuitList->begin() + currentSelection);
            _selection->Delete(currentSelection);
            _selection->SetSelection(0);
            if(_circuitList->empty())
                _selection->SetValue(wxEmptyString);
        }
    }
    else if(_conductorList != nullptr && _problem == physicProblems::PROB_ELECTROSTATIC)
    {
        if(!_conductorList->empty())
        {
            int currentSelection = _selection->GetCurrentSelection();
            _conductorList->erase(_conductorList->begin() + currentSelection);
            _selection->Delete(currentSelection);
            _selection->SetSelection(0);
            if(_conductorList->empty())
                _selection->SetValue(wxEmptyString);
        }
    }
}



void conductorPropertySetDialog::onModifyProperty(wxCommandEvent &event)
{
    
    if(_circuitList != nullptr && _problem == physicProblems::PROB_MAGNETICS)
    {
        if(!_circuitList->empty())
        {
            circuitProperty selectedCircuitProperty;
            circuitPropertyDialog *circuitPropDialog = new circuitPropertyDialog(this);
            int currentSelection = _selection->GetSelection();
            selectedCircuitProperty = _circuitList->at(currentSelection);
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
                for(std::vector<circuitProperty>::iterator circuitIterator = _circuitList->begin(); circuitIterator != _circuitList->end(); ++circuitIterator)
                {
                    if(circuitIterator->getName() == selectedCircuitProperty.getName() && (i != currentSelection))
                    {
                        wxMessageBox(selectedCircuitProperty.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                        break;
                    }
                    
                    i++;
                } 
                _circuitList->at(currentSelection) = selectedCircuitProperty;
                _selection->SetString(currentSelection, selectedCircuitProperty.getName());
                _selection->SetSelection(0);
            }
        }
    }
    else if(_conductorList != nullptr && _problem == physicProblems::PROB_ELECTROSTATIC)
    {
        if(!_conductorList->empty())
        {
            conductorProperty selectedConductor;
            conductorPropertyDialog *conductorPropDialog = new conductorPropertyDialog(this);
            int currentSelection = _selection->GetSelection();
            selectedConductor = _conductorList->at(currentSelection);
            conductorPropDialog->setConductor(selectedConductor);
            if(conductorPropDialog->ShowModal() == wxID_OK)
            {
                int i = 0;
                conductorPropDialog->getNewConductor(selectedConductor);
                for(std::vector<conductorProperty>::iterator conductorIterator = _conductorList->begin(); conductorIterator != _conductorList->end(); ++conductorIterator)
                {
                    if(conductorIterator->getName() == selectedConductor.getName() && i != currentSelection)
                    {
                        wxMessageBox(selectedConductor.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                        break;
                    }
                    i++;
                }
                _conductorList->at(currentSelection) = selectedConductor;
                _selection->SetString(currentSelection, selectedConductor.getName());
                _selection->SetSelection(0);
            }
        }
    }
}



conductorPropertySetDialog::~conductorPropertySetDialog()
{
    
}



wxBEGIN_EVENT_TABLE(conductorPropertySetDialog, wxDialog)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonAdd, conductorPropertySetDialog::onAddProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonDelete, conductorPropertySetDialog::onDeleteProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonModify, conductorPropertySetDialog::onModifyProperty)
wxEND_EVENT_TABLE()