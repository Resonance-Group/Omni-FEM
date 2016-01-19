/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

    /*
     *CKTlinkEq
     *  Link an already allocated node into the necessary structure
     */

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "iferrmsg.h"
#include "smpdefs.h"
#include "cktdefs.h"
#include "util.h"
#include "suffix.h"


/*
	Links an equation into the circuit's node data structure.
	The node data structures require IFuid in them as the node "name", but since the front end wants to keep a pointer in
	the structure associated with an object when it stores the name away, it is necessary to allocate that structure before calling
	IFuid.
	For the internal procedures for generating various kinds of equations in the circuit, the procedure has
	thus been broken into two parts, creation of the node structure, and linking of the structure into the overall
	node list.
	CKTlinkEq provides the latter half of that capability.
*/
///<param name = "*ckt"> Circuit to operate on </param>
///<param name = "*node"> Node structure to be linked </param>
int CKTlinkEq(CKTcircuit *ckt, CKTnode *node)
{
	if (!(ckt->CKTnodes))
	{ /*  starting the list - allocate both ground and 1 */
		ckt->CKTnodes = (CKTnode *)MALLOC(sizeof(CKTnode));

		if (ckt->CKTnodes == (CKTnode *)NULL)
			return(E_NOMEM);

		ckt->CKTnodes->name = (char *)NULL;
		ckt->CKTnodes->type = SP_VOLTAGE;
		ckt->CKTnodes->number = 0;
		ckt->CKTlastNode = ckt->CKTnodes;
	}
	if (node == (CKTnode *)NULL)
		return(E_BADPARM);

	ckt->CKTlastNode->next = node;
	ckt->CKTlastNode = ckt->CKTlastNode->next;
	ckt->CKTlastNode->number = ckt->CKTmaxEqNum++;
	ckt->CKTlastNode->next = (CKTnode *)NULL;
	return(OK);
}
