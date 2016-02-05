/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

    /*
     * INPdevParse()
     *
     *  parse a given input according to the standard rules - look
     *  for the parameters given in the parmlists, In addition, 
     *  an optional leading numeric parameter is handled.
     */

#include "spice.h"
#include <stdio.h>
#include "util.h"
#include "ifsim.h"
#include "inpdefs.h"
#include "iferrmsg.h"
#include "cpdefs.h"
#include "fteext.h"
#include "suffix.h"



/*
	Once a device input line has been reduced to a form where it consists of nothing
	but data of the form "keyword=value" or "flagkeyword" with a single optional unlabeled value, it can be 
	parsed by a single routine.
	INPdevParse breaks down this very regular form, performing all necessary operations to attach the parameter values to the instance. 
	The optional unlabeled value will be returned in leading, with wasteland set to a non-sero
	value if that value was present
*/
///<param name = "**line"> The line to parse </param>
///<param name = "*ckt"> The circuit this device is a member of </param>
///<param name = "dev"> the device type code to the device being parsed </param>
///<param name = "*fast"> Direct pointer to device being parsed </param>
///<param name = "*leading"> The optional leading numeric parameter </param>
///<param name = "*waslead"> Flag to indicate unlabeled leading val present. 1 if leading double given, 0 otherwise.  </param>
///<param name = "*tab"> The symbol table for the current circuit </param>
char * INPdevParse(char **line, GENERIC *ckt, int dev, GENERIC *fast, double *leading, int *waslead, INPtables *tab)
{
	int error;  /* int to store evaluate error return codes in */
	char *parm;
	char *errbuf;
	int i;
	IFvalue *val;

	/* check for leading value */
	*waslead = 0;
	*leading = INPevaluate(line, &error, 1);

	if (error == 0)
	{ /* found a good leading number */
		*waslead = 1;
	}
	else
		*leading = 0.0;

	while (**line != (char)0)
	{
		error = INPgetTok(line, &parm, 1);
		if (!*parm)
			continue;

		if (error)
			return(INPerror(error));

		for (i = 0; i < (*(*(ft_sim->devices)[dev]).numInstanceParms); i++)
		{
			if (strcmp(parm, ((*(ft_sim->devices)[dev]).instanceParms[i].keyword)) == 0)
			{
				val = INPgetValue(ckt, line, ((*(ft_sim->devices)[dev]).instanceParms[i].dataType), tab);
				
				if (!val)
					return (INPerror(E_PARMVAL));

				error = (*(ft_sim->setInstanceParm))(ckt, fast, (*(ft_sim->devices)[dev]).instanceParms[i].id, val, (IFvalue*)NULL);
				
				if (error)
					return(INPerror(error));

				break;
			}
		}

		if (i == (*(*(ft_sim->devices)[dev]).numInstanceParms))
		{
			errbuf = MALLOC(strlen(parm) + 25);
			(void)sprintf(errbuf, " unknown parameter (%s) \n", parm);
			return(errbuf);
		}

		FREE(parm);
	}
	return((char *)NULL);
}
