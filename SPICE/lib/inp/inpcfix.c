/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <ctype.h>
#include "inpdefs.h"
#include "suffix.h"



/*
	Operates on a character string, normally an input line record, and converts all characters to lower case.
	SInce the SPICE2 input syntax is case insensitive, and SPICE3 has been written entirely in terms 
	of lower case strings, the simplest step is to convert all SPICE2 format inputs all to lower case before 
	proceeding.
*/
///<param name = "*string"> String to convert to lower case </param>
void INPcaseFix(register char *string)
{

	while (*string) 
	{
		if (isupper(*string)) 
		{
			*string = tolower(*string);
		}
		string++;
	}
}
