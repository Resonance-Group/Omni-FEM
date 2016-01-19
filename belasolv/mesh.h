#define PI 3.141592653589793238462643383
#define eo 8.85418781762e-12
#define AXISYMMETRIC 1
#define PLANAR 0

class CNode
{
	public:
		
	double x, y;
		int bc;
		int InConductor;

};

class CElement
{
	public:

		int p[3];		// nodes at the corners of the element
		int e[3];		// boundary condition applied to each edge of the element
		int blk;		// block property applied to the element
		int lbl;		// block label associated with the element

};

class CBlockLabel
{
	public:

		double x;			// The x-point of the block
		double y;			// The y-point of the block
		double MaxArea;
		int BlockType;
		int InGroup;		// The Group indicates what mesh region the label is localed in
		BOOL IsExternal;
		BOOL IsDefault;

};

class CCommonPoint
{
	public:
	int x, y, t;

};

/////////////////////////////////////////////////////////////////////////////
// Classes that hold property data:  CMaterialProp, CBoundaryProp, CPointProp

class CMaterialProp
{
	public:

	double ex, ey;		// permittivity, relative
		double qv;			// charge density, C/m^3

};

class CBoundaryProp
{
	public:
	
		int BdryFormat;			// type of boundary condition we are applying
								// 0 = fixed voltage
								// 1 = mixed BC
								// 2 = surface charge
								// 3 = periodic
								// 4 = antiperiodic

		double V;				// set value of V for BdryFormat=0;
		double qs;				// surface charge density
	double c0, c1;			// coefficients for mixed BC

};

class CPointProp
{
	public:

		double V;			// fixed nodal voltage 
		double qp;		// point current density;

};

class CCircuit
{
	public:

	double V, q;
		int CircType;

};
