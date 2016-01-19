/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

    /* CKTinst2Node
     *  get the name and node pointer for a node given a device it is
     * bound to and the terminal of the device.
     */

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "sperror.h"
#include "cktdefs.h"
#include "gendefs.h"
#include "devdefs.h"
#include "suffix.h"


extern SPICEdev *DEVices[];

/*
	This function, again provided for front ends which do not maintain full symbol tables, provides both the name (IFuid)
	and node pointer of a node given an instance and terminal number it is attached to.

	This function allows the front end to find the node pointer and node unique identifier of the circuit
	node a pdcular terminal of an instance is bound to. If the node has not been bound yet, instTo-
	Nude will rem the node this terminal will be connected to by default if no call to bindhrode is made
	and the simulator provides default bindings, otherwise it will set nude and nudeUid to NULL.
*/
///<param name = "*ckt"> Circuit to operate on </param>
///<param name = "*instPtr"> pointer to instance </param>
///<param name = "terminal"> terminal number </param>
///<param name = "**node"> node structure </param>
///<param = "*nodeName"> node name </param>
int CKTinst2Node(GENERIC *ckt, GENERIC *instPtr, int terminal, GENERIC **node, IFuid *nodeName)
{
	int nodenum;
	register int type;
	CKTnode *here;

	type = ((GENinstance *)instPtr)->GENmodPtr->GENmodType;

	if (*((*DEVices[type]).DEVpublic.terms) >= terminal && terminal > 0)
	{
		switch (terminal)
		{
		default:
			return(E_NOTERM);
		case 1:
			nodenum = ((GENinstance *)instPtr)->GENnode1;
			break;
		case 2:
			nodenum = ((GENinstance *)instPtr)->GENnode2;
			break;
		case 3:
			nodenum = ((GENinstance *)instPtr)->GENnode3;
			break;
		case 4:
			nodenum = ((GENinstance *)instPtr)->GENnode4;
			break;
		case 5:
			nodenum = ((GENinstance *)instPtr)->GENnode5;
			break;
		}
		/* ok, now we know its number, so we just have to find it.*/
		for (here = ((CKTcircuit*)ckt)->CKTnodes; here; here = here->next)
		{
			if (here->number == nodenum)
			{
				/* found it */
				*node = (GENERIC*)here;
				*nodeName = here->name;
				return(OK);
			}
		}
		return(E_NOTFOUND);
	}
	else
	{
		return(E_NOTERM);
	}
}
