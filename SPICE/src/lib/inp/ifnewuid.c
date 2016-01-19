/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1988 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "inpdefs.h"
#include "util.h"
#include "ifsim.h"
#include "iferrmsg.h"
#include "cpdefs.h"
#include "fteext.h"
#include "suffix.h"



/*
	This function provides a mapping from names to the unique identifiers used to distinguish between
	named entities.
	The unique identifiers are pointer sized objects whcih can be compared to determine the equality
	of the referenced items.
	This implementation simply generates the full name specified by the arguement by concatenating the siffux
	with the existing ID with the # character as a seperator.
	This identifying character string is then inserted in one of the two string tables
	and the pointer to the string in the string table used as the unique identifier.
	2 string tables are used to keep the name spaces for nodes and other signa names distinct fron that for models,
	device names, and analysis names.

	This function allows a Simulator to generate a new IFuid from an existing IFuid. The new
	IFuid will be named as if the name corresponding to olduid had the character string sum appended to
	it with a front end specified character added to ensure uniqueness. The suffix must be made entirely
	from alphanumeric characters, upper and lower case letters and digits. The type field is used to
	specify to the front end the use that will be ma& of the IFuid. In the event that names must be generated
	from scratch for such things as time, the olduid should be specified as the reserved IFuid value
	0. Current legal tvpes UID-ANALYSIS, UID-TASK, UID-INSTANCE, UID-MODEL, UID - SIGNAL,
	and UID - OTHER for an id to be used to name an analysis, task, instance, model, any node or other
	naturally computed output of the circuit, and any other type of IFuid that is needed respectively.
	pointer is an optional pointer supplied to the simulator to point to the structure to be associated with
	the IFuid being created. This pointer may be left out completely, or may be ignored by the front end,
	but is supplied for the front end’s convenience in maintaining its data structures in which it may wish
	to keep a pointer to the structures associated with an Il?uid
*/
///<param name = "*ckt"> THe circuit the UID is to be contained in </param>
///<param name = "*newuid"> The UID to be returned </param>
///<param name = "olduid"> The old UID this ID is to be based on </param>
///<param name = "*suffix"> The suffix to logically add to olduid </param>
///<param name = "type"> The type of UID to create </param>
///<param name = "**nodedata"> An optional node structure if adding signal </param>
int IFnewUid(GENERIC *ckt, IFuid *newuid, IFuid olduid, char *suffix, int type, GENERIC **nodedata)
{
	char *newname;
	int error;

	if (olduid)
	{
		newname = (char *)MALLOC(sizeof(char)*(strlen(suffix) + strlen((char*)olduid) + 2));
		/* 2 = '#' + '\0' */
		sprintf(newname, "%s#%s", (char*)olduid, suffix);
	}
	else
	{
		newname = (char *)MALLOC(sizeof(char)*(strlen(suffix) + 1)); /* 1 = '\0' */
		sprintf(newname, "%s", suffix);
	}

	switch (type)
	{
	case UID_ANALYSIS:
	case UID_TASK:
	case UID_INSTANCE:
	case UID_OTHER:
	case UID_MODEL:
		error = INPinsert(&newname, (INPtables *)ft_curckt->ci_symtab);

		if (error && error != E_EXISTS)
			return(error);

		*newuid = (IFuid)newname;
		break;

	case UID_SIGNAL:
		error = INPmkTerm(ckt, &newname, (INPtables *)ft_curckt->ci_symtab, nodedata);

		if (error && error != E_EXISTS)
			return(error);

		*newuid = (IFuid)newname;
		break;

	default:
		return(E_BADPARM);
	}
	return(OK);
}




int IFdelUid(GENERIC *ckt, IFuid uid, int type)
{
	int error;

	switch (type)
	{
	case UID_ANALYSIS:
	case UID_TASK:
	case UID_INSTANCE:
	case UID_OTHER:
	case UID_MODEL:
		error = INPremove(uid, (INPtables *)ft_curckt->ci_symtab);

		if (error && error != E_EXISTS)
			return(error);

		break;

	case UID_SIGNAL:
		error = INPremTerm(uid, (INPtables *)ft_curckt->ci_symtab);

		if (error && error != E_EXISTS)
			return(error);

		break;

	default:
		return(E_BADPARM);
	}
	return(OK);
}
