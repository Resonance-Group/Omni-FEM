#ifndef ELECTROSTATIC_SOLVER_H_
#define ELECTROSTATIC_SOLVER_H_

#include <stdio.h>

#include <deal.II/grid/tria.h>
#include <deal.II/grid/tria_accessor.h>
#include <deal.II/grid/tria_iterator.h>
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/tria_boundary_lib.h>
#include <deal.II/grid/grid_out.h>
#include <deal.II/grid/manifold_lib.h>

#include <deal.II/fe/fe_q.h>
#include <deal.II/fe/fe_system.h>
#include <deal.II/fe/fe_values.h>

#include <deal.II/dofs/dof_handler.h>
#include <deal.II/dofs/dof_renumbering.h>
#include <deal.II/dofs/dof_tools.h>

#include <deal.II/lac/sparse_matrix.h>
#include <deal.II/lac/dynamic_sparsity_pattern.h>
#include <deal.II/lac/vector.h>
#include <deal.II/lac/solver_cg.h>
#include <deal.II/lac/precondition.h>

#include <deal.II/numerics/vector_tools.h>
#include <deal.II/numerics/matrix_tools.h>
#include <deal.II/numerics/data_out.h>
#include <deal.II/numerics/data_postprocessor.h>

#include <Solver/common/MeshOptimizer.h>
#include <Solver/common/CommonSolverFunctions.h>

#include <UI/ModelDefinition/ModelDefinition.h>

#include <common/ElectricalBoundary.h>
#include <common/ElectroStaticMaterial.h>
#include <common/ProblemDefinition.h>

#include <common/ElectricalBoundary.h>
#include <common/ElectroStaticMaterial.h>

#include <Mesh/ClosedPath.h>

#include <wx/stdpaths.h>


using namespace dealii;

class electricFieldPostProcessor : public DataPostprocessorVector<2>
{
public:
	electricFieldPostProcessor () : DataPostprocessorVector<2>("Electric_Field", update_gradients)
	{
		
	}
	
	virtual void evaluate_scalar_field(const DataPostprocessorInputs::Scalar<2> &input_data, std::vector<dealii::Vector<double> > &computed_quantities) const
	{
		for(unsigned int p = 0; p < input_data.solution_gradients.size(); ++p)
		{
			for(unsigned int d = 0; d < 2; ++d)
			{
				computed_quantities[p][d] = -1 * input_data.solution_gradients[p][d];
			}
		}
	}
};


class ElectroStaticSolver
{
private:
	meshOptimizer p_triangulation;
	
	std::vector<closedPath> *p_closedPath = nullptr;
	std::vector<electrostaticMaterial> *p_materialList = nullptr;
	std::vector<electricalBoundary> *p_boundaryList = nullptr;
	
	FE_Q<2> p_fe;
	DoFHandler<2> p_DOFHandler;
	SparsityPattern p_sparsePattern;
	SparseMatrix<double> p_systemMatrix;
	
	dealii::Vector<double>	p_solution;
	dealii::Vector<double>	p_systemRHS;
	
	void setupSolver();
	
	void solveSystem();
	
	void resultsProcessing(); 
	
	void setupGrid();
	
	void setupDOFS();
	
public:
	
	ElectroStaticSolver(modelDefinition *model, problemDefinition &problem) : p_fe(1)
	{
		p_triangulation.setupTriangulation(model);
		
		p_closedPath = problem.getClosedPath();
		p_materialList = problem.getElectricalMaterialList();
		p_boundaryList = problem.getElectricalBoundaryList();
	}

	void run();
};


#endif