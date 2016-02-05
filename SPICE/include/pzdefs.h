#ifndef PZDEFS
#define PZDEFS "PZdefs.h $Revision: 1.3 $  on $Date: 88/11/16 21:55:29 $ "

    /* structure used to describe an PZ analysis to be performed */

#include "jobdefs.h"
#include "complex.h"

typedef struct strial {
    SPcomplex	s, f_raw, f_def;
    struct strial *next, *prev;
    int		mag_raw, mag_def;
    int		multiplicity;
    int		flags;
    int		seq_num;
    int		count;
} PZtrial;



/*
	The PZAN structure describes a pole-zzero analysis to be performed.
	The first 3 fields are the standard JOB structure prefix.
*/
// TODO: This struct needs to be looked over again and compared with the implementation guide
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
    IFuid JOBname;



	/*
		The positive input node
	*/	
    int PZin_pos;



	/*
		The negative input node
	*/
    int PZin_neg;



	/*
		The positive output node
	*/
    int PZout_pos;



	/*
		The negtive output node
	*/
    int PZout_neg;




    int PZinput_type;



	/*
		This flag indicates the type of transfer function to analyize. 
		A value zero indicates an (outputVoltage) / (inputVoltage) TF, while
		a value one indicates an (outputVoltage) / (inputCurrent) TF.
	*/
    int PZwhich;



	/*
		This is a count of the number of row and column swaps have been performed in the decomposition of the matrix.
	*/
    int PZnumswaps;




    int PZbalance_col;
    int PZsolution_col;



	/*
		The points to the beginning of a linked list of poles already found in this analysis
	*/
    PZtrial *PZpoleList;



	/*
		The pointer to the beginning of a linked list of poles already found in this analysis
	*/
    PZtrial *PZzeroList;
    int PZnPoles;
    int PZnZeros;



	/*
		These are pointers into the sparse matrix at locations in the additional row
	*/
    double *PZdrive_pptr;
    double *PZdrive_nptr;
} PZAN;

#define PZ_DO_POLES	0x1
#define PZ_DO_ZEROS	0x2
#define PZ_IN_VOL	1
#define PZ_IN_CUR	2

#define PZ_NODEI 1
#define PZ_NODEG 2
#define PZ_NODEJ 3
#define PZ_NODEK 4
#define PZ_V 5
#define PZ_I 6
#define PZ_POL 7
#define PZ_ZER 8
#define PZ_PZ 9

#endif /*PZDEFS*/
