/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#ifndef TF
#define TF

#include "jobdefs.h"
#include "tskdefs.h"
#include "cktdefs.h"

    /* TFdefs.h - defs for transfer function analyses */


/*
	The TFan structure describes a transfer unction analysis to be performed.
	The first 3 elements of the structure are the standard JOB head to link the 
	structure into the TSKtask linked list. 
*/
typedef struct {
	/*
		The standard JOB structure
	*/
    int JOBtype;
    JOB *JOBnextJob;
    IFuid JOBname;



	/*
		These are the positive and negative nodes of the output port if the output port signal is
		a voltage, otherwise they are ignored.
	*/
    CKTnode *TFoutPos; // Postive node
    CKTnode *TFoutNeg; // Negative node
    
	
	
	/*
		This is the identifying name of the output source if the output variable is the
		current throught a source.
	*/
	IFuid TFoutSrc;



	/*
		This is the identifying name of the input source, either a volage source or a current source.
	*/
    IFuid TFinSrc;


	/*
		A pair of flags to indicate whether the output signal is to be the voltage between two
		nodes or the current throught a voltage source.
		If neither of these flags has been set, then no output signal has been specified which is an error
	*/
	unsigned int TFoutIsV : 1;
	unsigned int TFoutIsI : 1;


	/*
		A pair of flags to indicate whether the input signal is from a voltage source or a current source.
		These flags are currently mutually exclusive, but both exist for historical reasons
	*/
	unsigned int TFinIsV : 1;
	unsigned int TFinIsI : 1;



	/*
		a printable name for an output v(x,y)
	*/
    char *TFoutName;    
} TFan;

#define TF_OUTPOS 1
#define TF_OUTNEG 2
#define TF_OUTSRC 3
#define TF_INSRC 4
#define TF_OUTNAME 5
extern int TFsetParm();
extern int TFaskQuest();
#endif	/*TF*/
