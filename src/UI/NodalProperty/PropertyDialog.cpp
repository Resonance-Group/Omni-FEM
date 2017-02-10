#include <UI/NodalProperty/PropertyDialog.h>

nodalPropertiesDialog::nodalPropertiesDialog(std::vector<nodalProperty> nodalPropertyList) : wxDialog(NULL, wxID_ANY, "Nodal Definition", wxDefaultPosition, wxSize(204, 140))
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *propertySizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *okSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *intermediateSizer = new wxBoxSizer(wxHORIZONTAL);
    
    _nodalPropertyList = nodalPropertyList;
    
    for(std::vector<nodalProperty>::iterator nodalIterator = _nodalPropertyList.begin(); nodalIterator != _nodalPropertyList.end(); ++nodalIterator)
    {
        nodalPropertyNameArray->Add(wxString(nodalIterator->getName()));
    }

    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name: ", wxPoint(12, 9), wxSize(38, 13));
    name->SetFont(*font);
    
    selection->Create(this, wxID_ANY, wxEmptyString, wxPoint(56, 5), wxSize(139, 21), *nodalPropertyNameArray);
    selection->SetFont(*font);
    
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
    propertySizer->Add(modifyPropertyButton, 0, wxALIGN_BOTTOM | wxDOWN | wxLEFT, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "OK", wxPoint(120, 101), wxSize(75, 23));
    okButton->SetFont(*font);
    
    okSizer->Add(0, 68, 0);
    okSizer->Add(okButton, 0, wxALIGN_BOTTOM | wxDOWN | wxRIGHT, 6);
    
    intermediateSizer->Add(propertySizer, 0, wxALIGN_LEFT);
    intermediateSizer->Add(6, 0, 0);
    intermediateSizer->Add(okSizer, 0, wxALIGN_RIGHT);
    
    
    topSizer->Add(headerSizer, 0, wxALIGN_TOP);
    topSizer->Add(0, 10, 0);
    topSizer->Add(intermediateSizer, 0, wxALIGN_BOTTOM);
    
    SetSizerAndFit(topSizer);
}



void nodalPropertiesDialog::onAddProperty(wxCommandEvent &event)
{
    nodalProperty newNodalProperty;
    _nodalPropertyDialog->clearNodalProperty();
    if(_nodalPropertyDialog->ShowModal() == wxID_OK)
    {
        _nodalPropertyDialog->getNodalProperty(newNodalProperty);
        for(std::vector<nodalProperty>::iterator nodalIterator = _nodalPropertyList.begin(); nodalIterator != _nodalPropertyList.end(); ++nodalIterator)
        {
            if(nodalIterator->getName() == newNodalProperty.getName())
            {
                wxMessageBox(newNodalProperty.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                break;
            }
        }
        _nodalPropertyList.push_back(newNodalProperty);
        selection->Append(newNodalProperty.getName());
        selection->SetSelection(0);
    }
} 



void nodalPropertiesDialog::onDeleteProperty(wxCommandEvent &event)
{
    if(_nodalPropertyList.size() > 0)
    {
        int currentSelection = selection->GetCurrentSelection();
        _nodalPropertyList.erase(_nodalPropertyList.begin() + currentSelection);
        selection->Delete(currentSelection);
        selection->SetSelection(0);
    }
}



void nodalPropertiesDialog::onModifyProperty(wxCommandEvent &event)
{
    nodalProperty selectedNodalProperty;
    if(_nodalPropertyList.size() > 0)
    {
        int currentSelection = selection->GetSelection();
        selectedNodalProperty = _nodalPropertyList.at(currentSelection);
        _nodalPropertyDialog->setNodalProperty(selectedNodalProperty);
        if(_nodalPropertyDialog->ShowModal() == wxID_OK)
        {
            /*
             * This is a counter. The loop is checking to see if the user accidently changed the name of the material to one that is already there.
             * However, the one that the user wants to modify is still in the list. So, the program needs to skip
             * that one. Which, this counter will assit in that
              */
            int i = 0;
            _nodalPropertyDialog->getNodalProperty(selectedNodalProperty);
            for(std::vector<nodalProperty>::iterator nodalIterator = _nodalPropertyList.begin(); nodalIterator != _nodalPropertyList.end(); ++nodalIterator)
            {
                if(nodalIterator->getName() == selectedNodalProperty.getName() && (i != currentSelection))
                {
                    wxMessageBox(selectedNodalProperty.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                    break;
                }
                
                i++;
            } 
            _nodalPropertyList.at(currentSelection) = selectedNodalProperty;
            selection->SetString(currentSelection, selectedNodalProperty.getName());
        }
        selection->SetSelection(0);
    }
}



std::vector<nodalProperty> nodalPropertiesDialog::getNodalPropertyList()
{
    return _nodalPropertyList;
}





nodalPropertiesDialog::~nodalPropertiesDialog()
{
    
}


wxBEGIN_EVENT_TABLE(nodalPropertiesDialog, wxDialog)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonAdd, nodalPropertiesDialog::onAddProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonDelete, nodalPropertiesDialog::onDeleteProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonModify, nodalPropertiesDialog::onModifyProperty)
wxEND_EVENT_TABLE()