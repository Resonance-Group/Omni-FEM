/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

    /* CKTask
     *  Ask questions about a specified device.
     */

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "ifsim.h"
#include "devdefs.h"
#include "sperror.h"
#include "util.h"
#include "suffix.h"
#include "iferrmsg.h"
#include "cktdefs.h"
#include "devdefs.h"

extern SPICEdev *DEVices[];

/*
	CKTask is the inverse of CKTparam, providing the ability to query parameter of an instance as well as providing
	a means for more complete output by querying many other variables associated with an instance, such as internal 
	capacitances, equivalent conductances and similiar internal state information.
	The choice of the parameters avaiable is up to the device implementor, since a device specific subroutine is used 
	to access the actual data structure.
	The selector parameter is used to index into an array of similar parameters to select a single one to output.
	For example, the circuit sensitivity outputs are vectors of the same size as the node voltage/source current vectors but a sinple output
	system may prefer to have SPICE3 index into this vector to pick out a specific sensitivity instead of getting the entire vector
	and having to pick the value out itself.

	This function can be used at any time to determine the current value of any of the queryable
	parameters described in the instanceParms axray. The first two parameters are used simply to identify
	the instance in question, parm is one of the id's from the instanceParms array, and identifies the exact
	parameter to be returned, while value points to an empty IFvalue stxucture which will be filled in as
	appropriate by the simulator.
*/
///<param = *ckt> Circuit to operate on </param>
///<param = *inst> Instance to query </param>
///<param = parm> Parameter number </param>
///<param = *value> Parameter value </param>
///<param = *selector> Sub paramter selector </param>
int CKTask(GENERIC *ckt, GENERIC *fast, int which, IFvalue *value, IFvalue *selector)
{
	register int type = ((GENinstance *)fast)->GENmodPtr->GENmodType;

	if ((*DEVices[type]).DEVask)
	{
		return((*((*DEVices[type]).DEVask)) ((CKTcircuit *)ckt, (GENinstance *)fast, which, value, selector));
	}

	return(E_BADPARM);
}
