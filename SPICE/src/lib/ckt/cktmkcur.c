/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

    /* CKTmkCur
     *  make the given name a 'node' of type current in the 
     * specified circuit
     */

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "sperror.h"
#include "cktdefs.h"
#include "util.h"
#include "suffix.h"


/*
	Is used to create a new circuit equation corresponding to a current in the circuit.
	All ecessary calls are made to ensure that the IFuid needed to identify the node is properly registered with 
	the front end and the node is initialized as a current type equation.
*/
///<param name = "*ckt"> Circuit to operate on </param>
///<param name = "**node"> NOde to create and return </param>
///<param name = "basename"> Base UID of new name to create </param>
///<param name = "*suffix"> Suffix to add to the name </param>
int CKTmkCur(CKTcircuit *ckt, CKTnode **node, IFuid baseName, char *suffix)
{
	IFuid uid;
	int error;
	CKTnode *mynode;
	CKTnode *checknode;

	error = CKTmkNode(ckt, &mynode);

	if (error)
		return(error);
	checknode = mynode;

	error = (*(SPfrontEnd->IFnewUid))((GENERIC *)ckt, &uid, baseName, suffix, UID_SIGNAL, (GENERIC**)&checknode);
	if (error)
	{
		FREE(mynode);
		if (node) *node = checknode;
		return(error);
	}
	mynode->name = uid;
	mynode->type = SP_CURRENT;

	if (node)
		*node = mynode;

	error = CKTlinkEq(ckt, mynode);
	return(error);
}
