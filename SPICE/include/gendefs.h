/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#ifndef GEN
#define GEN

#include "ifsim.h"

      
/*
	The GENinstance structure is used to traverse the device specific per instance data structures
	without the knowledge of the devices.
	All devices can be examied with this structure if appropiate care is used not to reference a node
	with a number greater then the number of nodes defines for a device of that type in the corresponding
	SPICEdev structure.
*/
typedef struct sGENinstance {
	/*
		A backpointer to the model this is an instance of.
		The model contains the type of the device if this is needed and only an
		instance pointer is available.
		This also provides access to model parameters when only and instance pointer is given.
	*/
    struct sGENmodel *GENmodPtr;    /* backpointer to model */



	/*
		This is a pointer to the next instance in the linked list of device instances
	*/
    struct sGENinstance *GENnextInstance;



	/*
		The name of the instance
	*/
    IFuid GENname;  /* pointer to character string naming this instance */
    
	
	
	/*
		GENnodei
		These are node number for the nodes the instance is attached to.
		Not all of these are always valid, reference to a terminal GENnodei for
		i greater then (DEVices[inst->GENmodPtr->GENmodType])->DEVpublic.terms is an error
		and will produce unpredictable results
	*/
	int GENstate;   /* state index number */
    int GENnode1;   /* appropriate node numbers */
    int GENnode2;   /* appropriate node numbers */
    int GENnode3;   /* appropriate node numbers */
    int GENnode4;   /* appropriate node numbers */
    int GENnode5;   /* appropriate node numbers */

} GENinstance ;


/* Generic circuit data */

typedef void GENcircuit;

/*
	The GENmodel structure defines the standard prefix which must appear at hte beginning of all device models.
	This structure allows code in SPICE3 to search throuh device models without any knowledge of the devices themselves
	or even of the type of devices.
*/
typedef struct sGENmodel {
	/*
		The integer subscript of the descriptor for the type of device this model represents.
		This subscript allows code to access the correct routines to process the model by referencing the
		SPICEdev structure with that subscript in the DEVices array and thereby accessing all of the
		data on the model and the rountines to process it.
	*/
    int GENmodType; 



	/*
		A pointer to the next model in the linked list structure. 
		This model will have the same value for GENmodType and a distinct name but no other information
		about it is known.
	*/
    struct sGENmodel *GENnextModel;



	/*
		A pointer to the first element of the linked list of instances of this model.
		The instance linked list also has a standardized structure so that traversal of that list
		can also be done without knowledge of the device.
	*/
    GENinstance *GENinstances;



	/*
		The name of the model
	*/
    IFuid GENmodName;// pointer to character string naming this model 

} GENmodel;

#endif /*GEN*/
