/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

    /* CKTdump(ckt)
     * this is a simple program to dump the rhs vector to stdout
     */

#include "spice.h"
#include <stdio.h>
#include "smpdefs.h"
#include "cktdefs.h"
#include "suffix.h"



/*
	Used by all of the routines in SPICE3 which produce a real valued solution vector in the 
	CKTrhsOld vector.
	Ref is the value of ther reference vector which is varying the most frequently, plot is the plot identifier,
	and ckt identifies the circuit from which the output vectors are to be taken.
	The appropriate real-valued solution is constructed and passed to the output interface options
*/
///<param name = "*ckt> The circuit to operate on </param>
///<param name = "ref> Value of the reference variables </param>
///<param name = "*plot> Plot pointer retruned by OUTpBeginPlot </param>
void CKTdump(register CKTcircuit *ckt, double ref, GENERIC *plot)
{
	IFvalue refData;
	IFvalue valData;

	refData.rValue = ref;
	valData.v.numValue = ckt->CKTmaxEqNum - 1;
	valData.v.vec.rVec = ckt->CKTrhsOld + 1;
	(*(SPfrontEnd->OUTpData))(plot, &refData, &valData);
}
