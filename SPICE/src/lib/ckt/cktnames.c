/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1988 Thomas L. Quarles
**********/


#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "ifsim.h"
#include "iferrmsg.h"
#include "util.h"
#include "suffix.h"

/*
	Used to generate an IFuid list in the form needed by the interface package's 
	OUTpBeginPlot function.
	The nameList which is returned has been malloced and thus should be freed after use
*/
///<param name = "*ckt"> CIrcuit to operate on </param>
///<param name = "*numNames"> Return: number of names output </param>
///<param name = "**nameList"> Return: vector of names </param>
int CKTnames(register CKTcircuit *ckt, int *numNames, register IFuid **nameList)
{
	register CKTnode *here;
	register int i;
	*numNames = ckt->CKTmaxEqNum - 1;
	*nameList = (IFuid *)MALLOC(*numNames * sizeof(IFuid));
	if ((*nameList) == (IFuid *)NULL)
		return(E_NOMEM);
	i = 0;
	for (here = ckt->CKTnodes->next; here; here = here->next)
	{
		*((*nameList) + i++) = here->name;
	}
	return(OK);
}


int CKTdnames(CKTcircuit *ckt)
{
	CKTnode *here;
	register int i;

	i = 0;// ?
	for (here = ckt->CKTnodes->next; here; here = here->next)
	{
		printf("%03d: %s\n", here->number, here->name);
	}
	return(OK);
}
