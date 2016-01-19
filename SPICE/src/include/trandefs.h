/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */
#ifndef TRAN
#define TRAN


#include "jobdefs.h"
#include "tskdefs.h"
    /*
    /* TRANdefs.h - defs for transient analyses */

/*
	The TRANan structure contains the data necessary to control a transient analysis.
	The first 3 fields are the standard JOB header
*/
typedef struct {
	/*
		The standard JOB header
	*/
    int JOBtype;
    JOB *JOBnextJob;
    char *JOBname;



	/*
		The time at which the transient simulation should end
	*/
    double TRANfinalTime;



	/*
		The user suggested time step for the transient simulation
	*/
    double TRANstep;



	/*
		The user specified or program defualt maximum internal time step
	*/
    double TRANmaxStep;



	/*
		The first time at whcih output data should be stored
	*/
    double TRANinitTime;



	/*
		A word that may contain the "UIC" flag to indicate that the initial conditions supplied in the
		specification are to replace an operating point analysis before the start of the transient
		analysis.
	*/
    long TRANmode;



	/*
		The plot structure returned by OUTpBeginPlot which needs to be stored in the event the 
		analysis is paused or resumed
	*/
    GENERIC * TRANplot;
} TRANan;

#define TRAN_TSTART 1
#define TRAN_TSTOP 2
#define TRAN_TSTEP 3
#define TRAN_TMAX 4
#define TRAN_UIC 5
extern int TRANsetParm();
extern int TRANaskQuest();
#endif /*TRAN*/
