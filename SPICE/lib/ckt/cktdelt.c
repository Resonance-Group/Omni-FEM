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



/*
	Used to delete a task and all of the analyses it is composed of, thus
	freeing up memory its structure occupy.
	Note that these are only the task structures that are freed not the circuit structures since more
	than on task may reference the same circuit.
*/
///<param name = "*ckt"> Circuit to operate on </param>
///<param name = "*task"> Task being deleted </param>
int CKTdelTask(GENERIC *ckt, GENERIC *task)
{
	JOB *job;
	JOB *old = NULL;
	for (job = ((TSKtask*)task)->jobs; job; job = job->JOBnextJob)
	{
		if (old)
			FREE(old);
		old = job;
	}

	if (old)
		FREE(old);
	FREE(task);
	return(OK);
}
