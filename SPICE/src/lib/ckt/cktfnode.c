/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

    /* CKTfndNode
     *  find the given node given its name and return the node pointer
     */

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "sperror.h"
#include "cktdefs.h"
#include "suffix.h"


/* ARGSUSED */
/*
	This function performs a search through the node structunre in the specificed circuit to find
	the one with the given uniqueidentifier associated with it.
	If the identifier is found, *node is set to point to the node found, otherwais E_NOTFOUND is returned.
	This function is obviously not a fast one, since it must search a linked list, but is provided as a backstop for simple
	front endds which do not wish to maintain a complete symbol table and are willing to pay the costs of doing so.

	This function allows the front end to find a node pointer from the node’s unique identitier. The
	arguments are all exactly as in newNode, but the node must already exist or the error E - NOTFOUND
	will be retumed.
*/
///<param=*ckt> Circuit to operate on </param>
///<param=**node> node structure </param>
///<param=name> UID of node to find </param>
int CKTfndNode(GENERIC *ckt, GENERIC **node, IFuid name)
{
	register CKTnode *here;

	for (here = ((CKTcircuit *)ckt)->CKTnodes; here; here = here->next)
	{
		if (here->name == name)
		{
			if (node)
				*node = (char *)here;

			return(OK);
		}
	}
	return(E_NOTFOUND);
}
