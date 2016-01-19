/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "inpdefs.h"
#include "util.h"
#include "strext.h"
#include "suffix.h"


extern INPmodel *modtab;



/*
	Used to search the list of the ".model" cards found during pass 1 of the parser to
	determine whether name is the name of a known model or not.
	A return of zro indicates the name is
	not that of a model, while one indicates that it is a model name.
	The comparison is mafe by comparing
	the actual strings rather than pointers as is usually done, since this routine is used to solve the
	ambiguity in the BJT device card where the 5th token on the line may be either a model or node
	name, and thus hasn't been entered into a symbol table yet
*/
///<param name = "*name"> Model name to look up </param>
int INPlookMod(char *name)
{
	register INPmodel **i;

	for (i = &modtab; *i != (INPmodel *)NULL; i = &((*i)->INPnextModel))
	{
		if (strcmp((*i)->INPmodName, name) == 0)
		{
			/* found the model in question - return true */
			return(1);
		}
	}
	/* didn't find model - return false */
	return(0);
}

