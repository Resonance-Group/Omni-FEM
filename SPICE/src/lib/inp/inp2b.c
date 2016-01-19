/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1988 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "inpdefs.h"
#include "inpmacs.h"
#include "fteext.h"
#include "suffix.h"



/*
	This routine parses a SPICE2 format input line describing an arbitrary source.
	Since the input language does not allow for teh definition of a model for an arbitrary source,
	this routine generates and maintains in the INPtables structure a defulat model for the arbitrary source,
	creating it when needed and making all sources instances of that model.
*/
///<param name = "*ckt"> The current circuit </param>
///<param name = "*tab"> The symbol table </param>
///<param name = "*current> The current input line </param>
void INP2B(GENERIC *ckt, INPtables *tab, card *current)
{

	/* Bname <node> <node> [V=expr] [I=expr] */

	int type;   /* the type the model says it is */
	char *line; /* the part of the current line left to parse */
	char *name; /* the resistor's name */
	char *nname1;   /* the first node's name */
	char *nname2;   /* the second node's name */
	GENERIC *node1; /* the first node's node pointer */
	GENERIC *node2; /* the second node's node pointer */
	int error;      /* error code temporary */
	GENERIC *fast;  /* pointer to the actual instance */
	int waslead;    /* flag to indicate that funny unlabeled number was found */
	double leadval; /* actual value of unlabeled number */
	IFuid uid;      /* uid for default model name */

		/* Arbitrary source. */
	type = INPtypelook("ASRC");

	if (type < 0)
	{
		LITERR("Device type Asource not supported by this binary\n")
			return;
	}

	line = current->line;
	INPgetTok(&line, &name, 1);
	INPinsert(&name, tab);

	INPgetTok(&line, &nname1, 1);
	error = INPtermInsert(ckt, &nname1, tab, &node1);

	INPgetTok(&line, &nname2, 1);
	error = INPtermInsert(ckt, &nname2, tab, &node2);

	if (!tab->defBmod)
	{
		/* create default B model */
		IFnewUid(ckt, &uid, (IFuid)NULL, "B", UID_MODEL, (GENERIC**)NULL);
		IFC(newModel, (ckt, type, &(tab->defBmod), uid))
	}

	IFC(newInstance, (ckt, tab->defBmod, &fast, name))
		IFC(bindNode, (ckt, fast, 1, node1))
		IFC(bindNode, (ckt, fast, 2, node2))
		PARSECALL((&line, ckt, type, fast, &leadval, &waslead, tab))
}
