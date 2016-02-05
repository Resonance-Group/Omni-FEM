/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/


/*
	The DC curve analysis allows the user to sweep a voltage or current source through a set of values
	and obtain DC analysis results at each of the points.
	Additionally, a set of nested sweeps may be done, with each more deeply nested sweep varying throughout
	its entire range for each point in th outer sweep, producing families of curves
*/
#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "iferrmsg.h"
#include "trcvdefs.h"
#include "cktdefs.h"
#include "suffix.h"


/*
	Can return the values accpeted by DCTserParm and a additional value "maxness" whcih indicates the 
	maximumu nesting level used, with zero indicating no sweep specified, one indicating no nesting 
	(just a single sweep), and indicating one sweep nested within another.
	Note that this is not exact, but based on the assumption that the parameters corresponding to source one will always
	be set before source two. 
	If no values are set for source one, but values are given for source two, "maxnest" will
	still indicate a nesting level of two
*/
///<param = *ckt> Circuit to operate on </param>
///<param = *anal> Analysis to query parameter of </param>
///<param = which> Parameter to query </param>
///<param = *value> Value of parameter to return </param>
int DCTaskQuest(CKTcircuit *ckt, GENERIC *anal, int which, IFvalue *value)
{
    switch(which) {

    default:
	break;
    }
    /* NOTREACHED */ /* TEMPORARY until cases get added */
    return(E_BADPARM);
}

