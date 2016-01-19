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
	Parses a SPICE2 format bipolar junction transistor card.
	Due to the ambiguity present in the language after the SPICE2 restriction on node names is lifted,
	this routine must attempt to distinguish between the 2 cases.

	Q1 collector base emitter model other-parameters
	Q2 collector base emitter bulk model other-parameters

	To do this, the collected list of models is consulted and if a BJT model exists matching the 5th token
	on the line, it is assumed to be the model name and the model is used.
	If the 5th token does not match a BJT model found during pass 1, that token is assumed to be the bulk node 
	and the 6th token to be the model name.
	Thus, it is very important to include a known model name in a BJT instantiation.
	The final arguement to this function which distinguishes it from all the rest of the INPx
	functions is the ground node of the circuit which is needed to connect the bulk node if the bulk node is not specified
*/
///<param name = "*ckt"> The current circuit </param>
///<param name = "*tab"> The symbol table </param>
///<param name = "*current"> The current input line </param>
///<param name = "*gnode"> Node structure for the ground node </param>
void INP2Q(GENERIC *ckt, INPtables *tab, card *current, GENERIC *gnode)
{

	/* Qname <node> <node> <node> [<node>] <model> [<val>] [OFF]
	 *       [IC=<val>,<val>] */

	int mytype; /* the type we looked up */
	int type;   /* the type the model says it is */
	char *line; /* the part of the current line left to parse */
	char *name; /* the resistor's name */
	char *nname1;   /* the first node's name */
	char *nname2;   /* the second node's name */
	char *nname3;   /* the third node's name */
	char *nname4;   /* the fourth node's name */
	GENERIC *node1; /* the first node's node pointer */
	GENERIC *node2; /* the second node's node pointer */
	GENERIC *node3; /* the third node's node pointer */
	GENERIC *node4; /* the fourth node's node pointer */
	int error;      /* error code temporary */
	GENERIC *fast;  /* pointer to the actual instance */
	IFvalue ptemp;  /* a value structure to package resistance into */
	int waslead;    /* flag to indicate that funny unlabeled number was found */
	double leadval; /* actual value of unlabeled number */
	char *model;    /* the name of the model */
	INPmodel *thismodel;    /* pointer to model description for user's model */
	GENERIC *mdfast;    /* pointer to the actual model */
	IFuid uid;      /* uid of default model */

	mytype = INPtypelook("BJT");

	if (mytype < 0)
	{
		LITERR("Device type BJT not supported by this binary\n")
			return;
	}
	line = current->line;
	INPgetTok(&line, &name, 1);
	INPinsert(&name, tab);
	INPgetTok(&line, &nname1, 1);
	INPtermInsert(ckt, &nname1, tab, &node1);
	INPgetTok(&line, &nname2, 1);
	INPtermInsert(ckt, &nname2, tab, &node2);
	INPgetTok(&line, &nname3, 1);
	INPtermInsert(ckt, &nname3, tab, &node3);
	INPgetTok(&line, &model, 1);

	if (INPlookMod(model))
	{
		/* do nothing for now */
		node4 = gnode;
		/* no action required */
	}
	else
	{
		nname4 = model;
		INPtermInsert(ckt, &nname4, tab, &node4);
		INPgetTok(&line, &model, 1);
	}

	INPinsert(&model, tab);
	current->error = INPgetMod(ckt, model, &thismodel, tab);

	if (thismodel != NULL)
	{
		if (mytype != thismodel->INPmodType)
		{
			LITERR("incorrect model type")
				return;
		}
		type = mytype;
		mdfast = (thismodel->INPmodfast);
	}
	else
	{
		type = mytype;

		if (!tab->defQmod)
		{
			/* create default Q model */
			IFnewUid(ckt, &uid, (IFuid)NULL, "Q", UID_MODEL, (GENERIC**)NULL);
			IFC(newModel, (ckt, type, &(tab->defQmod), uid))
		}

		mdfast = tab->defQmod;
	}

	IFC(newInstance, (ckt, mdfast, &fast, name))
	IFC(bindNode, (ckt, fast, 1, node1))
	IFC(bindNode, (ckt, fast, 2, node2))
	IFC(bindNode, (ckt, fast, 3, node3))
	IFC(bindNode, (ckt, fast, 4, node4))
	PARSECALL((&line, ckt, type, fast, &leadval, &waslead, tab))
	if (waslead)
	{
		ptemp.rValue = leadval;
		GCA(INPpName, ("area", &ptemp, ckt, type, fast))
	}
}
