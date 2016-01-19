/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

    /*
     * INPpName()
     *
     *  Take a parameter by Name and set it on the specified device 
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
	A simple routine to set a parameter on an instance by specifying the name of the 
	parameter instead of the parameter ID as required by the lower level DEV routine.
	The dev parameter allows INPpName to search the parameter tables of the proper type of device for the name parm and
	then all the proper device specific setINstanceParm function to perform the actual work.
*/
///<param name = "*parm"> "The parameter name to set </param>
///<param name = "*val"> The alue to set it to </param>
///<param name = "*ckt"> THe current circuit </param>
///<param name = "dev"> THe device type of the device being parsed </param>
///<param name = "*inst"> The pointer to the device being parsed </param>
int INPpName(char *parm, IFvalue *val, GENERIC *ckt, int dev, GENERIC *fast)
{
	int error;  /* int to store evaluate error return codes in */
	int i;

	for (i = 0; i < (*(*(ft_sim->devices)[dev]).numInstanceParms); i++)
	{
		if (strcmp(parm, ((*(ft_sim->devices)[dev]).instanceParms[i].keyword)) == 0)
		{
			error = (*(ft_sim->setInstanceParm))(ckt, fast, (*(ft_sim->devices)[dev]).instanceParms[i].id, val, (IFvalue*)NULL);

			if (error)
				return(error);

			break;
		}
	}

	if (i == (*(*(ft_sim->devices)[dev]).numInstanceParms))
	{
		return(E_BADPARM);
	}

	return(OK);
}
