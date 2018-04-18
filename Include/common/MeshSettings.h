#ifndef MESHSETTINGS_H_
#define MESHSETTINGS_H_

#include <math.h>

//! Enum that is used to specify the mesh algorithm
enum MeshAlgorthim
{
	MESH_ALGO_AUTOMATIC,
	MESH_ALGO_MESHADAPT,
	MESH_ALGO_DELAUNAY,
	MESH_ALGO_FRONTAL
};


//! Enum that is used to specify the mesh parameterization method
enum MeshParametrization
{
	MESH_PARAM_HARMONIC,
	MESH_PARAM_CONFORMAL,
	MESH_PARAM_RBFHARMONIC
};


enum StructuredArrangement
{
	ARRANGMENT_LEFT,
	ARRANGMENT_RIGHT,
	ARRANGMENT_ALTERNATED
};


/**
 * @class meshSettings
 * @author Phillip
 * @date 17/04/18
 * @file MeshSettings.h
 * @brief This is the mesh setting class which contains all of the properties and methods
 * 			for the mesh settings. This includes which file to save the mesh as, which
 * 			2D mesh algorithm to use, which mesh parametrization algorithm to use, the smoothing steps
 * 			the element order, the mesh element size, and more
 * 			
 */
class meshSettings
{
private:
	
	//! THe directory to save the mesh file to 
	wxString p_meshSaveLocation = wxEmptyString;
	
	//! The path to save the various mesh files to
	wxString p_meshSavePath = wxString("");
	
	//! Boolean to indicate if the mesh should be saved as VTK (true)
	bool p_saveAsVTK = false;
	
	//! Boolean to indicate if the mesh should be saved as BDF (true)
	bool p_saveAsBDF = false;
	
	//! Boolean to indicate if the mesh should be saved as CELUM (true)
	bool p_saveAsCELUM = false;
	
	//! Boolean to indicate if the mesh should be saved as CGNS (true)
	bool p_saveAsCGNS = false;
	
	//! Boolean to indicate if the mesh should be saved as DIFFPACK (true)
	bool p_saveAsDIFFPACK = false;
	
	//! Boolean to indicate if the mesh should be saved as Fourier (true)
	bool p_saveAsFourier = false;
	
	//! Boolean to indicate if the mesh should be saved as Geo (true)
	bool p_saveAsGEO = false;
	
	//! Boolean to indicate if the mesh should be saved as INP (true)
	bool p_SaveAsINP = false;
	
	//! Boolean to indicate if the mesh should be saved as IR3 (true)
	bool p_saveAsIR3 = false;
	
	//! Boolean to indicate if the mesh should be saved as MAIL (true)
	bool p_saveAsMAIL = false;
	
	//! Boolean to indicate if the mesh should be saved as MESH (true)
	bool p_saveAsMESH = false;
	
	//! Boolean to indicate if the mesh should be saved as MSH (true)
	bool p_saveAsMSH = true;
	
	//! Boolean to indicate if the mesh should be saved as P3D (true)
	bool p_saveAsP3D = false;
	
	//! Boolean to indicate if the mesh should be saved as Patitioned Mesh (true)
	bool p_saveAsPatitionedMesh = false;
	
	//! Boolean to indicate if the mesh should be saved as PLY2 (true)
	bool p_saveAsPLY2 = false;
	
	//! Boolean to indicate if the mesh should be saved as STL (true)
	bool p_saveAsSTL = false;
	
	//! Boolean to indicate if the mesh should be saved as SU2 (true)
	bool p_saveAsSU2 = false;
	
	//! Boolean to indicate if the mesh should be saved as Tochnog (true)
	bool p_saveAsTochnog = false;
	
	//! Boolean to indicate if the mesh should be saved as UNV (true)
	bool p_saveAsUNV = false;
	
	//! Boolean to indicate if the mesh should be saved as VRML (true)
	bool p_saveAsVRML = false;

	bool p_isStructured = false;
	
