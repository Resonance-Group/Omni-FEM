/*
 * Copyright (c) 1985 Thomas L. Quarles
 */

/*
	The CKTcircuit structure is closet thing SPICE3 has to global data.
	Due to the decision to make SPICE3 handle multiple circuits completely
	indepednently, actual gobal data would provide and unwanted connection between circuits, 
	so all such data has been moved into this strucutre. 
	As such, this structure has become a sort of "catch-all" for global data values as well as
	data for algorithms or packages which don't have enough data to have been worth generating a private data strucutre
	for them yet.
	Thus, this structure is both the most widely known and one of the most frequenctly changing
	structures when non device-specific changes are made.
*/
#ifndef CKT
#define CKT "CKTdefs.h $Revision: 1.13 $  on $Date: 89/04/05 13:09:39 $ "

#define MAXNUMDEVS 32
extern int DEVmaxnum;
#define MAXNUMDEVNODES 4

#include "smpdefs.h"
#include "ifsim.h"
#include "acdefs.h"
#include "gendefs.h"
#include "trcvdefs.h"
#include "optdefs.h"
#include "sen2defs.h"
#include "pzdefs.h"

/*
	The CKTnode structure is used to describe an equation in the circuit.
	Generally, a node will correspond to a node in the circuit, but equations
	added for voltage sources will also generate equations and thus a CKTnode 
	structure.
*/
typedef struct sCKTnode {
	/*
		This is the name of the node and will be a unique identifier supplied by the front end
	*/
    IFuid name;



	/*
		This is an indication of the type of data reqpresented by the equation.
		Current legal values are NODE_VOTLAGE and NODE_CURRENT for equations
		representing the voltage at a node and equations representing the current through 
		a device repectively.
	*/
    int type;



#define SP_VOLTAGE 3
#define SP_CURRENT 4
#define NODE_VOLTAGE SP_VOLTAGE
#define NODE_CURRENT SP_CURRENT


	// This is the equation number assigned to the equation
    int number;


	// This is the initial condition specification provided by the user for hte node in question
    double ic;


	/*
		This is the suggested initial voltage for a node as provided bu the user in a ".nodeset" statement
	*/
    double nodeset;


	/*
		If either a ".nodeset" or ".ic" statement applies to this node, this is a pointer to the numberic
		value field of the sparse matrix corresponding to the diagonal element at location (number, number).
	*/
    double *ptr;


	/*
		This provide a pointer to the node structure representing the next higher numbered equation
	*/
    struct sCKTnode *next;


	/*
		These are on bit flags which indicate whether this equation has been the subject of a ".ic" or ".nodeset" statement.
	*/
    unsigned int icGiven:1;
    unsigned int nsGiven:1;
} CKTnode;

/* defines for node parameters */
#define PARM_NS 1
#define PARM_IC 2
#define PARM_NODETYPE 3


