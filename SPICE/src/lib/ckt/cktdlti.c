/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

    /* CKTdltInst
     *  delete the specified instance - not yet supported in spice 
     */

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "ifsim.h"
#include "sperror.h"
#include "util.h"
#include "suffix.h"



// TODO: Add in support to delete the specified instance
/*
	This rountine is intended to allow the deletetion of instance from the circuit.
	All of the bookkeeping necessary to permit this has not been completed,
	so this rountine retuns error code E_UNSUPP to te front enf to indicate
	that SPICE3 does not yet support the deletion of devices.

	This function removes the specified instance from the circuit. After return, instPtr is no longer
	valid and should not be used in any further subroutine calls.
*/
///<param = *ckt> Circuit to operate on </param>
///<param = *inst> Instance being deleted </param>
int CKTdltInst(GENERIC *ckt, GENERIC *instance)
{
	return(E_UNSUPP);
}
