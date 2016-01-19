/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

    /* CKTground(ckt,node)
     *  specify the node to be the ground node of the given circuit
     */

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "ifsim.h"
#include "sperror.h"
#include "util.h"
#include "suffix.h"


/*
	This is a special rountine to add the ground node to the circuit.
	This node is distinguished in that it must be given equation number zero and thus a 
	special location in the linked list of nodes, otherwise this routine operates as CKTnewNode does.
	Note that the interface specification calls for only a single call to this subroutine succeeding, but for future calls to
	return the error E_EXISTS and ignore the new name passed in, but return the old one instead.

	THis function creates a node exactly as newNOde does, but it indicates that this is the ground
	node and thus must be called exactly once for each circuit.
	THis subroutine will return E_EXISTS if a ground node has been previously defined
	for this circuit and the value of the grounf node is NOT changed.
	THis subroutine must be called before any other refence is made to the ground node by any other call to the simulator.
*/
///<param name = "*inCkt"> Circuit ground node is in </param>
///<param name = "**node"> Ground node pointer to return </param>
///<param name = "name"> Name of the node to be created </param>
int CKTground(GENERIC *inCkt, GENERIC **node, IFuid name)
{
	register CKTcircuit *ckt = (CKTcircuit *)inCkt;

	if (ckt->CKTnodes)
	{
		if (ckt->CKTnodes->name)
		{
			/*already exists - keep old name, but return it */
			if (node)
				*node = (char *)ckt->CKTnodes;

			return(E_EXISTS);
		}
		ckt->CKTnodes->name = name;
		ckt->CKTnodes->type = SP_VOLTAGE;
		ckt->CKTnodes->number = 0;
	}
	else
	{
		ckt->CKTnodes = (CKTnode *)MALLOC(sizeof(CKTnode));
		if (ckt->CKTnodes == NULL)
			return(E_NOMEM);
		ckt->CKTnodes->name = name;
		ckt->CKTnodes->type = SP_VOLTAGE;
		ckt->CKTnodes->number = 0;
		ckt->CKTnodes->next = (CKTnode *)NULL;
		ckt->CKTlastNode = ckt->CKTnodes;
	}
	if (node)
		*node = (char *)ckt->CKTnodes;
	return(OK);

}
