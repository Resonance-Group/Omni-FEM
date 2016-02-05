/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */
#ifndef TSK
#define TSK


#include "jobdefs.h"

/*
	The TSKtask structure defines a set of analyses to be performed together.
	The analyses will share such things as the option values for themby the SPICE2 ".options" statement.
	The task will consist of a set of values for task-wide data and a linked list of the individual jobs to be performed
	as a part of the task.
	For convenience and to present a more uniform interface to the front enf, the ".options" statement has been presented as an analysis itself
	and ths would normally be in the linked list of jobs to perform, but has been special cased.
	There must be only one ".options" job in the task and the values from all ".options" statements must be merged to produce that single job.
	These options must be readily accessible at the start of the task ad thus the ".options" analysis has been singled out and placed directly in the TSKtask structure.
	The ".options" analysis then uses the TSKtask structure directly as its own job strucutre rather than having a seperate one.
*/
typedef struct {
	/*
		The standard job header for the ".otions" jo that applies to the entire task
	*/
    JOB taskOptions;    /* job structure at the front to hold options */
    
	
	/*
		A linked list of jobs structures of all of the analyses to be performed as part of this task
	*/
	JOB *jobs;


	/*
		The name of the task as assigned by the front end
	*/
    char *TSKname;


	/*
		The default temperature at which instances will operate in this task
	*/
    double TSKtemp;


	/*
		The default temperature at which model parameters will be considered to have been measured
	*/
    double TSKnomTemp;


	/*
		The maximum integration order permitted during transient simualtion
	*/
    int TSKmaxOrder;       


	/*
		The integration method used during the transient simulations of this task
	*/
    int TSKintegrateMethod; 
    
	
	/*
		The type of analysis currently in progress in this task. 
		This field is not currenty used and should be replaced by a JOB pointer
		in a future version
	*/
	int TSKcurrentAnalysis; 

/* defines for the value of  TSKcurrentAnalysis */
#define DOING_DCOP 1
#define DOING_TRCV 2
#define DOING_AC   4
#define DOING_TRAN 8


	/*
		A flag to indicate whether the user wishes inactive device bypass to be enabled
		or disabled assuming it was not disabled at compile time.
	*/
    int TSKbypass;


	/*
		The maximum number of Newton-Rapheson iterations that will be taken before giving up in a 
		DC operating point analysis, A DC transfer curve analysis, and a single transient timepoint.
	*/
    int TSKdcMaxIter;       /* iteration limit for dc op.  (itl1) */
    int TSKdcTrcvMaxIter;   /* iteration limit for dc tran. curv (itl2) */
    int TSKtranMaxIter;     /* iteration limit for each timepoint for tran*/
                            /* (itl4) */

	/*
		The number of steps the source stepping or gmin stepping method should take
		in attempting to find an operating point
	*/
    int TSKnumSrcSteps;     /* number of steps for source stepping */
    int TSKnumGminSteps;    /* number of steps for Gmin stepping */
    
	
	/*
		The per task tolerances to be used in the correspondingly named fields of the CKT circuit structure during the analysis
	*/
	double TSKabstol;
	double TSKpivotAbsTol;
	double TSKpivotRelTol;
	double TSKreltol;
	double TSKchgtol;
	double TSKvoltTol;


	double TSKminBreak;
#ifdef NEWTRUNC
    double TSKlteReltol;
    double TSKlteAbstol;
#endif /* NEWTRUNC */


	/*
		A small user-specifyable minimal conductance used in several mdels when a zero conductance is not acceptable.
	*/
    double TSKgmin;


	/*
		The minimum timestep permitted during transient analysis before the program gives up.
		This is currently overwritten by the transient analysis code becuase of problems with users setting 
		unrealisticly sall values and causing simulations to run forever
	*/
    double TSKdelmin;
    

	/*
		The default values for MOSFET length, width, drain area, and source area for this circuit
	*/
    double TSKdefaultMosL;
    double TSKdefaultMosW;
    double TSKdefaultMosAD;
    double TSKdefaultMosAS;


	/*
		A flag to indicate whether unsymmetric but sometimes effective limiting of SPICE2 should
		be used or whether the correct symmetric limiting of SPICE3 should used.
	*/
    unsigned int TSKfixLimit:1;



	double TSKtrtol;
    unsigned int TSKnoOpIter:1; /* no OP iterating, go straight to gmin step */
    unsigned int TSKtryToCompact:1; /* flag for LTRA lines */
    unsigned int TSKbadMos3:1; /* flag for MOS3 models */
    unsigned int TSKkeepOpInfo:1; /* flag for small signal analyses */
}TSKtask;

#endif /*TSK*/
