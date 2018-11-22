#include <Solver/ElectrostaticSolver2.h>

void ElectroStaticSolver::run()
{
	setupGrid();
	setupDOFS();
	setupSolver();
	solveSystem();
	resultsProcessing();
}



void ElectroStaticSolver::setupGrid()
{
	for(auto cellIterator = p_triangulation.getTriangulation()->begin_active(); cellIterator != p_triangulation.getTriangulation()->end(); cellIterator++)
	{
		closedPath closedContour;
		
		for(auto contourIterator = p_closedPath->begin(); contourIterator != p_closedPath->end(); contourIterator++)
		{
			wxRealPoint cellCenter = wxRealPoint(cellIterator->center()(0), cellIterator->center()(1));
			
			if(contourIterator->pointInBoundingBox(cellCenter))
			{
				// If the center of the triagulation is inside of the bounding box, we need to check if the 
				// center is inside of the actual contour
				if(contourIterator->pointInContour(cellCenter))
				{
					bool cellLiesInHole = false;
					
					for(auto holeIterator = contourIterator->getHoles()->begin(); holeIterator != contourIterator->getHoles()->end(); holeIterator++)
					{
						if(holeIterator->pointInContour(cellCenter))
						{
							cellLiesInHole = true;
							break;
						}
					}
					
					/* If the cell does not lie in a hole, then the cell belongs to the closed path
					 * If this is the case, we need to add in the material id number and the boundary ID number
					 * if the cell belongs to a boundary
					 */ 
					if(!cellLiesInHole)
					{
						unsigned int materialID = contourIterator->getProperty()->getElectricalMaterial()->getMaterialID();
						cellIterator->set_material_id(contourIterator->getProperty()->getElectricalMaterial()->getMaterialID());
						
						// Now, we need to check if a face of the triagulation cell is on a boundary of the contour
						// If so, we need to set the boundary ID accordingly
						for(unsigned int f = 0; f < GeometryInfo<2>::faces_per_cell; f++)
						{
							wxRealPoint cellFaceCenter = wxRealPoint(cellIterator->face(f)->center()(0), cellIterator->face(f)->center()(1));
							
							for(auto edgeIterator = contourIterator->getClosedPath()->begin(); edgeIterator != contourIterator->getClosedPath()->end(); edgeIterator++)
							{
								if(CommonSolverFunctions::faceLiesOnBoundary(cellFaceCenter, *edgeIterator))
								{
									
									edgeLineShape *edge = *edgeIterator;
									unsigned int boundaryID = edge->getSegmentProperty()->getElectricalBoundary()->getBoundaryID();
									
									OmniFEMMsg::instance()->MsgInfo(	"Cell " + std::to_string(cellIterator->subdomain_id()) + " is at boundary: " + 
																		std::to_string(edge->getSegmentProperty()->getElectricalBoundary()->getBoundaryID()) + " " + 
																		edge->getSegmentProperty()->getElectricalBoundary()->getBoundaryName());
																		
									OmniFEMMsg::instance()->MsgInfo("Cell face set to: " + std::to_string(cellFaceCenter.x) + ", " + std::to_string(cellFaceCenter.y));
									
									cellIterator->face(f)->set_boundary_id(edge->getSegmentProperty()->getElectricalBoundary()->getBoundaryID());
								}
							}
						}
					}
				}
			}
		}
	}
}



