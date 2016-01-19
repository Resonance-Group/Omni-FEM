/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "iferrmsg.h"
#include "trcvdefs.h"
#include "cktdefs.h"
#include "suffix.h"

/*
	Used to query the parameters of a transfer function analysis.
	This fucntion is only a shell, with the actual query code still to be
	written as the need arises
*/
///<param name = "*ckt"> Circuit to operate on </param>
///<param name = "*anal"> Analysis to query parameter of </param>
///<param name = "which"> Parameter to query </param>
///<param name = "*value"> Value of parameter to return </param>
int TFaskQuest(CKTcircuit *ckt, GENERIC *anal, int which, IFvalue *value)
{
	switch (which) {

	default:
		break;
	}
	return(E_BADPARM);
}

