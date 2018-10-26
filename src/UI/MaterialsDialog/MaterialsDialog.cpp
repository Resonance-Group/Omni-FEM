#include <UI/MaterialsDialog/MaterialDialog.h>

materialDialog::materialDialog(wxWindow *par, std::vector<magneticMaterial> *materialList) : wxDialog(par, wxID_ANY, "Material Definition", wxDefaultPosition, wxSize(233, 148))
{
    _problem = physicProblems::PROB_MAGNETICS;
    
    _magneticMaterialList = materialList;
    
    makeDialog();
}



materialDialog::materialDialog(wxWindow *par, std::vector<electrostaticMaterial> *electroStaticMaterialList) : wxDialog(par, wxID_ANY, "Material Definition", wxDefaultPosition, wxSize(233, 148))
{
    _problem = physicProblems::PROB_ELECTROSTATIC;
    
    _electroStaticMaterialList = electroStaticMaterialList;
    
    makeDialog();
}



void materialDialog::makeDialog()
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *propertySizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *okSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *intermediateSizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name: ");
    name->SetFont(*font);
    
    wxArrayString materialNameArray;
    
    switch(_problem)
    {
        case physicProblems::PROB_ELECTROSTATIC:
        {
            for(std::vector<electrostaticMaterial>::iterator materialIterator = _electroStaticMaterialList->begin(); materialIterator != _electroStaticMaterialList->end(); ++materialIterator)
            {
                materialNameArray.Add(wxString(materialIterator->getName()));
            }
        }
        break;
        case physicProblems::PROB_MAGNETICS:
        {
           for(std::vector<magneticMaterial>::iterator materialIterator = _magneticMaterialList->begin(); materialIterator != _magneticMaterialList->end(); ++materialIterator)
            {
                materialNameArray.Add(wxString(materialIterator->getName()));
            } 
        }
        break;
        default:
            return;
    }
    
    _selection->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(139, 21), materialNameArray);
    _selection->SetFont(*font);
    if(materialNameArray.GetCount() > 0)
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


void materialDialog::onAddProperty(wxCommandEvent &event)
{
    if(_problem == physicProblems::PROB_MAGNETICS)
    {
        blockPropertyMagnetic *magneticMaterialPropertyDialog = new blockPropertyMagnetic(this);
        magneticMaterial newMat;
        magneticMaterialPropertyDialog->clearMaterial();
        if(magneticMaterialPropertyDialog->ShowModal() == wxID_OK)
        {
            magneticMaterialPropertyDialog->getNewMaterial(newMat);
            for(std::vector<magneticMaterial>::iterator materialIterator = _magneticMaterialList->begin();  materialIterator != _magneticMaterialList->end(); ++materialIterator)
            {
                if(materialIterator->getName() == newMat.getName())
                {
                    wxMessageBox(newMat.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER); 
                    break;
                }
            }
			newMat.setMaterialID(_magneticMaterialList->size() + 1);
            _magneticMaterialList->push_back(newMat);
            _selection->Append(newMat.getName());
            _selection->SetSelection(0);
        }
    }
    else if(_problem == physicProblems::PROB_ELECTROSTATIC)
    {
        electrostaticMaterial newMaterial;
        blockPropertyDialogElectrostatic *eStaticMaterialDialog = new blockPropertyDialogElectrostatic(this);
        eStaticMaterialDialog->clearMaterial();
        if(eStaticMaterialDialog->ShowModal() == wxID_OK)
        {
           eStaticMaterialDialog->getMaterial(newMaterial);
            for(std::vector<electrostaticMaterial>::iterator materialIterator = _electroStaticMaterialList->begin();  materialIterator != _electroStaticMaterialList->end(); ++materialIterator)
            {
                if(materialIterator->getName() == newMaterial.getName())
                {
                    wxMessageBox(newMaterial.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER); 
                    break;
                }
            }
			newMaterial.setMaterialID(_electroStaticMaterialList->size() + 1);
            _electroStaticMaterialList->push_back(newMaterial);
            _selection->Append(newMaterial.getName());
            _selection->SetSelection(0); 
        }
    }
} 



