#ifndef PROBLEM_DEFINITION_H_
#define PROBLEM_DEFINITION_H_

#include <vector>

#include <wx/string.h>

#include <common/ElectricalBoundary.h>
#include <common/ElectroStaticMaterial.h>
#include <common/ElectrostaticPreference.h>
#include <common/ConductorProperty.h>

#include <common/CircuitProperty.h>
#include <common/MagneticBoundary.h>
#include <common/MagneticMaterial.h>
#include <common/MagneticPreference.h>

#include <common/NodalProperty.h>

#include <common/ExteriorRegion.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

//! Class that handles all of main settings for runnning a simulation
/*!
    This class contains all of the datatypes that are related to running a simulation.
    This includes the name, the phyciscs problem, the problem definition,
    boundary, mateiral, conductor, nodal lists and preferences for the problem
*/ 
class problemDefinition
{
private:
	friend class boost::serialization::access;

	
	/************
	* Variables *
	*************/


    //! The global list for the electrostatic boundary conditions
    /*!
        This list contains all of the boundary conditions that the user user
        creates for a electrostaic simulation
    */ 
    std::vector<electricalBoundary> _localElectricalBoundaryConditionList;
    
    //! The global list for the magnetiostatic boundary conditions
    /*!
        This list contains all of the boundary conditions that the user user
        creates for a magnetiostatic simulation
    */ 
    std::vector<magneticBoundary> _localMagneticBoundaryConditionList;
    
    //! The global list for the conductor property
    /*!
        This list is modified if the simulation is an electrostatic
        simulation
    */ 
    std::vector<conductorProperty> _localConductorList;
    
    //! The global list for the circuit property
    /*!
        This list is modified if the simulation is an magnetiostatic
        simulation
    */
    std::vector<circuitProperty> _localCircuitList;
    
    //! Global list for the magnetic materials
    /*!
        This list is modified if the simulation is a magnetiostatic 
        simulation
    */ 
    std::vector<magneticMaterial> _localMagneticMaterialList;
    
    //! Global list for the electrostatic materials
    /*!
        This list is modified if the simulation is a electrostatic 
        simulation
    */
    std::vector<electrostaticMaterial> _localElectrialMaterialList;
    
    //! Global list for the nodal properties
    std::vector<nodalProperty> _localNodalList;
    
    //! Definition of the eletrostatic preference
    /*!
        This variable is modified if the simulation
        is an electrostatic simulation
    */
    electroStaticPreference _localElectricalPreference;
    
    //! Definition of the magnetic preferece
    /*!
        This variable is modified if the simulation
        is a magnetic simulation
    */
    magneticPreference _localMagneticPreference;
    
    //! The variable that is used to set the physics problem
    /*!
        This variable controls what is drawn on the screen and what
        the state is of each dialog. Should the property dialog create
        the frame with electrical or magnetic material properties
    */ 
    physicProblems _phycisProblem = physicProblems::NO_PHYSICS_DEFINED;
	
	exteriorRegion p_exteriorRegion;
    
    //! The name of the physics simulation
    wxString _problemName = "Untitled";
    
    //! Boolean used to determine if the status bar should be drawn
    bool _showStatusBar = true;
	
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & _phycisProblem;
		ar & p_exteriorRegion;
		ar & _localNodalList;
		std::string name = _problemName.ToStdString();
		ar & name;
		_problemName = wxString(name);
		if(_phycisProblem == physicProblems::PROB_ELECTROSTATIC)
		{
			ar & _localElectricalPreference;
			ar & _localElectricalBoundaryConditionList;
			ar & _localConductorList;
			ar & _localElectrialMaterialList;
		}
		else if(_phycisProblem == physicProblems::PROB_MAGNETICS)
		{
			ar & _localMagneticPreference;
			ar & _localMagneticBoundaryConditionList;
			ar & _localCircuitList;
			ar & _localMagneticMaterialList;
		}
	}
    
    /**********
    * Methods *
	***********/
