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
#include "cktdefs.h"
#include "suffix.h"

extern SPICEanalysis *analInfo[];

/*
	Used to set parameters further detailing an analysis to be performed in the
	same way as CKTparam further describes an instance.
	Again since the code does not ave any knowledge of the analysis data structure at this 
	level, a lower level routine is called
*/
///<param name = "*ckt"> Circuit to operate on </param>
///<param name = "*anal"> Analysis being modified </param>
///<param name = "parm"> Parameter number </param>
///<param name = "*value"> Parameter value </param>
///<param name = "*selector"> Sub parameter selector </param>
int CKTsetAnalPm(GENERIC *ckt, GENERIC *analPtr, int parm, IFvalue *value, IFvalue *selector)
{
	register int type = ((JOB *)analPtr)->JOBtype;

	if ((analInfo[type]->setParm) == NULL)
		return(E_BADPARM);

	return((*(analInfo[type]->setParm))(ckt, analPtr, parm, value));
}
