#include <UI/NodalProperty/PropertyDialog.h>


nodalPropertiesDialog::nodalPropertiesDialog(wxWindow *par, std::vector<nodalProperty> *nodalPropertyList, physicProblems problem) : wxDialog(par, wxID_ANY, "Nodal Definition", wxDefaultPosition, wxSize(204, 140))
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *propertySizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *okSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *intermediateSizer = new wxBoxSizer(wxHORIZONTAL);
    
    _nodalPropertyList = nodalPropertyList;
    _problem = problem;

    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name: ", wxPoint(12, 9), wxSize(38, 13));
    name->SetFont(*font);
    
    wxArrayString nodalPropertyNameArray;
    
    for(std::vector<nodalProperty>::iterator nodalIterator = _nodalPropertyList->begin(); nodalIterator != _nodalPropertyList->end(); ++nodalIterator)
    {
        nodalPropertyNameArray.Add(wxString(nodalIterator->getName()));
    }
    
    _selection->Create(this, wxID_ANY, wxEmptyString, wxPoint(56, 5), wxSize(139, 21), nodalPropertyNameArray);
    _selection->SetFont(*font);
    if(nodalPropertyNameArray.GetCount() > 0)
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
    intermediateSizer->Add(okSizer, 0);
    
    topSizer->Add(headerSizer, 0, wxALIGN_TOP);
    topSizer->Add(0, 10, 0);
    topSizer->Add(intermediateSizer, 0);
    
    SetSizerAndFit(topSizer);
}



void nodalPropertiesDialog::onAddProperty(wxCommandEvent &event)
{
    nodalProperty newNodalProperty;
    nodalPropertyDialog *nodalPropDialog = new nodalPropertyDialog(this, _problem);
        
    nodalPropDialog->clearNodalProperty();
    if(nodalPropDialog->ShowModal() == wxID_OK)
    {
        nodalPropDialog->getNodalProperty(newNodalProperty);
        for(std::vector<nodalProperty>::iterator nodalIterator = _nodalPropertyList->begin(); nodalIterator != _nodalPropertyList->end(); ++nodalIterator)
        {
            if(nodalIterator->getName() == newNodalProperty.getName())
            {
                wxMessageBox(newNodalProperty.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                break;
            }
        }
        _nodalPropertyList->push_back(newNodalProperty);
        _selection->Append(newNodalProperty.getName());
        _selection->SetSelection(0);
    }
} 



void nodalPropertiesDialog::onDeleteProperty(wxCommandEvent &event)
{
    if(!_nodalPropertyList->empty())
    {
        int currentSelection = _selection->GetCurrentSelection();
        _nodalPropertyList->erase(_nodalPropertyList->begin() + currentSelection);
        _selection->Delete(currentSelection);
        _selection->SetSelection(0);
        if(_nodalPropertyList->empty())
            _selection->SetValue(wxEmptyString);
    }
}



void nodalPropertiesDialog::onModifyProperty(wxCommandEvent &event)
{
    nodalProperty selectedNodalProperty;
    nodalPropertyDialog *nodalPropDialog = new nodalPropertyDialog(this, _problem);
        
    if(!_nodalPropertyList->empty())
    {
        int currentSelection = _selection->GetSelection();
        selectedNodalProperty = _nodalPropertyList->at(currentSelection);
        nodalPropDialog->setNodalProperty(selectedNodalProperty);
        if(nodalPropDialog->ShowModal() == wxID_OK)
        {
            /*
             * This is a counter. The loop is checking to see if the user accidently changed the name of the material to one that is already there.
             * However, the one that the user wants to modify is still in the list. So, the program needs to skip
             * that one. Which, this counter will assit in that
              */
            int i = 0;
            nodalPropDialog->getNodalProperty(selectedNodalProperty);
            for(std::vector<nodalProperty>::iterator nodalIterator = _nodalPropertyList->begin(); nodalIterator != _nodalPropertyList->end(); ++nodalIterator)
            {
                if(nodalIterator->getName() == selectedNodalProperty.getName() && (i != currentSelection))
                {
                    wxMessageBox(selectedNodalProperty.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER);
                    break;
                }
                
                i++;
            } 
            _nodalPropertyList->at(currentSelection) = selectedNodalProperty;
            _selection->SetString(currentSelection, selectedNodalProperty.getName());
        }
        _selection->SetSelection(0);
    }
}



nodalPropertiesDialog::~nodalPropertiesDialog()
{
    
}


wxBEGIN_EVENT_TABLE(nodalPropertiesDialog, wxDialog)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonAdd, nodalPropertiesDialog::onAddProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonDelete, nodalPropertiesDialog::onDeleteProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonModify, nodalPropertiesDialog::onModifyProperty)
wxEND_EVENT_TABLE()