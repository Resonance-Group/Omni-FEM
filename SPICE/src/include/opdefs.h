/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#ifndef DCOP
#define DCOP


#include "jobdefs.h"
#include "tskdefs.h"
    /*
     * structures used to describe D.C. operationg point analyses to
     * be performed.
     */


/*
	The OP stucture simply provides an indication that an operating point is to be done and provides
	a name for it. 
	Since the operating point is very simple and has no additional parameters, only
	the minimal structure as required by the JOB prefix is needed.
*/
typedef struct {
    int JOBtype;
    JOB *JOBnextJob;
    char *JOBname;
} OP;

extern int DCOsetParm();
extern int DCOaskQuest();
#endif /*DCOP*/
