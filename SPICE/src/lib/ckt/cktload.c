/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

    /* CKTload(ckt)
     * this is a driver program to iterate through all the various
     * load functions provided for the circuit elements in the
     * given circuit 
     */

#include "spice.h"
#include <stdio.h>
#include "smpdefs.h"
#include "cktdefs.h"
#include "devdefs.h"
#include "sperror.h"
#include "suffix.h"

static int ZeroNoncurRow( );



/*
	In many ways, CKTload is the heart of SPICE3. 
	At each iteration of the DC, transient, and operating point analyses, CKTload is called on to clear the matrix and RHS,
	then evaluate every device in the circuit.
	The devices are evalutated by calls to the device type specific DEVload functions, in which each device is expected to be evaluated
	and the proper additions made to the RHS vector and the circuit matrix.
	After all of the devices have been loaded, the nodeset and IC additions may be set, depending on the mode in efect at the time,
	by adding a 10M ohm resister from each node to GND and connecting a constant current source 10 * 10^6 * (desired voltage from ground to node).
	Finally, cumulative timing statistics are maintained for the load operation
*/
///<param = *ckt> Circuit to operate on </param>
int CKTload(register CKTcircuit *ckt)
{
	extern SPICEdev *DEVices[];
	register int i;
	register int size;
	double startTime;
	CKTnode *node;
	int error;
#ifdef STEPDEBUG
	int noncon;
#endif /* STEPDEBUG */

	startTime = (*(SPfrontEnd->IFseconds))();
	size = SMPmatSize(ckt->CKTmatrix);
	for (i = 0; i <= size; i++)
	{
		*(ckt->CKTrhs + i) = 0;
	}

	SMPclear(ckt->CKTmatrix);
#ifdef STEPDEBUG
	noncon = ckt->CKTnoncon;
#endif /* STEPDEBUG */

	for (i = 0; i < DEVmaxnum; i++)
	{
		if (((*DEVices[i]).DEVload != NULL) && (ckt->CKThead[i] != NULL))
		{
			error = (*((*DEVices[i]).DEVload))(ckt->CKThead[i], ckt);
			if (ckt->CKTnoncon)
				ckt->CKTtroubleNode = 0;
#ifdef STEPDEBUG
			if (noncon != ckt->CKTnoncon)
			{
				printf("device type %s nonconvergence\n", (*DEVices[i]).DEVpublic.name);
				noncon = ckt->CKTnoncon;
			}
#endif /* STEPDEBUG */
			if (error)
				return(error);
		}
	}
	if (ckt->CKTmode & MODEDC)
	{
		/* consider doing nodeset & ic assignments */
		if (ckt->CKTmode & (MODEINITJCT | MODEINITFIX))
		{
			/* do nodesets */
			for (node = ckt->CKTnodes; node; node = node->next)
			{
				if (node->nsGiven)
				{
					if (ZeroNoncurRow(ckt->CKTmatrix, ckt->CKTnodes, node->number))
					{
						*(ckt->CKTrhs + node->number) = 1.0e10 * node->nodeset;
						*(node->ptr) = 1e10;
					}
					else
					{
						*(ckt->CKTrhs + node->number) = node->nodeset;
						*(node->ptr) = 1;
					}
				}
			}
		}
		if ((ckt->CKTmode & MODETRANOP) && (!(ckt->CKTmode & MODEUIC)))
		{
			for (node = ckt->CKTnodes; node; node = node->next)
			{
				if (node->icGiven)
				{
					if (ZeroNoncurRow(ckt->CKTmatrix, ckt->CKTnodes, node->number))
					{
						*(ckt->CKTrhs + node->number) = 1.0e10 * node->ic;
						*(node->ptr) = 1e10;
					}
					else
					{
						*(ckt->CKTrhs + node->number) = node->ic;
						*(node->ptr) = 1;
					}
				}
			}
		}
	}
	ckt->CKTstat->STATloadTime += (*(SPfrontEnd->IFseconds))() - startTime;
	/* SMPprint(ckt->CKTmatrix, stdout); if you want to debug, this is a
	good place to start ... */
	return(OK);
}



static int ZeroNoncurRow(SMPmatrix *matrix, CKTnode *nodes, int rownum)
{
	CKTnode		*n;
	double		*x;
	int		currents;

	currents = 0;
	for (n = nodes; n; n = n->next)
	{
		x = (double *)SMPfindElt(matrix, rownum, n->number, 0);
		if (x)
		{
			if (n->type == SP_CURRENT)
				currents = 1;
			else
				*x = 0.0;
		}
	}
	return currents;
}

