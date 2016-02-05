/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/


#include "spice.h"
#include "const.h"
#include "optdefs.h"
#include "ifsim.h"
#include <stdio.h>
#include "util.h"
#include "cktdefs.h"
#include "suffix.h"



/*
	This is the routine used for uerying overall information about the circuit.
	Initially used for accounting information, thus the strange name, it is the opposite of CKTsetOpt for
	setting option values in the circuit.
	Note that since the option values are not transferred into the circuit itself until the task is actually started,
	this function will not return useful data until the task has been started even though options
	may have been set in the options analysis.
	This behaviour permits different tasks associated with the same circuit to have different options since the options themselves 
	associate with the task, but this function returns data about the actual current state of the circuit
*/
///<param name = "*ckt"> Circuit to operate on </param>
///<param name = "*anal"> Pointer to the options analysis </param>
///<param name = "which"> Which option/accounting value do we want? </param>
///<param name = "*val"> Value to return </param>
int CKTacct(CKTcircuit *ckt, GENERIC *anal, int which, IFvalue *val)
{
	switch (which)
	{

	case OPT_EQNS:
		val->iValue = ckt->CKTmaxEqNum;
		break;
	case OPT_ITERS:
		val->iValue = ckt->CKTstat->STATnumIter;
		break;
	case OPT_TRANIT:
		val->iValue = ckt->CKTstat->STATtranIter;
		break;
	case OPT_TRANCURITER:
		val->iValue = ckt->CKTstat->STATnumIter - ckt->CKTstat->STAToldIter;
		break;
	case OPT_TRANPTS:
		val->iValue = ckt->CKTstat->STATtimePts;
		break;
	case OPT_TRANACCPT:
		val->iValue = ckt->CKTstat->STATaccepted;
		break;
	case OPT_TRANRJCT:
		val->iValue = ckt->CKTstat->STATrejected;
		break;
	case OPT_TOTANALTIME:
		val->rValue = ckt->CKTstat->STATtotAnalTime;
		break;
	case OPT_TRANTIME:
		val->rValue = ckt->CKTstat->STATtranTime;
		break;
	case OPT_LOADTIME:
		val->rValue = ckt->CKTstat->STATloadTime;
		break;
	case OPT_REORDTIME:
		val->rValue = ckt->CKTstat->STATreorderTime;
		break;
	case OPT_DECOMP:
		val->rValue = ckt->CKTstat->STATdecompTime;
		break;
	case OPT_SOLVE:
		val->rValue = ckt->CKTstat->STATsolveTime;
		break;
	case OPT_TRANDECOMP:
		val->rValue = ckt->CKTstat->STATtranDecompTime;
		break;
	case OPT_TRANSOLVE:
		val->rValue = ckt->CKTstat->STATtranSolveTime;
		break;
	case OPT_TEMP:
		val->rValue = ckt->CKTtemp - CONSTCtoK;
		break;
	case OPT_TNOM:
		val->rValue = ckt->CKTnomTemp - CONSTCtoK;
		break;
	default:
		return(-1);
	}
	return(0);
}