public:
    
    //! Sets the physics problem
    /*!
        \param prob A value that represents the physics simulation that 
                    will be solved
    */ 
    void setPhysicsProblem(physicProblems prob)
    {
        _phycisProblem = prob;
    }
    
    //! Retrieves the physics problem that is associated with the simualtion
    /*!
        \return Returns a value representing the physics simulation
                that will be ran
    */ 
    physicProblems getPhysicsProblem()
    {
        return _phycisProblem;
    }

    //! Adds a single boundary condition to the magnetic boundary condition list
    /*!
        \param condition The boundary condition that is to be added to the list
    */ 
    void addBoundaryCondition(magneticBoundary condition)
    {
        _localMagneticBoundaryConditionList.push_back(condition);
    }
    
    //! Adds a single boundary condition to the electrical boundary condition list
    /*!
        \param condition The boundary condition that is to be added to the list
    */
    void addBoundaryCondition(electricalBoundary condition)
    {
        _localElectricalBoundaryConditionList.push_back(condition);
    }
    
    //! Replaces the global magnetic boundary condition with the one passed into the function
    /*!
        \param list The boundary list that will replace the global list
    */ 
    void setBoundaryList(std::vector<magneticBoundary> list)
    {
        _localMagneticBoundaryConditionList = list;
    }
    
    //! Replaces the global electricla boundary condition with the one passed into the function
    /*!
        \param list The boundary list that will replace the global list
    */
    void setBoundaryList(std::vector<electricalBoundary> list)
    {
        _localElectricalBoundaryConditionList = list;
    }
    
    //! Retrieves the magnetic boundary list
    /*!
        \return Returns a pointer to a vector that contains all of the magnetic boundary list
    */ 
    std::vector<magneticBoundary> *getMagneticBoundaryList()
    {
        return &_localMagneticBoundaryConditionList;
    }
    
    //! Retrieves the electrical boundary list
    /*!
        \return Returns a pointer to a vector that contains all of the electrical boundary list
    */
    std::vector<electricalBoundary> *getElectricalBoundaryList()
    {
        return &_localElectricalBoundaryConditionList;
    }
    
    //! Sets the conductor list
    /*!
        This function is used during an electrical simulation
        \param list The list that contains the conductor properties that
                    need to be saved
    */ 
    void setConductorList(std::vector<conductorProperty> list)
    {
        _localConductorList = list;
    }
    
    //! Retrieves the condutor list
    /*!
        \return Returns a pointer to a vector containing all of the conductor properties
    */ 
    std::vector<conductorProperty> *getConductorList()
    {
        return &_localConductorList;
    }
    
    //! Sets the circuit list
    /*!
        This function is used during a magnetic simulation
        \param list The list that contains the circuit properties that
                    need to be saved
    */
    void setCircuitList(std::vector<circuitProperty> list)
    {
        _localCircuitList = list;
    }
    
    //! Retrieves the circuit list
    /*!
        \return Returns a pointer to a vector containing all of the circuit properties
    */ 
    std::vector<circuitProperty> *getCircuitList()
    {
        return &_localCircuitList;
    }
    
    //! Sets the nodal list
    /*!
        \param list The list that contains the nodal properties that
                    need to be saved
    */
    void setNodalPropertyList(std::vector<nodalProperty> list)
    {
        _localNodalList = list;
    }
    
    //! Retrieves the nodal list
    /*!
        \return Returns a pointer to a vector containing all of the nodal properties
    */
    std::vector<nodalProperty> *getNodalPropertyList()
    {
        return &_localNodalList;
    }
    
    //! Sets the magnetic material list
    /*!
        This function is used during a magnetic simulation
        \param list The list that contains the magnetic material properties that
                    need to be saved
    */
    void setMaterialList(std::vector<magneticMaterial> list)
    {
        _localMagneticMaterialList = list;
    }
    
    //! Sets the electrical material list
    /*!
        This function is used during an electrical simulation
        \param list The list that contains the electrical material properties that
                    need to be saved
    */
    void setMaterialList(std::vector<electrostaticMaterial> list)
    {
        _localElectrialMaterialList = list;
    }
    
    //! Retrieves the magnetic material list
    /*!
        \return Returns a pointer to a vector containing all of the magnetic material properties
    */
    std::vector<magneticMaterial> *getMagnetMaterialList()
    {
        return &_localMagneticMaterialList;
    }
    
    //! Retrieves the electrical material list
    /*!
        \return Returns a pointer to a vector containing all of the electrical material properties
    */
    std::vector<electrostaticMaterial> *getElectricalMaterialList()
    {
        return &_localElectrialMaterialList;
    }
    
    //! Sets the name of the simulation
    /*!
        This name is used when saving the simulation
        \param name The name of the simulation
    */
    void setName(wxString name)
    {
        _problemName = name;
    }
    
    //! Retrieves the name of the simulation
    /*!
        \return Returns a string representing the simulation name
    */ 
    wxString getName()
    {
        return _problemName;
    }
    
    //! Sets the preferences for the electrostatic simulation
    /*!
        \param preferences The preferences that are to be saved
    */ 
    void setPreferences(electroStaticPreference preference)
    {
        _localElectricalPreference = preference;
    }
    
    //! Sets the preferences for the magnetic simulation
    /*!
        \param preferences The preferences that are to be saved
    */
    void setPreferences(magneticPreference preference)
    {
        _localMagneticPreference = preference;
    }
    
    //! Retrieves the electrical preferences
    /*!
        \return Returns an object representing the preferences of the
                electrical simulation
    */ 
    electroStaticPreference getElectricalPreferences()
    {
        return _localElectricalPreference;
    }
    
    
    //! Retrieves the magnetic preferences
    /*!
        \return Returns an object representing the preferences of the
                magnetic simulation
    */ 
    magneticPreference getMagneticPreference()
    {
        return _localMagneticPreference;
    }
    
    //! Retrieves the state of displaying the status bar
    /*!
        \return Returns true if the user would like to display the status bar
                Returns false if the user does not want to display the status
    */ 
    bool getShowStatusBarState()
    {
        return _showStatusBar;
    }
    
    //! Sets the state of displaying the status bar
    /*!
        For now, the status bar is displaying the coordinate position of the mouse
        \param state Set to true in order to display the status bar.
                    Set to false to not display the status bar
    */ 
    void setShowStatusBarState(bool state)
    {
        _showStatusBar = state;
    }
	
	/**
	 * @brief Function that will set the exterior region of the problem
	 * @param value The exterior region properties that the simulation
	 * 				need to take.
	 */
	void setExteriorRegion(exteriorRegion value)
	{
		p_exteriorRegion = value;
	}
	
	/**
	 * @brief Function that will return a pointer pointing to the exterior region of the problem
	 * @return The pointer pointing to the exterier region class of the simulation
	 */
	exteriorRegion *getExteriorRegion()
	{
		return &p_exteriorRegion;
	}
};

#endif


