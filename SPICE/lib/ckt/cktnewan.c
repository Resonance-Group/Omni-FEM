/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "tskdefs.h"
#include "jobdefs.h"
#include "ifsim.h"
#include "util.h"
#include "iferrmsg.h"
#include "suffix.h"

extern SPICEanalysis *analInfo[];


/*
	CKTnewAnal adds a new analysis to an existing task, The new analysis type is determined
	within the front end by searching through the analysis array within the IFsimulator structure
	and using the index of the desired analysis as the type value passed to CKTnewAnal. The 
	anal pointer returned can then be used to add parameters to further describe the characteristics 
	of the analysis.

	This function creates a new analysis within the specified task, and sets the pointer pointed to by
	anuZysisPtr to be the appropriate analysis pointer.
*/
///<param name = "*ckt"> Circuit to operate on </param>
///<param name = "type"> Type of analysis being requested </param>
///<param name = "name"> Name of analysis </param>
///<param name = "**anal"> Returned analysis pointer </param>
///<param name = "*task"> Task this analysis should be part of </param>
int CKTnewAnal(GENERIC *ckt, int type, IFuid name, GENERIC **analPtr, GENERIC *taskPtr)
{
	if (type == 0)
	{
		/* special case for analysis type 0 == option card */
		*analPtr = taskPtr; /* pointer to the task itself */
		(*(JOB **)analPtr)->JOBname = name;
		(*(JOB **)analPtr)->JOBtype = type;
		return(OK); /* doesn't need to be created */
	}

	*analPtr = (GENERIC *)MALLOC(analInfo[type]->size);

	if (*analPtr == NULL)
		return(E_NOMEM);

	(*(JOB **)analPtr)->JOBname = name;
	(*(JOB **)analPtr)->JOBtype = type;
	(*(JOB **)analPtr)->JOBnextJob = ((TSKtask *)taskPtr)->jobs;
	((TSKtask *)taskPtr)->jobs = (JOB *)*analPtr;
	return(OK);
}
