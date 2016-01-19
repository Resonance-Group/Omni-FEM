/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/


#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "util.h"
#include "suffix.h"


/*
	This is a debugging routine used for diagnosing problems with breakpoints.
	It will print a table giving every entry currently in the breakpoint table on the
	standard output device, typically the ternimal. 
	This table is not pretty, nor is it efficient or useful for normal operationgs but it can be indipensable for 
	tracking down mysterious breakpoint troubles.
*/
///<param name = "*ckt"> CIrcuit to operate on </param>
void CKTbreakDump(CKTcircuit *ckt)
{
	register int i;
	for (i = 0; i < ckt->CKTbreakSize; i++)
	{
		(void)printf("breakpoint table entry %d is %g\n", i, *(ckt->CKTbreaks + i));
	}
}
