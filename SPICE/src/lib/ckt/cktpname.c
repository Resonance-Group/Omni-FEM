/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/


#include "spice.h"
#include <stdio.h>
#include "util.h"
#include "ifsim.h"
#include "devdefs.h"
#include "cktdefs.h"
#include "gendefs.h"
#include "sperror.h"
#include "suffix.h"


extern SPICEdev *DEVices[];


/*
	This is another routine used for modifying instances of other devices used to implement part of 
	a new device much as CKTpModName, but this routine modifies instances parameters instead of model parameters
*/
///<param name = "*parm"> Name of the parameter </param>
///<param name = "*val"> Parm union containing value </param>
///<param name = "*ckt"> Circuit instance is in </param>
///<param name = "dev"> Device type </param>
///<param name = "*name"> Name of the instance </param>
///<param name = "**fast"> Pointer of the instance </param>
int CKTpName(char *parm, IFvalue *val, CKTcircuit *ckt, int dev, char *name, GENinstance **fast)
{
	int error;  /* int to store evaluate error return codes in */
	int i;

	for (i = 0; i < (*(*DEVices[dev]).DEVpublic.numInstanceParms); i++)
	{
		if (strcmp(parm, ((*DEVices[dev]).DEVpublic.instanceParms[i].keyword)) == 0)
		{
			error = CKTparam((GENERIC*)ckt, (GENERIC *)*fast, (*DEVices[dev]).DEVpublic.instanceParms[i].id, val, (IFvalue *)NULL);
			if (error)
				return(error);
			break;
		}
	}
	if (i == (*(*DEVices[dev]).DEVpublic.numInstanceParms))
	{
		return(E_BADPARM);
	}
	return(OK);
}