/*
	This is the CKTcircuit structure. This is the closest that SPICE3 comes to as a global data structure.
	Due to the decision to make SPICE3 handle multiple circuit completely indepednently, actual gloable data would provide an
	unwanted connection between circuits, so all such data has been moved into this structure. 
	As such, this structure has become a sort of "catch-all" for global data values as well as data for algorithms or packages which don't have enough
	data to have been worth generating a private data strucutre for them yet. 
	Thus,this structure is both the most widely known and one of the most frequenctly changing strucutres when non device-specific changes are made.
*/
typedef struct {
	
	
	
	/*
		This array provides pointer to the first model of each device types.
		Each of these pointers thus points to the head of a linked lisdt of a
		different type of device model. The definition of this array is the only place
		in SPICE 3 where the numeber of device types supported is limitied and that is
		governed by MAXNUMDEVS
	*/
    GENmodel *CKThead[MAXNUMDEVS];	
    


	/*
		This is the accounting structure used to accumulate statistics about the simulation.
		Statistics accumulated include timing, iteration counts, and timepoint counts.
		Additional statistics, if collected, should be aded to this stucture (STATistics)
	*/
	STATistics *CKTstat;			
   


	/*
		CKTstates, and the macros CKTstate[i] for all integer values i, are used to store the per timepoint data.
		EAch device will research porions of each of thwese vecotrs in its DEVsteup routine and the hihger level code will allocate
		them and manipulate them between timepoints so that vector i always contains data from the ith previous timepoint
		where the 0th previous timepoint is defined as the current point.
	*/
	double *(CKTstates[8]);
#define CKTstate0 CKTstates[0]
#define CKTstate1 CKTstates[1]
#define CKTstate2 CKTstates[2]
#define CKTstate3 CKTstates[3]
#define CKTstate4 CKTstates[4]
#define CKTstate5 CKTstates[5]
#define CKTstate6 CKTstates[6]
#define CKTstate7 CKTstates[7]
    


	/*
		CKTtime stores the current simulation time during transient analysis
	*/
	double CKTtime;



	/*
		CKTdelta contains the current timestep while the array CKTdeltaOld contains the current
		timestep as its 0th element along the 6 previous timesteps in order
	*/
    double CKTdelta;
    double CKTdeltaOld[7];



	/*
		CKTtemp is the default temperature for devices in the current simulation.
		Any device which does not have an overriding temperature specification will operate at the 
		temperature CKTtemp.
		CKTnomTemp is the default parameter measurement temperature for the models and all model
		parameter will be assumed to be measuresd at this temperature unless overridden by the Tnom 
		specification on the model
	*/
    double CKTtemp;
    double CKTnomTemp;



	/*
		Obsolete. REtained for backwards compatibility and conversion purposes.
		This is the calue of thethermal voltage at temperature CKTtemp
	*/
    double CKTvt;



	/*
		These arrays (CKTag and CKTagp) contains the coefficients for the corrector and predictor, respectively, of the
		variable timestep integration algorithm
	*/
    double CKTag[7];        /* the gear variable coefficient matrix */
#ifdef PREDICTOR
    double CKTagp[7];       /* the gear predictor variable coefficient matrix */
#endif /*PREDICTOR*/



	/*
		CKTorder is the current integration order and varies as the simulation progresses. 
		CKTmaxOrder is the maximum value CKTorder may take on, either becuase the user or program has limited it.
	*/
    int CKTorder;           /* the integration method order */
    int CKTmaxOrder;        /* maximum integration method order */





	/*
		This is the sparse matric for current circuit.
		Details of this structure are in the sparse matrick strucutre description
	*/
    SMPmatrix *CKTmatrix;   /* pointer to sparse matrix */


	/*
		This is a bit vector containing status information on the numeric package.
		Various bits indicate such information as whether the numeric package need to reorder the matrix, whether
		the package has been initialized completely or whether additional data needs to be allocates and similiar
		data for ac, pole-zero, and other algorithms of the numeric package
	*/
    int CKTniState;         /* internal state */



	/*
		CKTrhs, CKTrhsOld, CKTrhsSpare, CKTirhs, CKTirhsOld, CKTirhsSpare
		These vectors form a 2x3 grid of possible right hand side vectors for the matrix package.
		The three with names having prefix CKTi are the imaginary parts of the right hand sides used in complex calculations, while
		those withouth the i are real parts.
		The vectors ending in rhs are the normal right hand side to be loaded by device routines. 
		The vectors ending in rhsOld are the right hand side vector from the previous interation which now contain the solution
		for that interation.
		The vectors ending in rhsSpare are extra vectors of the same size required by the SMP package for its own internal use.
	*/
    double *CKTrhs;         /* current rhs value - being loaded */
    double *CKTrhsOld;      /* previous rhs value for convergence testing */
    double *CKTrhsSpare;    /* spare rhs value for reordering */
    double *CKTirhs;        /* current rhs value - being loaded (imag) */
    double *CKTirhsOld;     /* previous rhs value (imaginary)*/
    double *CKTirhsSpare;   /* spare rhs value (imaginary)*/




#ifdef PREDICTOR
    double *CKTpred;        /* predicted solution vector */
    double *CKTsols[8];     /* previous 8 solutions */
#endif /* PREDICTOR */



	/*
		These values were added to the structe to support sensitivity analysis and are described in the sensitivity report
	*/
    double *CKTrhsOp;      /* opearating point values */
    double *CKTsenRhs;      /* current sensitivity rhs  values */
    double *CKTseniRhs;      /* current sensitivity rhs  values (imag)*/


	/*
		This indicates whcih integration method is to be used by SPICE3.
		Constants have been defined for the trapezoidal and gear methods, all other values are currently 
		uassigned and illegal
	*/
	int CKTintegrateMethod; /* the integration method to be used */
#define TRAPEZOIDAL 1
#define GEAR 2

/*
 *  symbolic constants for CKTniState
 *      Note that they are bitwise disjoint
 */

#define NISHOULDREORDER 0x1
#define NIREORDERED 0x2
#define NIUNINITIALIZED 0x4
#define NIACSHOULDREORDER 0x10
#define NIACREORDERED 0x20
#define NIACUNINITIALIZED 0x40
#define NIDIDPREORDER 0x100
#define NIPZSHOULDREORDER 0x200



	/*
		This is the number of equations currently defined.
		Since the ground node is equation 0, this is always one
		greater thena the largest equation number
	*/
    int CKTmaxEqNum;



	/*
		This is obsolete value. 
		This value is used by restart code to find the correct analysis simulation with.
		Since the code has been enhanced to support more then 1 anaylsis of a given type, this
		variable no longer contains sufficient information, but has not been removed for backwards compatability
	*/
    int CKTcurrentAnalysis; /* the analysis in progress (if any) */



	/*
		CKTnode points to the first element in the linked list of node structures
		which describe the equations of the circuit.
		CKTlastNode points to the last node structure on the list headed by CKTnodes and is used
		for fast addition on the end of the list, since the list is kept sorted by node
		number and full list searches are not performed for efficiency reasons.
	*/
    CKTnode *CKTnodes;
    CKTnode *CKTlastNode;



#define NODENAME(ckt,nodenum) CKTnodName(ckt,nodenum)


	/*
		CKTnumStates is the size of the CKTstates vectors in units of the size of a double
		precision variable.
	*/
    int CKTnumStates;


	/*
		CKTmode is a bit vector containing data on the state machine used to control anlyses.
		The low order 4 bits are used to determine what type of analysis is being performed:
		AC
		DC
		Transient

		The next 4 bits enumerate the types of DC analyses that may be in progress, operating point,
		transfer curve, or transient operating point.
		The next 8 are the state of the Nliter state machine and control the source of the voltages seen
		by the devices in the load routines.
		Finally, the next bit indicates the presence of the UIC flag on the transient command and the forced 
		use of I.C. given without a full operating point analysis
	*/
    long CKTmode;

/* defines for CKTmode */

/* old 'mode' parameters */
#define MODE 0x3
#define MODETRAN 0x1
#define MODEAC 0x2

/* old 'modedc' parameters */
#define MODEDC 0x70
#define MODEDCOP 0x10
#define MODETRANOP 0x20
#define MODEDCTRANCURVE 0x40

/* old 'initf' parameters */
#define INITF 0x3f00
#define MODEINITFLOAT 0x100
#define MODEINITJCT 0x200
#define MODEINITFIX 0x400
#define MODEINITSMSIG 0x800
#define MODEINITTRAN 0x1000
#define MODEINITPRED 0x2000

/* old 'nosolv' paramater */
#define MODEUIC 0x10000l


	/*
		This is the flag which has a non-zero value if inactive device bypass is to be permitted 
		in decives if the code to do so has been compiled in
	*/
    int CKTbypass;


	/*
		CKTdcMaxlter, CKTtrcvMaxIter, CKTamMaxIter

		These three values determine the maximum number of iterations to be expected respectively
		on the computation of an operating point before giving up, the computation of any 1 point
		in a DC transfer curve analysis before giving up, and the computation of a single timepoint
		in a transient analysis before giving up and reducing the timestep
	*/
    int CKTdcMaxIter;       /* iteration limit for dc op.  (itl1) */
    int CKTdcTrcvMaxIter;   /* iteration limit for dc tran. curv (itl2) */
    int CKTtranMaxIter;     /* iteration limit for each timepoint for tran*/
                            /* (itl4) */


	/*
		CKTbreaks is the actual breakpoint table and consists of an allocated array
		of double containing all of the current breakpoints including at least one and possibly 
		2 previous points.
		CKTbreakSize is the actual size of the table in units of the size of a double precision value.
	*/
    int CKTbreakSize;
    int CKTbreak;



	/*
		This is the saved timestep from before the step was cut to hit a breakpoint.
		An effort is made to return the analysis to this stepsize immediately after the breakpoint to 
		minimize the distruption caused by the breakpoint
	*/
    double CKTsaveDelta;



	/*
		This is the minumu amount of time by which 2 potential breakpoints must
		be seperated in order to considered distinct.
		Whenever 2 breakpoints are closer together than this amount, the later of the 
		2 is discarded
	*/
    double CKTminBreak;



	/*
		
	*/
    double *CKTbreaks;



	/*
		CKTabstol, CKTchgtol, CKTvoltTol, CKTpivotAbsTol

		These 4 tolerances are the absolute error tolerances on, respectively,
		current, charge, voltage, and minimum acceptable pivot element on the matrix.
	*/
    double CKTabstol;
	double CKTchgtol;
	double CKTvoltTol;
	double CKTpivotAbsTol;
	
	

	/*
		These are the relative error tolerance and the factor by which a pivot may be nu,erically
		non-optimal value and still be chosen for its sparseness preserving properties.
	*/
	double CKTreltol;
    double CKTpivotRelTol;
    
    
#ifdef NEWTRUNC
    double CKTlteReltol;
    double CKTlteAbstol;
#endif /* NEWTRUNC */


	/*
		This is a small "minimal" conductance which is used in several device models 
		to ensure that they do not create zero conductance branches.
		This is NOT to be confused with the Gmin used in the Gmin stepping algorithm.
	*/
    double CKTgmin;



	/*
		This is the minimum timestep which is allowed.
		Timsteps below this value will results in "Timestep Too Small" error.
		It is currently set unconditionally to 1 * 10^-9 times the largest timestep allowed by the user.
	*/
    double CKTdelmin;



	/*
		This is the factor which is used to account for the fact that the truncation error estimation
		algorithm tends to be too conservative by a significant factor.
		The value is currently defaulted to the value 7 as chosen by Nagel.
	*/
    double CKTtrtol;



	/*
		CKTinitTime, CKTstep, CKTmaxStep, CKThalTime

		These 4 variables control a transient simulation and give the time at whcih output should start, the
		user requested tiemsteip, the upper limit on internal timesteps, and the ending time of a simualtion.
		These are copied into these variables from the transient analysis specific structure at the start of the transient simulation since too
		many reference to them are made in too much code to make the proper check that the structure pointed to by CKTcurJob is of the correct
		type and refence through it to these parameters.
		At some point in the future, the necessary checks should be made unneccessary by a thorough testing of the code to eliminate other
		places which find these good approximate vlaues and use them for other purposes and then replace these with macros which reference
		the proper field in the substructure.
	*/
    double CKTfinalTime;
    double CKTstep;
    double CKTmaxStep;
    double CKTinitTime;



	/*
		This is the frequency of the current AC analysis.
		This should probably be replaced by a macro referencing AC analysis structure directly, but
		has been left here for backward compatabiity.
	*/
    double CKTomega;



	/*
		This is the fator by which all independent source values must be multipied before loading the
		right hand side vector to implement the source stepping method.
	*/
    double CKTsrcFact;



	/*
		This is the Gmin of the Gmin stepping method not the be confused with the CKTgmin described above.
	*/
    double CKTdiagGmin;



	/*
		These are the number of steps to be taken in the source stepping and Gmin stepping methods respectively.
	*/
    int CKTnumSrcSteps;
    int CKTnumGminSteps;



	/*
		This is a flag which is incremented by a device code when it is determined that the current iteration has
		not or will not produce a correct solution or that the iteration has not converged and this another iteration will be forced.
	*/
    int CKTnoncon;



	/*
		CKTdefaultMosL, CKTdefaultMosW, CKTdefaultMosAD, CKTdefaulMosAS

		These 4 variables contain the user specified or system provided efaults for the 
		length, width, drain area, and source area respectively of MOSFETS. They don't really fit
		in well with the structure of SPICE3, but are needed for backward compatability with SPICE2 
		and this structure is the only place they can be put where all the MOS models will have access to them.
	*/
    double CKTdefaultMosL;
    double CKTdefaultMosW;
    double CKTdefaultMosAD;
    double CKTdefaultMosAS;



	/*
		THis is a one bit flag to indicate that nodeset lines have occured in the current circuit and
		therefor a second convergance iteration will be required in the DC analysis
	*/
    unsigned int CKThadNodeset:1;



	/*
		This is a simple flag to indicate that the MOSFET limiting should be performed in the same way as in SPICE2
		which included an error making it unsymmetrical, but inadvertently helping the convergence of many circuit.
		Setting this flag to 1 will emulate the old performance.
	*/
    unsigned int CKTfixLimit:1; /* flag to indicate that the limiting of 
                                 * MOSFETs should be done as in SPICE2 */



	 /* 
		flag to indicate not to try the operating
		point brute force, but to use gmin stepping
		first 
	*/
    unsigned int CKTnoOpIter:1; 



	/* flag to indicate if CKTsetup done */
    unsigned int CKTisSetup:1;



	/*
		This is a pointer to the JOB structure for the analysis currently being performed.
		This will be set in CKTdoJob before the analysis specific subrountine is called.
	*/
    JOB *CKTcurJob;



	/*
		This is a pointer to the structure providing information about any sensitivity analysis being
		performed concurrently with the current analysis.
		This pointer will be set in CKTdoJOb and be used only by code related to sensitivity as describes 
		in the seperate sensitivity documentation.
	*/
    SENstruct *CKTsenInfo;



	/* 
		list of all accepted timepoints in the
		current transient simulation 
	*/
    double *CKTtimePoints;	



	/* 
		list of all timesteps in the current
		transient simulation 
	*/
    double *CKTdeltaList;



	/* 
		size of above lists 
	*/
    int CKTtimeListSize;



	/* 
		current position in above lists 
	*/
    int CKTtimeIndex;



	/* 
		amount to increment size of above arrays
		when you run out of space 
	*/
    int CKTsizeIncr;



	/* 
		try to compact past history for LTRA
		lines 
	*/
    unsigned int CKTtryToCompact:1; 



	/* Use old, unfixed MOS3 equations */
    unsigned int CKTbadMos3:1; 



	/* flag for small signal analyses */
    unsigned int CKTkeepOpInfo:1; 



	/* Non-convergent node number */
    int CKTtroubleNode;	



	/* Non-convergent device instance */
    GENinstance *CKTtroubleElt;	

} CKTcircuit;

