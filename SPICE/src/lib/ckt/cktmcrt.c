/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

    /* CKTmodCrt(type,name,ckt,fast)
     *  Create a device model of the specified type, with the given name
     *  in the named circuit.
     */

#include "spice.h"
#include <stdio.h>
#include "devdefs.h"
#include "cktdefs.h"
#include "sperror.h"
#include "util.h"
#include "suffix.h"


/*
	Creates a new model in the circuit.
	The model is initilized with only a name and a default set of parameters which may be overridden with CKTmodParam.
	The type of the model is the identification of which the SPICE3 device implements this model is to use.
	The type are identified by their zero based index in the devices array of the IFsimulator structure, where
	they should be located by name.
	The model structure is initilized to an all zero bit pattern with a size given by the 
	DEVmodSize field of the SPICEdev structure for the specified device type.
	This implementation checks for model name duplications even though the front end interface does not call for this level checking.

	This function is similar to the newInstance function, except it creates a model instead of an
	instance, thus treating modUid and modelPtr as nameUid and instPtr were treated in newhtance.
	devZndex is a specification to the simulator of the type of model which is being created The model
	type is defined as the (0 based) index to the description of the device in the devices field of the
	IFsimualtor structure.
*/
///<param = *ckt> Circuit to operate on </param>
///<param = type> Type of model to create </param>
///<param = **modFast> Model being created </param>
///<param = name> Name of new model </param>
int CKTmodCrt(GENERIC *ckt, int type, GENERIC **modfast, IFuid name)
{
	extern SPICEdev *DEVices[];
	GENmodel *mymodfast = NULL;
	int error;

	error = CKTfndMod(ckt, &type, (GENERIC**)&mymodfast, name);

	if (error == E_NOMOD)
	{
		mymodfast = (GENmodel *)MALLOC(*DEVices[type]->DEVmodSize);

		if (mymodfast == (GENmodel *)NULL)
			return(E_NOMEM);

		mymodfast->GENmodType = type;
		mymodfast->GENmodName = name;
		mymodfast->GENnextModel = (GENmodel *)((CKTcircuit *)ckt)->CKThead[type];
		((CKTcircuit *)ckt)->CKThead[type] = (GENmodel *)mymodfast;

		if (modfast)
			*modfast = (GENERIC *)mymodfast;

		return(OK);
	}
	else if (error == 0)
	{
		if (modfast)
			*modfast = (GENERIC *)mymodfast;

		return(E_EXISTS);
	}
	else
	{
		return(error);
	}
	/*NOTREACHED*/
}
