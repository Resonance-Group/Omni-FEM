/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

    /*
     *CKTnewEq(ckt,node,name)
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


/*
	Obsolete routine used to generate a circuit equation.
	This was formly used in the V1.0 front end to simulator interface but has been replaced in that context
	by the new CKTnewNode function which uses the primitives CKTmkNode and CKTlinkEq insteaed of attempting
	to do all the work itself.
	Instead of using CKTnewEq, all parts of SPICE3 noew use the funcitons CKTmkVolt or CKTmkCur
*/
///<param name = "*inCkt"> Circuit to operate on </param>
///<param name = "**node"> New node name </param>
///<param name = "name"> Name node should have </param>
int CKTnewEq(GENERIC *inCkt, GENERIC **node, IFuid name)
{
	CKTnode *mynode;
	register CKTcircuit *ckt = (CKTcircuit *)inCkt;
	int error;

	error = CKTmkNode(ckt, &mynode);
	if (error)
		return(error);

	if (node)
		*node = (GENERIC *)mynode;
	mynode->name = name;

	error = CKTlinkEq(ckt, mynode);

	return(error);
}
