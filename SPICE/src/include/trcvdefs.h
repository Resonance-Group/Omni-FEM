/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */
#ifndef DCTR
#define DCTR


#include "jobdefs.h"
#include "tskdefs.h"
#include "gendefs.h"
    /*
     * structures used to describe D.C. transfer curve analyses to
     * be performed.
     */

#define TRCVNESTLEVEL 2 /* depth of nesting of curves - 2 for spice2 */

/*
	The TRCV structure contains the data necessary to control a sensitivity analysis.
*/
typedef struct {
	/*
		Standard JOB header
	*/
    int JOBtype;
    JOB *JOBnextJob;
    char *JOBname;



	/*
		The array contains the starting voltage or current values for each of the 
		sources to be swept
	*/
    double TRCVvStart[TRCVNESTLEVEL];   /* starting voltage/current */



	/*
		This array contains the final voltage or current values for each of the sources
		to be swept
	*/
    double TRCVvStop[TRCVNESTLEVEL];    /* ending voltage/current */



	/*
		This aray contains the step to be added to the value of each of the sources
		as it progresses from TRCVvStart to TRCVvStop
	*/
    double TRCVvStep[TRCVNESTLEVEL];    /* voltage/current step */



	/*
		This array is used to save the original DC values of the sources while transfer
		curve values are beign put into their places during the course of the analysis.
		When the analysis is over, these values must be restored to their original places.
	*/
    double TRCVvSave[TRCVNESTLEVEL];    /* voltage of this source BEFORE 
                                         * analysis-to restore when done */
    


	/*
		An array containing the names of the sourcesto be swept
	*/
    IFuid TRCVvName[TRCVNESTLEVEL];     /* source being varied */



	/*
		A pointer to the GENinstance structure for the individual sources to be swept
	*/
    GENinstance *TRCVvElt[TRCVNESTLEVEL];   /* pointer to source */



	/*
		The type of each element
	*/
    int TRCVvType[TRCVNESTLEVEL];   /* type of element being varied */



	/*
		An array of flags to indicate to the transfer curve analysis code which nesting levels actually
		have data stored in them and which have been left empty so that the empty nesting level can be 
		properly skipped over without generating errors.
	*/
    int TRCVset[TRCVNESTLEVEL];     /* flag to indicate this nest level used */



	/*
		The highest nesting level that has been used so far in the analysis
	*/
    int TRCVnestLevel;      /* number of levels of nesting called for */



	/*
		This is the nesting level of the voltage or current that changes most recently which needs
		to be saved so that the analysis can be resumed correctly after a puase.
	*/
    int TRCVnestState;      /* iteration state during pause */

	int TRCVgSave[TRCVNESTLEVEL];    /* dcGiven flag; as with vSave */
} TRCV;

#define DCT_START1 1
#define DCT_STOP1 2
#define DCT_STEP1 3
#define DCT_NAME1 4
#define DCT_TYPE1 5
#define DCT_START2 6
#define DCT_STOP2 7
#define DCT_STEP2 8
#define DCT_NAME2 9
#define DCT_TYPE2 10

#endif /*DCTR*/
