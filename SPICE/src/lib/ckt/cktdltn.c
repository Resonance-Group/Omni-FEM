/**********
Copyright 1992 Regents of the University of California.  All rights reserved.
**********/

/* CKTdltNod
*/

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "ifsim.h"
#include "sperror.h"
#include "util.h"
#include "misc.h"
#include "suffix.h"



/*
	This function is required by the front end interface and should delete a node from the circuit.
	Since SPICE3 does not yet have all the facailities required to perform this operation, it simply
	returns the E_UNSUPP error code.
	Before this function is implemented, it will be necessary to unstitute node refence counts to ensure
	that the node is no longer referenced before deletion to provide a way to renumber circuit equations
	if this is not the highest numbered equation and to delete rows and columns from the matrix

	This function is used to indicate to the simulator that the last attachment to the spedied node
	has been deleted and the node will no longer be used. Since the simulator may keep reference counts
	on nodes, it may detect a call to deleteNode that MUST be ignored because the node is still in use and
	return the E - NOTEMFTY error code, but the Simulator’s behavior in such a situation is undefined
	since it need not do such reference counting. Note that it is always illegal to delete the ground node.
*/
///<param name = "*ckt"> Circuit to operate on </param>
///<param name = "*node"> Node Structure </param>
int CKTdltNod(GENERIC *ckt, GENERIC *node)
{
	return CKTdltNNum(ckt, ((CKTnode *)node)->number);
}




int CKTdltNNum(GENERIC *cktp, int num)
{
	CKTcircuit *ckt = (CKTcircuit *)cktp;
	CKTnode *n, *prev, *node, *sprev = NULL;
	int	i, error;

	prev = NULL;
	node = NULL;
	for (n = ckt->CKTnodes; n; n = n->next)
	{
		if (n->number == num)
		{
			node = n;
			sprev = prev;
		}
		prev = n;
	}

	if (!node)
		return OK;

	ckt->CKTmaxEqNum -= 1;

	if (!sprev)
	{
		ckt->CKTnodes = node->next;
	}
	else
	{
		sprev->next = node->next;
	}

	if (node == ckt->CKTlastNode)
		ckt->CKTlastNode = sprev;

	error = (*(SPfrontEnd->IFdelUid))((GENERIC *)ckt, node->name, UID_SIGNAL);
	tfree(node);

	return error;
}
