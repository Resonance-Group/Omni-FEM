/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

    /* CKTfndAnal
     *  find the given Analysis given its name and return the Analysis pointer
     */

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "jobdefs.h"
#include "tskdefs.h"
#include "sperror.h"
#include "cktdefs.h"
#include "suffix.h"


/*
	Provided for a simple front end to search through an existing task to find a specific analysis request
	given the name of the analysis.
	This routine is not overly efficient but since most tasks will be small and an intelligent front end 
	should never need to use this routine anyway, the cost of such an implementataion
	is negligible.

	This function is provided to allow the front end to locate a specific analysis from limited information.
	analysisUid is the unique identifier of the analysis to be found and must be specified.
	anaUndex is a pointer to the index used in the newhalysis call, and is set on return. taskptr is a
	pointer to the task this analysis is a member of, and may be passed as NULL if it is not known.
	faskuid is the unique identifier of the task this analysis is a member of, and may be passed as NULL
	if it is not known. If both faskPfr and faskuid are passed as null, then for the return value to be
	defined, the analysisuid must be unique over all analyses in all tasks.
*/
///<param name = "*ckt"> Circuit to operate on </param>
///<param name = "*analIndex"> Type of analysis </param>
///<param name = "**anal"> Analysis pointer to return </param>
///<param name = "name"> Pointer to task containing analysis </param>
///<param name = "taskName"> Name of task </param>
int CKTfndAnal(GENERIC *ckt, int *analIndex, GENERIC **anal, IFuid name, GENERIC *inTask, IFuid taskName)
{
	TSKtask *task = (TSKtask *)inTask;
	register JOB *here;

	for (here = ((TSKtask *)task)->jobs; here; here = here->JOBnextJob)
	{
		if (strcmp(here->JOBname, name) == 0)
		{
			if (anal)
				*anal = (GENERIC *)here;

			return(OK);
		}
	}
	return(E_NOTFOUND);
}
