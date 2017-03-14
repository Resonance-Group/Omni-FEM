#include <UI/MaterialsDialog/MaterialDialog.h>

materialDialog::materialDialog(wxWindow *par, std::vector<magneticMaterial> materialList) : wxDialog(par, wxID_ANY, "Material Definition", wxDefaultPosition, wxSize(233, 148))
{
    _problem = physicProblems::PROB_MAGNETICS;
    
    _magneticMaterialList = materialList;
    
    for(std::vector<magneticMaterial>::iterator materialIterator = _magneticMaterialList.begin(); materialIterator != _magneticMaterialList.end(); ++materialIterator)
    {
        materialNameArray->Add(wxString(materialIterator->getName()));
    }
    
    makeDialog();
}



materialDialog::materialDialog(wxWindow *par, std::vector<electrostaticMaterial> electroStaticMaterialList) : wxDialog(par, wxID_ANY, "Material Definition", wxDefaultPosition, wxSize(233, 148))
{
    _problem = physicProblems::PROB_ELECTROSTATIC;
    
    _electroStaticMaterialList = electroStaticMaterialList;
    
    for(std::vector<electrostaticMaterial>::iterator materialIterator = _electroStaticMaterialList.begin(); materialIterator != _electroStaticMaterialList.end(); ++materialIterator)
    {
        materialNameArray->Add(wxString(materialIterator->getName()));
    }
    
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
    
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name: ", wxPoint(12, 9), wxSize(38, 13));
    name->SetFont(*font);
    
    selection->Create(this, wxID_ANY, wxEmptyString, wxPoint(56, 5), wxSize(139, 21), *materialNameArray);
    selection->SetFont(*font);
    if(materialNameArray->GetCount() > 0)
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


void materialDialog::onAddProperty(wxCommandEvent &event)
{
    if(_problem == physicProblems::PROB_MAGNETICS)
    {
        blockPropertyMagnetic *magneticMaterialPropertyDialog = new blockPropertyMagnetic();
        magneticMaterial newMat;
        magneticMaterialPropertyDialog->clearMaterial();
        if(magneticMaterialPropertyDialog->ShowModal() == wxID_OK)
        {
            magneticMaterialPropertyDialog->getNewMaterial(newMat);
            for(std::vector<magneticMaterial>::iterator materialIterator = _magneticMaterialList.begin();  materialIterator != _magneticMaterialList.end(); ++materialIterator)
            {
                if(materialIterator->getName() == newMat.getName())
                {
                    wxMessageBox(newMat.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER); 
                    break;
                }
            }
            _magneticMaterialList.push_back(newMat);
            selection->Append(newMat.getName());
            selection->SetSelection(0);
        }
    }
    else if(_problem == physicProblems::PROB_ELECTROSTATIC)
    {
        electrostaticMaterial newMaterial;
        _eStaticMaterialDialog->clearMaterial();
        if(_eStaticMaterialDialog->ShowModal() == wxID_OK)
        {
           _eStaticMaterialDialog->getMaterial(newMaterial);
            for(std::vector<electrostaticMaterial>::iterator materialIterator = _electroStaticMaterialList.begin();  materialIterator != _electroStaticMaterialList.end(); ++materialIterator)
            {
                if(materialIterator->getName() == newMaterial.getName())
                {
                    wxMessageBox(newMaterial.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER); 
                    break;
                }
            }
            _electroStaticMaterialList.push_back(newMaterial);
            selection->Append(newMaterial.getName());
            selection->SetSelection(0); 
        }
    }
} 



void materialDialog::onDeleteProperty(wxCommandEvent &event)
{
    if(_magneticMaterialList.size() > 0 && _problem == physicProblems::PROB_MAGNETICS)
    {
        int currentSelection = selection->GetCurrentSelection();
        _magneticMaterialList.erase(_magneticMaterialList.begin() + currentSelection);
        selection->Delete(currentSelection);
        selection->SetSelection(0);
    }
    else if(_electroStaticMaterialList.size() > 0 && _problem == physicProblems::PROB_ELECTROSTATIC)
    {
        int currentSelection = selection->GetCurrentSelection();
        _electroStaticMaterialList.erase(_electroStaticMaterialList.begin() + currentSelection);
        selection->Delete(currentSelection);
        selection->SetSelection(0);
    }
}



void materialDialog::onModifyProperty(wxCommandEvent &event)
{
    
    if(_magneticMaterialList.size() > 0 && _problem == physicProblems::PROB_MAGNETICS)
    {
        blockPropertyMagnetic *magneticMaterialPropertyDialog = new blockPropertyMagnetic();
        magneticMaterial selectedMaterial;
        int currentSelection = selection->GetSelection();
        selectedMaterial = _magneticMaterialList.at(currentSelection);
        magneticMaterialPropertyDialog->setMaterial(selectedMaterial);
        if(magneticMaterialPropertyDialog->ShowModal() == wxID_OK)
        {
            int i = 0;
            magneticMaterialPropertyDialog->getNewMaterial(selectedMaterial);
            for(std::vector<magneticMaterial>::iterator materialIterator = _magneticMaterialList.begin();  materialIterator != _magneticMaterialList.end();++materialIterator)
            {
                if(materialIterator->getName() == selectedMaterial.getName() && (i != currentSelection))
                {
                    wxMessageBox(selectedMaterial.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER); 
                    break;
                }
                i++;
            }
            _magneticMaterialList.at(currentSelection) = selectedMaterial;
            selection->SetString(currentSelection, selectedMaterial.getName());
        }
    }
    else if(_electroStaticMaterialList.size() > 0 && _problem == physicProblems::PROB_ELECTROSTATIC)
    {
        electrostaticMaterial selectedMaterial;
        int currentSelection = selection->GetSelection();
        selectedMaterial = _electroStaticMaterialList.at(currentSelection);
        _eStaticMaterialDialog->setMaterial(selectedMaterial);
        if(_eStaticMaterialDialog->ShowModal() == wxID_OK)
        {
            int i = 0;
            _eStaticMaterialDialog->getMaterial(selectedMaterial);
            for(std::vector<electrostaticMaterial>::iterator materialIterator = _electroStaticMaterialList.begin();  materialIterator != _electroStaticMaterialList.end();++materialIterator)
            {
                if(materialIterator->getName() == selectedMaterial.getName() && (i != currentSelection))
                {
                    wxMessageBox(selectedMaterial.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxICON_INFORMATION | wxCENTER); 
                    break;
                }
                i++;
            }
            _electroStaticMaterialList.at(currentSelection) = selectedMaterial;
            selection->SetString(currentSelection, selectedMaterial.getName());
        }
    }
}



std::vector<magneticMaterial> materialDialog::getMagenticMaterialList()
{
    return _magneticMaterialList;
}



std::vector<electrostaticMaterial>  materialDialog::getElectroMaterialList()
{
    return _electroStaticMaterialList;
}


materialDialog::~materialDialog()
{
    
}



wxBEGIN_EVENT_TABLE(materialDialog, wxDialog)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonAdd, materialDialog::onAddProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonDelete, materialDialog::onDeleteProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonModify, materialDialog::onModifyProperty)
wxEND_EVENT_TABLE()