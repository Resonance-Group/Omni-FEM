/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

/*
 * CKTpModName()
 *
 *  Take a parameter by Name and set it on the specified model
 */

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
	This is a routine used by devices which are implemented by creating instances of other devices
	to replace themselves.
	This routine allows such a device to readily find parameters in the other
	devices model description and set them.
	This function eventually uses the same model parameter
	setting routines exported to the front end, but contains a front end to find a parameter in the model's
	description by name rather then by its ID number.
*/
///<param name = "*parm"> The name of the parameter to set </param>
///<param name = "*val"> Parm union containing value </param>
///<param name = "*ckt"> Circuit model is in </param>
///<param name = "type"> Type of model </param>
///<param name = "name"> Name of the model </param>
///<param name = "**modFast"> Pointer to the model </param>
int CKTpModName(char *parm, IFvalue *val, CKTcircuit *ckt, int type, IFuid name, GENmodel **modFast)
{
	int error;  /* int to store evaluate error return codes in */
	int i;

	for (i = 0; i < (*(*DEVices[type]).DEVpublic.numModelParms); i++)
	{
		if (strcmp(parm, ((*DEVices[type]).DEVpublic.modelParms[i].keyword)) == 0)
		{
			error = CKTmodParam((GENERIC *)ckt, (GENERIC*)*modFast, (*DEVices[type]).DEVpublic.modelParms[i].id, val, (IFvalue*)NULL);
			if (error) return(error);
			break;
		}
	}
	if (i == (*(*DEVices[type]).DEVpublic.numModelParms))
	{
		return(E_BADPARM);
	}
	return(OK);
}
