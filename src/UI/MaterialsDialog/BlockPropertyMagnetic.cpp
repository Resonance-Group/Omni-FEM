#include <UI/MaterialsDialog/BlockPropertyMagnetics.h>

// TODO: Add in the saize of this thing
blockPropertyMagnetic::blockPropertyMagnetic(magneticMaterial material) : wxFrame(NULL, wxID_ANY, "Magnetic Block Property", wxDefaultPosition, wxSize(416, 484))
{
    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name:", wxPoint(21, 15), wxSize(38, 13));
    wxStaticText *BHCurve = new wxStaticText(this, wxID_ANY, "B-H Curve", wxPoint(21, 45), wxSize(56, 13));
    wxStaticText *linearMaterial = new wxStaticText(this, wxID_ANY, "Linear Material Properties", wxPoint(2, 85), wxSize(129, 13));
    wxStaticText *relativeUx = new wxStaticText(this, wxID_ANY, "Relative ux:", wxPoint(21, 104), wxSize(63,13));
    wxStaticText *relativeUy = new wxStaticText(this, wxID_ANY, "Relative uy:", wxPoint(233, 104), wxSize(63, 13));
    wxStaticText *phiX = new wxStaticText(this, wxID_ANY, "Phi hx:", wxPoint(21, 130), wxSize(38, 13));
    wxStaticText *phiY = new wxStaticText(this, wxID_ANY, "Phi hy:", wxPoint(233, 130), wxSize(38, 13));
    wxStaticText *deg1 = new wxStaticText(this, wxID_ANY, "deg", wxPoint(187, 130), wxSize(25, 13));
    wxStaticText *deg2 = new wxStaticText(this, wxID_ANY, "deg", wxPoint(383, 130), wxSize(25, 13));
    wxStaticText *deg3 = new wxStaticText(this, wxID_ANY, "deg", wxPoint(385, 183), wxSize(25, 13));
    wxStaticText *nonlinearMatLabel = new wxStaticText(this, wxID_ANY, "Nonlinear Material Properties:", wxPoint(2, 162), wxSize(145, 13));
    wxStaticText *phiMaxLabel = new wxStaticText(this, wxID_ANY, "Phi hmax:", wxPoint(233, 183), wxSize(52, 13));
    wxStaticText *coercivityLabel = new wxStaticText(this, wxID_ANY, "Coeercivity:", wxPoint(2, 214), wxSize(56, 13));
    wxStaticText *eConductivityLabel = new wxStaticText(this, wxID_ANY, "Electrical Conductivity:", wxPoint(209, 214), wxSize(114, 13));
    wxStaticText *HcLabel = new wxStaticText(this, wxID_ANY, "Hc, A/m2", wxPoint(24, 236), wxSize(56, 13));
    wxStaticText *sigLabel = new wxStaticText(this, wxID_ANY, "sig. MS/m:", wxPoint(233, 236), wxSize(55, 13));
    wxStaticText *specialAttrLabel = new wxStaticText(this, wxID_ANY, "Special Attributes: Lamination and Wire Type", wxPoint(2, 322), wxSize(219, 13));
    wxStaticText *lamThickLabel = new wxStaticText(this, wxID_ANY, "Lam. Thickness:", wxPoint(5, 375), wxSize(82, 13));
    wxStaticText *numTurnsLabel = new wxStaticText(this, wxID_ANY, "Number of Turns:", wxPoint(5, 408), wxSize(89, 13));
    wxStaticText *lamFillLabel = new wxStaticText(this, wxID_ANY, "Lam. Fill Factor:", wxPoint(221, 375), wxSize(78, 13));
    wxStaticText *strandDiaLabel = new wxStaticText(this, wxID_ANY, "Strand Dia:", wxPoint(221, 411), wxSize(60,13));
    wxStaticText *mmLabel1 = new wxStaticText(this, wxID_ANY, "mm", wxPoint(187, 375), wxSize(23, 13));
    wxStaticText *mmLabel2 = new wxStaticText(this, wxID_ANY, "mm", wxPoint(385, 411), wxSize(23, 13));
    wxStaticText *sourceCurrentLabel = new wxStaticText(this, wxID_ANY, "Source Current Density:", wxPoint(2, 274), wxSize(119, 13));
    wxStaticText *currentDesnityLabel = new wxStaticText(this, wxID_ANY, "J MA/m2:", wxPoint(24, 293), wxSize(56, 13));
    
    wxButton *editBHCurve = new wxButton(this, generalFrameButton::ID_ButtonEdit, "Edit B-H Curve", wxPoint(24, 178), wxSize(157, 23));
    wxButton *okButton = new wxButton(this, generalFrameButton::ID_ButtonOk, "Ok", wxPoint(248, 449), wxSize(75, 23));
    wxButton *cancelButton = new wxButton(this, generalFrameButton::ID_ButtonCancel, "Cancel", wxPoint(329, 449), wxSize(75, 23));
    
    BHSettingsArray->Add("Linear B-H Relationship");
    BHSettingsArray->Add("Nonlinear B-H Curve");
    
    LamWireSettingsArray->Add("Not Laminated or Stranded");
    LamWireSettingsArray->Add("Laminated In-Plane");
    LamWireSettingsArray->Add("Laminated Parallel to x (Planar) or r (Axisymmetric)");
    LamWireSettingsArray->Add("Laminated Parallel to y (Planar) or z (Axisymmetric)")
    LamWireSettingsArray->Add("Magnet Wire");
    LamWireSettingsArray->Add("Plain Stranded Wire");
    LamWireSettingsArray->Add("Litz Wire");
    LamWireSettingsArray->Add("Square Wire");
    LamWireSettingsArray->Add("10% CCA");
    LamWireSettingsArray->Add("15% CCA");
    
    specialAttriComboBox->Create(this, generalFrameButton::ID_ComboBox2, wxPoint(24, 338), wxSize(355, 21), *LamWireSettingsArray);
    BHCurveComboBox->Create(this, generalFrameButton::ID_ComboBox1, wxPoint(95, 42), wxSize(165, 21), *BHSettingsArray);
    
    
    if(material == NULL)
    {
        _magneticMaterial.setCoercivity(0);
        _magneticMaterial.setName("New Material");
        _magneticMaterial.setCurrentDensity(0);
        _magneticMaterial.setLaminationFillFactor(1);
        _magneticMaterial.setLaminationThickness(0);
        _magneticMaterial.setMUrX(1);
        _magneticMaterial.setMUrY(1);
        _magneticMaterial.setNumberStrands(1);
        _magneticMaterial.setPhiX(0);
        _magneticMaterial.setPhiY(0);
        _magneticMaterial.setSigma(0);
        _magneticMaterial.setSpecialAttribute(lamWireEnum::NOT_LAMINATED_OR_STRANDED);
        _magneticMaterial.setStrandDiameter(0);
    }
    else
        _magneticMaterial = material;
    
    
}







wxBEGIN_EVENT_TABLE(blockPropertyMagnetic, wxFrame)

wxEND_EVENT_TABLE()