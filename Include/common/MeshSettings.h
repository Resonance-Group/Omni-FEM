#ifndef MESHSETTINGS_H_
#define MESHSETTINGS_H_

#include <math.h>

enum MeshAlgorthim
{
	MESH_ALGO_AUTOMATIC,
	MESH_ALGO_MESHADAPT,
	MESH_ALGO_DELAUNAY,
	MESH_ALGO_FRONTAL
};


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


class meshSettings
{
private:
	
	wxString p_meshSaveLocation;
	
	bool p_saveAsVTK = false;
	
	bool p_saveAsBDF = false;
	
	bool p_saveAsCELUM = false;
	
	bool p_saveAsCGNS = false;
	
	bool p_saveAsDIFFPACK = false;
	
	bool p_saveAsFourier = false;
	
	bool p_saveAsGEO = false;
	
	bool p_SaveAsINP = false;
	
	bool p_saveAsIR3 = false;
	
	bool p_saveAsMAIL = false;
	
	bool p_saveAsMESH = false;
	
	bool p_saveAsMSH = true;
	
	bool p_saveAsP3D = false;
	
	bool p_saveAsPatitionedMesh = false;
	
	bool p_saveAsPLY2 = false;
	
	bool p_saveAsSTL = false;
	
	bool p_saveAsSU2 = false;
	
	bool p_saveAsTochnog = false;
	
	bool p_saveAsUNV = false;
	
	bool p_saveAsVRML = false;

	bool p_isStructured = false;
	
	StructuredArrangement p_faceMeshStructuredArrangment = StructuredArrangement::ARRANGMENT_LEFT;
	
	MeshAlgorthim p_meshingAlgorthim = MeshAlgorthim::MESH_ALGO_AUTOMATIC;
	
	bool p_recombinationBlossom = false;
	
	bool p_remeshAuto = false;
	
	MeshParametrization p_remeshParam = MeshParametrization::MESH_PARAM_HARMONIC;
	
	unsigned char p_smoothingSteps = 1;
	
	double p_elementSizeFactor = 1.0;
	
	double p_minElementSize = 0.0;
	
	double p_maxElementSize = 1.0 * pow(10, 22);
	
	unsigned int p_elementOrder = 1;
	
	unsigned int p_multiplePasses = 1;
	
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