void materialDialog::onDeleteProperty(wxCommandEvent &event)
{
    if(_magneticMaterialList != nullptr && _problem == physicProblems::PROB_MAGNETICS)
    {
        if(!_magneticMaterialList->empty())
        {
            int currentSelection = _selection->GetCurrentSelection();
			unsigned int IDCounter = 1;
			
            _magneticMaterialList->erase(_magneticMaterialList->begin() + currentSelection);
            _selection->Delete(currentSelection);
            _selection->SetSelection(0);
			
			for(auto materialIterator = _magneticMaterialList->begin(); materialIterator != _magneticMaterialList->end(); materialIterator++)
			{
				materialIterator->setMaterialID(IDCounter++);
			}
			
            if(_magneticMaterialList->empty())
                _selection->SetValue(wxEmptyString);
        }
    }
    else if(_electroStaticMaterialList != nullptr && _problem == physicProblems::PROB_ELECTROSTATIC)
    {
        if(!_electroStaticMaterialList->empty())
        {
            int currentSelection = _selection->GetCurrentSelection();
			unsigned int IDCounter = 1;
			
            _electroStaticMaterialList->erase(_electroStaticMaterialList->begin() + currentSelection);
            _selection->Delete(currentSelection);
            _selection->SetSelection(0);
			
			for(auto materialIterator = _electroStaticMaterialList->begin(); materialIterator != _electroStaticMaterialList->end(); materialIterator++)
			{
				materialIterator->setMaterialID(IDCounter++);
			}
			
            if(_electroStaticMaterialList->empty())
                _selection->SetValue(wxEmptyString);
        }
    }
}



void materialDialog::onModifyProperty(wxCommandEvent &event)
{
    
    if(_magneticMaterialList != nullptr && _problem == physicProblems::PROB_MAGNETICS)
    {
        if(!_magneticMaterialList->empty())
        {
            blockPropertyMagnetic *magneticMaterialPropertyDialog = new blockPropertyMagnetic(this);
            magneticMaterial selectedMaterial;
            int currentSelection = _selection->GetSelection();
            selectedMaterial = _magneticMaterialList->at(currentSelection);
            magneticMaterialPropertyDialog->setMaterial(selectedMaterial);
            if(magneticMaterialPropertyDialog->ShowModal() == wxID_OK)
            {
                int i = 0;
                magneticMaterialPropertyDialog->getNewMaterial(selectedMaterial);
                for(std::vector<magneticMaterial>::iterator materialIterator = _magneticMaterialList->begin();  materialIterator != _magneticMaterialList->end(); ++materialIterator)
                {
                    if(materialIterator->getName() == selectedMaterial.getName() && (i != currentSelection))
                    {
                        wxMessageBox(selectedMaterial.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER); 
                        break;
                    }
                    i++;
                }
                _magneticMaterialList->at(currentSelection) = selectedMaterial;
                _selection->SetString(currentSelection, selectedMaterial.getName());
            }
        }
    }
    else if(_electroStaticMaterialList != nullptr && _problem == physicProblems::PROB_ELECTROSTATIC)
    {
        if(!_electroStaticMaterialList->empty())
        {
            electrostaticMaterial selectedMaterial;
            blockPropertyDialogElectrostatic *eStaticMaterialDialog = new blockPropertyDialogElectrostatic(this);
            int currentSelection = _selection->GetSelection();
            selectedMaterial = _electroStaticMaterialList->at(currentSelection);
            eStaticMaterialDialog->setMaterial(selectedMaterial);
            if(eStaticMaterialDialog->ShowModal() == wxID_OK)
            {
                int i = 0;
                eStaticMaterialDialog->getMaterial(selectedMaterial);
                for(std::vector<electrostaticMaterial>::iterator materialIterator = _electroStaticMaterialList->begin();  materialIterator != _electroStaticMaterialList->end();++materialIterator)
                {
                    if(materialIterator->getName() == selectedMaterial.getName() && (i != currentSelection))
                    {
                        wxMessageBox(selectedMaterial.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER); 
                        break;
                    }
                    i++;
                }
                _electroStaticMaterialList->at(currentSelection) = selectedMaterial;
                _selection->SetString(currentSelection, selectedMaterial.getName());
            }
        }
    }
}



materialDialog::~materialDialog()
{
    
}



wxBEGIN_EVENT_TABLE(materialDialog, wxDialog)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonAdd, materialDialog::onAddProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonDelete, materialDialog::onDeleteProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonModify, materialDialog::onModifyProperty)
wxEND_EVENT_TABLE()