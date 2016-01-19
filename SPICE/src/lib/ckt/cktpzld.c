/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
**********/

#include "spice.h"
#include <stdio.h>
#include "pzdefs.h"
#include "smpdefs.h"
#include "cktdefs.h"
#include "complex.h"
#include "devdefs.h"
#include "sperror.h"
#include "suffix.h"

extern SPICEdev *DEVices[];


/*
	The primary driving routine for the Pole Zero analysis device evaluation.
	Each device's pole zero evaluation will be called to evaluate the device thus loading the complex
	sparse matrix and the RHS. (Statement no longer applies???) -> Following this, depending on type, column
	operations are performed in the resulting matrix structure before the matrix is solved.
	The possible values of type and their meaning are:

	TYPE	Operation
	----	---------
	1		clear row and column I
	2		clear row and column I-G
	3		clear row and column I
	4		clear row and column J-K
	5		clear row and column I-G
	6		no-op
	7		no-op
	8		illegal
	9		illegal
	10		illegal
	11		clear row and column J
	12		clear row and column J
	13		clear row and column J-K
	14		clear row and column J-K
	15		clear row and column J-K
	16		clear row and column J-K
	17		clear row and column J
*/
///<param name = "*ckt"> Circuit to operate on </param>
///<param name = "*s"> Complex Multiplie </param>
int CKTpzLoad(CKTcircuit *ckt, SPcomplex *s)
{
    PZAN *pzan = (PZAN *) (ckt->CKTcurJob);
    SMPelement *elt, *telt;
    int solution_col;
    int error;
    int i;

	for (i = 0; i <= SMPmatSize(ckt->CKTmatrix); i++)
	{
		ckt->CKTrhs[i] = 0.0;
		ckt->CKTirhs[i] = 0.0;
	}

    SMPcClear(ckt->CKTmatrix);
	for (i = 0; i < DEVmaxnum; i++)
	{
		if (DEVices[i]->DEVpzLoad != NULL && ckt->CKThead[i] != NULL)
		{
			error = (*DEVices[i]->DEVpzLoad)(ckt->CKThead[i], ckt, s);
			if (error)
				return(error);
		}
	}

#ifdef notdef
	printf("*** Before PZ adjustments *\n");
	SMPprint(ckt->CKTmatrix, stdout);
#endif

	if (pzan->PZbalance_col && pzan->PZsolution_col)
	{
		SMPcAddCol(ckt->CKTmatrix, pzan->PZbalance_col, pzan->PZsolution_col);
		/* AC sources ?? XXX */
	}

	if (pzan->PZsolution_col)
	{
		SMPcZeroCol(ckt->CKTmatrix, pzan->PZsolution_col);
	}

	/* Driving function (current source) */
	if (pzan->PZdrive_pptr)
		*pzan->PZdrive_pptr = 1.0;
	if (pzan->PZdrive_nptr)
		*pzan->PZdrive_nptr = -1.0;

#ifdef notdef
	printf("*** After PZ adjustments *\n");
	SMPprint(ckt->CKTmatrix, stdout);
#endif

	return(OK);
}

