#ifndef SOLVER_FUNCTIONS_H_
#define SOLVER_FUNCTIONS_H

#include <wx/wx.h>

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

#include <common/ElectricalBoundary.h>
#include <common/ElectroStaticMaterial.h>
#include <common/ProblemDefinition.h>

#include <common/ElectricalBoundary.h>
#include <common/ElectroStaticMaterial.h>

#include <Mesh/ClosedPath.h>

#include <UI/geometryShapes.h>

class CommonSolverFunctions
{
public:
	static bool faceLiesOnBoundary(wxRealPoint faceCenter, edgeLineShape *contourEdge)
	{
		if(contourEdge->getArcID() == 0)
		{
			const double edgeSlope = (contourEdge->getFirstNode()->getCenterYCoordinate() - contourEdge->getSecondNode()->getCenterYCoordinate()) / 
									(contourEdge->getFirstNode()->getCenterXCoordinate() - contourEdge->getSecondNode()->getCenterXCoordinate());
			
			//const wxRealPoint faceCenter = wxRealPoint(cellFace->center()(0), cellFace->center()(1));
			
			const double faceSlope = (contourEdge->getFirstNode()->getCenterYCoordinate() - contourEdge->getSecondNode()->getCenterYCoordinate()) / 
									(contourEdge->getFirstNode()->getCenterXCoordinate() - contourEdge->getSecondNode()->getCenterXCoordinate());
			
			const double calculation = 	edgeSlope * faceCenter.x - 
										edgeSlope * contourEdge->getSecondNode()->getCenterXCoordinate() + 
										contourEdge->getSecondNode()->getCenterYCoordinate();
			
			if((calculation < faceCenter.y + 1e-6) && (calculation > faceCenter.y - 1e-6))
				return true;
			
			return false;
		}
		else
		{
			return false;
		}
	}
};

#endif