int ACan( CKTcircuit *, int );
int ACaskQuest( CKTcircuit *, GENERIC *, int , IFvalue *);
int ACsetParm( CKTcircuit *, GENERIC *, int , IFvalue *);
int CKTacDump( CKTcircuit *, double , GENERIC *);
int CKTacLoad( CKTcircuit *);
int CKTaccept( CKTcircuit *);
int CKTacct( CKTcircuit *, GENERIC *, int , IFvalue *);
int CKTask( GENERIC *, GENERIC *, int , IFvalue *, IFvalue *);
//int CKTaskAnalQ( GENERIC *, GENERIC *, int , IFvalue *, IFvalue *);
int CKTaskNodQst( GENERIC *, GENERIC *, int , IFvalue *, IFvalue *);
int CKTbindNode( GENERIC *, GENERIC *, int , GENERIC *);
void CKTbreakDump( CKTcircuit *);
int CKTclrBreak( CKTcircuit *);
int CKTconvTest( CKTcircuit *);
int CKTcrtElt( GENERIC *, GENERIC *, GENERIC **, IFuid );
int CKTdelTask( GENERIC *, GENERIC *);
int CKTdestroy( GENERIC *);
//int CKTdltAnal( GENERIC *, GENERIC *, GENERIC *);
int CKTdltInst( GENERIC *, GENERIC *);
int CKTdltMod( GENERIC *, GENERIC *);
int CKTdltNod( GENERIC *, GENERIC *);
int CKTdoJob( GENERIC *, int , GENERIC *);
void CKTdump( CKTcircuit *, double, GENERIC *);
int CKTfndAnal( GENERIC *, int *, GENERIC **, IFuid , GENERIC *, IFuid );
int CKTfndBranch( CKTcircuit *, IFuid);
int CKTfndDev( GENERIC *, int *, GENERIC **, IFuid , GENERIC *, IFuid );
int CKTfndMod( GENERIC *, int *, GENERIC **, IFuid );
int CKTfndNode( GENERIC *, GENERIC **, IFuid );
int CKTfndTask( GENERIC *, GENERIC **, IFuid  );
int CKTground( GENERIC *, GENERIC **, IFuid );
int CKTic( CKTcircuit *);
int CKTinit( GENERIC **);
int CKTinst2Node( GENERIC *, GENERIC *, int , GENERIC **, IFuid *);
int CKTlinkEq(CKTcircuit*,CKTnode*);
int CKTload( CKTcircuit *);
int CKTmapNode( GENERIC *, GENERIC **, IFuid );
int CKTmkCur( CKTcircuit  *, CKTnode **, IFuid , char *);
int CKTmkNode(CKTcircuit*,CKTnode**);
int CKTmkVolt( CKTcircuit  *, CKTnode **, IFuid , char *);
int CKTmodAsk( GENERIC *, GENERIC *, int , IFvalue *, IFvalue *);
int CKTmodCrt( GENERIC *, int , GENERIC **, IFuid );
int CKTmodParam( GENERIC *, GENERIC *, int , IFvalue *, IFvalue *);
int CKTnames(CKTcircuit *, int *, IFuid **);
int CKTnewAnal( GENERIC *, int , IFuid , GENERIC **, GENERIC *);
int CKTnewEq( GENERIC *, GENERIC **, IFuid );
int CKTnewNode( GENERIC *, GENERIC **, IFuid );
int CKTnewTask( GENERIC *, GENERIC **, IFuid );
IFuid CKTnodName( CKTcircuit *, int );
void CKTnodOut( CKTcircuit *);
CKTnode * CKTnum2nod( CKTcircuit *, int );
int CKTop(CKTcircuit *, long, long, int );
int CKTpModName( char *, IFvalue *, CKTcircuit *, int , IFuid , GENmodel **);
int CKTpName( char *, IFvalue *, CKTcircuit *, int , char *, GENinstance **);
int CKTparam( GENERIC *, GENERIC *, int , IFvalue *, IFvalue *);
int CKTpzFindZeros( CKTcircuit *, PZtrial **, int * );
int CKTpzLoad( CKTcircuit *, SPcomplex * );
int CKTpzSetup( CKTcircuit *, int);
int CKTsenAC( CKTcircuit *);
//int CKTsenComp( CKTcircuit *);
int CKTsenDCtran( CKTcircuit *);
//int CKTsenLoad( CKTcircuit *); // TODO: Only instance of "function" found. Check to ensure definition no longer used
void CKTsenPrint( CKTcircuit *); // TODO: No function definition found??? Used in code?
int CKTsenSetup( CKTcircuit *);	// TODO: Check for removal of function. No definition found
//int CKTsenUpdate( CKTcircuit *);
int CKTsetAnalPm( GENERIC *, GENERIC *, int , IFvalue *, IFvalue *);
int CKTsetBreak( CKTcircuit *, double );
int CKTsetNodPm( GENERIC *,GENERIC *, int , IFvalue *, IFvalue *);
int CKTsetOpt( GENERIC *, GENERIC *, int , IFvalue *);
int CKTsetup( CKTcircuit *);
//int CKTtemp( CKTcircuit *);
char *CKTtrouble(GENERIC *, char *);
void CKTterr( int , CKTcircuit *, double *);
int CKTtrunc( CKTcircuit *, double *);
int CKTtypelook( char *);
int DCOaskQuest( CKTcircuit *, GENERIC *, int , IFvalue *);
int DCOsetParm( CKTcircuit  *, GENERIC *, int , IFvalue *);
int DCTaskQuest( CKTcircuit *, GENERIC *, int , IFvalue *);
int DCTsetParm( CKTcircuit  *, GENERIC *, int , IFvalue *);
//int DCop( CKTcircuit *);
int DCtrCurv( CKTcircuit *, int );
int DCtran( CKTcircuit *, int );
int DISTOan(CKTcircuit *, int);
int NOISEan(CKTcircuit *, int);
int PZan( CKTcircuit *, int );
int PZinit( CKTcircuit * );
int PZpost( CKTcircuit * );
int PZaskQuest( CKTcircuit *, GENERIC *, int , IFvalue *);
int PZsetParm( CKTcircuit *, GENERIC *, int , IFvalue *);
//int SENaskQuest( CKTcircuit *, GENERIC *, int , IFvalue *);
void SENdestroy( SENstruct *);
//int SENsetParm( CKTcircuit *, GENERIC *, int , IFvalue *);
//int SENstartup( CKTcircuit *);
int SPIinit( IFfrontEnd *, IFsimulator **);
char * SPerror( int );
int TFanal( CKTcircuit *, int );
int TFaskQuest( CKTcircuit *, GENERIC *, int , IFvalue *);
int TFsetParm( CKTcircuit *, GENERIC *, int , IFvalue *);
int TRANaskQuest( CKTcircuit *, GENERIC *, int , IFvalue *);
int TRANsetParm( CKTcircuit *, GENERIC *, int , IFvalue *);
int TRANinit(CKTcircuit *, JOB *);
int NIacIter( CKTcircuit * );
int NIcomCof( CKTcircuit * ); 
int NIconvTest(CKTcircuit * );
void NIdestroy(CKTcircuit * );
int NIinit( CKTcircuit  * );
int NIintegrate( CKTcircuit *, double *, double *, double , int );
int NIiter( CKTcircuit * , int );
int NIpzMuller(PZtrial **, PZtrial *);
int NIpzComplex(PZtrial **, PZtrial *);
int NIpzSym(PZtrial **, PZtrial *);
int NIpzSym2(PZtrial **, PZtrial *);
int NIreinit( CKTcircuit *);
int NIsenReinit( CKTcircuit *);

extern IFfrontEnd *SPfrontEnd;

#endif /*CKT*/
