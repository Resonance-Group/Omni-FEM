#include <UI/EditMenu/GlobalPreferencesDialog.h>



globalPreferencesDialog::globalPreferencesDialog(wxWindow *par, gridPreferences gridPref, magneticPreference pref) : wxPropertySheetDialog(par, wxID_ANY, "Preferences")
{
    _problem = physicProblems::PROB_MAGNETICS;
    _magneticPreference = pref;
    createDialog();
}



globalPreferencesDialog::globalPreferencesDialog(wxWindow *par, gridPreferences gridPref, electroStaticPreference pref) : wxPropertySheetDialog(par, wxID_ANY, "Preferences")
{
    _problem = physicProblems::PROB_ELECTROSTATIC;
    _electricalPreference = pref;
    createDialog();
}



void globalPreferencesDialog::createDialog()
{
    wxFont *font = new wxFont(8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    wxPanel *panel = new wxPanel(this);
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
    
    wxStaticBoxSizer *documentSettingsSizer = new wxStaticBoxSizer(wxVERTICAL, panel);
    wxStaticBoxSizer *gridSettingsSizer = new wxStaticBoxSizer(wxVERTICAL, panel);
    
    wxBoxSizer *documentSettingLine1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine6 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine7 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *documentSettingLine8 = new wxBoxSizer(wxHORIZONTAL);
    
    wxBoxSizer *gridSettingLine1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *gridSettingLine6 = new wxBoxSizer(wxHORIZONTAL);
    
   
    
    CreateButtons(wxOK|wxCANCEL);
    LayoutDialog();
}  



void globalPreferencesDialog::updateInterface()
{
    if(_problem == physicProblems::PROB_ELECTROSTATIC)
    {
        
    }
    else if(_problem == physicProblems::PROB_MAGNETICS)
    {
        
    }
}