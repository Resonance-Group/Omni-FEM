/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "iferrmsg.h"
#include "acdefs.h"
#include "cktdefs.h"
#include "suffix.h"

/*
	Since dec, oct, and lin are mutually exclusive, querying for them returns one for
	whichever one is set, zero for the others, and zero for all of them if none have been set
*/
///<param = *ckt> Circuit to operate on </param>
///<param = *anal> Analysis to quesry parameter of </param>
///<param = which> Parameter to query </param>
///<param = *value> Value of parameter to return </param>
int ACaskQuest(CKTcircuit *ckt, GENERIC *anal, int which, IFvalue *value)
{
	switch (which)
	{

	case AC_START:
		value->rValue = ((ACAN*)anal)->ACstartFreq;
		break;

	case AC_STOP:
		value->rValue = ((ACAN*)anal)->ACstopFreq;
		break;

	case AC_STEPS:
		value->iValue = ((ACAN*)anal)->ACnumberSteps;
		break;

	case AC_DEC:
		if (((ACAN*)anal)->ACstepType == DECADE)
		{
			value->iValue = 1;
		}
		else
		{
			value->iValue = 0;
		}
		break;

	case AC_OCT:
		if (((ACAN*)anal)->ACstepType == OCTAVE)
		{
			value->iValue = 1;
		}
		else
		{
			value->iValue = 0;
		}
		break;

	case AC_LIN:
		if (((ACAN*)anal)->ACstepType == LINEAR)
		{
			value->iValue = 1;
		}
		else
		{
			value->iValue = 0;
		}
		break;

	default:
		return(E_BADPARM);
	}
	return(OK);
}

