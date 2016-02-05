/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

    /* CKTcrtElement(ckt,type,inModPtr,inInstPtr,name,subname)
     *  Create a device of the specified type, with the given name, using
     *  the specified model in the named circuit.
     */

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "cktdefs.h"
#include "devdefs.h"
#include "sperror.h"
#include "util.h"
#include "suffix.h"



/*
	Creates circuit elements by instantiating existing models.
	A new instance will be created with all default parameters and with the name given.
	THe returned instPtr will point irectly to the created instance and can be used 
	by subsequent calls to set parameters, bind node, and query parameters.

	Circuit is the circuit structure describing the Circuit this instance is to be a part of. ModelPtr
	will be a pointer to the actual model that is to be instantiated. ZnstPtr points to the pointer the 
	newInstance routine should initialize to point to the new instance. Nameid is the unique identifier of the
	instance to be created.
*/
///<param = *ckt> Circuit to operate on </param>
///<param = *modPtr> Model to create instance of </param>
///<param = **instPtr> Returned new instance </param>
///<param = name> Name of the new instance </param>
int CKTcrtElt(GENERIC *ckt, GENERIC *inModPtr, GENERIC **inInstPtr, IFuid name)
{
	GENinstance *instPtr = NULL;
	GENmodel *modPtr = (GENmodel*)inModPtr;
	extern SPICEdev *DEVices[];
	int error;
	int type;

	if ((GENmodel *)modPtr == (GENmodel*)NULL)
		return(E_NOMOD);

	type = ((GENmodel*)modPtr)->GENmodType;
	error = CKTfndDev(ckt, &type, (GENERIC**)&instPtr, name, inModPtr, (char *)NULL);

	if (error == OK)
	{
		if (inInstPtr)
			*inInstPtr = (GENERIC *)instPtr;

		return(E_EXISTS);
	}
	else if (error != E_NODEV)
		return(error);

	instPtr = (GENinstance *)MALLOC(*DEVices[type]->DEVinstSize);

	if (instPtr == (GENinstance *)NULL)
		return(E_NOMEM);

	instPtr->GENname = name;
	instPtr->GENmodPtr = modPtr;
	instPtr->GENnextInstance = modPtr->GENinstances;
	modPtr->GENinstances = instPtr;

	if (inInstPtr != NULL)
		*inInstPtr = (GENERIC *)instPtr;

	return(OK);
}
