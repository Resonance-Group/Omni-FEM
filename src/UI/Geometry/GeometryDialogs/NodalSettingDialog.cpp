#include <UI/GeometryDialog/NodalSettingDialog.h>


setNodalPropertyDialog::setNodalPropertyDialog(std::vector<nodalProperty> &nodePropertyList, nodeSetting &nodeSettings, std::vector<conductorProperty> &conductorPropertyList) : wxDialog(NULL, wxID_ANY, "Nodal Settings")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
     
    wxBoxSizer *line1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line2Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line3Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
     
    _nodalList = nodePropertyList;
    _conductorList = conductorPropertyList;
    _nodeSetting = nodeSettings;
    _problem = physicProblems::PROB_ELECTROSTATIC;
    
    wxArrayString *nodePropertyNameArray = new wxArrayString();
    nodePropertyNameArray->Add("None");
     
    wxArrayString *conductorPropertyNameArray = new wxArrayString();
    conductorPropertyNameArray->Add("None");
     
    for(std::vector<nodalProperty>::iterator nameIterator = _nodalList.begin(); nameIterator != _nodalList.end(); ++nameIterator)
    {
        nodePropertyNameArray->Add(nameIterator->getName());
    }
    
    for(std::vector<conductorProperty>::iterator nameIterator = _conductorList.begin(); nameIterator != _conductorList.end(); ++nameIterator)
    {
        conductorPropertyNameArray->Add(nameIterator->getName());
    }
    
    wxStaticText *nodalName = new wxStaticText(this, wxID_ANY, "Nodal Property:");
    nodalName->SetFont(*font);
    _nodePropertyComboBox->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(156, 21), *nodePropertyNameArray);
    _nodePropertyComboBox->SetFont(*font);
    if(!_nodeSetting.getNodePropertyState())
    {
        _nodePropertyComboBox->SetSelection(0);
    }
    else
    {
        /* Here we take the global nodel list and find at what position the node's nodal property is at given that
         * we know the name. From there, we can determine what selection to set the combo box becuase it is +1 of the 
         * nodal list position
         */ 
        for(int i = 0; i < _nodalList.size(); i++)
        {
            if(_nodalList.at(i).getName() == _nodeSetting.getNodalProperty().getName())
            {
                _nodePropertyComboBox->SetSelection(i + 1);
                break;
            }
        }
    }
    
    line1Sizer->Add(nodalName, 0, wxCENTER | wxALL, 6);
    line1Sizer->Add(_nodePropertyComboBox, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *groupText = new wxStaticText(this, wxID_ANY, "In Group:");
    groupText->SetFont(*font);
    _groupTextCtrl->Create(this, wxID_ANY, std::to_string(_nodeSetting.getGroupNumber()), wxDefaultPosition, wxSize(156, 21));
    _groupTextCtrl->SetFont(*font);
    
    line2Sizer->Add(groupText, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    line2Sizer->Add(33, 0, 0);
    line2Sizer->Add(_groupTextCtrl, 0, wxCENTER | wxRIGHT | wxBOTTOM, 6);
    
    wxStaticText *conductorText = new wxStaticText(this, wxID_ANY, "Conductor:");
    conductorText->SetFont(*font);
    _conductorsComboBox->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(156, 21), *conductorPropertyNameArray);
    _conductorsComboBox->SetFont(*font);
    if(!_nodeSetting.getConductorPropertyState())
    {
        _conductorsComboBox->SetSelection(0);
    }
    else
    {
        for(int i = 0; i < _conductorList.size(); i++)
        {
            if(_conductorList.at(i).getName() == _nodeSetting.getConductorProperty().getName())
            {
                _conductorsComboBox->SetSelection(i + 1);
                break;
            }
        }
    }
    
    line3Sizer->Add(conductorText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    line3Sizer->Add(23, 0, 0);
    line3Sizer->Add(_conductorsComboBox, 0, wxCENTER | wxRIGHT | wxBOTTOM, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxDefaultPosition, wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    footerSizer->Add(cancelButton, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    topSizer->Add(line1Sizer);
    topSizer->Add(line2Sizer);
    topSizer->Add(line3Sizer);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
}
 
 
 
setNodalPropertyDialog::setNodalPropertyDialog(std::vector<nodalProperty> &nodePropertyList, nodeSetting &nodeSettings) : wxDialog(NULL, wxID_ANY, "Nodal Settings")
{
     wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
     
    wxBoxSizer *line1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *line2Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
     
    _nodalList = nodePropertyList;
    _nodeSetting = nodeSettings;
    _problem = physicProblems::PROB_MAGNETICS;
    
    wxArrayString *nodePropertyNameArray = new wxArrayString();
    nodePropertyNameArray->Add("None");
     
    for(std::vector<nodalProperty>::iterator nameIterator = _nodalList.begin(); nameIterator != _nodalList.end(); ++nameIterator)
    {
        nodePropertyNameArray->Add(nameIterator->getName());
    }
    
    wxStaticText *nodalName = new wxStaticText(this, wxID_ANY, "Nodal Property:");
    nodalName->SetFont(*font);
    _nodePropertyComboBox->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(156, 21), *nodePropertyNameArray);
    _nodePropertyComboBox->SetFont(*font);
    if(!_nodeSetting.getNodePropertyState())
    {
        _nodePropertyComboBox->SetSelection(0);
    }
    else
    {
        /* Here we take the global nodel list and find at what position the node's nodal property is at given that
         * we know the name. From there, we can determine what selection to set the combo box becuase it is +1 of the 
         * nodal list position
         */ 
        for(int i = 0; i < _nodalList.size(); i++)
        {
            if(_nodalList.at(i).getName() == _nodeSetting.getNodalProperty().getName())
            {
                _nodePropertyComboBox->SetSelection(i + 1);
                break;
            }
        }
    }
    
    line1Sizer->Add(nodalName, 0, wxCENTER | wxALL, 6);
    line1Sizer->Add(_nodePropertyComboBox, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticText *groupText = new wxStaticText(this, wxID_ANY, "In Group:");
    groupText->SetFont(*font);
    _groupTextCtrl->Create(this, wxID_ANY, std::to_string(_nodeSetting.getGroupNumber()), wxDefaultPosition, wxSize(156, 21));
    _groupTextCtrl->SetFont(*font);
    
    line2Sizer->Add(groupText, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    line2Sizer->Add(33, 0, 0);
    line2Sizer->Add(_groupTextCtrl, 0, wxCENTER | wxRIGHT | wxBOTTOM, 6);
    
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxDefaultPosition, wxSize(75, 23));
    okButton->SetFont(*font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(okButton, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    footerSizer->Add(cancelButton, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    topSizer->Add(line1Sizer);
    topSizer->Add(line2Sizer);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
}



void setNodalPropertyDialog::getNodalSettings(nodeSetting &settings)
{
    long value;
    
    settings.setPhysicsProblem(_nodeSetting.getPhysicsProblem());
    
    if(_nodePropertyComboBox->GetSelection() != 0)
    {
        for(int i = 1; i < _nodePropertyComboBox->GetCount(); i++)
        {
            if(_nodalList.at(i - 1).getName() == _nodePropertyComboBox->GetString(_nodePropertyComboBox->GetSelection()))
            {
                settings.setNodalProperty(_nodalList.at(i - 1));
                break;
            }
        }
    }
    
    _groupTextCtrl->GetValue().ToLong(&value);
    settings.setGroupNumber((unsigned int)value);
    
    if(_problem == physicProblems::PROB_ELECTROSTATIC)
    {
        if(_conductorsComboBox->GetSelection() != 0)
        {
           for(int i = 1; i < _conductorsComboBox->GetCount(); i++)
            {
                if(_conductorList.at(i - 1).getName() == _conductorsComboBox->GetString(_conductorsComboBox->GetSelection()))
                {
                    settings.setConductorProperty(_conductorList.at(i - 1));
                    break;
                }
            } 
        }
    }
}



setNodalPropertyDialog::~setNodalPropertyDialog()
{
    
}