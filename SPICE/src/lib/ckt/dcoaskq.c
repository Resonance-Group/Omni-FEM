/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "iferrmsg.h"
#include "opdefs.h"
#include "cktdefs.h"
#include "suffix.h"



/*
	Always returns E_BADPARAM since the DC operating point analysis does not 
	support any options. 
	This routine itself is provided to statisfy the analysis interface requirement
*/
///<param = *ckt> Circuit to operate on </param>
///<param = *anal> Analysis to query parameter of </param>
///<param = which> Parameter to query </param>
///<param = *value> Value of parameter to return </param>
int DCOaskQuest(CKTcircuit *ckt, GENERIC *anal, int which, IFvalue *value)
{
    return(E_BADPARM);
}

