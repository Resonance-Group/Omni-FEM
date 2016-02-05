/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "iferrmsg.h"
#include "cktdefs.h"
#include "opdefs.h"
#include "suffix.h"



/*
	There are no parameters to the DC operating point analysis so this function returns
	E_BADPARM on all calls
*/
///<param = *ckt> Circuit to operate on </param>
///<param = *anal> Analysis to query parameter of </param>
///<param = which> Parameter to query </param>
///<param = *value> Value of parameter to return </param>
int DCOsetParm(CKTcircuit *ckt, GENERIC *anal, int which, IFvalue *value)
{
	switch (which)
	{
	default:
		break;
	}

	return(E_BADPARM);
}


SPICEanalysis DCOinfo  = {
    { 
        "OP",
        "D.C. Operating point analysis",

        0,
        NULL,
    },
    sizeof(OP),
    NODOMAIN,
    1,
    DCOsetParm,
    DCOaskQuest,
    NULL,
    DCop
};