	StructuredArrangement p_faceMeshStructuredArrangment = StructuredArrangement::ARRANGMENT_LEFT;
	
	//! Data type to indicate which 2D mesh algorithm to use
	MeshAlgorthim p_meshingAlgorthim = MeshAlgorthim::MESH_ALGO_AUTOMATIC;
	
	//! Boolean used to indicate if GMSH should use the Blossom algorithm when recombining
	bool p_recombinationBlossom = true;
	
	bool p_remeshAuto = false;
	
	//! Property used to indicate which remesh parameterization algorithm GMSH should use
	MeshParametrization p_remeshParam = MeshParametrization::MESH_PARAM_HARMONIC;
	
	//! Value used to indicate the number of smoothing steps
	unsigned char p_smoothingSteps = 1;
	
	//! Value used to specify the global mesh size scaling factor
	double p_elementSizeFactor = 1.0;
	
	//! Property used to specify the smallest element size
	double p_minElementSize = 0.0;
	
	//! Property used to specify the largest element size
	double p_maxElementSize = 1.0 * pow(10, 22);
	
	//! Property used to specify the element order of the mesh
	unsigned int p_elementOrder = 1;
	
	//! Property used to specify the number of times GMSH should remesh the geometry
	unsigned int p_multiplePasses = 1;
	
	//! Property used to specify the number of smoothing steps for Blossom algorithm 
	unsigned int p_llyodSmoothingSteps = 5;
	
//---- Section is for structured meshes	

public:
	
	void setStructuredState(bool state)
	{
		p_isStructured = state;
	}
	
	bool getStructuredState()
	{
		return p_isStructured;
	}
	
	void setDirString(wxString dirPath)
	{
		p_meshSavePath = dirPath;
	}
	
	wxString getDirString()
	{
		return p_meshSavePath;
	}
	
	void setMeshArrangment(StructuredArrangement arrangment)
	{
		p_faceMeshStructuredArrangment = arrangment;
	}
	
	StructuredArrangement getMeshArrangment()
	{
		return p_faceMeshStructuredArrangment;
	}
	
	void setMeshAlgorithm(MeshAlgorthim algorithm)
	{
		p_meshingAlgorthim = algorithm;
	}
	
	MeshAlgorthim getMeshAlgorithm()
	{
		return p_meshingAlgorthim;
	}
	
	void setBlossomRecombinationState(bool state)
	{
		p_recombinationBlossom = state;
	}
	
	bool getBlossomRecombinationState()
	{
		return p_recombinationBlossom;
	}
	
	void setAutoRemeshingState(bool state)
	{
		p_remeshAuto = state;
	}
	
	bool getAutoRemeshingState()
	{
		return p_remeshAuto;
	}
	
	void setRemeshParameter(MeshParametrization param)
	{
		p_remeshParam = param;
	}
	
	MeshParametrization getRemeshParameter()
	{
		return p_remeshParam;
	}
	
	void setSmoothingSteps(unsigned char value)
	{
		p_smoothingSteps = value;
	}
	
	unsigned char getSmoothingSteps()
	{
		return p_smoothingSteps;
	}
	
	void setElementSizeFactor(double value)
	{
		p_elementSizeFactor = value;
	}
	
	double getElementSizeFactor()
	{
		return p_elementSizeFactor;
	}
	
	void setMinElementSize(double value)
	{
		p_minElementSize = value;
	}
	
	double getMinElementSize()
	{
		return p_minElementSize;
	}
	
	void setMaxElementSize(double value)
	{
		p_maxElementSize = value;
	}
	
	double getMaxElementSize()
	{
		return p_maxElementSize;
	}
	
	void setElementOrder(unsigned int order)
	{
		p_elementOrder = order;
	}
	
	unsigned int getElementOrder()
	{
		return p_elementOrder;
	}
	
	void setMultiplePasses(unsigned int value)
	{
		if(value > 0)
			p_multiplePasses = value;
	}
	
