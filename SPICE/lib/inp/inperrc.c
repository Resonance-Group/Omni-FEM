/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include "strext.h"
#include <stdio.h>
#include "inpdefs.h"
#include "util.h"
#include "suffix.h"



/*
	Used to concatenate error messages during the parsing operation.
	a and b are assumed to be either malloc'ed character string or NULL pointers.
	If both strings are non-null, they will be concatenated together into a new string separated by a neline,
	and their original storage will be free'd.
	If either string is null, the other will be retunred unchanged.
	If both are null, null will be returned.
*/
///<param name = "*a"> First string to concatenate </param>
///<param name = "*b"> Second string to concatenate </param>
char *INPerrCat(char *a, char *b)
{

	if (a != (char *)NULL)
	{
		if (b == (char *)NULL)
		{ /* a valid, b null, return a */
			return(a);
		}
		else
		{ /* both valid  - hard work...*/
			register char *errtmp;
			errtmp = (char *)MALLOC((strlen(a) + strlen(b) + 2)*sizeof(char));
			(void)strcpy(errtmp, a);
			(void)strcat(errtmp, "\n");
			(void)strcat(errtmp, b);
			FREE(a);
			FREE(b);
			return(errtmp);
		}
	}
	else
	{ /* a null, so return b */
		return(b);
	}
}
