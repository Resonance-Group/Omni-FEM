#include <UI/BoundaryDialog/BoundaryDialog.h>

boundaryDialog::boundaryDialog(std::vector<magneticBoundary> boundaryList) : wxDialog(NULL, wxID_ANY, "Boundary Definition", wxDefaultPosition, wxSize(233, 148))
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    _magneticBoundaryList = boundaryList;
    
    for(std::vector<magneticBoundary>::iterator boundaryIterator = _magneticBoundaryList.begin(); boundaryIterator != _magneticBoundaryList.end(); ++boundaryIterator)
    {
        magneticBoundaryNameArray->Add(wxString(boundaryIterator->getBoundaryName()));
    }
    
    wxButton *addPropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonAdd, "Add Property", wxPoint(12, 49), wxSize(125, 26));
    
    wxButton *deletePropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonDelete, "Delete Property", wxPoint(12, 78), wxSize(125, 26));
    
    wxButton *modifyPropertyButton = new wxButton(this, propertiesDialogEnum::ID_ButtonModify, "Modify Property", wxPoint(12, 107), wxSize(125, 26));
    
    wxButton *okButton = new wxButton(this, wxID_OK, "OK", wxPoint(146, 107), wxSize(75, 23));
    
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name: ", wxPoint(12, 9), wxSize(38, 13));
    name->SetFont(*font);
    
    selection->Create(this, wxID_ANY, wxEmptyString, wxPoint(56, 6), wxSize(165, 21), *magneticBoundaryNameArray);
    selection->SetFont(*font);
    
    this->FitInside();
    this->SetMinSize(this->GetSize());
    this->SetMaxSize(this->GetSize());
}



void boundaryDialog::onAddProperty(wxCommandEvent &event)
{
    if(_magBoundaryDialog->ShowModal() == wxID_OK)
    {
        
    }
    /*
    magneticMaterial newMat;
    magneticMaterialPropertyDialog->clearMaterial();
    if(magneticMaterialPropertyDialog->ShowModal() == wxID_OK)
    {
        magneticMaterialPropertyDialog->getNewMaterial(newMat);
        for(std::vector<magneticMaterial>::iterator boundaryIterator = _magneticMaterialList.begin();  boundaryIterator != _magneticMaterialList.end(); ++boundaryIterator)
        {
            if(boundaryIterator->getName() == newMat.getName())
            {
                wxMessageBox(newMat.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxCENTRE | wxICON_INFORMATION); 
                break;
            }
        }
        _magneticMaterialList.push_back(newMat);
        selection->Append(newMat.getName());
        selection->SetSelection(0);
    }
     */
} 



void boundaryDialog::onDeleteProperty(wxCommandEvent &event)
{
    if(_magneticBoundaryList.size() > 0)
    {
        int currentSelection = selection->GetCurrentSelection();
        _magneticBoundaryList.erase(_magneticBoundaryList.begin() + currentSelection);
        selection->Delete(currentSelection);
        selection->SetSelection(0);
    }
}



void boundaryDialog::onModifyProperty(wxCommandEvent &event)
{
    /*
    magneticMaterial selectedMaterial;
    if(_magneticMaterialList.size() > 0)
    {
        int currentSelection = selection->GetSelection();
        selectedMaterial = _magneticMaterialList.at(currentSelection);
        magneticMaterialPropertyDialog->setMaterial(selectedMaterial);
        if(magneticMaterialPropertyDialog->ShowModal() == wxID_OK)
        {
            int i = 0;
            magneticMaterialPropertyDialog->getNewMaterial(selectedMaterial);
            for(std::vector<magneticMaterial>::iterator boundaryIterator = _magneticMaterialList.begin();  boundaryIterator != _magneticMaterialList.end();++boundaryIterator)
            {
                if(boundaryIterator->getName() == selectedMaterial.getName() && (i != currentSelection))
                {
                    wxMessageBox(selectedMaterial.getName().append(" already exists. Choose a different name."), "Information", wxOK | wxCENTRE | wxICON_INFORMATION); 
                    break;
                }
                i++;
            }
            _magneticMaterialList.at(currentSelection) = selectedMaterial;
            selection->SetString(currentSelection, selectedMaterial.getName());
            
        }
    }
     */ 
}



std::vector<magneticBoundary> boundaryDialog::getBoundaryList()
{
    return _magneticBoundaryList;
}



boundaryDialog::~boundaryDialog()
{
    
}



wxBEGIN_EVENT_TABLE(boundaryDialog, wxDialog)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonAdd, boundaryDialog::onAddProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonDelete, boundaryDialog::onDeleteProperty)
    EVT_BUTTON(propertiesDialogEnum::ID_ButtonModify, boundaryDialog::onModifyProperty)
wxEND_EVENT_TABLE()