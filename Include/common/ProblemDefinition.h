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
  //  std::vector<boundaryCondition> _boundaryConditionList;
    
    //! This list is the global list for all of the materials that will be used in the problem
  //  std::vector<materialProperty> _materialList;
    
    /**********
    * Methods *
	***********/
public:
    //! This first function will add a single boundary condition to the list
    void addBoundaryCondition(boundaryCondition condition);
    
    //! This function will take a list and add the input list to the one in the problem Definition class
    void addBoundaryConditionList(std::vector<boundaryCondition> conditionList);
    
    //! This function will copy the conditionList into the current data type
    void copyBoundaryCondition(std::vector<boundaryCondition> conditionList);
    
    //! This function will return the boundary condition list
    std::vector<boundaryCondition> getBoundaryConditionList();
    
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


