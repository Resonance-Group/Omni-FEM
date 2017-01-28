#include <UI/MaterialsDialog/BlockPropertyMagnetics.h>

// TODO: Add in the saize of this thing
blockPropertyMagnetic::blockPropertyMagnetic() : wxFrame(NULL, wxID_ANY, "Magnetic Block Property", wxDefaultPosition, wxSize(416, 484))
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
    
    
    _magneticMaterial.setCoercivity(0);
}







wxBEGIN_EVENT_TABLE(blockPropertyMagnetic, wxFrame)

wxEND_EVENT_TABLE()