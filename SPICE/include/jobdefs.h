/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#ifndef JOBdef
#define JOBdef


#include "ifsim.h"

/*
	The job structure is used to containi thee data needed to run a single analysis.
	This is actually a structure prefix, and is included as the first element of every analysis specific data structure.
	This allows common code to manipulate the strucutres without knowing the details of each analysis type's specific structure.
*/
typedef struct sJOB{
	/*
		An integer that identifies the type of analysis the JOB structure provides details of.
		THe integer is the index in the anaINfo array to the SPICEanalysis structure which provides a description of the analysis along with 
		pointers to the functions which implement it.
	*/
    int JOBtype;                



	/*
		A pointer to the next JOB structure in the linked list of structures that makes up a task.
	*/
    struct sJOB *JOBnextJob;



	/*
		A character string used to identify the analysis during output.
	*/
    IFuid JOBname;              /* name of this job */

} JOB;
// A job describes the specific analysis that will be performed. 
// All jobs have a standard prefix on their data structure so that higher level
// software can examine the jobs and organize them into a group of jobs
// to be perfromed all at once and called a task


/*
	Provides information to the higher level routines about the analyses that SPICE3 is capable of performing.
*/
typedef struct {
	/*
		This is teh simulator to front end interface specified description of the analysis parameters and
		is described in detail in the docuemntation on that interface
	*/
	IFanalysis public;


	/*
		This is the size in bytes of the private data structure used by analysis to store its data
	*/
	int size;


	/*
		This is pointer to a function which accepts values of parameters and sets them in the device specific data structure
	*/
	int(*(setParm))();



	/*
		This is a pointer to a function which accessess values in the device data structure and makes them avaliable to another
		routine which does not have any knowledge of the device specific data structures
	*/
	int(*(askQuest))();


	int domain;
	int do_ic;
	int(*an_init)();
	int(*an_func)();
	
} SPICEanalysis;

#define NODOMAIN	0
#define TIMEDOMAIN	1
#define FREQUENCYDOMAIN 2
#define SWEEPDOMAIN	3

#endif /*JOBdef*/
