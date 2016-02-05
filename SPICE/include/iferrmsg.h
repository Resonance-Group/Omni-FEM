/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1986 Thomas L. Quarles
**********/

/*
 */

#ifndef IFERRMSGS
#define IFERRMSGS


    /* common error message descriptions */

/*
	A special retunr code provided for the simulator to indicate to various levels of its
	own code as well as the front end that it is pausing as a result of a request from the front end, and not
	terminating normally or in error.
	Pausing on demand
*/
#define E_PAUSE -1      



/*
	No error
*/
#define OK 0



/*
	A very vague message that is provided for errors that don't fit into any other category
	and are of the type that can never occur, but paranoid programming practice dictates that a test for
	them by made anyway.
	Internal error for "can't get here" cases
*/
#define E_PANIC 1



/*
	An attemt has been made to create model, instance, node, or analysis that already exists.
	This can be either an error or a warning, depending on the amount of state maintained by the front end.
	As a warning, it allows a front end to maintain a minimal amount of state about models,
	instances, and analyses, and still correctly handle cases where a usesr makes a second reference to one.
	If the front end is careful about state and never repeats a creation, then this indicates an error in that data.
	The creation routine will not create a new model, instance, or analysis but will instead find and
	return existing one. 
	Not all simulators provide this level of checking and it is undefined what will happen in such a 
	simualtor if a duplicate of a device is created.
	Warning/error - attempt to create duplicate
*/
#define E_EXISTS 2      
 


/*
	An attempt has been made to refence a device which doesn't exist.
*/
#define E_NODEV 3



/*
	An attempt been made to reference a model which doesn't exist
*/
#define E_NOMOD 4       



/*
	An attempt has been made to refence an analysis which doesn't exist.
*/
#define E_NOANAL 5      



/*
	An attempt has been made to bind a circuit node to a terminal that isn't defined for the 
	specified device.
*/
#define E_NOTERM 6



/*
	A parameter specification is in error, becuase the specified parameter number is not valid in this
	circumstance/
*/
#define E_BADPARM 7     



/*
	The simulator has run out of memory.
	This is usually a fatal error and the simualtor in question can not be resumed.
	The exact state of the circuit involved is undefined although it is
	guaranteed that the circuit can be freed with the deleteCircuit function, and if the circuit has reached
	the simulation stage, the simualtion can be restarted without difficulty, although continuation is not
	possible
*/
#define E_NOMEM 8



/*
	A node binding for a terminal of an instance has been specified for a terminal that is already bound.
	The simulator must bind the terminal to the new node, but this error is retunred as a warning
	that a rebinding is occuring
*/
#define E_NODECON 9



/*
	The front end called a function which the simulator has not implemented.
	For full functionality, all the described functions should be implemented but in some implementations some of the
	functions will be left out either becuase the simulator can;t support them or becuase the interface is
	only partially implemented.
*/
#define E_UNSUPP 10



/*
	The parameter specified is not in the legal range for this parameter.
	The specification has been rejected by the simulator
*/
#define E_PARMVAL 11    



/*
	The device, model, analysis, or node specified to a deletion function is still referenced by something
	and cannot be deleted.
*/
#define E_NOTEMPTY 12



/*
	The simumlator has reached a pont where it can no longer accept additions to or changes in the
	structure of the circuit and the operation requested by the user would have made such an addition or change.
	The requested operation is rejected.
*/
#define E_NOCHANGE 13  



/*
	The simulator has been asked to find something and has not been successful in locatin it
*/
#define E_NOTFOUND 14 



/*
	The output package has detected some incompatibility between the pairing of OUTbeginDomain
	and OUTendDomain calls or the nesting level of the calls at the time OUTpData or OUTwData was
	called.
	Output interface begin/end domain calls mismatched
*/
#define E_BAD_DOMAIN 15



/*
	Messages above this number are private to
	the simulator and MUST be accompanied by
	a proper setting of errMsg.
	This constant should be added to all such messages
	to ensure error free operation if it must be
	changed in the future
*/
#define E_PRIVATE 100   



/*
	Descriptive message about what went wrong.
	MUST be malloc()'d - front end will free().
	This should be a detailed message, and it assumed
	malloc()'d so that you will fell free to add
	lots of descriptive information with sprintf
*/
extern char *errMsg;    



/*
	Name of the routine declaring error.
	SHould not be malloc()'d, will not be free()'d.
	This should be a simple constant in your routine
	and thus can be set correctly even if we run out of memory
*/
extern char *errRtn;    

#endif /*IFERRMSGS*/
