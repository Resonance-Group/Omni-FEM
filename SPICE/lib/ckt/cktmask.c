/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

    /* CKTmodAsk
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

extern SPICEdev *DEVices[];


/*
	This function performs the equivalent function to CKTask but for models instead of instances.
	Unlike CKTask though, the selectro paramter is not yet used by any device, although it is 
	passed through for possible future use.

	This is similar to the askInstanceQuest function, but applies to parameters of a device model
	instead of an instance.
*/
///<param = *ckt> Circuit to operate on </param>
///<param = *model> model being queried </param>
///<param = parm> Parameter number </param>
///<param = *value> Parameter value </param>
///<param = selector> Subparameter selector </param>
int CKTmodAsk(GENERIC *ckt, GENERIC *modfast, int which, IFvalue *value, IFvalue *selector)
{
	int type = ((GENmodel *)modfast)->GENmodType;

	if ((*DEVices[type]).DEVmodAsk)
	{
		return((*((*DEVices[type]).DEVmodAsk)) ((CKTcircuit *)ckt, (GENmodel *)modfast, which, value));
	}
	return(E_BADPARM);
}
