#ifndef PROBLEM_DEFINITION_H_
#define PROBLEM_DEFINITION_H_

#include <vector>

#include <common/ElectricalBoundary.h>
#include <common/ElectroStaticMaterial.h>
#include <common/ElectrostaticPreference.h>
#include <common/ConductorProperty.h>

#include <common/CircuitProperty.h>
#include <common/MagneticBoundary.h>
#include <common/MagneticMaterial.h>
#include <common/MagneticPreference.h>

#include <common/NodalProperty.h>


/*! /class problemDef
 *  /brief This class will contain any and all data types that are related to defining a problem
 *  This includes problem name, physics type, problem definition, 
 *  boundary condition list, electrostatic/magnetic preferences, and other data
 */ 
class problemDefinition
{
	/************
	* Variables *
	*************/
private:
    //! This list contains all of the boundary conditions that the user sets. THis is the most generic form such that it holds BC for both the magnetic domain and the electrical
    std::vector<electricalBoundary> _localElectricalBoundaryConditionList;
    
    //! This list is the global list for all of the materials that will be used in the problem
    std::vector<magneticBoundary> _localMagneticBoundaryConditionList;
    
    std::vector<conductorProperty> _localConductorList;
    
    std::vector<circuitProperty> _localCircuitList;
    
    std::vector<magneticMaterial> _localMagneticMaterialList;
    
    std::vector<electrostaticMaterial> _localElectrialMaterialList;
    
    std::vector<nodalProperty> _localNodalList;
    
    electroStaticPreference _localElectricalPreference;
    
    magneticPreference _localMagneticPreference;
    
    physicProblems _phycisProblem = physicProblems::NO_PHYSICS_DEFINED;
    
    /**********
    * Methods *
	***********/
public:
    void setPhysicsProblem(physicProblems prob)
    {
        _phycisProblem = prob;
    }
    
    physicProblems getPhysicsProblem()
    {
        return _phycisProblem;
    }

    //! This first function will add a single boundary condition to the list
    void addBoundaryCondition(magneticBoundary condition)
    {
        _localMagneticBoundaryConditionList.push_back(condition);
    }
    
    void addBoundaryCondition(electricalBoundary condition)
    {
        _localElectricalBoundaryConditionList.push_back(condition);
    }
    
    void setBoundaryList(std::vector<magneticBoundary> list)
    {
        _localMagneticBoundaryConditionList = list;
    }
    
    void setBoundaryList(std::vector<electricalBoundary> list)
    {
        _localElectricalBoundaryConditionList = list;
    }
    
    std::vector<magneticBoundary> getMagneticBoundaryList()
    {
        return _localMagneticBoundaryConditionList;
    }
    
    std::vector<electricalBoundary> getElectricalBoundaryList()
    {
        return _localElectricalBoundaryConditionList;
    }
    
    //! This function will add a single material into the global list
    void addMaterial(materialProperty material);
    
    //! This function will combine the input list with the global list
    void addMaterialList(std::vector<materialProperty> materialList);
    
    //! THis function will copy the input list to the global list
    void copyMaterialList(std::vector<materialProperty> materialList);
    
    //! This function will return the global list
    std::vector<materialProperty> getMaterialList();
    
    
};


#endif


