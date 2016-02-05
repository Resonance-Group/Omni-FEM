/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

    /*
     *CKTnewNode(ckt,node,name)
     *  Allocate a new circuit equation number (returned) in the specified
     *  circuit to contain a new equation or node
     * returns -1 for failure to allocate a node number 
     *
     */

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "iferrmsg.h"
#include "smpdefs.h"
#include "cktdefs.h"
#include "util.h"
#include "suffix.h"

/* should just call CKTnewEQ and set node type afterwards */


/*
	This rountine creates a new node in the circuit.
	Creating the node involves allocating a node structure, linking that structure into the node list, allocating
	a new equation number to the node, storing the IFuid in the node structure, and 
	filling in the rest of the structure with appropriate defaults.
	Note the if used inside of SPICE3, this requires a prior call to the front end function IFnewUID to create
	the unique id to be stored in the node structure

	This function will be called by the front end whenever a new circuit node is to be created.
	The pointer pointed to by node will be set to a value to be used by the front end for all future references
	to this node.
	It is expected that the simulator will keep the node IFuid it recieves in order to describe 
	its output and to prodice error messages.
	The simualtor may also wish to assign it own node numbersing based on these calls.
	node is the unique identifier assigned by the front end for this node.
	NOte that it is an error to call this function with a IFuid that matches that passed to a prvious call,
	although it is not necessary for the simulator to check for this error.
*/
///<param name = "*inCkt"> Circuit node is to be in </param>
///<param name = "**node"> NOd epointer to return </param>
///<param name = "name"> Name of the node to be created </param>
int CKTnewNode(GENERIC *inCkt, GENERIC **node, IFuid name)
{
	register CKTcircuit *ckt = (CKTcircuit *)inCkt;
	if (!(ckt->CKTnodes))
	{ /*  starting the list - allocate both ground and 1 */
		ckt->CKTnodes = (CKTnode *)MALLOC(sizeof(CKTnode));
		if (ckt->CKTnodes == (CKTnode *)NULL) return(E_NOMEM);
		ckt->CKTnodes->name = (char *)NULL;
		ckt->CKTnodes->type = SP_VOLTAGE;
		ckt->CKTnodes->number = 0;
		ckt->CKTlastNode = ckt->CKTnodes;
	}

	ckt->CKTlastNode->next = (CKTnode *)MALLOC(sizeof(CKTnode));

	if (ckt->CKTlastNode->next == (CKTnode *)NULL)
		return(E_NOMEM);

	ckt->CKTlastNode = ckt->CKTlastNode->next;
	ckt->CKTlastNode->name = name;
	ckt->CKTlastNode->number = ckt->CKTmaxEqNum++;
	ckt->CKTlastNode->type = SP_VOLTAGE;
	ckt->CKTlastNode->next = (CKTnode *)NULL;

	if (node)
		*node = (GENERIC *)ckt->CKTlastNode;

	return(OK);
}
