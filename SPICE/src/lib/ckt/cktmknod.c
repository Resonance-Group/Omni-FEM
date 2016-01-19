/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

    /*
     *CKTmkNode(ckt,node)
     *  Tentatively allocate a new circuit equation structure
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
	Allocates an empty node structure.
	The node structure must be filled in with the IFuid and type of node and then be linked into the node linked
	list by an appropiate call to CKTlinkEq.
	This is usually done automatically by CKTmkVolt or CKTmkCUr instead o using
	CKTmkNode directly
*/
///<param name = "*ckt"> Circuit to operate on </param>
///<param name = "**node"> Pointer for new node </param>
int CKTmkNode(CKTcircuit *ckt, CKTnode **node)
{
	CKTnode *mynode;

	mynode = (CKTnode *)MALLOC(sizeof(CKTnode));
	if (mynode == (CKTnode *)NULL) return(E_NOMEM);
	mynode->next = (CKTnode *)NULL;
	mynode->name = (IFuid)0;

	if (node) *node = mynode;
	return(OK);
}
