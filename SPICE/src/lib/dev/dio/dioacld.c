/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "util.h"
#include "diodefs.h"
#include "sperror.h"
#include "suffix.h"



int DIOacLoad(GENmodel *inModel, register CKTcircuit *ckt)
{
	register DIOmodel *model = (DIOmodel*)inModel; // Passing the Circuit model into a local variable. This is the matrix that will be solves 
	double gspr;
	double geq;
	double xceq;
	register DIOinstance *here;

	/*  loop through all the diode models */
	for (; model != NULL; model = model->DIOnextModel) 
	{
		/* loop through all the instances of the model */
		for (here = model->DIOinstances; here != NULL; here = here->DIOnextInstance) 
		{
			/* Calculating Constants */
			gspr = model->DIOconductance*here->DIOarea;
			geq = *(ckt->CKTstate0 + here->DIOconduct);
			xceq = *(ckt->CKTstate0 + here->DIOcapCurrent) * ckt->CKTomega;

			/* This section is the STAMP of the diode for AC analysis */
			*(here->DIOposPosPtr) += gspr;
			*(here->DIOnegNegPtr) += geq;
			*(here->DIOnegNegPtr + 1) += xceq;
			*(here->DIOposPrimePosPrimePtr) += geq + gspr;
			*(here->DIOposPrimePosPrimePtr + 1) += xceq;
			*(here->DIOposPosPrimePtr) -= gspr;
			*(here->DIOnegPosPrimePtr) -= geq;
			*(here->DIOnegPosPrimePtr + 1) -= xceq;
			*(here->DIOposPrimePosPtr) -= gspr;
			*(here->DIOposPrimeNegPtr) -= geq;
			*(here->DIOposPrimeNegPtr + 1) -= xceq;
		}
	}
	return(OK);
}
