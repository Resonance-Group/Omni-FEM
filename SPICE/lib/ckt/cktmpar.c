/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

    /* CKTmodParam
     *  attach the given parameter to the specified model in the given circuit
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
	This function is equivalent to CKTparam, but operates on models instead of instances.
	The specified parameter is updated to have the specified value by a device type specific subroutine provided by the device implementator.
	As with CKTparam, the selector parameter is not yet used, but is provided to comply with the front end interface specification
	and for possible future needs.

	This function is identical to SetInstanceParm, except it applies to parameters of a model instead
	of an instance.
*/
///<param = *ckt> Circuit to operate on </param>
///<param = *model> Model beign modified </param>
///<param = parm> Parameter number </param>
///<param = *value> Parameter value </param>
///<param = *selector> Subparameter selector </param>
int CKTmodParam(GENERIC *ckt, GENERIC *modfast, int param, IFvalue *val, IFvalue *selector)
{
	register int type = ((GENmodel *)modfast)->GENmodType;

	if (((*DEVices[type]).DEVmodParam))
	{
		return(((*((*DEVices[type]).DEVmodParam)) (param, val, (GENmodel *)modfast)));
	}
	else
	{
		return(E_BADPARM);
	}
}
