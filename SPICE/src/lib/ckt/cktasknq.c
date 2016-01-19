/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

    /*
     *CKTaskNodQst
     *
     *   ask about a parameter on a node.
     */

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "iferrmsg.h"
#include "cktdefs.h"
#include "util.h"
#include "suffix.h"



/*
	This function provides the inverse of CKTsetNodePm by allowing the front end 
	to find out the value of any of the node parameters.

	The node 'node' in circuit 'circuit' is queried for the value of its parameter quest which is returned
	in the appropriate field in the supplied value structure. As with the setNodeParm function, the selector
	allows the specification of a single value within a uni- or multi- dimensional array, but is ignored
	unless F-SELECT or IF-VSELECT is specified in the warm structure for the parameter.
*/
///<param=*ckt> circuit to operate on </param>
///<param=*node> Node structure </param>
///<param=parm> parameter number </param>
///<param=*value> parameter value </param>
///<param=*selector> sub parameter selector </param>
int CKTaskNodQst(GENERIC *ckt, GENERIC *node, int parm, IFvalue *value, IFvalue *selector)
{
	if (!node)
		return(E_BADPARM);

	switch (parm)
	{
	case PARM_NS:
		value->rValue = ((CKTnode *)node)->nodeset;
		break;

	case PARM_IC:
		value->rValue = ((CKTnode *)node)->ic;
		break;

	case PARM_NODETYPE:
		value->iValue = ((CKTnode *)node)->type;
		break;

	default:
		return(E_BADPARM);
	}
	return(OK);
}
