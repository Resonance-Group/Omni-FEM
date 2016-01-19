/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

    /* CKTparam
     *  attach the given parameter to the specified device in the given circuit
     */

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "ifsim.h"
#include "util.h"
#include "devdefs.h"
#include "sperror.h"
#include "suffix.h"


extern SPICEdev *DEVices[];

/*
	CKTparam modifies existing elements in the circuit by changing the values of various parameters associated with them.
	SInce the code at this level is not permitted to know any of the details of the device implementations, a lower
	level routine is provided by each device to handle its own parameters and this routine simply passes the problem off
	to teh correct device specific routine after determineing the type of device involved.
	The selector parameter is currently unused but can be ised to select a specific value out of an array of
	similiar values to be changed.

	This function is used to set a single parameter on a instance to a specified value. instPtr is the
	instance pointer provided by the navlnstance function.
*/
///<param = *ckt> Circuit to operate on </param>
///<param = *inst> Instance beign modified </param>
///<param = parm> Parameter number </param>
///<param = *value> Parameter value </param>
///<param = *selector> Sub parameter selector </param>
int CKTparam(GENERIC *ckt, GENERIC *fast, int param, IFvalue *val, IFvalue *selector)
{
	register int type;
	GENinstance *myfast = (GENinstance *)fast;
	type = myfast->GENmodPtr->GENmodType;
	if (((*DEVices[type]).DEVparam))
	{
		return(((*((*DEVices[type]).DEVparam)) (param, val, myfast, selector)));
	}
	else
	{
		return(E_BADPARM);
	}
}
