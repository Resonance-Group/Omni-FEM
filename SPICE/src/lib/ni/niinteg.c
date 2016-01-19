/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

/* NIintegrate(ckt,geq,ceq,cap,qcap)
 *  integrate the specified capacitor - method and order in the
 *  ckt structure, ccap follows qcap.
 */

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "sperror.h"
#include "util.h"
#include "suffix.h"

#define ccap qcap+1



/*
	This routine performs the numerical integration required for an individual energy storage device.
	The integration coefficients computed by NIcomCof and stored in the CKTcircuit structure and the capacitance
	of the capacitor in question, along with the current charge and prvious charge and current values are used to compute
	the new current and the equivalent circuit current source and conductance values.
*/
///<param name = "*ckt"> Circuit to operate on </param>
///<param name = "*geq"> Equivalent Conductance </param>
///<param name = "*ceq"> Equivalent Current source </param>
///<param name = "cap"> Capacitance </param>
///<param name = "qcap"> Offset in state vector of charge </param>
int NIintegrate(register CKTcircuit *ckt, double *geq, double *ceq, double cap, int qcap)
{
	static char *ordmsg = "Illegal integration order";
	static char *methodmsg = "Unknown integration method";

	switch (ckt->CKTintegrateMethod)
	{

	case TRAPEZOIDAL:
		switch (ckt->CKTorder)
		{
		case 1:
			*(ckt->CKTstate0 + ccap) = ckt->CKTag[0] * (*(ckt->CKTstate0 + qcap)) + ckt->CKTag[1] * (*(ckt->CKTstate1 + qcap));
			break;
		case 2:
			*(ckt->CKTstate0 + ccap) = -*(ckt->CKTstate1 + ccap) * ckt->CKTag[1] + ckt->CKTag[0] * (*(ckt->CKTstate0 + qcap) - *(ckt->CKTstate1 + qcap));
			break;
		default:
			errMsg = MALLOC(strlen(ordmsg) + 1);
			strcpy(errMsg, ordmsg);
			return(E_ORDER);
		}
		break;
	case GEAR:
		*(ckt->CKTstate0 + ccap) = 0;

		switch (ckt->CKTorder)
		{

		case 6:
			*(ckt->CKTstate0 + ccap) += ckt->CKTag[6] * *(ckt->CKTstate6 + qcap);
			/* fall through */
		case 5:
			*(ckt->CKTstate0 + ccap) += ckt->CKTag[5] * *(ckt->CKTstate5 + qcap);
			/* fall through */
		case 4:
			*(ckt->CKTstate0 + ccap) += ckt->CKTag[4] * *(ckt->CKTstate4 + qcap);
			/* fall through */
		case 3:
			*(ckt->CKTstate0 + ccap) += ckt->CKTag[3] * *(ckt->CKTstate3 + qcap);
			/* fall through */
		case 2:
			*(ckt->CKTstate0 + ccap) += ckt->CKTag[2] * *(ckt->CKTstate2 + qcap);
			/* fall through */
		case 1:
			*(ckt->CKTstate0 + ccap) += ckt->CKTag[1] * *(ckt->CKTstate1 + qcap);
			*(ckt->CKTstate0 + ccap) += ckt->CKTag[0] * *(ckt->CKTstate0 + qcap);
			break;

		default:
			return(E_ORDER);

		}
		break;

	default:
		errMsg = MALLOC(strlen(methodmsg) + 1);
		strcpy(errMsg, methodmsg);
		return(E_METHOD);
	}
	*ceq = *(ckt->CKTstate0 + ccap) - ckt->CKTag[0] * *(ckt->CKTstate0 + qcap);
	*geq = ckt->CKTag[0] * cap;
	return(OK);
}