	unsigned int getMultiplePasses()
	{
		return p_multiplePasses;
	}
	
	void setLlyodSmoothingSteps(unsigned int value)
	{
		if(value > 0)
			p_llyodSmoothingSteps = value;
	}
	
	unsigned int getLlyodSmoothingSteps()
	{
		return p_llyodSmoothingSteps;
	}
	
	void setSaveVTKState(bool state)
	{
		p_saveAsVTK = state;
	}
	
	bool getSaveVTKState()
	{
		return p_saveAsVTK;
	}
	
	void setSaveBDFState(bool state)
	{
		p_saveAsBDF = state;
	}
	
	bool getSaveBDFState()
	{
		return p_saveAsBDF;
	}
	
	void setSaveCELUMState(bool state)
	{
		p_saveAsCELUM = state;
	}
	
	bool getSaveCELUMState()
	{
		return p_saveAsCELUM;
	}
	
	void setSaveCGNSState(bool state)
	{
		p_saveAsCGNS = state;
	}
	
	bool getSaveCGNSState()
	{
		return p_saveAsCGNS;
	}
	
	void setSaveDIFFPACKSate(bool state)
	{
		p_saveAsDIFFPACK = state;
	}
	
	bool getSaveDIFFPACKSate()
	{
		return p_saveAsDIFFPACK;
	}
	
	void setSaveFourierState(bool state)
	{
		p_saveAsFourier = state;
	}
	
	bool getSaveFourierState()
	{
		return p_saveAsFourier;
	}
	
	void setSaveGEOState(bool state)
	{
		p_saveAsGEO = state;
	}
	
	bool getSaveGEOState()
	{
		return p_saveAsGEO;
	}
	
	void setSaveINPState(bool state)
	{
		p_SaveAsINP = state;
	}
	
	bool getSaveINPState()
	{
		return p_SaveAsINP;
	}
	
	void setSaveIR3State(bool state)
	{
		p_saveAsIR3 = state;
	}
	
	bool getSaveIR3State()
	{
		return p_saveAsIR3;
	}
	
	void setSaveMAILState(bool state)
	{
		p_saveAsMAIL = state;
	}
	
	bool getSaveMAILState()
	{
		return p_saveAsMAIL;
	}
	
	void setSaveMESHState(bool state)
	{
		p_saveAsMESH = state;
	}
	
	bool getSaveMESHState()
	{
		return p_saveAsMESH;
	}
	
	void setSaveP3DState(bool state)
	{
		p_saveAsP3D = state;
	}
	
	bool getSaveP3DState()
	{
		return p_saveAsP3D;
	}
	
	void setSavePartitionedMeshState(bool state)
	{
		p_saveAsPatitionedMesh = state;
	}
	
	bool getSavePartitionedMeshState()
	{
		return p_saveAsPatitionedMesh;
	}
	
	void setSavePLY2State(bool state)
	{
		p_saveAsPLY2 = state;
	}
	
	bool getSavePLY2State()
	{
		return p_saveAsPLY2;
	}
	
	void setSaveSTLState(bool state)
	{
		p_saveAsSTL = state;
	}
	
	bool getSaveSTLState()
	{
		return p_saveAsSTL;
	}
	
	void setSaveSU2State(bool state)
	{
		p_saveAsSU2 = state;
	}
	
	bool getSaveSU2State()
	{
		return p_saveAsSU2;
	}
	
	void setSaveTochnogState(bool state)
	{
		p_saveAsTochnog = state;
	}
	
	bool getSaveTochnogState()
	{
		return p_saveAsTochnog;
	}
	
	void setSaveUNVState(bool state)
	{
		p_saveAsUNV = state;
	}
	
	bool getSaveUNVState()
	{
		return p_saveAsUNV;
	}
	
	void setSaveVRMLState(bool state)
	{
		p_saveAsVRML = state;
	}
	
	bool getSaveVRMLState()
	{
		return p_saveAsVRML;
	}
};

#endif