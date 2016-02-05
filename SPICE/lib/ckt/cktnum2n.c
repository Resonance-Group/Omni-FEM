/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/


#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "sperror.h"
#include "cktdefs.h"
#include "suffix.h"


/*
	Is used to convert a node number to a node structure on which further operations
	may be performed.
	THis is not a very efficient routine as it must linearly seach a linked list but is
	avaiable where such a conversion must be performed
*/
///<param name = "*ckt"> Circuit to operate on </param>
///<param name = "node"> NUmber of equation </param>
CKTnode *CKTnum2nod(CKTcircuit *ckt, int node)
{
	register CKTnode *here;

	for (here = ((CKTcircuit *)ckt)->CKTnodes; here; here = here->next)
	{
		if (here->number == node)
		{
			return(here);
		}
	}
	return((CKTnode *)NULL);
}
