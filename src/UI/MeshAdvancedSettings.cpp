#include "UI/MeshAdvancedSettings.h"


meshAdvanced::meshAdvanced(wxWindow *par, meshSettings &settings) : wxDialog(par, wxID_ANY, "Mesh Settings Advanced")
{
	p_meshSettings = &settings;
	
	wxFont font = wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	
	wxBoxSizer *multiplePassesSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *smoothingSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *meshFactorSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticBoxSizer *meshFormatsSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, "Mesh File Save Formats");
	wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
	
	// THis section is for the save formats section
	wxBoxSizer *columnOneSize = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *columnTwoSize = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *columnThreeSize = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *columnFourSize = new wxBoxSizer(wxVERTICAL);
	
	meshFormatsSizer->GetStaticBox()->SetFont(font);
	
	wxIntegerValidator<unsigned int> greaterThenZeroVal;
	greaterThenZeroVal.SetMin(1);
	
	wxFloatingPointValidator<double> doubleGreaterThenZeroVal(NULL, wxNUM_VAL_NO_TRAILING_ZEROES);
	doubleGreaterThenZeroVal.SetMin(0);
	
	wxStaticText *passesText = new wxStaticText(this, wxID_ANY, "Number of Passes: ");
	passesText->SetFont(font);
	
	p_passesTextCtrl->Create(this, wxID_ANY, std::to_string(p_meshSettings->getMultiplePasses()), wxDefaultPosition, wxDefaultSize, 0, greaterThenZeroVal);
	p_passesTextCtrl->SetFont(font);
	
	multiplePassesSizer->Add(passesText, 0, wxCENTER | wxALL, 6);
	multiplePassesSizer->Add(p_passesTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT , 6);
	
	wxStaticText *llyodSmoothingStepsText = new wxStaticText(this, wxID_ANY, "Llyod Smoothing Steps: ");
	llyodSmoothingStepsText->SetFont(font);
	
	p_llyodTextCtrl->Create(this, wxID_ANY, std::to_string(p_meshSettings->getLlyodSmoothingSteps()), wxDefaultPosition, wxDefaultSize, 0, greaterThenZeroVal);
	p_llyodTextCtrl->SetFont(font);
	
	smoothingSizer->Add(llyodSmoothingStepsText, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
	smoothingSizer->Add(p_llyodTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
	
	wxStaticText *factorText = new wxStaticText(this, wxID_ANY, "Mesh Size Factor: ");
	factorText->SetFont(font);
	
	p_factorTextCtrl->Create(this, wxID_EDIT, std::to_string(p_meshSettings->getElementSizeFactor()), wxDefaultPosition, wxDefaultSize, 0, doubleGreaterThenZeroVal);
	p_factorTextCtrl->SetValue(std::to_string(p_meshSettings->getElementSizeFactor()));
	p_factorTextCtrl->SetFont(font);
	
	meshFactorSizer->Add(factorText, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
	meshFactorSizer->Add(p_factorTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
	
	// For colunn 1
	
	p_saveAsVTK->Create(meshFormatsSizer->GetStaticBox(), wxID_ANY, "VTK");
	p_saveAsVTK->SetFont(font);
	p_saveAsVTK->SetValue(p_meshSettings->getSaveVTKState());
	
	p_saveAsBDF->Create(meshFormatsSizer->GetStaticBox(), wxID_ANY, "BDF");
	p_saveAsBDF->SetFont(font);
	p_saveAsBDF->SetValue(p_meshSettings->getSaveBDFState());
	
	p_saveAsCELUM->Create(meshFormatsSizer->GetStaticBox(), wxID_ANY, "CELUM");
	p_saveAsCELUM->SetFont(font);
	p_saveAsCELUM->SetValue(p_meshSettings->getSaveCELUMState());
	
	p_saveAsCGNS->Create(meshFormatsSizer->GetStaticBox(), wxID_ANY, "CGNS");
	p_saveAsCGNS->SetFont(font);
	p_saveAsCGNS->SetValue(p_meshSettings->getSaveCGNSState());
	
	p_saveAsDIFFPACK->Create(meshFormatsSizer->GetStaticBox(), wxID_ANY, "DIFFPACK");
	p_saveAsDIFFPACK->SetFont(font);
	p_saveAsDIFFPACK->SetValue(p_meshSettings->getSaveDIFFPACKSate());
	
	columnOneSize->Add(p_saveAsVTK, 0, wxALL, 6);
	columnOneSize->Add(p_saveAsBDF, 0, wxLEFT | wxRIGHT | wxBOTTOM, 6);
	columnOneSize->Add(p_saveAsCELUM, 0, wxLEFT | wxRIGHT | wxBOTTOM, 6);
	columnOneSize->Add(p_saveAsCGNS, 0, wxLEFT | wxRIGHT | wxBOTTOM, 6);
	columnOneSize->Add(p_saveAsDIFFPACK, 0, wxLEFT | wxRIGHT | wxBOTTOM, 6);

	// ---- For column 2
	
	p_saveAsFourier->Create(meshFormatsSizer->GetStaticBox(), wxID_ANY, "Fourier");
	p_saveAsFourier->SetFont(font);
	p_saveAsFourier->SetValue(p_meshSettings->getSaveFourierState());
	
	p_saveAsGEO->Create(meshFormatsSizer->GetStaticBox(), wxID_ANY, "GEO");
	p_saveAsGEO->SetFont(font);
	p_saveAsGEO->SetValue(p_meshSettings->getSaveGEOState());
	
	p_SaveAsINP->Create(meshFormatsSizer->GetStaticBox(), wxID_ANY, "INP");
	p_SaveAsINP->SetFont(font);
	p_SaveAsINP->SetValue(p_meshSettings->getSaveINPState());
	
	p_saveAsIR3->Create(meshFormatsSizer->GetStaticBox(), wxID_ANY, "IR3");
	p_saveAsIR3->SetFont(font);
	p_saveAsIR3->SetValue(p_meshSettings->getSaveIR3State());
	
	p_saveAsMAIL->Create(meshFormatsSizer->GetStaticBox(), wxID_ANY, "MAIL");
	p_saveAsMAIL->SetFont(font);
	p_saveAsMAIL->SetValue(p_meshSettings->getSaveMAILState());
	
	columnTwoSize->Add(p_saveAsFourier, 0, wxTOP | wxBOTTOM | wxLEFT, 6);
	columnTwoSize->Add(p_saveAsGEO, 0, wxBOTTOM | wxLEFT, 6);
	columnTwoSize->Add(p_SaveAsINP, 0, wxBOTTOM | wxLEFT, 6);
	columnTwoSize->Add(p_saveAsIR3, 0, wxBOTTOM | wxLEFT, 6);
	columnTwoSize->Add(p_saveAsMAIL, 0, wxBOTTOM | wxLEFT, 6);
	
	// Column 3
	p_saveAsMESH->Create(meshFormatsSizer->GetStaticBox(), wxID_ANY, "MESH");
	p_saveAsMESH->SetFont(font);
	p_saveAsMESH->SetValue(p_meshSettings->getSaveMESHState());
	
	p_saveAsP3D->Create(meshFormatsSizer->GetStaticBox(), wxID_ANY, "P3D");
	p_saveAsP3D->SetFont(font);
	p_saveAsP3D->SetValue(p_meshSettings->getSaveP3DState());
	
	p_saveAsPatitionedMesh->Create(meshFormatsSizer->GetStaticBox(), wxID_ANY, "ParitionedMesh");
	p_saveAsPatitionedMesh->SetFont(font);
	p_saveAsPatitionedMesh->SetValue(p_meshSettings->getSavePartitionedMeshState());
	
	p_saveAsPLY2->Create(meshFormatsSizer->GetStaticBox(), wxID_ANY, "PLY2");
	p_saveAsPLY2->SetFont(font);
	p_saveAsPLY2->SetValue(p_meshSettings->getSavePLY2State());
	
	p_saveAsSTL->Create(meshFormatsSizer->GetStaticBox(), wxID_ANY, "STL");
	p_saveAsSTL->SetFont(font);
	p_saveAsSTL->SetValue(p_meshSettings->getSaveSTLState());
	
	columnThreeSize->Add(p_saveAsMESH, 0, wxTOP | wxBOTTOM | wxLEFT, 6);
	columnThreeSize->Add(p_saveAsP3D, 0, wxBOTTOM | wxLEFT, 6);
	columnThreeSize->Add(p_saveAsPatitionedMesh, 0, wxBOTTOM | wxLEFT, 6);
	columnThreeSize->Add(p_saveAsPLY2, 0, wxBOTTOM | wxLEFT, 6);
	columnThreeSize->Add(p_saveAsSTL, 0, wxBOTTOM | wxLEFT, 6);
	
	// column 4
	
	p_saveAsSU2->Create(meshFormatsSizer->GetStaticBox(), wxID_ANY, "SU2");
	p_saveAsSU2->SetFont(font);
	p_saveAsSU2->SetValue(p_meshSettings->getSaveSU2State());
	
	p_saveAsTochnog->Create(meshFormatsSizer->GetStaticBox(), wxID_ANY, "Tochnog");
	p_saveAsTochnog->SetFont(font);
	p_saveAsTochnog->SetValue(p_meshSettings->getSaveTochnogState());
	
	p_saveAsUNV->Create(meshFormatsSizer->GetStaticBox(), wxID_ANY, "UNV");
	p_saveAsUNV->SetFont(font);
	p_saveAsUNV->SetValue(p_meshSettings->getSaveUNVState());
	
	p_saveAsVRML->Create(meshFormatsSizer->GetStaticBox(), wxID_ANY, "VRML");
	p_saveAsVRML->SetFont(font);
	p_saveAsVRML->SetValue(p_meshSettings->getSaveVRMLState());
	
	columnFourSize->Add(p_saveAsSU2, 0, wxTOP | wxBOTTOM | wxLEFT, 6);
	columnFourSize->Add(p_saveAsTochnog, 0, wxBOTTOM | wxLEFT, 6);
	columnFourSize->Add(p_saveAsUNV, 0, wxBOTTOM | wxLEFT, 6);
	columnFourSize->Add(p_saveAsVRML, 0, wxBOTTOM | wxLEFT, 6);
	
	meshFormatsSizer->Add(columnOneSize);
	meshFormatsSizer->Add(columnTwoSize);
	meshFormatsSizer->Add(columnThreeSize);
	meshFormatsSizer->Add(columnFourSize);
	
	wxButton *okButton  = new wxButton(this, wxID_OK, "Ok", wxDefaultPosition, wxSize(75, 23));
    okButton->SetFont(font);
    
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(75, 23));
    cancelButton->SetFont(font);
    
    footerSizer->Add(okButton, 0, wxLEFT | wxRIGHT | wxBOTTOM, 6);
    footerSizer->Add(cancelButton, 0, wxBOTTOM | wxRIGHT, 6);
	
	topSizer->Add(multiplePassesSizer);
	topSizer->Add(smoothingSizer);
	topSizer->Add(meshFactorSizer);
	topSizer->Add(meshFormatsSizer, 0, wxLEFT | wxRIGHT | wxBOTTOM, 6);
	topSizer->Add(footerSizer, 0, wxALIGN_RIGHT);
	
	SetSizerAndFit(topSizer);
}



void meshAdvanced::setSettings()
{
	long longValue = 0;
	double doubleValue = 0;
	
	p_passesTextCtrl->GetValue().ToLong(&longValue);
	p_meshSettings->setMultiplePasses((unsigned int)longValue);

	p_llyodTextCtrl->GetValue().ToLong(&longValue);
	p_meshSettings->setLlyodSmoothingSteps((unsigned int)longValue);
	
	p_factorTextCtrl->GetValue().ToDouble(&doubleValue);
	p_meshSettings->setElementSizeFactor(doubleValue);
	
	p_meshSettings->setSaveVTKState(p_saveAsVTK->GetValue());
	p_meshSettings->setSaveBDFState(p_saveAsBDF->GetValue());
	p_meshSettings->setSaveCELUMState(p_saveAsCELUM->GetValue());
	p_meshSettings->setSaveCGNSState(p_saveAsCGNS->GetValue());
	p_meshSettings->setSaveDIFFPACKSate(p_saveAsDIFFPACK->GetValue());
	p_meshSettings->setSaveFourierState(p_saveAsFourier->GetValue());
	p_meshSettings->setSaveGEOState(p_saveAsGEO->GetValue());
	p_meshSettings->setSaveINPState(p_SaveAsINP->GetValue());
	p_meshSettings->setSaveIR3State(p_saveAsIR3->GetValue());
	p_meshSettings->setSaveMAILState(p_saveAsMAIL->GetValue());
	p_meshSettings->setSaveMESHState(p_saveAsMESH->GetValue());
	p_meshSettings->setSaveP3DState(p_saveAsP3D->GetValue());
	p_meshSettings->setSavePartitionedMeshState(p_saveAsPatitionedMesh->GetValue());
	p_meshSettings->setSavePLY2State(p_saveAsPLY2->GetValue());
	p_meshSettings->setSaveSTLState(p_saveAsSTL->GetValue());
	p_meshSettings->setSaveSU2State(p_saveAsSU2->GetValue());
	p_meshSettings->setSaveTochnogState(p_saveAsTochnog->GetValue());
	p_meshSettings->setSaveUNVState(p_saveAsUNV->GetValue());
	p_meshSettings->setSaveVRMLState(p_saveAsVRML->GetValue());
}