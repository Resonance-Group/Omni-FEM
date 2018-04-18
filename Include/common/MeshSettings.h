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
	
	/**
	 * @brief Function that is used to set the structed mesh state in the settings. This is a global setting.
	 * 			Note that in GMSH, a structured mesh can only be applied if the mesh has 4 sides that are not
	 * 			curves or arcs.
	 * @param state Set to True if all meshes should be structed. Otherwise set to false.
	 */
	void setStructuredState(bool state)
	{
		p_isStructured = state;
	}
	
	/**
	 * @brief Returns a boolean to indicate the structed state.
	 * @return Returns true if the mesh should be structued. Otherwise, returns false.
	 */
	bool getStructuredState()
	{
		return p_isStructured;
	}
	
	/**
	 * @brief Function that is used to set the directory path of the location for saving
	 * 			the mesh files. Note, for DealII to operate, a seperate mesh file is always generated.
	 * 			This mesh file is used for importing into DealII. This function does NOT change
	 * 			the path for the DealII mesh file. The mesh file for DealII is always saved in the same
	 * 			location as the .omnifem file.
	 * @param dirPath A string representing the direcotry path
	 */
	void setDirString(wxString dirPath)
	{
		p_meshSavePath = dirPath;
	}
	
	/**
	 * @brief Returns the string of the directory path for saving the mesh files. This function does not return
	 * 			the directory path of the DealII mesh file. The DealII mesh file is always saved in the same location
	 * 			as the .omnifem file.
	 * @return A string which specifies the direcotry location of where the mesh files 
	 * 			will be saved to.
	 */
	wxString getDirString()
	{
		return p_meshSavePath;
	}
	
	/**
	 * @brief Function that is used to set the mesh arragement of the structured mesh. The options are 
	 * 			left, right, and alternating. Again, this is for structed meshes only. This is 
	 * @param arrangment The arrangment of the mesh.
	 */
	void setMeshArrangment(StructuredArrangement arrangment)
	{
		p_faceMeshStructuredArrangment = arrangment;
	}
	
	/**
	 * @brief Function that is used to retrieve the mesh arrangement of the structured mesh
	 * @return Returns the enum that specifies the mesh arrangement
	 */
	StructuredArrangement getMeshArrangment()
	{
		return p_faceMeshStructuredArrangment;
	}
	
	/**
	 * @brief Function that is used to set the mesh algorithm for the 2D meshes
	 * @param algorithm The algorithm that will be used to create 2D meshes
	 */
	void setMeshAlgorithm(MeshAlgorthim algorithm)
	{
		p_meshingAlgorthim = algorithm;
	}
	
	/**
	 * @brief Function that retrieves the mesh algorithm that will be used for 2D meshes
	 * @return Returns an enum representing the algorithm that will be used.
	 */
	MeshAlgorthim getMeshAlgorithm()
	{
		return p_meshingAlgorthim;
	}
	
	/**
	 * @brief Function that is used to set the Blossom Recombination algorithm for 2D meshes
	 * @param state Set to true if GMSH should use the Blossom Algorithm to recombine the mesh
	 * 				into quads. If false, GMSH will use the "standard" algorithm.
	 */
	void setBlossomRecombinationState(bool state)
	{
		p_recombinationBlossom = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the Blossom Recombination algorithm state
	 * @return Returns true if GMSH should use the Blossom Algorithm for recombination. Otherwise,
	 * 			returns false if GMSH should use the "Standard" Algorithm.
	 */
	bool getBlossomRecombinationState()
	{
		return p_recombinationBlossom;
	}
	
	/**
	 * @brief Function that is used to set the state of GMSH using the Automatic Algorithm 
	 * 			for remeshing.
	 * @param state Set to True to allow GMSH to use the Automatic Algorithm for remeshing. Otherwise
	 * 				set to false to use the No Split algorithm.
	 */
	void setAutoRemeshingState(bool state)
	{
		p_remeshAuto = state;
	}
	
	/**
	 * @brief Function that is used in order retrieve the auto remeshing algorithm state
	 * @return Returns true if GMSH should use to the Automatic algorithm. Otherwise, returns 
	 * 			false if GMSH will use the No Split Algorithm
	 */
	bool getAutoRemeshingState()
	{
		return p_remeshAuto;
	}
	
	/**
	 * @brief Function that is used to specify the Mesh Parameterization algorithm that
	 * 			GMSH will be using.
	 * @param param An enum that will specify which Mesh Parameterization algorithm that GMSH
	 * 				will be using.
	 */
	void setRemeshParameter(MeshParametrization param)
	{
		p_remeshParam = param;
	}
	
	/**
	 * @brief Function that will retrieve the remesh parameterization algorithm setting
	 * @return Returns an enum to indicate which parameterization algorithm GMSH will use 
	 * 			when creating the mesh
	 */
	MeshParametrization getRemeshParameter()
	{
		return p_remeshParam;
	}
	
	/**
	 * @brief Function that will be used to set the number of smoothing steps GMSH will use 
	 * 			to create the mesh
	 * @param value A number between 0 and 255 that speficies the number of smoothing steps GMSH should use
	 * 				when constructing the mesh.
	 */
	void setSmoothingSteps(unsigned char value)
	{
		p_smoothingSteps = value;
	}
	
	/**
	 * @brief Function that is used to retrieve the number of smoothing steps
	 * @return Returns a number representing the number of smoothing steps GMSH uses when creating
	 * 			the mesh.
	 */
	unsigned char getSmoothingSteps()
	{
		return p_smoothingSteps;
	}
	
	/**
	 * @brief Function that is used to set the element size factor for the entire mesh. This is a global
	 * 			setting.
	 * @param value The element size scaling factor for the entire mesh.
	 */
	void setElementSizeFactor(double value)
	{
		p_elementSizeFactor = value;
	}
	
	/**
	 * @brief Function that is used to retrieve the mesh element size scaling factor.
	 * @return Returns a double that represents the mesh element size scaling factor
	 */
	double getElementSizeFactor()
	{
		return p_elementSizeFactor;
	}
	
	/**
	 * @brief Function that is used to set the smallest element size GMSH can use
	 * @param value Value that specifies the smallest element size GMSH can use.
	 */
	void setMinElementSize(double value)
	{
		p_minElementSize = value;
	}
	
	/**
	 * @brief Function that is used retrieve the smallest element size GMSH should use.
	 * @return Returns a number that represents the smallest element size GMSH should use
	 * 			for creating the mesh.
	 */
	double getMinElementSize()
	{
		return p_minElementSize;
	}
	
	/**
	 * @brief Function that is used to set the max element size that GMSH will use when creating the mesh
	 * @param value Value that is used to specify the max element size for meshing.
	 */
	void setMaxElementSize(double value)
	{
		p_maxElementSize = value;
	}
	
	/**
	 * @brief Function that is used in order to retrieve the max element size GMSH will use when 
	 * 			creating meshes
	 * @return Returns a number to represent the max element size of the mesh.
	 */
	double getMaxElementSize()
	{
		return p_maxElementSize;
	}
	
	/**
	 * @brief Function that is used in order to set the mesh element order. Currently, 1st and 2nd order
	 * 			meshes are supported.
	 * @param order The order that the mesh will be after creation
	 */
	void setElementOrder(unsigned int order)
	{
		if(order > 2)
			p_elementOrder = 2;
		else if (order == 0)
			p_elementOrder = 1;
		else
			p_elementOrder = order;
	}
	
	/**
	 * @brief Function that is used to retrieve the mesh element order
	 * @return Returns a number representing the mesh element order
	 */
	unsigned int getElementOrder()
	{
		return p_elementOrder;
	}
	
	/**
	 * @brief Function that is used to specify the number of passes GMSH will perform. THis is for
	 * 			remeshing the geometry.
	 * @param value A number that specifies the number of passes that GMSH will perform for meshing
	 */
	void setMultiplePasses(unsigned int value)
	{
		p_multiplePasses = value;
	}
	
	/**
	 * @brief Function that is used to retrieve the number of times GMSH will remesh the geometry.
	 * @return Returns a number which represents the number of times GMSH will remesh the geometry.
	 */
	unsigned int getMultiplePasses()
	{
		return p_multiplePasses;
	}
	
	/**
	 * @brief Function that is used to set the number of Llyod smoothing steps. THis only applies to the 
	 * 			Blossom Algorithm.
	 * @param value The number of Llyod smoothing steps GMSH will take when using the Blossom Algorithm
	 */
	void setLlyodSmoothingSteps(unsigned int value)
	{
		p_llyodSmoothingSteps = value;
	}
	
	/**
	 * @brief Function that is used in order to retrieve the number of Llyod smoothing steps 
	 * @return Returns a number that represents the number of Llyod Smoothing steps GMSH will use 
	 * 			when performing the Blossom Algorithm
	 */
	unsigned int getLlyodSmoothingSteps()
	{
		return p_llyodSmoothingSteps;
	}
	
	/**
	 * @brief Function that is used to set the save as VTK State
	 * @param state Set to true to save the mesh as a VTK file. Otherwise, set to false.
	 */
	void setSaveVTKState(bool state)
	{
		p_saveAsVTK = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the save as VTK State
	 * @return Returns true if the mesh should be saved as a VTK file. Otherwise, returns false.
	 */
	bool getSaveVTKState()
	{
		return p_saveAsVTK;
	}
	
	/**
	 * @brief Function that is used to set the save as BDF State
	 * @param state Set to true to save the mesh as a BDF file. Otherwise, set to false.
	 */
	void setSaveBDFState(bool state)
	{
		p_saveAsBDF = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the save as BDF State
	 * @return Returns true if the mesh should be saved as a BDF file. Otherwise, returns false.
	 */
	bool getSaveBDFState()
	{
		return p_saveAsBDF;
	}
	
	/**
	 * @brief Function that is used to set the save as CELUM State
	 * @param state Set to true to save the mesh as a CELUM file. Otherwise, set to false.
	 */
	void setSaveCELUMState(bool state)
	{
		p_saveAsCELUM = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the save as CELUM State
	 * @return Returns true if the mesh should be saved as a CELUM file. Otherwise, returns false.
	 */
	bool getSaveCELUMState()
	{
		return p_saveAsCELUM;
	}
	
	/**
	 * @brief Function that is used to set the save as CGNS State
	 * @param state Set to true to save the mesh as a CGNS file. Otherwise, set to false.
	 */
	void setSaveCGNSState(bool state)
	{
		p_saveAsCGNS = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the save as CGNS State
	 * @return Returns true if the mesh should be saved as a CGNS file. Otherwise, returns false.
	 */
	bool getSaveCGNSState()
	{
		return p_saveAsCGNS;
	}
	
	/**
	 * @brief Function that is used to set the save as DIFFPACK State
	 * @param state Set to true to save the mesh as a DIFFPACK file. Otherwise, set to false.
	 */
	void setSaveDIFFPACKSate(bool state)
	{
		p_saveAsDIFFPACK = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the save as DIFFPACK State
	 * @return Returns true if the mesh should be saved as a DIFFPACK file. Otherwise, returns false.
	 */
	bool getSaveDIFFPACKSate()
	{
		return p_saveAsDIFFPACK;
	}
	
	/**
	 * @brief Function that is used to set the save as Fourier State
	 * @param state Set to true to save the mesh as a Fourier file. Otherwise, set to false.
	 */
	void setSaveFourierState(bool state)
	{
		p_saveAsFourier = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the save as Fourier State
	 * @return Returns true if the mesh should be saved as a Fourier file. Otherwise, returns false.
	 */
	bool getSaveFourierState()
	{
		return p_saveAsFourier;
	}
	
	/**
	 * @brief Function that is used to set the save as GEO State
	 * @param state Set to true to save the mesh as a GEO file. Otherwise, set to false.
	 */
	void setSaveGEOState(bool state)
	{
		p_saveAsGEO = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the save as GEO State
	 * @return Returns true if the mesh should be saved as a GEO file. Otherwise, returns false.
	 */
	bool getSaveGEOState()
	{
		return p_saveAsGEO;
	}
	
	/**
	 * @brief Function that is used to set the save as INP State
	 * @param state Set to true to save the mesh as a INP file. Otherwise, set to false.
	 */
	void setSaveINPState(bool state)
	{
		p_SaveAsINP = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the save as INP State
	 * @return Returns true if the mesh should be saved as a INP file. Otherwise, returns false.
	 */
	bool getSaveINPState()
	{
		return p_SaveAsINP;
	}
	/**
	 * @brief Function that is used to set the save as IR3 State
	 * @param state Set to true to save the mesh as a IR3 file. Otherwise, set to false.
	 */
	void setSaveIR3State(bool state)
	{
		p_saveAsIR3 = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the save as IR3 State
	 * @return Returns true if the mesh should be saved as a IR3 file. Otherwise, returns false.
	 */
	bool getSaveIR3State()
	{
		return p_saveAsIR3;
	}
	
	/**
	 * @brief Function that is used to set the save as MAIL State
	 * @param state Set to true to save the mesh as a MAIL file. Otherwise, set to false.
	 */
	void setSaveMAILState(bool state)
	{
		p_saveAsMAIL = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the save as MAIL State
	 * @return Returns true if the mesh should be saved as a MAIL file. Otherwise, returns false.
	 */
	bool getSaveMAILState()
	{
		return p_saveAsMAIL;
	}
	
	/**
	 * @brief Function that is used to set the save as MESH State
	 * @param state Set to true to save the mesh as a MESH file. Otherwise, set to false.
	 */
	void setSaveMESHState(bool state)
	{
		p_saveAsMESH = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the save as MESH State
	 * @return Returns true if the mesh should be saved as a MESH file. Otherwise, returns false.
	 */
	bool getSaveMESHState()
	{
		return p_saveAsMESH;
	}
	
	/**
	 * @brief Function that is used to set the save as P3D State
	 * @param state Set to true to save the mesh as a P3D file. Otherwise, set to false.
	 */
	void setSaveP3DState(bool state)
	{
		p_saveAsP3D = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the save as P3D State
	 * @return Returns true if the mesh should be saved as a P3D file. Otherwise, returns false.
	 */
	bool getSaveP3DState()
	{
		return p_saveAsP3D;
	}
	
	/**
	 * @brief Function that is used to set the save as Partitioned Mesh State
	 * @param state Set to true to save the mesh as a Partitioned Mesh file. Otherwise, set to false.
	 */
	void setSavePartitionedMeshState(bool state)
	{
		p_saveAsPatitionedMesh = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the save as Partitioned Mesh State
	 * @return Returns true if the mesh should be saved as a Partitioned Mesh file. Otherwise, returns false.
	 */
	bool getSavePartitionedMeshState()
	{
		return p_saveAsPatitionedMesh;
	}
	
	/**
	 * @brief Function that is used to set the save as PLY2 State
	 * @param state Set to true to save the mesh as a PLY2 file. Otherwise, set to false.
	 */
	void setSavePLY2State(bool state)
	{
		p_saveAsPLY2 = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the save as PLY2 State
	 * @return Returns true if the mesh should be saved as a PLY2 file. Otherwise, returns false.
	 */
	bool getSavePLY2State()
	{
		return p_saveAsPLY2;
	}
	
	/**
	 * @brief Function that is used to set the save as STL State
	 * @param state Set to true to save the mesh as a STL file. Otherwise, set to false.
	 */
	void setSaveSTLState(bool state)
	{
		p_saveAsSTL = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the save as STL State
	 * @return Returns true if the mesh should be saved as a STL file. Otherwise, returns false.
	 */
	bool getSaveSTLState()
	{
		return p_saveAsSTL;
	}
	
	/**
	 * @brief Function that is used to set the save as SU2 State
	 * @param state Set to true to save the mesh as a SU2 file. Otherwise, set to false.
	 */
	void setSaveSU2State(bool state)
	{
		p_saveAsSU2 = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the save as SU2 State
	 * @return Returns true if the mesh should be saved as a SU2 file. Otherwise, returns false.
	 */
	bool getSaveSU2State()
	{
		return p_saveAsSU2;
	}
	
	/**
	 * @brief Function that is used to set the save as Tochnog State
	 * @param state Set to true to save the mesh as a Tochnog file. Otherwise, set to false.
	 */
	void setSaveTochnogState(bool state)
	{
		p_saveAsTochnog = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the save as Tochnog State
	 * @return Returns true if the mesh should be saved as a Tochnog file. Otherwise, returns false.
	 */
	bool getSaveTochnogState()
	{
		return p_saveAsTochnog;
	}
	
	/**
	 * @brief Function that is used to set the save as UNV State
	 * @param state Set to true to save the mesh as a UNV file. Otherwise, set to false.
	 */
	void setSaveUNVState(bool state)
	{
		p_saveAsUNV = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the save as UNV State
	 * @return Returns true if the mesh should be saved as a UNV file. Otherwise, returns false.
	 */
	bool getSaveUNVState()
	{
		return p_saveAsUNV;
	}
	
	/**
	 * @brief Function that is used to set the save as VRML State
	 * @param state Set to true to save the mesh as a VRML file. Otherwise, set to false.
	 */
	void setSaveVRMLState(bool state)
	{
		p_saveAsVRML = state;
	}
	
	/**
	 * @brief Function that is used to retrieve the save as VRML State
	 * @return Returns true if the mesh should be saved as a VRML file. Otherwise, returns false.
	 */
	bool getSaveVRMLState()
	{
		return p_saveAsVRML;
	}
};

#endif