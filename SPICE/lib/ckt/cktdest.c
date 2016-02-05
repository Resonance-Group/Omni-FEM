/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

    /* CKTdestroy(ckt)
     * this is a driver program to iterate through all the various
     * destroy functions provided for the circuit elements in the
     * given circuit 
     */

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "devdefs.h"
#include "util.h"
#include "ifsim.h"
#include "sperror.h"
#include "suffix.h"


extern SPICEdev *DEVices[];



/*
	Thos dismantles all of the data structures associated with teh given circuit.
	All structures and substructures are freed.
	On return, ckt is no longer a valid pointer to a circuit and must not be used as such.

	A cleanup function that recursively traverses all the data structures that may be associeated with circuit and frees them.
	After return, inCkt is no longer a valid circuit pointer and its
	use in any subsequent subroutine calls will cause unpredictable results.
*/
///<param name = "*inCkt"> Circuit to destroy </param>
int CKTdestory(GENERIC *inCkt)
{
	register CKTcircuit *ckt = (CKTcircuit *)inCkt;
	register int i;
	register CKTnode *node;
	register CKTnode *nnode;


#ifdef HAS_SENSE2
	if (ckt->CKTsenInfo)
	{
		if (ckt->CKTrhsOp)
			FREE(ckt->CKTrhsOp);

		if (ckt->CKTsenRhs)
			FREE(ckt->CKTsenRhs);

		if (ckt->CKTseniRhs)
			FREE(ckt->CKTseniRhs);

		SENdestroy(ckt->CKTsenInfo);
	}
#endif

	for (i = 0; i < DEVmaxnum; i++)
	{
		if (((*DEVices[i]).DEVdestroy != NULL) && (ckt->CKThead[i] != NULL))
		{
			(*((*DEVices[i]).DEVdestroy))(&(ckt->CKThead[i]));
		}
	}
	for (i = 0; i <= ckt->CKTmaxOrder + 1; i++)
	{
		FREE(ckt->CKTstates[i]);
	}
	if (ckt->CKTmatrix)
		SMPdestroy(ckt->CKTmatrix);

	if (ckt->CKTbreaks)
		FREE(ckt->CKTbreaks);

	for (node = ckt->CKTnodes; node; )
	{
		nnode = node->next;
		FREE(node);
		node = nnode;
	}
	ckt->CKTnodes = (CKTnode *)NULL;
	ckt->CKTlastNode = (CKTnode *)NULL;
	FREE(ckt);
	return(OK);
}
