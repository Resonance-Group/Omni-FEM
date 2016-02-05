/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

/* CKTdltMod
 *  delete the specified model - not yet supported in spice 
 */

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "ifsim.h"
#include "sperror.h"
#include "util.h"
#include "misc.h"
#include "suffix.h"


/*
	This function is provided for compatability with the front end interface and future expansion, but
	is not implemented yet.
	The current action is to return E_UNSUPP as permitted by the front end to indicate that SPICE3
	does not yet have capability of deleting a model from the circuit.
	The function should bot be hard to implement given the existing structure and the constaints on the
	function required by the front end, but it is not useful until the CKTdltInst function has been implemented.

	This function removes the specified model from the circuit. After return, modelPtr is no longer valid
	and should not be used in any further subroutine. If any instances of the specified model exist,
	deleteMudel should return E_NOTEMPTY without deleting anythmg.
*/
///<param name = "*cktp"> Circuit to operate on </param>
///<param name = "*model"> Model being deleted </param>
int CKTdltMod(GENERIC *cktp, GENERIC *modPtr)
{
	CKTcircuit *ckt = (CKTcircuit *)cktp;
	GENmodel *m = (GENmodel *)modPtr, *mod, **prevp;
	GENinstance *h, *next_i;
	int	error;

	prevp = &ckt->CKThead[m->GENmodType];
	for (mod = *prevp; m && mod != m; mod = mod->GENnextModel)
		prevp = &mod->GENnextModel;

	if (!mod)
		return OK;

	*prevp = m->GENnextModel;

	for (h = m->GENinstances; h; h = next_i)
	{
		next_i = h->GENnextInstance;
		error = (*(SPfrontEnd->IFdelUid))((GENERIC *)ckt, h->GENname, UID_INSTANCE);
		tfree(h);
	}
	error = (*(SPfrontEnd->IFdelUid))((GENERIC *)ckt, m->GENmodName, UID_MODEL);
	tfree(m);
	return(OK);
}
