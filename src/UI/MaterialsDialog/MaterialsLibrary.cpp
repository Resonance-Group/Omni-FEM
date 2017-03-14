#include <UI/MaterialsDialog/MaterialsLibrary.h>

materialLibraryDialog::materialLibraryDialog(wxWindow *par, std::vector<electrostaticMaterial> &material) : wxDialog(par, wxID_ANY, "Material Library")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *line1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *column1Sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *column2Sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *column3Sizer = new wxBoxSizer(wxVERTICAL);
    
    _masterLibraryTreeCtrl->Create(this, generalFrameButton::ID_TREECTRL1, wxDefaultPosition, wxSize(237, 196), wxTR_MULTIPLE);
    _masterLibraryTreeCtrl->SetFont(*font);
    
    column1Sizer->Add(_masterLibraryTreeCtrl, 0, wxCENTER | wxALL, 6);
    
    wxButton *addToLocalButton = new wxButton(this, generalFrameButton::ID_BUTTON1, "->", wxDefaultPosition, wxSize(30, 23));
    addToLocalButton->SetFont(*font);
    wxButton *addToMasterButton = new wxButton(this, generalFrameButton::ID_BUTTON2, "<-", wxDefaultPosition, wxSize(30, 23));
    
    column2Sizer->Add(addToLocalButton, 0, wxTOP | wxBOTTOM | wxCENTER | wxALIGN_CENTER, 6);
    column2Sizer->Add(addToMasterButton, 0, wxBOTTOM | wxCENTER | wxALIGN_CENTER, 6);
    
    _localLibraryTreeCtrl->Create(this, generalFrameButton::ID_TREECTRL2, wxDefaultPosition, wxSize(237, 196), wxTR_MULTIPLE);
    
    column3Sizer->Add(_localLibraryTreeCtrl, 0, wxCENTER | wxALL, 6);
    
    line1Sizer->Add(column1Sizer);
    line1Sizer->Add(column2Sizer, 0, wxCENTER);
    line1Sizer->Add(column3Sizer);
    
    wxButton *editButton = new wxButton(this, wxID_EDIT, "Edit", wxDefaultPosition, wxSize(75, 23));
    editButton->SetFont(*font);
    wxButton *newFolderButton = new wxButton(this, wxID_NEW, "Add Folder", wxDefaultPosition, wxSize(75, 23));
    newFolderButton->SetFont(*font);
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxDefaultPosition, wxSize(75, 23));
    okButton->SetFont(*font);
    wxButton *deleteButton = new wxButton(this, wxID_DELETE, "Delete", wxDefaultPosition, wxSize(75, 23));
    deleteButton->SetFont(*font);
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(editButton, 0, wxCENTER | wxRIGHT | wxBOTTOM, 6);
    footerSizer->Add(newFolderButton, 0, wxCENTER | wxRIGHT | wxBOTTOM, 6);
    footerSizer->Add(112, 0, 0);
    footerSizer->Add(okButton, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    footerSizer->Add(deleteButton, 0, wxCENTER | wxRIGHT | wxBOTTOM, 6);
    footerSizer->Add(cancelButton, 0, wxCENTER | wxRIGHT | wxBOTTOM, 6);
    
    topSizer->Add(line1Sizer);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
}



