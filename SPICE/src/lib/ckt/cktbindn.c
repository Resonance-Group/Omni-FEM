/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

/* CKTbindNode
 *  bind a node of the specified device of the given type to its place
 *  in the specified circuit.
 */

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "smpdefs.h"
#include "cktdefs.h"
#include "util.h"
#include "devdefs.h"
#include "sperror.h"
#include "suffix.h"

extern SPICEdev *DEVices[];

/*
	CKTbindNode connects a node in the circuit with a specific terminal of a device terminal of a device instance.
	For this to work, both the node and device instance must already exist, and the termianl number specified must be less than 
	or equal to the maximum number of terminals support by the device. 
	Note that terminals are numbered.

	This function connects a terminal of an instance to a node in the circuit. The terminal parameter
	is used to select a terminal by number. Terminals of the device are numbered from 1 to the maximum
	terminal number allowed, while nodes are passed by the pointers returned by newNode and
	groundhrode. Note that the terminal numbering is assumed to correspond to the ordering of the term-
	Names field in the device structure.
*/
///<param name = "*ckt"> The circuit to operate on </param>
///<param name = "*fast"> POinter to instance </param>
///<param name = "term"> Terminal number </param>
///<param name = "*node"> Node structure </param>
int CKTbindNode(GENERIC *ckt, GENERIC *fast, int term, GENERIC *node)
{
    int mappednode;
    register int type = ((GENinstance *)fast)->GENmodPtr->GENmodType;

    mappednode = ((CKTnode *)node)->number;

    if(*((*DEVices[type]).DEVpublic.terms) >= term && term >0 ) 
	{
        switch(term) 
		{
            
            case 1:
                ((GENinstance *)fast)->GENnode1 = mappednode;
                break;
            case 2:
                ((GENinstance *)fast)->GENnode2 = mappednode;
                break;
            case 3:
                ((GENinstance *)fast)->GENnode3 = mappednode;
                break;
            case 4:
                ((GENinstance *)fast)->GENnode4 = mappednode;
                break;
            case 5:
                ((GENinstance *)fast)->GENnode5 = mappednode;
                break;
			default:
				return(E_NOTERM);
        }
    } 
	else 
	{
        return(E_NOTERM);
    }
	
	return(OK);
}
