/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

    /*  INPgetTitle(ckt,data)
     *      get the title card from the specified data deck and pass
     *      it through to SPICE-3.
     */

#include "spice.h"
#include <stdio.h>
#include "util.h"
#include "inpdefs.h"
#include "iferrmsg.h"
#include "cpstd.h"
#include "fteext.h"
#include "suffix.h"



/*
	Obsolete routine used by earlier version of the parse to grab the title card 
	off of the front of the input deck and call the initialization routine to create a new circuit with that
	name.
*/
///<param name = "**ckt"> The circuit to create and save title of </param>
///<param name = "**data"> The data structure representing the input </param>
int INPgetTitle(GENERIC **ckt, card **data)
{
	int error;

	error = (*(ft_sim->newCircuit))(ckt);

	if (error)
		return(error);

	*data = (*data)->nextcard;
	return(OK);
}

