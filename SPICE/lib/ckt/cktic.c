/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "smpdefs.h"
#include "util.h"
#include "sperror.h"
#include "devdefs.h"
#include "suffix.h"


extern SPICEdev *DEVices[];

/*
	Used to establish th initial conditions before performing a DC analysis. 
	The circuit's RHS vector is cleared and then loaded with the nodeset and IC values given
	for nodes with IC values taking precedence over nodeset values.
	If the "UIC" keyword has been given, each device's DEVsetic function is then called to allow devices which did not 
	have an instance specific IC given to pick up the node IC. 
	The RHS vector is left loaded with the .nodeset and .ic values
*/
///<param = *ckt> Circuit to operate on </param>
int CKTic(CKTcircuit *ckt)
{
	int error;
	int size;
	int i;
	CKTnode *node;

	size = SMPmatSize(ckt->CKTmatrix);
	for (i = 0; i <= size; i++)
	{
		*(ckt->CKTrhs + i) = 0;
	}

	for (node = ckt->CKTnodes; node != NULL; node = node->next)
	{
		if (node->nsGiven)
		{
			node->ptr = SMPmakeElt(ckt->CKTmatrix, node->number, node->number);

			if (node->ptr == (double *)NULL)
				return(E_NOMEM);

			ckt->CKThadNodeset = 1;
			*(ckt->CKTrhs + node->number) = node->nodeset;
		}

		if (node->icGiven)
		{
			if (!(node->ptr))
			{
				node->ptr = SMPmakeElt(ckt->CKTmatrix, node->number, node->number);

				if (node->ptr == (double *)NULL)
					return(E_NOMEM);
			}
			*(ckt->CKTrhs + node->number) = node->ic;
		}
	}

	if (ckt->CKTmode & MODEUIC)
	{
		for (i = 0; i < DEVmaxnum; i++)
		{
			if (((*DEVices[i]).DEVsetic != NULL) && (ckt->CKThead[i] != NULL))
			{
				error = (*((*DEVices[i]).DEVsetic))(ckt->CKThead[i], ckt);
				if (error)
					return(error);
			}
		}
	}
	return(OK);
}
