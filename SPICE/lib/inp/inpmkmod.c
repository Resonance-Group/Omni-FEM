/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "util.h"
#include "inpdefs.h"
#include "iferrmsg.h"
#include "strext.h"
#include "suffix.h"

INPmodel *modtab;

    /* create/lookup a 'model' entry */


/*
	Used to store the ".MODEL" cards found during pass 1 of the parser 
	into a list where they can be accessed during pass 2 without actually parsing the entire model
*/
///<param name = "*token"> The model name </param>
///<param name = "type"> The type of the model </param>
///<param name = "line"> The line representing the model </param>
int INPmakeMod(char *token, int type, card *line)
{
	register INPmodel **i;

	for (i = &modtab; *i != (INPmodel *)NULL; i = &((*i)->INPnextModel))
	{
		if (strcmp((*i)->INPmodName, token) == 0)
		{
			return(OK);
		}
	}

	*i = (INPmodel *)MALLOC(sizeof(INPmodel));

	if (*i == NULL)
		return(E_NOMEM);

	(*i)->INPmodName = token;
	(*i)->INPmodType = type;
	(*i)->INPnextModel = (INPmodel *)NULL;
	(*i)->INPmodUsed = 0;
	(*i)->INPmodLine = line;
	(*i)->INPmodfast = NULL;

	return(OK);
}
