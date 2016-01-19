/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "tskdefs.h"
#include "ifsim.h"
#include "util.h"
#include "cktdefs.h"
#include "iferrmsg.h"
#include "suffix.h"

/*
	CKTnewTask allows the front end to create a task structure which can describe a set of 
	analyses to be performed by the simulator as a single step.
	This function allocates the necessary structure and initializes it to default values, but
	does not insert any analysis requests in the new task, although it does create the "options"
	analysis with default values.

	A task is a grouping of analyses that are to be performed as a group by a single call to doAnalyses.
	The simulator is free to re-arrange analyses within a task if doing so will improve its
	efficiency, but may not move analyses between tasks. This function creates a new task associated
	with the given circuit with the unique identifier specified and renuns a pointer through taskPtr.
*/
///<param name = "*ckt"> Circuit to operate on </param>
///<param name = "**task"> Task structure to be created </param>
///<param name = "taskName"> Name to give the task </param>
int CKTnewTask(GENERIC *ckt, GENERIC **taskPtr, IFuid taskName)
{
	register TSKtask *tsk;
	*taskPtr = (GENERIC *)MALLOC(sizeof(TSKtask));
	if (*taskPtr == NULL) return(E_NOMEM);
	tsk = *(TSKtask **)taskPtr;
	tsk->TSKname = taskName;
	tsk->TSKgmin = 1e-12;
	tsk->TSKabstol = 1e-12;
	tsk->TSKreltol = 1e-3;
	tsk->TSKchgtol = 1e-14;
	tsk->TSKvoltTol = 1e-6;
#ifdef NEWTRUNC
	tsk->TSKlteReltol = 1e-3;
	tsk->TSKlteAbstol = 1e-6;
#endif /* NEWTRUNC */
	tsk->TSKtrtol = 7;
	tsk->TSKbypass = 1;
	tsk->TSKtranMaxIter = 10;
	tsk->TSKdcMaxIter = 100;
	tsk->TSKdcTrcvMaxIter = 50;
	tsk->TSKintegrateMethod = TRAPEZOIDAL;
	tsk->TSKmaxOrder = 2;
	tsk->TSKnumSrcSteps = 10;
	tsk->TSKnumGminSteps = 10;
	tsk->TSKpivotAbsTol = 1e-13;
	tsk->TSKpivotRelTol = 1e-3;
	tsk->TSKtemp = 300.15;
	tsk->TSKnomTemp = 300.15;
	tsk->TSKdefaultMosL = 1e-4;
	tsk->TSKdefaultMosW = 1e-4;
	tsk->TSKdefaultMosAD = 0;
	tsk->TSKdefaultMosAS = 0;
	tsk->TSKnoOpIter = 0;
	tsk->TSKtryToCompact = 0;
	tsk->TSKbadMos3 = 0;
	tsk->TSKkeepOpInfo = 0;
	return(OK);
}
