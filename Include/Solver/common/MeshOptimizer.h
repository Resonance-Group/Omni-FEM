#ifndef MESH_OPTIMIZER_H_
#define MESH_OPTIMIZER_H_

#include <iostream>
#include <fstream>
#include <stdio.h>

#include <deal.II/grid/tria.h>
#include <deal.II/grid/tria_accessor.h>
#include <deal.II/grid/tria_iterator.h>
#include <deal.II/grid/grid_tools.h>
#include <deal.II/grid/manifold_lib.h>
#include <deal.II/grid/grid_in.h>
#include <deal.II/grid/grid_out.h>

#include <Mesh/GMSH/GModel.h>

#include <UI/ModelDefinition/ModelDefinition.h>

#include <wx/stdpaths.h>
#include <wx/string.h>

using namespace dealii;

class meshOptimizer
{
private:
	Triangulation<2> p_problemMesh;
	
public:
	
	meshOptimizer()
	{
		
	}
	
	
	void setupTriangulation(modelDefinition *problemModel)
	{
		GridIn<2> gridIn;
		GridOut outputGrid;
		wxStandardPaths paths = wxStandardPaths::Get();
		std::string filePath = paths.GetDocumentsDir().ToStdString() + "/" + "mesh.msh";
		
		//problemModel->getMeshModel()->writeVTK(filePath);
		problemModel->getMeshModel()->writeMSH(filePath, 2.0, false, false, false, 1.0, 0, 0, false);
		
		gridIn.attach_triangulation(p_problemMesh);
		std::ifstream inputMeshFile(filePath);
		gridIn.read_msh(inputMeshFile);
		
		remove(filePath.c_str());
		
		// May need to add a manifold object here?
		p_problemMesh.set_all_manifold_ids(0);
	}
	
	/**
	 * @brief Returns the Deal.ii mesh
	 */
	Triangulation<2> *getTriangulation()
	{
		return &p_problemMesh;
	}
};

#endif