materialLibraryDialog::materialLibraryDialog(wxWindow *par, std::vector<magneticMaterial> &material) : wxDialog(par, wxID_ANY, "Material Library")
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxBoxSizer *line1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *column1Sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *column2Sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *column3Sizer = new wxBoxSizer(wxVERTICAL);
    
    _masterLibraryTreeCtrl->Create(this, generalFrameButton::ID_TREECTRL1, wxDefaultPosition, wxSize(237, 196), wxTR_MULTIPLE);
    _masterLibraryTreeCtrl->SetFont(*font);
    
    column1Sizer->Add(_masterLibraryTreeCtrl, 0, wxCENTER | wxALL, 6);
    
    wxButton *addToLocalButton = new wxButton(this, generalFrameButton::ID_BUTTON1, "->", wxDefaultPosition, wxSize(30, 23));
    addToLocalButton->SetFont(*font);
    wxButton *addToMasterButton = new wxButton(this, generalFrameButton::ID_BUTTON2, "<-", wxDefaultPosition, wxSize(30, 23));
    
    column2Sizer->Add(addToLocalButton, 0, wxTOP | wxBOTTOM | wxCENTER | wxALIGN_CENTER, 6);
    column2Sizer->Add(addToMasterButton, 0, wxBOTTOM | wxCENTER | wxALIGN_CENTER, 6);
    
    _localLibraryTreeCtrl->Create(this, generalFrameButton::ID_TREECTRL2, wxDefaultPosition, wxSize(237, 196), wxTR_MULTIPLE);
    
    column3Sizer->Add(_localLibraryTreeCtrl, 0, wxCENTER | wxALL, 6);
    
    line1Sizer->Add(column1Sizer);
    line1Sizer->Add(column2Sizer, 0, wxCENTER);
    line1Sizer->Add(column3Sizer);
    
    wxButton *editButton = new wxButton(this, wxID_EDIT, "Edit", wxDefaultPosition, wxSize(75, 23));
    editButton->SetFont(*font);
    wxButton *newFolderButton = new wxButton(this, wxID_NEW, "Add Folder", wxDefaultPosition, wxSize(75, 23));
    newFolderButton->SetFont(*font);
    wxButton *okButton = new wxButton(this, wxID_OK, "Ok", wxDefaultPosition, wxSize(75, 23));
    okButton->SetFont(*font);
    wxButton *deleteButton = new wxButton(this, wxID_DELETE, "Delete", wxDefaultPosition, wxSize(75, 23));
    deleteButton->SetFont(*font);
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(75, 23));
    cancelButton->SetFont(*font);
    
    footerSizer->Add(editButton, 0, wxCENTER | wxRIGHT | wxBOTTOM, 6);
    footerSizer->Add(newFolderButton, 0, wxCENTER | wxRIGHT | wxBOTTOM, 6);
    footerSizer->Add(112, 0, 0);
    footerSizer->Add(okButton, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    footerSizer->Add(deleteButton, 0, wxCENTER | wxRIGHT | wxBOTTOM, 6);
    footerSizer->Add(cancelButton, 0, wxCENTER | wxRIGHT | wxBOTTOM, 6);
    
    topSizer->Add(line1Sizer);
    topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
    
    SetSizerAndFit(topSizer);
}



void materialLibraryDialog::getMagneticLocalMaterialList(std::vector<magneticMaterial> &magneticMaterialList)
{
    
}



void materialLibraryDialog::getElectricalLocalMaterialList(std::vector<electrostaticMaterial> &electricalMaterialList)
{
    
}



void materialLibraryDialog::onEditMaterial(wxCommandEvent &event)
{
    
}



void materialLibraryDialog::onAddMaterialToLocal(wxCommandEvent &event)
{
    
}



void materialLibraryDialog::onAddMaterialToMaster(wxCommandEvent &event)
{
    
}



void materialLibraryDialog::onRemoveMaterial(wxCommandEvent &event)
{
    
}



void materialLibraryDialog::onAddFolder(wxCommandEvent &event)
{
    
}



void materialLibraryDialog::onClickEditMaterial(wxTreeEvent &event)
{
    
}



void materialLibraryDialog::onLocalDrag(wxTreeEvent &event)
{
    
}


wxBEGIN_EVENT_TABLE(materialLibraryDialog, wxDialog)
    EVT_BUTTON(generalFrameButton::ID_BUTTON1, materialLibraryDialog::onAddMaterialToLocal)
    EVT_BUTTON(generalFrameButton::ID_BUTTON2, materialLibraryDialog::onAddMaterialToMaster)
    EVT_BUTTON(wxID_EDIT, materialLibraryDialog::onEditMaterial)
    EVT_BUTTON(wxID_NEW, materialLibraryDialog::onAddFolder)
    EVT_BUTTON(wxID_DELETE, materialLibraryDialog::onRemoveMaterial)
    EVT_TREE_ITEM_RIGHT_CLICK(generalFrameButton::ID_TREECTRL1, materialLibraryDialog::onClickEditMaterial)
    EVT_TREE_ITEM_RIGHT_CLICK(generalFrameButton::ID_TREECTRL2, materialLibraryDialog::onClickEditMaterial)
    EVT_TREE_END_DRAG(generalFrameButton::ID_TREECTRL2, materialLibraryDialog::onLocalDrag)
wxEND_EVENT_TABLE()