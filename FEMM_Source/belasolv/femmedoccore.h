// femmeDoc.h : interface of the CFemmeDoc class
//
/////////////////////////////////////////////////////////////////////////////
#define muo 1.2566370614359173e-6
#define Golden 0.3819660112501051517954131656

class CFemmeDocCore
{

	

// Attributes
public:

	CFemmeDocCore();
	~CFemmeDocCore();

	// General problem attributes
	double  Precision;
	double  Depth;
	int		LengthUnits;
	BOOL    ProblemType;
	BOOL	Coords;

	// Axisymmetric external region parameters
	double extRo, extRi, extZo;
	
	CbelasolvDlg *TheView;
	
	// CArrays containing the mesh information
	int	BandWidth;
	CNode *meshnode;
	CElement	*meshele;

	int NumNodes;
	int NumEls;
	
	// lists of properties
	int NumBlockProps;
	int NumPBCs;
	int NumLineProps;
	int NumPointProps;
	int NumCircProps;
	int NumBlockLabels;					// Global variable that indicates The total number of black variables in the problem

	CMaterialProp	*blockproplist;
	CBoundaryProp	*lineproplist;
	CPointProp		*nodeproplist;
	CCircuit		*circproplist;
	CBlockLabel		*labellist;
	CCommonPoint	*pbclist;			//Global variable for storing the Periodic Boundary Condition points

	// stuff usually kept track of by CDocument
	char *PathName;// Stores the path name of the file to be open (This is the definition so far)
	

// Operations
public:

	BOOL LoadMesh();
	BOOL OnOpenDocument();
	BOOL Cuthill();
	BOOL SortElements();
	BOOL AnalyzeProblem(CBigLinProb &L);
	double ChargeOnConductor(int OnConductor, CBigLinProb &L);
	BOOL WriteResults(CBigLinProb &L);
	void CleanUp();

};

/////////////////////////////////////////////////////////////////////////////

double Power(double x, int n);