void ElectroStaticSolver::setupSolver()
{
	
	QGauss<2> quadrature(2);
	FEValues<2> finiteElementValues(p_fe, quadrature, update_values | update_gradients | update_quadrature_points | update_JxW_values);
	
//	const RightHandSide right_hand_side;
	
	const unsigned int dofsPerCell = p_fe.dofs_per_cell;
	const unsigned int numQuadPoints = quadrature.size();
	
	FullMatrix<double> localCellMatrix(dofsPerCell, dofsPerCell);
	dealii::Vector<double> localRHSCell(dofsPerCell);
	std::vector<types::global_dof_index> localDOFIndices(dofsPerCell);
	
	OmniFEMMsg::instance()->MsgInfo("Setting up " + std::to_string(p_DOFHandler.n_dofs()) + " DOFs");
	
	for(auto activeCellIterator : p_DOFHandler.active_cell_iterators())
	{
		const double materialRelativeEpsilonValue 	= p_materialList->at(activeCellIterator->material_id() - 1).getEpsilonX();
		const double materialChargeDensity 			= p_materialList->at(activeCellIterator->material_id() - 1).getChargeDensity();
		
		finiteElementValues.reinit(activeCellIterator);
		localCellMatrix = 0;
		localRHSCell = 0;
		
		cout << "working on cell: " << activeCellIterator << endl;
		
		for(unsigned int qIndex = 0; qIndex < numQuadPoints; qIndex++)
		{
			for(unsigned int i = 0; i < dofsPerCell; i++)
			{
				
				for(unsigned int j = 0; j < dofsPerCell; j++)
				{
					// This is where the code for the solver will go in
					// In the linear form AU=F, this is the code that will
					// populate the local A. Later, the local A will be placed
					// into the global A.
					localCellMatrix(i, j) += 	finiteElementValues.shape_grad(i, qIndex) * 
												finiteElementValues.shape_grad(j, qIndex) *
												finiteElementValues.JxW(qIndex);
				}
				
				// Add in the code that will populate the local RHS using RHSCell
				localRHSCell(i) += 	finiteElementValues.shape_value(i, qIndex) * 
									(materialChargeDensity / (materialRelativeEpsilonValue * 8.854187814e-12)) *
								//	right_hand_side.value (finiteElementValues.quadrature_point (qIndex)) *
								//	0.0 *
									finiteElementValues.JxW(qIndex);
			}
		}
		
		activeCellIterator->get_dof_indices(localDOFIndices);
		
		for(unsigned int i = 0; i < dofsPerCell; i++)
		{
			for(unsigned int j = 0; j < dofsPerCell; j++)
			{
				p_systemMatrix.add(localDOFIndices[i], localDOFIndices[j], localCellMatrix(i, j));
			}
			
			p_systemRHS(localDOFIndices[i]) += localRHSCell(i);
		}
	}
	
	map<types::global_dof_index, double> boundaryValues;
	
	/*VectorTools::interpolate_boundary_values(p_DOFHandler, 0, ConstantFunction<2>(100.0), boundaryValues);
	VectorTools::interpolate_boundary_values(p_DOFHandler, 1, ZeroFunction<2>(), boundaryValues);
	VectorTools::interpolate_boundary_values(p_DOFHandler, 2, ZeroFunction<2>(), boundaryValues);
	
	 */ 
	
	/*VectorTools::interpolate_boundary_values(p_DOFHandler, 2, ConstantFunction<2>(100.0), boundaryValues);
	VectorTools::interpolate_boundary_values(p_DOFHandler, 1, ZeroFunction<2>(), boundaryValues);
	VectorTools::interpolate_boundary_values(p_DOFHandler, 3, ZeroFunction<2>(), boundaryValues);
	 */ 
	
	
	
	// Add in code to interpolate boundary values
	for(unsigned int i = 0; i < p_boundaryList->size(); i++)
	{
		OmniFEMMsg::instance()->MsgInfo("Working on boundary " + std::to_string(i + 1) + " " + p_boundaryList->at(i).getBoundaryName());
		if(p_boundaryList->at(i).getVoltage() > 0)
		{
			OmniFEMMsg::instance()->MsgInfo("Boundary " + std::to_string(i + 1) + " " + p_boundaryList->at(i).getBoundaryName() + " value " + std::to_string(p_boundaryList->at(i).getVoltage()));
			VectorTools::interpolate_boundary_values(p_DOFHandler, i + 1, ConstantFunction<2>(p_boundaryList->at(i).getVoltage()), boundaryValues);
		}
		else
		{
			VectorTools::interpolate_boundary_values(p_DOFHandler, i + 1, ZeroFunction<2>(), boundaryValues);
			OmniFEMMsg::instance()->MsgInfo("Boundary " + std::to_string(i + 1) + " " + p_boundaryList->at(i).getBoundaryName() + " value 0");
		}
	}
	 
	  
	 
	//VectorTools::interpolate_boundary_values(p_DOFHandler, 0, ZeroFunction<2>(), boundaryValues);
	
	MatrixTools::apply_boundary_values(boundaryValues, p_systemMatrix, p_solution, p_systemRHS);
	
  /*std::map<types::global_dof_index,double> boundary_values;
  VectorTools::interpolate_boundary_values (p_DOFHandler,
                                            0,
                                            BoundaryValues(),
                                            boundary_values);
  MatrixTools::apply_boundary_values (boundary_values,
                                      p_systemMatrix,
                                      p_solution,
                                      p_systemRHS);
									   */ 
	
}



void ElectroStaticSolver::solveSystem()
{
	
	SolverControl controlSolver(1000, 1e-12);
	
	SolverCG<> solver(controlSolver);
	
	solver.solve(p_systemMatrix, p_solution, p_systemRHS, PreconditionIdentity());
}



void ElectroStaticSolver::resultsProcessing()
{
	wxStandardPaths paths = wxStandardPaths::Get();
	std::string filePath = paths.GetDocumentsDir().ToStdString() + "/" + "solution.vtk";
	electricFieldPostProcessor electric_field_Post_processor;
	/*
	
	
	DataOut<2> outputData;
	
	outputData.attach_dof_handler(p_DOFHandler);
	outputData.add_data_vector(p_solution, "Voltage Solution");
	outputData.add_data_vector(p_solution, electric_field_Post_processor);
	outputData.build_patches();
	
	wxStandardPaths paths = wxStandardPaths::Get();
	std::string filePath = paths.GetDocumentsDir().ToStdString() + "/" + "solution.vtk";
	
	ofstream outputSolution(filePath);
	outputData.write_vtk(outputSolution);
	 */

	DataOut<2> data_out;
	data_out.attach_dof_handler (p_DOFHandler);
	data_out.add_data_vector (p_solution, "solution");
	data_out.add_data_vector(p_solution, electric_field_Post_processor);
	data_out.build_patches ();
	std::ofstream output (filePath);
	data_out.write_vtk (output); 
}



void ElectroStaticSolver::setupDOFS()
{
	//p_DOFHandler.initialize(*(p_triangulation.getTriangulation()), p_fe);
	
	p_DOFHandler.distribute_dofs(p_fe);
	DoFRenumbering::Cuthill_McKee(p_DOFHandler);
	
	DynamicSparsityPattern dSparsePattern(p_DOFHandler.n_dofs());
	DoFTools::make_sparsity_pattern(p_DOFHandler, dSparsePattern);
	
	p_sparsePattern.copy_from(dSparsePattern);
	
	// Add some other stuff regarding sparse pattern here
	
	p_systemMatrix.reinit(p_sparsePattern);
	p_solution.reinit(p_DOFHandler.n_dofs());
	p_systemRHS.reinit(p_DOFHandler.n_dofs());
	  
}
