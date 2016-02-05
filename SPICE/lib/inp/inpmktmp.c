/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "strext.h"
#include "inpdefs.h"
#include "util.h"
#include "suffix.h"



/*
	USed to generate malloc'ed copies of constant strings.
	There are many places, such as error messages, where a string may need to be a literal, but the routines whcih manipulate the
	string later on need to be able to treat all strings equally, and to free those that were obtained from 
	malloc, so literals are copied into malloc'ed memory with INPmkTemp
*/
///<param name = "*string"> String to make a copy of </param>
char *INPmkTemp(char *string)
{
	int len;
	char *temp;

	len = strlen(string);
	temp = MALLOC(len + 1);

	if (temp != (char *)NULL)
		(void)strcpy(temp, string);

	return(temp);
}
