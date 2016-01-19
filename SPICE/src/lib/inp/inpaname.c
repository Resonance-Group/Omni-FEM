/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

    /*
     * INPaName()
     *
     *  Take a parameter by Name and ask for the specified value 
     * *dev is -1 if type unknown, otherwise, device type
     * **fast is a device, and will be set if possible.
     */

#include "spice.h"
#include <stdio.h>
#include "util.h"
#include "cpdefs.h"
#include "fteext.h"
#include "ifsim.h"
#include "iferrmsg.h"
#include "suffix.h"




/*
	A convenience function used to ask for the value of an instance output variable by name rather than by the exlicit ID required
	by the DEVask function.
	BY using the findInstance fucntion, this function will find the correct instance given a minimal amount of
	data and then identify the correct parameter and call teh required DEVask function with the necessary ID.
	The dataType field is filled in with the type of the returned data, while the val field is filled in with the actual data.
	Other unknown data about the device such as the type code and the pointer to the instane structure will be filled in as 
	approiate
*/
///<param name = "*param"> The name of the parameter to set </param>
///<param name = "*val"> The parameter union containing the value to set </param>
///</param name = "*ckt"> The circuit this device is a member of </param>
///<param name = "*dev"> The device type code to the device being parsed </param>
///<param name = "*devnam"> the name of the device </param>
///<param name = "**fast"> Direct pointer to device being parsed </param>
///<param name = "*sim"> The simulator data structure </param>
///<param name = "*dataType"> The datatype of the returned value structure </param>
///<param name = "*selector"> Data sub-selector for questions </param>
int INPaName(char *parm, IFvalue *val, GENERIC *ckt, int *dev, char *devnam, GENERIC **fast, IFsimulator *sim, int *dataType, IFvalue *selector)
{
	int error;  /* int to store evaluate error return codes in */
	int i;

	/* find the instance - don't know about model, so use null there,
	 * otherwise pass on as much info as we have about the device
	 * (name, type, direct pointer) - the type and direct pointer
	 * WILL be set on return unless error is not OK
	 */
	error = (*(sim->findInstance))(ckt, dev, fast, devnam, (GENERIC *)NULL, (char *)NULL);
	
	if (error) 
		return(error);

	/* now find the parameter - hunt through the parameter tables for
	 * this device type and look for a name match of an 'ask'able
	 * parameter.
	 */
	for (i = 0; i < (*(*(sim->devices)[*dev]).numInstanceParms); i++)
	{
		if (strcmp(parm, ((*(sim->devices)[*dev]).instanceParms[i].keyword)) == 0 && (((*(sim->devices)[*dev]).instanceParms[i].dataType)&IF_ASK))
		{
			/* found it, so we ask the question using the device info we got
			 * above and put the results in the IFvalue structure our caller
			 * gave us originally
			 */
			error = (*(sim->askInstanceQuest))(ckt, *fast, (*(sim->devices)[*dev]).instanceParms[i].id, val, selector);
			if (dataType)
				*dataType = (*(sim->devices)[*dev]).instanceParms[i].dataType;
			return(error);
		}
	}
	return(E_BADPARM);
}
