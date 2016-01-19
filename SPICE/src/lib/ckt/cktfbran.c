/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

    /* CKTfndBranch(ckt,name)
     * this is a driver program to iterate through all the various
     * findBranch functions provided for the circuit elements in the
     * given circuit 
     */

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "devdefs.h"
#include "suffix.h"

/*
	Used by SPICE3 to find the branch equations associated with other devices to allow them to act as controls.
	The routine will call every device type specific DEVfindBranch routine fow which there are corresponding 
	devices in existance, each of which will check for the existance of a device with the given IFuid and return the equation
	number of the corresponding current
*/
///<param = *ckt> Circuit to operate on </param>
///<param = name> Name of device to find branch of </param>
int CKTfndBranch(register CKTcircuit *ckt, IFuid name)
{
	extern SPICEdev *DEVices[];

	register int i;
	int j;

	for (i = 0; i < DEVmaxnum; i++)
	{
		if ((*DEVices[i]).DEVfindBranch != NULL && ckt->CKThead[i] != NULL)
		{
			j = (*((*DEVices[i]).DEVfindBranch))(ckt, ckt->CKThead[i], name);
			if (j != 0)
				return(j);
		}
	}
	return(0);
}
