/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

    /*
     *CKTsetNodPm
     *
     *   set a parameter on a node.
     */

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "iferrmsg.h"
#include "cktdefs.h"
#include "util.h"
#include "suffix.h"


/* ARGSUSED */

/*
	CKTsetNodPm is used to set parameters on circuit nodes.
	This is intended to generalize the capabilities of the ".nodeset" and ".ic" commands of SPICE2
	by allowing any parameters to be set on nodes.
	The selector argument is currently unused but is specified by the front end interface.

	The node 'node' in circuit 'circuit' has its parameter parm set to the appropriate value taken from
	the value structure. The selector structure provides additional information about the way the parameter
	is to be modified. Specifically, it is either an integer or vector of integers which selects a specific
	enuy from the set of possible values to set. For example, if a possible parameter is a multidimensional
	matrix, and a user wishes to change only a single entry in the matrix, rather than passing
	the entire matrix it is possible to set the selector structure to have the array of matrix subscripts to
	specify the element to be changed and place just its value in the value field. Another parameter with
	a similar but not identical name may be used to manipulate the entire array or matrix. Note that for
	any parameter not declared with the IF-SELECT or IF-VSELECT bit in its IFparm structure, this argument
	is ignored.
*/
///<param=*ckt> Circuit to operate on </param>
///<param=*node> Node structure </param>
///<param=parm> parameter number </param>
///<param=*value> parameter value </param>
///<param=*selector> sub parameter selector </param>
int CKTsetNodPm(GENERIC *ckt, GENERIC *node, int parm, IFvalue *value, IFvalue *selector)
{
	if (!node)
		return(E_BADPARM);

	switch (parm)
	{

	case PARM_NS:
		((CKTnode *)node)->nodeset = value->rValue;
		((CKTnode *)node)->nsGiven = 1;
		break;

	case PARM_IC:
		((CKTnode *)node)->ic = value->rValue;
		((CKTnode *)node)->icGiven = 1;
		break;

	case PARM_NODETYPE:
		((CKTnode *)node)->type = value->iValue;
		break;

	default:
		return(E_BADPARM);
	}
	return(OK);
}
