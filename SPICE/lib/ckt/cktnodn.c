/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "suffix.h"



/*
	A routine used to return the "name" of an equation given its equation number.
	This function is intended only for debugging output, as it is quite inefficienct having to
	search down a linked list and returning a token which can still only be interpreted by the front
	end package.
*/
///<param name = "*ckt"> Circuit to operate on </param>
///<param name = "nodeNum"> Name of node to get info about </param>
IFuid CKTnodName(CKTcircuit *ckt, register int nodeNum)
{
	register CKTnode *here;

	for (here = ckt->CKTnodes; here; here = here->next)
	{
		if (here->number == nodeNum)
		{
			/* found it */
			return(here->name);
		}
	}
	/* doesn't exist - do something */
	return("UNKNOWN NODE");
}
