/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

/* CKTaccept(ckt)
 * this is a driver program to iterate through all the various
 * accept functions provided for the circuit elements in the
 * given circuit 
 */

#include "spice.h"
#include <stdio.h>
#include "smpdefs.h"
#include "cktdefs.h"
#include "util.h"
#include "devdefs.h"
#include "sperror.h"
#include "suffix.h"



/*
	This routine is used by the transient code when it has been determined
	that a particular timepoint is to be accpeted thus allowing each device 
	to perform any once per timepoint cleanup or preparation for the next timepoint.
	This is primarliy intended for the generation of breakpoints by sources and transmission
	lines whcih should be done exactly once at a timepoint and only if the timepoint is to be accpeted but
	can be used for anything else. 
	As with all other routines that iterate through all devices this will call the corresponding device type specific
	routine, DEVaccept, for each device type for which that routine has been defined and of whcih there are instance in 
	the current circuit
*/
///<param = *ckt> Circuit to operate on </param>
int CKTaccept(register CKTcircuit *ckt)
{
	extern SPICEdev *DEVices[];

	register int i;
	int size;
	int error;
	double *temp;

	for (i = 0; i < DEVmaxnum; i++)
	{
		if (((*DEVices[i]).DEVaccept != NULL) && (ckt->CKThead[i] != NULL))
		{
			error = (*((*DEVices[i]).DEVaccept))(ckt, ckt->CKThead[i]);
			if (error)
				return(error);
		}
	}
#ifdef PREDICTOR
	/* now, move the sols vectors around */
	temp = ckt->CKTsols[7];
	for (i = 7; i > 0; i--)
	{
		ckt->CKTsols[i] = ckt->CKTsols[i - 1];
	}

	ckt->CKTsols[0] = temp;
	size = SMPmatSize(ckt->CKTmatrix);
	for (i = 0; i <= size; i++)
	{
		ckt->CKTsols[0][i] = ckt->CKTrhs[i];
	}
#endif /* PREDICTOR */
	return(OK);
}
