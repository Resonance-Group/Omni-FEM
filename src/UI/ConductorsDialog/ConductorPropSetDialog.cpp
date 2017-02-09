#include <UI/ConductorsDialog/ConductorPropSetDialog.h>

conductorPropertySetDialog::conductorPropertySetDialog(std::vector<circuitProperty> circuitList) : wxDialog(NULL, wxID_ANY, "Nodal Definition", wxDefaultPosition)
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *propertySizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *okSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *intermediateSizer = new wxBoxSizer(wxHORIZONTAL);
    
    _circuitList = circuitList;
    
    for(std::vector<circuitProperty>::iterator circuitIterator = _circuitList.begin(); circuitIterator != _circuitList.end(); ++circuitIterator)
    {
        circuitNameArray->Add(wxString(circuitIterator->getName()));
    }
    
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name: ", wxPoint(12, 9), wxSize(38, 13));
    name->SetFont(*font);
    
    selection->Create(this, wxID_ANY, wxEmptyString, wxPoint(56, 5), wxSize(139, 21), *circuitNameArray);
    selection->SetFont(*font);
    
    headerSizer->Add(name, 0, wxALIGN_CENTER);
  //  headerSizer->Add(6, 0, 0);
    headerSizer->Add(selection, 0, wxLEFT | wxDOWN, 6);
    
    wxButton *addPropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonAdd, "Add Property", wxPoint(12, 43), wxSize(102, 23));
    addPropertyButton->SetFont(*font);
    
    wxButton *deletePropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonDelete, "Delete Property", wxPoint(12, 72), wxSize(102, 23));
    deletePropertyButton->SetFont(*font);
    
    wxButton *modifyPropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonModify, "Modify Property", wxPoint(12, 101), wxSize(102, 23));
    modifyPropertyButton->SetFont(*font);
    
    propertySizer->Add(addPropertyButton, 0, wxALIGN_TOP | wxALIGN_LEFT);
    propertySizer->Add(deletePropertyButton, 0, wxALIGN_CENTER | wxALIGN_LEFT);
    propertySizer->Add(modifyPropertyButton, 0, wxALIGN_BOTTOM | wxALIGN_LEFT);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "OK", wxPoint(120, 101), wxSize(75, 23));
    okButton->SetFont(*font);
    
    okSizer->Add(0, 46, 0);
    okSizer->Add(okButton, 0, wxALIGN_BOTTOM);
    
    intermediateSizer->Add(propertySizer, 0, wxALIGN_LEFT);
    intermediateSizer->Add(6, 0, 0);
    intermediateSizer->Add(okSizer, 0, wxALIGN_RIGHT);
    
    
    topSizer->Add(headerSizer, 0, wxALIGN_TOP);
    topSizer->Add(0, 10, 0);
    topSizer->Add(intermediateSizer, 0, wxALIGN_BOTTOM);
    
    SetSizerAndFit(topSizer);
}



void conductorPropertySetDialog::onAddProperty(wxCommandEvent &event)
{
    /*
    nodalProperty newNodalProperty;
    _nodalPropertyDialog->clearNodalProperty();
    if(_nodalPropertyDialog->ShowModal() == wxID_OK)
    {
        _nodalPropertyDialog->getNodalProperty(newNodalProperty);
        for(std::vector<nodalProperty>::iterator circuitIterator = _circuitList.begin(); circuitIterator != _circuitList.end(); ++circuitIterator)
        {
            if(circuitIterator->getName() == newNodalProperty.getName())
            {
                wxMessageBox(newNodalProperty.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                break;
            }
        }
        _circuitList.push_back(newNodalProperty);
        selection->Append(newNodalProperty.getName());
        selection->SetSelection(0);
    }
     */
} 



void conductorPropertySetDialog::onDeleteProperty(wxCommandEvent &event)
{
    if(_circuitList.size() > 0)
    {
        int currentSelection = selection->GetCurrentSelection();
        _circuitList.erase(_circuitList.begin() + currentSelection);
        selection->Delete(currentSelection);
        selection->SetSelection(0);
    }
    else if(_conductorList.size() > 0)
    {
        int currentSelection = selection->GetCurrentSelection();
        _conductorList.erase(_conductorList.begin() + currentSelection);
        selection->Delete(currentSelection);
        selection->SetSelection(0);
    }
}



void conductorPropertySetDialog::onModifyProperty(wxCommandEvent &event)
{
    /*
    circuitProperty selectedCircuitProperty;
    if(_circuitList.size() > 0)
    {
        int currentSelection = selection->GetSelection();
        selectedCircuitProperty = _circuitList.at(currentSelection);
        _nodalPropertyDialog->setNodalProperty(selectedCircuitProperty);
        if(_nodalPropertyDialog->ShowModal() == wxID_OK)
        {
            /*
             * This is a counter. The loop is checking to see if the user accidently changed the name of the material to one that is already there.
             * However, the one that the user wants to modify is still in the list. So, the program needs to skip
             * that one. Which, this counter will assit in that
              *
            int i = 0;
            _nodalPropertyDialog->getNodalProperty(selectedCircuitProperty);
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
        }
        selection->SetSelection(0);
    }
     */ 
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