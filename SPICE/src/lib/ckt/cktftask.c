/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

    /* CKTfndTask
     *  find the specified task - not yet supported in spice 
     */

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "ifsim.h"
#include "sperror.h"
#include "util.h"
#include "suffix.h"


/*
	A procedure to be used by a very simple front end to find a pointer to a task given
	nothing but the name of the task and the circuit it is a task in.
	This function is not implemented in SPICE3 since SPICE3 does not maintain a list of the tasks 
	associated with a circuit and thus always returns E_UNSUPP
*/
///<param name = "*ckt"> Circuit to operate on </param>
///<param name = "**task"> Task pointer to return </param>
///<param name = "taskName"> Name of task </param>
int CKTfndTask(GENERIC *ckt, GENERIC **taskPtr, IFuid taskName)
{
    return(E_UNSUPP);
}
