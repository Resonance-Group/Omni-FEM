/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "ifsim.h"
#include "util.h"
#include "sperror.h"
#include "suffix.h"


/*
	This routine is similar to CKTfndDev in that it is used to find a model pointer given a minimal
	amount of information about the model itself.
	An efficient front end wil maintain its own data structures and not depend on this function since
	CKTfndMod must perform a reletively inefficient search through the model structures.

	This function allows the front end to attempt to get a model pointer from whatever information
	it has about the model. devIndex is the device index of the device type the model is an instance of,
	and may be specified as -1 if it is unknown. The actual index value will be returned to facilitate
	obtaining information from the IFdevice structure for further operations on the model. rnodeZUid
	specifies the unique identifier of the model being looked for, and must be supplied. rnodelPtr points
	to a pointer which will be set to the desired model pointer if the specified model is found. If the
	specified model can't be found either because it doesn't exist or because not enough data has been
	supplied, fZndMode1 returns E-NOTFOUND.
*/
int CKTfndMod(GENERIC *ckt, int *type, GENERIC **modfast, IFuid modname)
{
	register GENmodel *mods;

	if (modfast != NULL && *(GENmodel **)modfast != NULL)
	{
		/* already have  modfast, so nothing to do */
		if (type)
			*type = (*(GENmodel **)modfast)->GENmodType;

		return(OK);
	}
	if (*type >= 0 && *type < DEVmaxnum)
	{
		/* have device type, need to find model */
		/* look through all models */
		for (mods = ((CKTcircuit *)ckt)->CKThead[*type]; mods != NULL; mods = mods->GENnextModel)
		{
			if (mods->GENmodName == modname)
			{
				*modfast = (char *)mods;
				return(OK);
			}
		}
		return(E_NOMOD);
	}
	else if (*type == -1)
	{
		/* look through all types (UGH - worst case - take forever) */
		for (*type = 0; *type < DEVmaxnum; (*type)++)
		{
			/* need to find model & device */
			/* look through all models */
			for (mods = ((CKTcircuit *)ckt)->CKThead[*type]; mods != NULL; mods = mods->GENnextModel)
			{
				if (mods->GENmodName == modname)
				{
					*modfast = (char *)mods;
					return(OK);
				}
			}
		}
		*type = -1;
		return(E_NOMOD);
	}
	else
		return(E_BADPARM);
}
