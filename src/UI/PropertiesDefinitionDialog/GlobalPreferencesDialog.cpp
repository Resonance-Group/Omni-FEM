#include <UI/EditMenu/GlobalPreferencesDialog.h>



globalPreferencesDialog::globalPreferencesDialog(wxWindow *par, gridPreferences *gridPref, magneticPreference pref, meshSettings settings)
{
    _problem = physicProblems::PROB_MAGNETICS;
    _magneticPreference = pref;
    _preferences = gridPref;
	p_meshSetting = settings;
    createDialog(par);
}



globalPreferencesDialog::globalPreferencesDialog(wxWindow *par, gridPreferences *gridPref, electroStaticPreference pref, meshSettings settings)
{
    _problem = physicProblems::PROB_ELECTROSTATIC;
    _electricalPreference = pref;
    _preferences = gridPref;
	p_meshSetting = settings;
    createDialog(par);
}
 


void globalPreferencesDialog::createDialog(wxWindow *par)
{
    this->Create(par, wxID_ANY, "Preferences");
    this->CreateButtons();
    
    wxBookCtrlBase *base = GetBookCtrl();
    
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    this->SetFont(*font);
    base->SetFont(*font);
    
    wxPanel *gridSettingPanel = new wxPanel(base);
    wxPanel *physicsProblemPreferencesPanel = new wxPanel(base);
	wxPanel *meshSettingsPanel = new wxPanel(base);
  //  GetBookCtrl()->AddPage(panel, "Input Settings");
    
    wxArrayString lengthName;
    wxArrayString problemTypeNameArray;
    wxArrayString coordianteNameArray;
    wxArrayString acSovlerNameArray;
	
    
    lengthName.Add("Inches");
    lengthName.Add("Millimeters");
    lengthName.Add("Centimeters");
    lengthName.Add("Meters");
    lengthName.Add("Mils");
    lengthName.Add("Micrometers");
    
    problemTypeNameArray.Add("Planar");
    problemTypeNameArray.Add("Axisymmetric");
    
    coordianteNameArray.Add("Cartesian");
    coordianteNameArray.Add("Polar");
    
    acSovlerNameArray.Add("Succ. Approx");
    acSovlerNameArray.Add("Newton");
    
    wxBoxSizer *documentSettingsSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *gridSettingsSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *meshSettingsSizer = new wxBoxSizer(wxVERTICAL);
    
    wxBoxSizer *documentSettingLine1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine6 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine7 = new wxBoxSizer(wxHORIZONTAL);
    
    wxBoxSizer *gridSettingLine1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine6 = new wxBoxSizer(wxHORIZONTAL);
    
    wxFloatingPointValidator<double> greaterThenZero(15, NULL, wxNUM_VAL_NO_TRAILING_ZEROES);
    greaterThenZero.SetMin(0);
    
    wxFloatingPointValidator<double> angleValidator(15);
    angleValidator.SetRange(0, 360);

    /* The frist section will be creating everything for the grid preferences */
    wxStaticText *gridText = new wxStaticText(gridSettingPanel, wxID_ANY, "Grid Step:");
    gridText->SetFont(*font);
    _gridStepTextCtrl->Create(gridSettingPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20), 0, greaterThenZero);
    _gridStepTextCtrl->SetFont(*font);
    std::ostream gridSizeStream(_gridStepTextCtrl);
    gridSizeStream << std::setprecision(15);
    gridSizeStream << _preferences->getGridStep();
    
    gridSettingLine1->Add(gridText, 0, wxCENTER | wxALL, 6);
    gridSettingLine1->Add(12, 0, 0);
    gridSettingLine1->Add(_gridStepTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxTOP, 6);
    
    wxStaticText *coordianteText = new wxStaticText(gridSettingPanel, wxID_ANY, "Coordinate:");
    coordianteText->SetFont(*font);
    _coordinateComboBox->Create(gridSettingPanel, wxID_ANY, wxEmptyString, wxPoint(79, 64), wxSize(121, 21), coordianteNameArray);
    _coordinateComboBox->SetFont(*font);
    _coordinateComboBox->SetSelection((int)_preferences->getCoordinateSystem());
    
    gridSettingLine2->Add(coordianteText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
    gridSettingLine2->Add(_coordinateComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _showGridCheckBox->Create(gridSettingPanel, wxID_ANY, "Show Grid");
    _showGridCheckBox->SetValue(_preferences->getShowGridState());
    _showGridCheckBox->SetFont(*font);
    _showOriginCheckBox->Create(gridSettingPanel, wxID_ANY, "Show Origin");
    _showOriginCheckBox->SetFont(*font);
    _showOriginCheckBox->SetValue(_preferences->getShowOriginState());
    
    gridSettingLine3->Add(_showGridCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    gridSettingLine3->Add(_showOriginCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _snapGridCheckBox->Create(gridSettingPanel, wxID_ANY, "Snap Grid");
    _snapGridCheckBox->SetFont(*font);
    _snapGridCheckBox->SetValue(_preferences->getSnapGridState());
    _showGridAxisCheckBox->Create(gridSettingPanel, wxID_ANY, "Show Grid Axis");
    _showGridAxisCheckBox->SetFont(*font);
    _showGridAxisCheckBox->SetValue(_preferences->getShowAxisState());
    
    gridSettingLine4->Add(_snapGridCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    gridSettingLine4->Add(_showGridAxisCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    _showBlockNameCheckBox->Create(gridSettingPanel, wxID_ANY, "Show Block Names");
    _showBlockNameCheckBox->SetValue(_preferences->getShowBlockNameState());
    _showBlockNameCheckBox->SetFont(*font);
    
    gridSettingLine5->Add(_showBlockNameCheckBox, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
    
    _reverseMouseZoomCheckBox->Create(gridSettingPanel, wxID_ANY, "Reverse Mouse Zoom Direction");
    _reverseMouseZoomCheckBox->SetValue(_preferences->getMouseZoomReverseState());
    _reverseMouseZoomCheckBox->SetFont(*font);
    
    gridSettingLine6->Add(_reverseMouseZoomCheckBox, 0, wxCENTER | wxRIGHT | wxLEFT | wxBOTTOM, 6);
    
    gridSettingsSizer->Add(gridSettingLine1);
    gridSettingsSizer->Add(gridSettingLine2);
    gridSettingsSizer->Add(0, 10, 0);
    gridSettingsSizer->Add(gridSettingLine3);
    gridSettingsSizer->Add(gridSettingLine4);
    gridSettingsSizer->Add(gridSettingLine5);
    gridSettingsSizer->Add(gridSettingLine6);
    
    /* This next section is for the preferences related to the settings */
    wxStaticText *probTypeText = new wxStaticText(physicsProblemPreferencesPanel, wxID_ANY, "Problem Type:");
    probTypeText->SetFont(*font);
    _problemTypeComboBox->Create(physicsProblemPreferencesPanel, generalFrameButton::ID_ComboBox1, wxEmptyString, wxPoint(98, 12), wxSize(121, 21), problemTypeNameArray);
    _problemTypeComboBox->SetFont(*font);
    documentSettingLine1->Add(probTypeText, 0, wxCENTER | wxTOP | wxBOTTOM | wxLEFT, 6);
    documentSettingLine1->Add(20, 0, 0);
    documentSettingLine1->Add(_problemTypeComboBox, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
   
    wxStaticText *lengthUnitsText = new wxStaticText(physicsProblemPreferencesPanel, wxID_ANY, "Length Units:");
    lengthUnitsText->SetFont(*font);
    _lengthComboBox->Create(physicsProblemPreferencesPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 21), lengthName);
    _lengthComboBox->SetFont(*font);
    documentSettingLine2->Add(lengthUnitsText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
    documentSettingLine2->Add(23, 0, 0);
    documentSettingLine2->Add(_lengthComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    if(_problem == physicProblems::PROB_MAGNETICS)
    {
        wxStaticText *acSolverText = new wxStaticText(physicsProblemPreferencesPanel, wxID_ANY, "AC Solver:");
        acSolverText->SetFont(*font);
        _acSolverComboBox->Create(physicsProblemPreferencesPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 21), acSovlerNameArray);
        _acSolverComboBox->SetFont(*font);
        _acSolverComboBox->SetSelection((int)_magneticPreference.getACSolver());
        documentSettingLine3->Add(acSolverText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
        documentSettingLine3->Add(41, 0, 0);
        documentSettingLine3->Add(_acSolverComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);

        wxStaticText *freqText = new wxStaticText(physicsProblemPreferencesPanel, wxID_ANY, "Frequency (Hz):");
        freqText->SetFont(*font);
        _frequencyTextCtrl->Create(physicsProblemPreferencesPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20), 0, greaterThenZero);
        std::ostream freqStream(_frequencyTextCtrl);
        freqStream << std::setprecision(3);
        freqStream << _magneticPreference.getFrequency();
        _frequencyTextCtrl->SetFont(*font);
        documentSettingLine4->Add(freqText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
        documentSettingLine4->Add(11, 0, 0);
        documentSettingLine4->Add(_frequencyTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    }
   
    wxStaticText *depthText = new wxStaticText(physicsProblemPreferencesPanel, wxID_ANY, "Depth:");
    depthText->SetFont(*font);
    _depthTextCtrl->Create(physicsProblemPreferencesPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20), 0, greaterThenZero);
    std::ostream dStream(_depthTextCtrl);
    dStream << std::setprecision(4);
    _depthTextCtrl->SetFont(*font);
    documentSettingLine5->Add(depthText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
    documentSettingLine5->Add(59, 0, 0);
    documentSettingLine5->Add(_depthTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
   
    wxStaticText *solverPrecisionText = new wxStaticText(physicsProblemPreferencesPanel, wxID_ANY, "Solver Precision:");
    solverPrecisionText->SetFont(*font);
    _precisionTextCtrl->Create(physicsProblemPreferencesPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20), 0, greaterThenZero);
    std::ostream spStream(_precisionTextCtrl);
    spStream << std::setprecision(4);
    _precisionTextCtrl->SetFont(*font);
    documentSettingLine6->Add(solverPrecisionText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
    documentSettingLine6->Add(6, 0, 0);
    documentSettingLine6->Add(_precisionTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
   
    wxStaticText *minAngleText = new wxStaticText(physicsProblemPreferencesPanel, wxID_ANY, "Min Angle (deg):");
    minAngleText->SetFont(*font);
    _minAngleTextCtrl->Create(physicsProblemPreferencesPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(121, 20), 0, angleValidator);
    std::ostream minAngleStream(_minAngleTextCtrl);
    minAngleStream << std::setprecision(4);
    _minAngleTextCtrl->SetFont(*font);
    documentSettingLine7->Add(minAngleText, 0, wxCENTER | wxBOTTOM | wxLEFT, 6);
    documentSettingLine7->Add(7, 0, 0);
    documentSettingLine7->Add(_minAngleTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
    
    wxStaticBoxSizer *commentSizer = new wxStaticBoxSizer(wxVERTICAL, physicsProblemPreferencesPanel, "Comments");
    commentSizer->GetStaticBox()->SetFont(*font);
    _commentsTextCtrl->Create(commentSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(192, 87), wxTE_MULTILINE);
    _commentsTextCtrl->SetFont(*font);
    commentSizer->Add(_commentsTextCtrl, 0, wxALL, 6);

    documentSettingsSizer->Add(documentSettingLine1);
    documentSettingsSizer->Add(documentSettingLine2);
    
    if(_problem == physicProblems::PROB_MAGNETICS)
    {
        documentSettingsSizer->Add(documentSettingLine3);
        documentSettingsSizer->Add(documentSettingLine4);
    }
    
    documentSettingsSizer->Add(documentSettingLine5);
    documentSettingsSizer->Add(documentSettingLine6);
    documentSettingsSizer->Add(documentSettingLine7);
    documentSettingsSizer->Add(commentSizer, 0, wxLEFT | wxRIGHT | wxCENTER, 6);
  //  topSizer->Add(commentSizer, 0, wxLEFT | wxRIGHT | wxCENTER, 6);
    
    if(_problem == physicProblems::PROB_ELECTROSTATIC)
    {
        _problemTypeComboBox->SetSelection((int)_electricalPreference.getProblemType());
        _lengthComboBox->SetSelection((int)_electricalPreference.getUnitLength());
        dStream << _electricalPreference.getDepth();
        spStream << _electricalPreference.getPrecision();
        minAngleStream << _electricalPreference.getMinAngle();
        _commentsTextCtrl->SetValue(_electricalPreference.getComments());
    }
    else if(_problem == physicProblems::PROB_MAGNETICS)
    {
        _problemTypeComboBox->SetSelection((int)_magneticPreference.getProblemType());
        _lengthComboBox->SetSelection((int)_magneticPreference.getUnitLength());
        dStream << _magneticPreference.getDepth();
        spStream << _magneticPreference.getPrecision();
        minAngleStream << _magneticPreference.getMinAngle();
        _commentsTextCtrl->SetValue(_magneticPreference.getComments());
    }
    
    if(_problemTypeComboBox->GetSelection() == 1)
    {
        _depthTextCtrl->Enable(false);
    }
// -------------- This section is for the creation of the mesh options ---------------

	wxArrayString structuredMeshArray;
	wxArrayString meshArrangmentArray;
	wxArrayString meshAlgorthimArray;
	wxArrayString meshRecombinationArray;
	wxArrayString remeshingAlgorithmArray;
	wxArrayString remeshParameterizationArray;
	
	structuredMeshArray.Add("Unstructured");
	structuredMeshArray.Add("Structured");
	
	meshArrangmentArray.Add("Left");
	meshArrangmentArray.Add("Right");
	meshArrangmentArray.Add("Alternating");
	
	meshAlgorthimArray.Add("Automatic");
	meshAlgorthimArray.Add("MeshAdapt");
	meshAlgorthimArray.Add("Delaunay");
	meshAlgorthimArray.Add("Frontal");
	
	meshRecombinationArray.Add("Standard");
	meshRecombinationArray.Add("Blossom");
	
	remeshingAlgorithmArray.Add("No Split");
	remeshingAlgorithmArray.Add("Automatic");
	
	remeshParameterizationArray.Add("Harmonic");
	remeshParameterizationArray.Add("Conformal");
	remeshParameterizationArray.Add("Rbf Harmonic");
	
	wxBoxSizer *stucturedMeshSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *meshArrangmentSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *meshAlgoSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *meshRecombinationSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *reMeshAlgoSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *reMeshParamSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *smootherSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *elementOrderSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *buttonResetSizer = new wxBoxSizer(wxHORIZONTAL);
	
	wxStaticText *text1 = new wxStaticText(meshSettingsPanel, wxID_ANY, "Mesh Structure:");
	text1->SetFont(*font);
	
	p_structuredComboBox->Create(meshSettingsPanel, generalFrameButton::ID_ComboBox2, wxEmptyString, wxDefaultPosition, wxDefaultSize, structuredMeshArray);
	p_structuredComboBox->SetFont(*font);
	
	if(!p_meshSetting.getStructuredState())
	{
		p_structuredComboBox->SetSelection(0);
		OmniFEMMsg::instance()->MsgInfo("Mesh structure loaded as unstructured");
	}
	else
	{
		p_structuredComboBox->SetSelection(1);
		OmniFEMMsg::instance()->MsgInfo("Mesh structure loaded as structured");
	}
	
	stucturedMeshSizer->Add(text1, 0, wxCENTER | wxALL, 6);
	stucturedMeshSizer->Add(p_structuredComboBox, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
	
	wxStaticText *meshArrangmentText = new wxStaticText(meshSettingsPanel, wxID_ANY, "Face Mesh Arrangement: ");
	meshArrangmentText->SetFont(*font);
	
	p_meshArrangementComboBox->Create(meshSettingsPanel, generalFrameButton::ID_ComboBox3, wxEmptyString, wxDefaultPosition, wxDefaultSize, meshArrangmentArray);
	p_meshArrangementComboBox->SetFont(*font);
	
	switch(p_meshSetting.getMeshArrangment())
	{
		case StructuredArrangement::ARRANGMENT_LEFT:
			p_meshArrangementComboBox->SetSelection(0);
			OmniFEMMsg::instance()->MsgInfo("Face Mesh Arrangment loaded as Left");
			break;
		case StructuredArrangement::ARRANGMENT_RIGHT:
			p_meshArrangementComboBox->SetSelection(1);
			OmniFEMMsg::instance()->MsgInfo("Face Mesh Arrangment loaded as Right");
			break;
		case StructuredArrangement::ARRANGMENT_ALTERNATED:
			p_meshArrangementComboBox->SetSelection(2);
			OmniFEMMsg::instance()->MsgInfo("Face Mesh Arrangment loaded as Alternated");
			break;
	}
	
	if(!p_meshSetting.getStructuredState())
		p_meshArrangementComboBox->Enable(false);
	else
		p_meshArrangementComboBox->Enable(true);
		
	meshArrangmentSizer->Add(meshArrangmentText, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
	meshArrangmentSizer->Add(p_meshArrangementComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
	
	wxStaticText *meshAlgoText = new wxStaticText(meshSettingsPanel, wxID_ANY, "Mesh Algorithm:");
	meshAlgoText->SetFont(*font);
	
	p_meshAlgothimComboBox->Create(meshSettingsPanel, generalFrameButton::ID_ComboBox4, wxEmptyString, wxDefaultPosition, wxDefaultSize, meshAlgorthimArray);
	p_meshAlgothimComboBox->SetFont(*font);
	
	switch(p_meshSetting.getMeshAlgorithm())
	{
		case MeshAlgorthim::MESH_ALGO_AUTOMATIC:
			p_meshAlgothimComboBox->SetSelection(0);
			OmniFEMMsg::instance()->MsgInfo("Mesh Algorithm loaded as Automatic");
			break;
		case MeshAlgorthim::MESH_ALGO_MESHADAPT:
			p_meshAlgothimComboBox->SetSelection(1);
			OmniFEMMsg::instance()->MsgInfo("Mesh Algorithm loaded as MeshAdapt");
			break;
		case MeshAlgorthim::MESH_ALGO_DELAUNAY:
			p_meshAlgothimComboBox->SetSelection(2);
			OmniFEMMsg::instance()->MsgInfo("Mesh Algorithm loaded as Delaunay");
			break;
		case MeshAlgorthim::MESH_ALGO_FRONTAL:
			p_meshAlgothimComboBox->SetSelection(3);
			OmniFEMMsg::instance()->MsgInfo("Mesh Algorithm loaded as Frontal");
			break;
	}
	
	meshAlgoSizer->Add(meshAlgoText, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
	meshAlgoSizer->Add(p_meshAlgothimComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
	
	wxStaticText *meshRecombinationText = new wxStaticText(meshSettingsPanel, wxID_ANY, "Mesh Recombination Algorithm:");
	meshRecombinationText->SetFont(*font);
	
	p_meshRecombinationComboBox->Create(meshSettingsPanel, generalFrameButton::ID_ComboBox5, wxEmptyString, wxDefaultPosition, wxDefaultSize, meshRecombinationArray);
	p_meshRecombinationComboBox->SetFont(*font);
	
	if(!p_meshSetting.getBlossomRecombinationState())
	{
		OmniFEMMsg::instance()->MsgInfo("Mesh Recombination Loaded as Standard");
		p_meshRecombinationComboBox->SetSelection(0);
	}
	else
	{
		OmniFEMMsg::instance()->MsgInfo("Mesh Recombination Loaded as Blossom");
		p_meshRecombinationComboBox->SetSelection(1);
	}
	
	meshRecombinationSizer->Add(meshRecombinationText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
	meshRecombinationSizer->Add(p_meshRecombinationComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
	
	wxStaticText *remeshAlgoText = new wxStaticText(meshSettingsPanel, wxID_ANY, "Remeshing Algorithm:");
	remeshAlgoText->SetFont(*font);
	
	p_remeshAlgorithmComboBox->Create(meshSettingsPanel, generalFrameButton::ID_ComboBox6, wxEmptyString, wxDefaultPosition, wxDefaultSize, remeshingAlgorithmArray);
	p_remeshAlgorithmComboBox->SetFont(*font);
	
	if(!p_meshSetting.getAutoRemeshingState())
	{
		OmniFEMMsg::instance()->MsgInfo("Remesh Algorithm loaded as No Split");
		p_remeshAlgorithmComboBox->SetSelection(0);
	}
	else
	{
		OmniFEMMsg::instance()->MsgInfo("Remesh Algorithm loaded as Automatic");
		p_remeshAlgorithmComboBox->SetSelection(1);
	}
	
	reMeshAlgoSizer->Add(remeshAlgoText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
	reMeshAlgoSizer->Add(p_remeshAlgorithmComboBox, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
	
	wxStaticText *remeshParamText = new wxStaticText(meshSettingsPanel, wxID_ANY, "Remeshing Parameterization:");
	remeshParamText->SetFont(*font);
	
	p_remeshParamterizationComboBox->Create(meshSettingsPanel, generalFrameButton::ID_ComboBox7, wxEmptyString, wxDefaultPosition, wxDefaultSize, remeshParameterizationArray);
	p_remeshParamterizationComboBox->SetFont(*font);
	
	switch(p_meshSetting.getRemeshParameter())
	{
		case MeshParametrization::MESH_PARAM_HARMONIC:
			OmniFEMMsg::instance()->MsgInfo("Remesh Parametrization loaded as Harmonic");
			p_remeshParamterizationComboBox->SetSelection(0);
			break;
		case MeshParametrization::MESH_PARAM_CONFORMAL:
			OmniFEMMsg::instance()->MsgInfo("Remesh Parametrization loaded as Conformal");
			p_remeshParamterizationComboBox->SetSelection(1);
			break;
		case MeshParametrization::MESH_PARAM_RBFHARMONIC:
			OmniFEMMsg::instance()->MsgInfo("Remesh Parametrization loaded as Rbf Harmonic");
			p_remeshParamterizationComboBox->SetSelection(2);
			break;
	}
	
	reMeshParamSizer->Add(remeshParamText, 0, wxCENTER | wxLEFT | wxBOTTOM | wxRIGHT, 6);
	reMeshParamSizer->Add(p_remeshParamterizationComboBox, 0, wxRIGHT | wxBOTTOM, 6);
	
	wxStaticText *smootherText = new wxStaticText(meshSettingsPanel, wxID_ANY, "Smoothing Steps:");
	smootherText->SetFont(*font);
	
	wxIntegerValidator<unsigned char> smoothingValidator;
	smoothingValidator.SetRange(0, 100);
	
	p_smoothingStepsTextCtrl->Create(meshSettingsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, smoothingValidator);

	std::ostream smoothingStream(p_smoothingStepsTextCtrl);
	smoothingStream << (unsigned int)p_meshSetting.getSmoothingSteps();
	p_smoothingStepsTextCtrl->SetFont(*font);
	OmniFEMMsg::instance()->MsgInfo("Set smoother steps to " + std::to_string(p_meshSetting.getSmoothingSteps()) + " steps");
	
	smootherSizer->Add(smootherText, 0, wxCENTER | wxBOTTOM | wxLEFT | wxRIGHT, 6);
	smootherSizer->Add(p_smoothingStepsTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
	
	wxStaticBoxSizer *elementSizeSizer = new wxStaticBoxSizer(wxHORIZONTAL, meshSettingsPanel, "Element Size Settings");
	elementSizeSizer->GetStaticBox()->SetFont(*font);
	
	wxStaticText *minText = new wxStaticText(elementSizeSizer->GetStaticBox(), wxID_ANY, "Min:");
	minText->SetFont(*font);
	wxStaticText *maxText = new wxStaticText(elementSizeSizer->GetStaticBox(), wxID_ANY, "Max:");
	maxText->SetFont(*font);
	wxStaticText *factorText = new wxStaticText(elementSizeSizer->GetStaticBox(), wxID_ANY, "Factor:");
	factorText->SetFont(*font);
	
	wxSize aSize(60, 23);
	
	p_minElementSizeTextCtrl->Create(elementSizeSizer->GetStaticBox(), wxID_EDIT, wxEmptyString, wxDefaultPosition, aSize, wxTE_PROCESS_ENTER, greaterThenZero);
	p_minElementSizeTextCtrl->SetFont(*font);
	
	wxTextValidator testValidator(wxFILTER_NUMERIC | wxFILTER_EXCLUDE_LIST);
	wxArrayString excludeList;
	excludeList.Add("-");
	testValidator.SetExcludes(excludeList);
	p_minElementSizeTextCtrl->SetValidator(testValidator);
	
	std::ostream minStream(p_minElementSizeTextCtrl);
	minStream << std::setprecision(4);
	minStream << p_meshSetting.getMinElementSize();
	OmniFEMMsg::instance()->MsgInfo("Loading min element size as: " + std::to_string(p_meshSetting.getMinElementSize()));
	
	p_maxElementSizeTextCtrl->Create(elementSizeSizer->GetStaticBox(), wxID_EDIT, wxEmptyString, wxDefaultPosition, aSize, wxTE_PROCESS_ENTER, greaterThenZero);
	p_maxElementSizeTextCtrl->SetFont(*font);
	p_maxElementSizeTextCtrl->SetValidator(testValidator);
	
	std::ostream maxStream(p_maxElementSizeTextCtrl);
	maxStream << std::setprecision(4);
	maxStream << p_meshSetting.getMaxElementSize();
	OmniFEMMsg::instance()->MsgInfo("Loading max element size as: " + std::to_string(p_meshSetting.getMaxElementSize()));
	
	p_elementSizeFactorTextCtrl->Create(elementSizeSizer->GetStaticBox(), wxID_EDIT, wxEmptyString, wxDefaultPosition, aSize, wxTE_PROCESS_ENTER, greaterThenZero);
	p_elementSizeFactorTextCtrl->SetFont(*font);
	p_elementSizeFactorTextCtrl->SetValidator(testValidator);
	
	std::ostream factorStream(p_elementSizeFactorTextCtrl);
	factorStream << std::setprecision(4);
	factorStream << p_meshSetting.getElementSizeFactor();
	OmniFEMMsg::instance()->MsgInfo("Loading mesh size factor as " + std::to_string(p_meshSetting.getElementSizeFactor()));
	
	elementSizeSizer->Add(minText, 0, wxCENTER | wxALL, 6);
	elementSizeSizer->Add(p_minElementSizeTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
	elementSizeSizer->Add(maxText, 0, wxCENTER | wxBOTTOM | wxTOP | wxRIGHT, 6);
	elementSizeSizer->Add(p_maxElementSizeTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
	elementSizeSizer->Add(factorText, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
	elementSizeSizer->Add(p_elementSizeFactorTextCtrl, 0, wxCENTER | wxTOP | wxBOTTOM | wxRIGHT, 6);
	
	wxStaticText *elementOrder = new wxStaticText(meshSettingsPanel, wxID_ANY, "Element Order:");
	elementOrder->SetFont(*font);
	
	wxIntegerValidator<unsigned int> elementValidator;
	elementValidator.SetMin(0);
	
	p_ElementOrderTextCtrl->Create(meshSettingsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, elementValidator);
	p_ElementOrderTextCtrl->SetFont(*font);
	
	std::ostream elementOrderStream(p_ElementOrderTextCtrl);
	elementOrderStream << p_meshSetting.getElementOrder();
	OmniFEMMsg::instance()->MsgInfo("Loading element order as " + std::to_string(p_meshSetting.getElementOrder()));
	
	elementOrderSizer->Add(elementOrder, 0, wxCENTER | wxBOTTOM | wxRIGHT | wxLEFT, 6);
	elementOrderSizer->Add(p_ElementOrderTextCtrl, 0, wxCENTER | wxBOTTOM | wxRIGHT, 6);
	
	p_meshResetDefaultsButton->Create(meshSettingsPanel, wxID_RESET, "Reset to Defaults");
	p_meshResetDefaultsButton->SetFont(*font);
	
	wxButton *advancedMeshSettings = new wxButton(meshSettingsPanel, wxID_MORE, "Advanced");
	advancedMeshSettings->SetFont(*font); 
	
	buttonResetSizer->Add(advancedMeshSettings, 0, wxCENTER | wxLEFT | wxRIGHT | wxBOTTOM, 6);
	buttonResetSizer->Add(p_meshResetDefaultsButton, 0, wxCENTER | wxRIGHT | wxBOTTOM, 6);
	
	meshSettingsSizer->Add(stucturedMeshSizer);
	meshSettingsSizer->Add(meshArrangmentSizer);
	meshSettingsSizer->Add(meshAlgoSizer);
	meshSettingsSizer->Add(meshRecombinationSizer);
	meshSettingsSizer->Add(reMeshAlgoSizer);
	meshSettingsSizer->Add(reMeshParamSizer);
	meshSettingsSizer->Add(smootherSizer);
	meshSettingsSizer->Add(elementSizeSizer, 0, wxLEFT | wxRIGHT | wxBOTTOM, 6);
	meshSettingsSizer->Add(elementOrderSizer);
	meshSettingsSizer->Add(buttonResetSizer, 0, wxALIGN_RIGHT);
    
    gridSettingPanel->SetSizerAndFit(gridSettingsSizer);
    physicsProblemPreferencesPanel->SetSizerAndFit(documentSettingsSizer);
	meshSettingsPanel->SetSizerAndFit(meshSettingsSizer);
    
    base->AddPage(gridSettingPanel, "Grid Settings");
    base->AddPage(physicsProblemPreferencesPanel, "Problem Settings");
	base->AddPage(meshSettingsPanel, "Mesh Settings");
    
    LayoutDialog();
}




void globalPreferencesDialog::onProblemTypeComboBox(wxCommandEvent &event)
{
    switch(_problemTypeComboBox->GetSelection())
    {
        case 0:// This first case is if the user selected the problem type to be planar
            _depthTextCtrl->Enable(true);
			OmniFEMMsg::instance()->MsgStatus("Problem set to Planar");
            break;
        case 1:// This second case is if the user selected the problem type to be axisymmetric
            _depthTextCtrl->Enable(false);
			OmniFEMMsg::instance()->MsgStatus("Problem set to Axisymmetric");
            break;
        default:// Everything else
            break;
    }
}



void globalPreferencesDialog::onMeshStructureComboBox(wxCommandEvent &event)
{
	switch(p_structuredComboBox->GetSelection())
	{
		case 0:
			p_meshArrangementComboBox->Enable(false);
			OmniFEMMsg::instance()->MsgStatus("Mesh structure set to unstructured");
			break;
		case 1:
			p_meshArrangementComboBox->Enable(true);
			OmniFEMMsg::instance()->MsgStatus("Mesh structure set to structured");
			break;
		default:
			break;
	}
	
	p_meshSetting.setStructuredState(p_structuredComboBox->GetSelection() & 1);
}



void globalPreferencesDialog::onMeshArrangemesntComboBox(wxCommandEvent &event)
{
	switch(p_meshArrangementComboBox->GetSelection())
	{
		case 0:
			OmniFEMMsg::instance()->MsgStatus("Face mesh Arrangment set to Left");
			break;
		case 1:
			OmniFEMMsg::instance()->MsgStatus("Face Mesh Arrangment set to Right");
			break;
		case 2:
			OmniFEMMsg::instance()->MsgStatus("Face Mesh Arrangment set to Alternate");
			break;
	}
	
	p_meshSetting.setMeshArrangment((StructuredArrangement)p_meshArrangementComboBox->GetSelection());
}



void globalPreferencesDialog::onMeshAlgoComboBox(wxCommandEvent &event)
{
	switch(p_meshAlgothimComboBox->GetSelection())
	{
		case 0:
			OmniFEMMsg::instance()->MsgStatus("Mesh Algorithm Set as Automatic");
			break;
		case 1:
			OmniFEMMsg::instance()->MsgStatus("Mesh Algorithm Set as MeshAdapt");
			break;
		case 2:
			OmniFEMMsg::instance()->MsgStatus("Mesh Algorithm Set as Delaunay");
			break;
		case 3:
			OmniFEMMsg::instance()->MsgStatus("Mesh Algorithm Set as Frontal");
			break;
	}
	
	p_meshSetting.setMeshAlgorithm((MeshAlgorthim)p_meshAlgothimComboBox->GetSelection());
}



void globalPreferencesDialog::onMeshRecombinationComboBox(wxCommandEvent &event)
{
	switch(p_meshRecombinationComboBox->GetSelection())
	{
		case 0:
			OmniFEMMsg::instance()->MsgStatus("Mesh Recombination set to Standard");
			break;
		case 1:
			OmniFEMMsg::instance()->MsgStatus("Mesh Recombination set to Blossom");
			break;
	}
	
	p_meshSetting.setBlossomRecombinationState(p_meshRecombinationComboBox->GetSelection() & 1);
}



void globalPreferencesDialog::onRemeshAlgo(wxCommandEvent &event)
{
	switch(p_remeshAlgorithmComboBox->GetSelection())
	{
		case 0:
			OmniFEMMsg::instance()->MsgStatus("Remesh Algorithm set to No Split");
			break;
		case 1:
			OmniFEMMsg::instance()->MsgStatus("Remesh Algorithm set to Automatic");
			break;
	}
	
	p_meshSetting.setAutoRemeshingState(p_remeshAlgorithmComboBox->GetSelection() & 1);
}



void globalPreferencesDialog::onRemeshParam(wxCommandEvent &event)
{
	switch(p_remeshParamterizationComboBox->GetSelection())
	{
		case 0:
			OmniFEMMsg::instance()->MsgStatus("Remesh Parameterization set to Harmonic");
			break;
		case 1:
			OmniFEMMsg::instance()->MsgStatus("Remesh Parameterization set to Conformal");
			break;
		case 2:
			OmniFEMMsg::instance()->MsgStatus("Remesh Parameterization set to Rbf Harmonic");
			break;
	}
	
	p_meshSetting.setRemeshParameter((MeshParametrization)p_remeshParamterizationComboBox->GetSelection());
}



void globalPreferencesDialog::onMeshDefaultsReset(wxCommandEvent &event)
{
	OmniFEMMsg::instance()->MsgStatus("Mesh settings defaults loaded");
	
	meshSettings defaultSetting;
	
	p_meshSetting = defaultSetting;
	
	p_structuredComboBox->SetSelection(0);
	
	p_meshArrangementComboBox->SetSelection(0);
	
	p_meshArrangementComboBox->Enable(false);
	
	p_meshAlgothimComboBox->SetSelection(0);
	
	p_meshRecombinationComboBox->SetSelection(0);
	
	p_remeshAlgorithmComboBox->SetSelection(0);
	
	p_remeshParamterizationComboBox->SetSelection(0);
	
	p_smoothingStepsTextCtrl->SetValue(wxEmptyString);
	std::ostream smoothingStream(p_smoothingStepsTextCtrl);
	smoothingStream << (unsigned int)p_meshSetting.getSmoothingSteps();
	
	p_minElementSizeTextCtrl->SetValue(wxEmptyString);
	std::ostream minStream(p_minElementSizeTextCtrl);
	minStream << std::setprecision(4);
	minStream << p_meshSetting.getMinElementSize();
	
	p_maxElementSizeTextCtrl->SetValue(wxEmptyString);
	std::ostream maxStream(p_maxElementSizeTextCtrl);
	maxStream << std::setprecision(4);
	maxStream << p_meshSetting.getMaxElementSize();
	
	p_elementSizeFactorTextCtrl->SetValue(wxEmptyString);
	std::ostream factorStream(p_elementSizeFactorTextCtrl);
	factorStream << std::setprecision(4);
	factorStream << p_meshSetting.getElementSizeFactor();
	
	p_ElementOrderTextCtrl->SetValue(wxEmptyString);
	std::ostream elementOrderStream(p_ElementOrderTextCtrl);
	elementOrderStream << p_meshSetting.getElementOrder();
}



void globalPreferencesDialog::getPreferences(electroStaticPreference &electricPref, meshSettings &settings)
{
    double value;
	long otherValue;
    
    /* This section will get the values for the grid preferences */
    _gridStepTextCtrl->GetValue().ToDouble(&value);
    _preferences->setGridStep(value);
    _preferences->setCoordinateSystem((planarCoordinateEnum)_coordinateComboBox->GetSelection());
    _preferences->setShowGridState(_showGridCheckBox->GetValue());
    _preferences->setShowOriginState(_showOriginCheckBox->GetValue());
    _preferences->setSnapGridState(_snapGridCheckBox->GetValue());
    _preferences->setShowAxisState(_showGridAxisCheckBox->GetValue());
    _preferences->setShowBlockNameState(_showBlockNameCheckBox->GetValue());
    _preferences->setMouseZoomReverseState(_reverseMouseZoomCheckBox->GetValue());
    
    /* THis section will get the preferences for the physics problem */
    electricPref.setProblemType((problemTypeEnum)_problemTypeComboBox->GetSelection());
    electricPref.setUnitLength((unitLengthEnum)_lengthComboBox->GetSelection());
    _depthTextCtrl->GetValue().ToDouble(&value);
    electricPref.setDepth(value);
    _precisionTextCtrl->GetValue().ToDouble(&value);
    electricPref.setPrecision(value);
    _minAngleTextCtrl->GetValue().ToDouble(&value);
    electricPref.setMinAngle(value);
    electricPref.setComments(_commentsTextCtrl->GetValue());
	
	settings = p_meshSetting;
	
	p_smoothingStepsTextCtrl->GetValue().ToLong(&otherValue);
	settings.setSmoothingSteps((unsigned char)otherValue);
	OmniFEMMsg::instance()->MsgStatus("Set smoothing steps as " + std::to_string(otherValue));
	
	p_minElementSizeTextCtrl->GetValue().ToDouble(&value);
	settings.setMinElementSize(value);
	OmniFEMMsg::instance()->MsgStatus("Set min element size as " + std::to_string(value));
	
	p_maxElementSizeTextCtrl->GetValue().ToDouble(&value);
	settings.setMaxElementSize(value);
	OmniFEMMsg::instance()->MsgStatus("Set max element size as " + std::to_string(value));
	
	p_elementSizeFactorTextCtrl->GetValue().ToDouble(&value);
	settings.setElementSizeFactor(value);
	OmniFEMMsg::instance()->MsgStatus("Set element size factor as " + std::to_string(value));
	
	p_ElementOrderTextCtrl->GetValue().ToLong(&otherValue);
	settings.setElementOrder((unsigned int)otherValue);
	OmniFEMMsg::instance()->MsgStatus("Set element order as " + std::to_string(otherValue));
}



void globalPreferencesDialog::getPreferences(magneticPreference &magneticPref, meshSettings &settings)
{
    double value;
	long otherValue;
    
    /* This section will get the values for the grid preferences */
    _gridStepTextCtrl->GetValue().ToDouble(&value);
    _preferences->setGridStep(value);
    _preferences->setCoordinateSystem((planarCoordinateEnum)_coordinateComboBox->GetSelection());
    _preferences->setShowGridState(_showGridCheckBox->GetValue());
    _preferences->setShowOriginState(_showOriginCheckBox->GetValue());
    _preferences->setSnapGridState(_snapGridCheckBox->GetValue());
    _preferences->setShowAxisState(_showGridAxisCheckBox->GetValue());
    _preferences->setShowBlockNameState(_showBlockNameCheckBox->GetValue());
    _preferences->setMouseZoomReverseState(_reverseMouseZoomCheckBox->GetValue());
    
    /* THis section will get the preferences for the physics problem */
    magneticPref.setProblemType((problemTypeEnum)_problemTypeComboBox->GetSelection());
    magneticPref.setUnitLength((unitLengthEnum)_lengthComboBox->GetSelection());
    _depthTextCtrl->GetValue().ToDouble(&value);
    magneticPref.setDepth(value);
    _precisionTextCtrl->GetValue().ToDouble(&value);
    magneticPref.setPrecision(value);
    _minAngleTextCtrl->GetValue().ToDouble(&value);
    magneticPref.setMinAngle(value);
    magneticPref.setComments(_commentsTextCtrl->GetValue());
    magneticPref.setACSolver((acSolverEnum)_acSolverComboBox->GetSelection());
    _frequencyTextCtrl->GetValue().ToDouble(&value);
    magneticPref.setFrequency(value);
	
	settings = p_meshSetting;
	
	p_smoothingStepsTextCtrl->GetValue().ToLong(&otherValue);
	settings.setSmoothingSteps((unsigned char)otherValue);
	OmniFEMMsg::instance()->MsgStatus("Set smoothing steps as " + std::to_string(otherValue));
	
	p_minElementSizeTextCtrl->GetValue().ToDouble(&value);
	settings.setMinElementSize(value);
	OmniFEMMsg::instance()->MsgStatus("Set min element size as " + std::to_string(value));
	
	p_maxElementSizeTextCtrl->GetValue().ToDouble(&value);
	settings.setMaxElementSize(value);
	OmniFEMMsg::instance()->MsgStatus("Set max element size as " + std::to_string(value));
	
	p_elementSizeFactorTextCtrl->GetValue().ToDouble(&value);
	settings.setElementSizeFactor(value);
	OmniFEMMsg::instance()->MsgStatus("Set element size factor as " + std::to_string(value));
	
	p_ElementOrderTextCtrl->GetValue().ToLong(&otherValue);
	settings.setElementOrder((unsigned int)otherValue);
	OmniFEMMsg::instance()->MsgStatus("Set element order as " + std::to_string(otherValue));
}      



void globalPreferencesDialog::onMeshAdvance(wxCommandEvent &event)
{
	wxMessageBox("ADvanced Mesh Settings displayed");
}


void globalPreferencesDialog::onTextChange(wxCommandEvent &event)
{
	double value = 0;
	
	p_minElementSizeTextCtrl->GetValue().ToDouble(&value);
	
	if(value < 0)
		p_minElementSizeTextCtrl->SetValue("0");
		
	p_maxElementSizeTextCtrl->GetValue().ToDouble(&value);
	
	if(value < 0)
		p_maxElementSizeTextCtrl->SetValue("0");
		
	p_elementSizeFactorTextCtrl->GetValue().ToDouble(&value);
	
	if(value < 0)
		p_elementSizeFactorTextCtrl->SetValue("0");
}


wxBEGIN_EVENT_TABLE(globalPreferencesDialog, wxPropertySheetDialog)
    EVT_COMBOBOX(generalFrameButton::ID_ComboBox1, globalPreferencesDialog::onProblemTypeComboBox)
	EVT_COMBOBOX(generalFrameButton::ID_ComboBox2, globalPreferencesDialog::onMeshStructureComboBox)
	EVT_COMBOBOX(generalFrameButton::ID_ComboBox3, globalPreferencesDialog::onMeshArrangemesntComboBox)
	EVT_COMBOBOX(generalFrameButton::ID_ComboBox4, globalPreferencesDialog::onMeshAlgoComboBox)
	EVT_COMBOBOX(generalFrameButton::ID_ComboBox5, globalPreferencesDialog::onMeshRecombinationComboBox)
	EVT_COMBOBOX(generalFrameButton::ID_ComboBox6, globalPreferencesDialog::onRemeshAlgo)
	EVT_COMBOBOX(generalFrameButton::ID_ComboBox7, globalPreferencesDialog::onRemeshParam)
	EVT_BUTTON(wxID_RESET, globalPreferencesDialog::onMeshDefaultsReset)
	EVT_BUTTON(wxID_MORE, globalPreferencesDialog::onMeshAdvance)
	EVT_TEXT_ENTER(wxID_EDIT, globalPreferencesDialog::onTextChange)
wxEND_EVENT_TABLE()