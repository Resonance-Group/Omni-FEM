/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

    /* CKTacDump(ckt,freq,file)
     * this is a simple program to dump the complex rhs vector 
     * into the rawfile.
     */

#include "spice.h"
#include <stdio.h>
#include "smpdefs.h"
#include "cktdefs.h"
#include "iferrmsg.h"
#include "ifsim.h"
#include "util.h"
#include "suffix.h"



/*
	This routine is used by the AC analysis pahse of SPICE3 to output the computed results.
	CKTacDump will properly format the contents of the CKTrhsOld and CKTirhsOld vectors and pass them
	to the output routine along with current frequency as the real-valued independent variable
*/
///<param = ckt> Circuit to operate on </param>
///<param = freq> Frequency at which analysis was done </param>
///<param = *plot> Plot pointer returned by OUTpBeginPlot </param>
int CKTacDump(register CKTcircuit *ckt, double freq, GENERIC *plot)
{
	register double *rhsold;
	register double *irhsold;
	register int i;
	register IFcomplex *data;
	IFvalue freqData;
	IFvalue valueData;

	rhsold = ckt->CKTrhsOld;
	irhsold = ckt->CKTirhsOld;
	freqData.rValue = freq;
	valueData.v.numValue = ckt->CKTmaxEqNum - 1;
	data = (IFcomplex *)MALLOC((ckt->CKTmaxEqNum - 1)*sizeof(IFcomplex));
	// TODO: Add in a check to make sure that data does not become a null pointer
	valueData.v.vec.cVec = data;
	for (i = 0; i < ckt->CKTmaxEqNum - 1; i++)
	{
		data[i].real = rhsold[i + 1];
		data[i].imag = irhsold[i + 1];
	}
	(*(SPfrontEnd->OUTpData))(plot, &freqData, &valueData);
	FREE(data);
	return(OK);

}
