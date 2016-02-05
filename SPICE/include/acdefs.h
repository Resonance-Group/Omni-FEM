/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#ifndef ACDEFS
#define ACDEFS

#include "jobdefs.h"

    /* structure used to describe an AC analysis to be performed */
/*
	The ACAN structure contains the data necessary to control an AC analysis.
	The first 3 fields of teh structure are those required to match the JOB structure.
	The remaining fields are specific to the AC analysis.
*/
typedef struct {
	/*
		An integer that identifies the type of analysis the JOB structure provides details of.
		THe integer is the index in the anaINfo array to the SPICEanalysis structure which provides a description of the analysis along with
		pointers to the functions which implement it.
	*/
    int JOBtype;



	/*
		A pointer to the next JOB structure in the linked list of structures that makes up a task.
	*/
    JOB *JOBnextJob;



	/*
		A character string used to identify the analysis during output.
	*/
    char *JOBname;      /* name of this job */


	/*
		The lowest frequency at which the AC analysis is to be performed
	*/
    double ACstartFreq;



	/*
		The highest frequency at which the AC analysis is to be performed
	*/
    double ACstopFreq;



	/*
		The frequency change factor.
		If the frequncy is being stepped linearly, this is the size of the step in Hz, if
		the frequency is being stepped with either the octave or decade stepping option, this
		is the factor by which each frequency is multiplied to obtain the next frequency.
	*/
    double ACfreqDelta; 



	/*
		If the analysis is interrupted, this is the last frequency at which the analysis was complete, thus
		allowing the analysis to continue where it left off
	*/
    double ACsaveFreq;  



	/*
		The type of step.
		This takes on one of 3 symbolic constant values.
		When set to LINEAR, linear stepping is done with the number of steps interpreted as the total number of frequency points.
		When set to OCTAVE or DECADE, logarithmic stepping is done with the number of steps interpreted as the number of 
		frequency points per octave or decade.
	*/
    int ACstepType;



	/*
		ACnumberSteps is the number of steps to be computed and output, interpreted as 
		described under ACstepType above.
	*/
    int ACnumberSteps;
} ACAN;

/* available step types: XXX should be somewhere else */

#define DECADE 1
#define OCTAVE 2
#define LINEAR 3

#define AC_DEC 1
#define AC_OCT 2
#define AC_LIN 3
#define AC_START 4
#define AC_STOP 5
#define AC_STEPS 6

#endif /*ACDEFS*/
