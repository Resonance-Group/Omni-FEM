/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1986 Thomas L. Quarles
**********/

#ifndef IFSIMULATOR
#define IFSIMULATOR

/*
 * We don't always have access to an ANSI C compiler yet, so we
 * make the following convenient definition
 */

    /* using an ansi C compiler, so we have the void* construct */

typedef void GENERIC;

/* 
 * structure:   IFparm
 *
 *
 * The structure used to describe all values passed
 * between the front end and the simulator when there is any
 * possibility one argument of the function could have more
 * than one type.
 *
 * keyword is provided for the front end and is the token
 *    the user is expected to label the data with.
 *
 * id is an integer intended to uniquely identify the parameter
 *    to the simulator
 *
 * dataType is an integer which indicates the type of argument
 *    that must be passed for this parameter
 *
 * description is a longer description intended for help menus
 *    the description should all fit on one line, but should
 *    give a knowledgable user a good idea what the parameter is
 *    used for.
 */

typedef struct sIFparm {
	/*
		The keyword entry is a one word character string which would be used on an inpt line to indicate
		the beginnning of an entry of this type.
		To avoid problems with special characters which may be used by some parses,
		the keyword should be use a very restricted character set.
		We recommend restricting the keyword to letters, digits, and underscores, with the first character a letter.
	*/
    char *keyword;



	/*
		The ID field is a simple integer which uniquely identifies this parameter within the set of parameters in this array of
		IFparm structures.
		This is a simple integer since integer comparison is much faster than string comparison,
		and it allows simple aliasing of keywords.
	*/
    int id;



	/*
		The dataType field is an integer that holds one od the values defined in the IFsim.h header filer.
		The legal values currently include the primitive types:
		
		IF_FLAG
		IF_INTEGER
		IF_REAL
		IF_COMPLEX
		IF_NODE
		IF_NODE
		IF_STRING
		IF_INSTANCE
		IF_PARSETREE
		
		Vectors of these primitive types, indicated by oring IF_VECTOR with the propser tpye.
		This identifies the type of argument the keyword should be associated with in an input or the type 
		of value to be returned in respose to a query.
		THe parser should use this to determine how to interpeet the arguement
		and to place it in the correct field of the union used to pass data to the
		simulator or extract the result from the returned union. 
		The dataType field also may have a bit set indicating the parameter is required (IF - REQUIRED), which allows the front end to do some additional
		error checking by not asking the simulator to run an analysis if all parameters are not specified, but
		the simulator should not depend on this level of checking, it is simply provided as a level of optimization
		for front ends which wish to save some time processing bad inputs. 
		There are also bits for indicating whether the description is of an input data item valid in a parameter call (IF_SET), is an
		output data item valid in a question call (IF_ASK), or is both. 
		As a special case, if it is not indicated as an input or output data item, it is an input parameter which the simulator recognizes as being a
		normal parameter under the circumstance, but which one this simulator chooses not to support.
		Finally, the simulator can indicate that additional information is required to specify the parameter
		more precisely by setting the IF_SELECT or IF_VSELECI' bit. 
		If either of these bits are set, then the 'selector' parameter may contain an integer or vector of integers respectively to further specify the
		parameter. 
		It is intended that these be used to provide access to individual elements in arrays of
		parameters without having to set or output the entire array. 
		See setN0dePa.m and aslcNodeQuest for a more detailed desaiption of this mechanism.
	*/
    int dataType;



	/*
		The description is a longer, more descriptive character string that describes the parameter.
		The description should be short enough to easily fit on a single line of a standard termina, but sufficiently
		detailed to identify the function of the parameter to a user of the program.
		NOte that the order in which parameters are passed to the simulator is not defined, and may be the order in which the user
		specified them, the order the simulator defined them in or completely random at the option of the
		front end.
	*/
    char *description;
} IFparm;

/*
 *
 * datatype: IFuid
 *
 * unique identifier for all name-type data in the simulator.
 * this permits the front end to use something other than
 * a unique, fully qualified character string to identify
 * an object.
 *
 */

typedef GENERIC *IFuid;

/* 
 *
 * types for IFnewUid
 *
 */

#define UID_ANALYSIS 0x1
#define UID_TASK 0x2
#define UID_INSTANCE 0x4
#define UID_MODEL 0x8
#define UID_SIGNAL 0x10
#define UID_OTHER 0x20


/* 
 * dataType values:
 *
 * Note:  These structures are put together by ORing together the
 *    appropriate bits from the fields below as is shown for the vector
 *    types.  
 * IF_REQUIRED indicates that the parameter must be specified.
 *    The front end does not NEED to check for this, but can to save time,
 *    since failure to do so will cause the simulator to fail.
 * IF_SET indicates that the specified item is an input parameter.
 * IF_ASK indicates that the specified item is something the simulator
 *    can provide information about.
 * IF_SET and IF_ASK are NOT mutually exclusive.
 * if IF_SET and IF_ASK are both zero, it indicates a parameter that
 *    the simulator recoginizes are being a reasonable paremeter, but
 *    which this simulator does not implement.
 */

#define IF_FLAG 0x1
#define IF_INTEGER 0x2
#define IF_REAL 0x4
#define IF_COMPLEX 0x8
#define IF_NODE 0x10
#define IF_STRING 0x20
#define IF_INSTANCE 0x40
#define IF_PARSETREE 0x80

/* indicates that for a query the integer field will have a selector
 * in it to pick a sub-field */
#define IF_SELECT 0x800
#define IF_VSELECT 0x400

/* indicates a vector of the specified type */
#define IF_VECTOR 0x8000

#define IF_FLAGVEC     (IF_FLAG|IF_VECTOR)
#define IF_INTVEC      (IF_INTEGER|IF_VECTOR)
#define IF_REALVEC     (IF_REAL|IF_VECTOR)
#define IF_CPLXVEC     (IF_COMPLEX|IF_VECTOR)
#define IF_NODEVEC     (IF_NODE|IF_VECTOR)
#define IF_STRINGVEC   (IF_STRING|IF_VECTOR)
#define IF_INSTVEC     (IF_INSTANCE|IF_VECTOR)

#define IF_REQUIRED 0x4000

#define IF_VARTYPES 0x80ff

#define IF_SET 0x2000
#define IF_ASK 0x1000

/* If you AND with IF_UNIMP_MASK and get 0, it is recognized, but not
 * implemented 
 */
#define IF_UNIMP_MASK (~0xfff)

/* Used by sensetivity to check if a parameter is or is not useful */
#define IF_REDUNDANT	0x0010000
#define IF_PRINCIPAL	0x0020000
#define IF_AC		0x0040000
#define IF_AC_ONLY	0x0080000
#define IF_NOISE	0x0100000
#define IF_NONSENSE	0x0200000

#define IF_SETQUERY	0x0400000
#define IF_ORQUERY	0x0800000
#define IF_CHKQUERY	0x1000000

/* For "show" command: do not print value in a table by default */
#define IF_UNINTERESTING 0x2000000

/* Structure:   IFparseTree
 *
 * This structure is returned by the parser for a IF_PARSETREE valued
 * parameter and describes the information that the simulator needs
 * to know about the parse tree in order to use it.
 * It is expected that the front end will have a more extensive
 * structure which this structure will be a prefix of.
 *
 * Note that the function pointer is provided as a hook for 
 * versions which may want to compile code for the parse trees
 * if they are used heavily.
 *
 */
typedef struct sIFparseTree {
	
	/*
		number of variables used
	*/
	int numVars;            



	/*
		An array of the actual parameters used in the expression.
		Note that all of the variables must be names of signals, either those generated
		normally by the ircuit or those in the list of special signals provided in the IFsimulator structure.
	*/
    int *varTypes;          



	/*
		array of structures describing values
	*/
    union uIFvalue * vars;  



	/*
		A function provided by the front end which will evaluate the equation represented by 
		the parse tree structure and its partial derivatives. 
	*/
    int ((*IFeval)(struct sIFparseTree*,double,double*,double*,double*)); /* function to call to get evaluated */
} IFparseTree;


/*
 * Structure:    IFvalue
 *
 * structure used to pass the values corresponding to the above
 * dataType.  All types are passed in one of these structures, with
 * relatively simple rules concerning the handling of the structure.
 *
 * whoever makes the subroutine call allocates a single instance of the
 * structure.  The basic data structure belongs to you, and you
 * should arrange to free it when appropriate.
 *
 * The responsibilities of the data supplier are:
 * Any vectors referenced by the structure are to be malloc()'d 
 * and are assumed to have been turned over to the recipient and 
 * thus should not be re-used or free()'d.
 *
 * The responsibilities of the data recipient are:
 * scalar valued data is to be copied by the recipient
 * vector valued data is now the property of the recipient,
 * and must be free()'d when no longer needed.
 *
 * Character strings are a special case:  Since it is assumed
 * that all character strings are directly descended from input 
 * tokens, it is assumed that they are static, thus nobody
 * frees them until the circuit is deleted, when the front end
 * may do so.
 *
 * EVERYBODY's responsibility is to be SURE that the right data
 * is filled in and read out of the structure as per the IFparm
 * structure describing the parameter being passed.  Programs
 * neglecting this rule are fated to die of data corruption
 *
 */

/*
 * Some preliminary definitions:
 *
 * IFnode's are returned by the simulator, thus we don't really 
 * know what they look like, just that we get to carry pointers
 * to them around all the time, and will need to save them occasionally
 *
 */


typedef void * IFnode;

/*
 * and of course, the standard complex data type 
 */
typedef struct sIFcomplex {
    double real;
    double imag;
} IFcomplex;



/*
	Structure used to pass data to and from the simulator.
	All of the possible parameter types can be placed in this structure, integer values in the iValue field, 
	reals in the rValue field, node pointers in the nValue field and strings in the sValue field.
	Vectors are given as a length in v.numvalue field with an array of values in on of the v.vec.Xvecs fields.
	Flags are passed in the iValue field, with the convention that any non-zero value corresponds to
	setting the flag, and zero corresponds to clearing it.
*/
typedef union uIFvalue {
    int iValue;             /* integer or flag valued data */
    double rValue;          /* real valued data */
    IFcomplex cValue;       /* complex valued data */
    char *sValue;           /* string valued data */
    IFuid uValue;           /* UID valued data */
    IFnode nValue;          /* node valued data */
    IFparseTree *tValue;    /* parse tree */
    struct 
	{
        int numValue;       /* length of vector */
        union 
		{
            int *iVec;      /* pointer to integer vector */
            double *rVec;   /* pointer to real vector */
            IFcomplex *cVec;/* pointer to complex vector */
            char **sVec;    /* pointer to string vector */
            IFuid *uVec;    /* pointer to UID vector */
            IFnode *nVec;   /* pointer to node vector */
        }vec;
    }v;
} IFvalue;



/*
	This structure contains all the information available to the
	front end about a particular device.  The simulator will
	present the front end with an array of pointers to these structures
	which it will use to determine legal device types and parameters.
	This structure is used to describe a device to be parsed, along with its parameters and the
	corresponding information, if any, about the model used for the device

	Note to simulators:  you are passing an array of pointers to
	these structures, so you may in fact make this the first component
	in a larger, more complex structure which includes other data
	which you need, but which is not needed in the common
	front end interface.

	THe front end will use these structures to determine what operations are legal
	on each device and pass the appropriate IFparm ID back to the simualtor as necessary.
 */
typedef struct sIFdevice {
	/*
		THe character string used to describe all devices of this type, such as 'resistor'.
		Again, to prevent problems with special characters in parses, the name should be limited to letters, digits,
		and underscores, with the first character a letter.
	*/
	char *name;



	/*
		A one-line description of the device.
	*/
	char *description;



	/*
		The number of terminals allowed on the device.
		To allow for devices with a variable number of terminals, if terms is negative,
		then at least -terms terminals must be present, but any number
		larger than that is legal.
	*/
	int *terms;



	/*
		number of names in termNames
	*/
	int *numNames;



	/*
		A pointer to an array of length numNames of character
		pointers, each of which points to a character string describing a node of the device.
		If terms is non negative, then it is equal to numNmae, while if it is negatie, its absolute value must be less than or
		equal to numNames.
		There are 2 arrays of IFparm structures foreach device.
	*/
	char **termNames;



	/*
		number of instance parameter descriptors
	*/
	int *numInstanceParms;



	/*
		The instancePArms array is of length numInstanceParms and contains parameters and questions that apply to individual
		instances.
	*/
	IFparm *instanceParms;



	/*
		number of model parameter descriptors
	*/
	int *numModelParms;



	/*
		The modelParms array is of length numModelParms and contains parameters and questions
		that apply to a device model.
		Array of model parameter descriptors
	*/
	IFparm *modelParms;



	/*
		For dev pruposes
	*/
	int	flags;

} IFdevice;



/*
 * Structure: IFanalysis
 *
 * This structure contains all the information available to the
 * front end about a particular analysis type.  The simulator will
 * present the front end with an array of pointers to these structures 
 * which it will use to determine legal analysis types and parameters.
 *
 * Note to simulators:  As for IFdevice above, you pass an array of pointers
 * to these, so you can make this structure a prefix to a larger structure
 * which you use internally.
 *
 */

typedef struct sIFanalysis {
	/*
		Name and description are reqpectively one word and one line descriptions of the analysis being offered
		Again, the name should be composed only of letters, digits, and underscores with a leading letter.
	*/
	char *name;                 /* name of this analysis type */
	char *description;          /* description of this type of analysis */



	/*
		number of analysis parameter descriptors
	*/
	int numParms;



	/*
		Describes the parameters and queries that are applicable to this particular analysis
	*/
	IFparm *analysisParms;

} IFanalysis;



/*
	This is what we have been leading up to all along.
	This structure describes a simulator to the front end, and is
	returned from the SIMinit command to the front end.
	This is where all those neat structures we described in the first
	few hundred lines of this file come from.
 
	This structure consists of a number of pointers to function that the
	parser may use, as well as tables of data.
	The parser willobtain this simulator data by calling the
	simulator routine XXXinit(). 
	This routin returns a pointer to a copy of the following IFsimulator structure.
 */

typedef struct sIFsimulator {
	/*
		the simulator's name
	*/
	char *simulator;



	/*
		description of this simulator
	*/
	char *description;



	/*
		version or revision level of simulator
	*/
	char *version;



	/*
		create new circuit
	*/
	int((*newCircuit)(GENERIC **));



	/*
		destroy old circuit's data structures
	*/
	int((*deleteCircuit)(GENERIC *));



	/*
		create new node
	*/
	int((*newNode)(GENERIC *, GENERIC**, IFuid));



	/*
		create ground node
	*/
	int((*groundNode)(GENERIC*, GENERIC**, IFuid));



	/*

	*/
	int((*bindNode)(GENERIC *, GENERIC*, int, GENERIC*));
	/* bind a node to a terminal */


	/*
		find a node by name
	*/
	int((*findNode)(GENERIC *, GENERIC**, IFuid));



	/*
		find the node attached to a terminal
	*/
	int((*instToNode)(GENERIC *, GENERIC *, int, GENERIC **, IFuid *));



	/*
		set a parameter on a node
	*/
	int((*setNodeParm)(GENERIC*, GENERIC*, int, IFvalue*, IFvalue*));



	/*
		ask a question about a node
	*/
	int((*askNodeQuest)(GENERIC*, GENERIC*, int, IFvalue*, IFvalue*));



	/*
		delete a node from the circuit
	*/
	int((*deleteNode)(GENERIC*, GENERIC*));



	/*
		create new instance
	*/
	int((*newInstance)(GENERIC*, GENERIC*, GENERIC**, IFuid));



	/*
		set a parameter on an instance
	*/
	int((*setInstanceParm)(GENERIC*, GENERIC*, int, IFvalue*, IFvalue*));



	/*
		ask a question about an instance
	*/
	int((*askInstanceQuest)(GENERIC*, GENERIC*, int, IFvalue*, IFvalue*));



	/*
		find a specific instance
	*/
	int((*findInstance)(GENERIC*, int*, GENERIC**, IFuid, GENERIC*, IFuid));



	/*
		delete an instance from the circuit
	*/
	int((*deleteInstance)(GENERIC*, GENERIC*));



	/*
		create new model
	*/
	int((*newModel)(GENERIC*, int, GENERIC**, IFuid));



	/*
		set a parameter on a model
	*/
	int((*setModelParm)(GENERIC*, GENERIC*, int, IFvalue*, IFvalue*));



	/*
		ask a questions about a model
	*/
	int((*askModelQuest)(GENERIC*, GENERIC*, int, IFvalue*, IFvalue*));



	/*
		find a specific model
	*/
	int((*findModel)(GENERIC*, int*, GENERIC**, IFuid));



	/*
		delete a model from the circuit
	*/
	int((*deleteModel)(GENERIC*, GENERIC*));



	/*
		create a new task
	*/
	int((*newTask)(GENERIC*, GENERIC**, IFuid));



	/*
		create new analysis within a task
	*/
	int((*newAnalysis)(GENERIC*, int, IFuid, GENERIC**, GENERIC*));



	/*
		set a parameter on an analysis
	*/
	int((*setAnalysisParm)(GENERIC*, GENERIC*, int, IFvalue*, IFvalue*));



	/*
		ask a question about an analysis
	*/
	int((*askAnalysisQuest)(GENERIC*, GENERIC*, int, IFvalue*, IFvalue*));



	/*
		find a specific analysis
	*/
	int((*findAnalysis)(GENERIC*, int*, GENERIC**, IFuid, GENERIC*, IFuid));


	/*
		find a specific task
	*/
	int((*findTask)(GENERIC*, GENERIC**, IFuid));



	/*
		delete a task
	*/
	int((*deleteTask)(GENERIC*, GENERIC*));



	/*

	*/
	int((*doAnalyses)(GENERIC*, int, GENERIC*));



	/*
		return nonconvergence error
	*/
	char *((*nonconvErr)(GENERIC*, char *));



	/*
		number of device types supported
	*/
	int numDevices;



	/*
		array of device type descriptors
	*/
	IFdevice **devices;



	/*
		number of analysis types supported
	*/
	int numAnalyses;



	/*
		array of analysis type descriptors
	*/
	IFanalysis **analyses;



	/*
		number of node parameters supported
	*/
	int numNodeParms;



	/*
		array of node parameter descriptors
	*/
	IFparm *nodeParms;



	/*
		number of special signals legal in parse trees
	*/
	int numSpecSigs;



	/*
		 names of special signals legal in parse trees
	*/
	char **specSigs;

} IFsimulator;




/*
 * Structure: IFfrontEnd
 *
 * This structure provides the simulator with all the information
 * it needs about the front end.  This is the entire set of
 * front end and back end related routines the simulator
 * should know about.
 *
 */ 

typedef struct sIFfrontEnd {
	/* create a new UID in the circuit */
	int((*IFnewUid)(GENERIC*, IFuid*, IFuid, char*, int, GENERIC**));	



	/* Delete UID from the circuit */
	int((*IFdelUid)(GENERIC*, IFuid, int));		



	/*
		This function is a simple function passed from the front end to the simulator as part of the
		IFfrontEnd structure and is used to signal the simulator that the front end wants control. Since the
		front end can not take control away from the simulator and expect to return without damage to the
		simulator’s data smctures, the simulator must relinquish control when necessary. This is accomplished
		by having the simulator call the IFpauseTest function frequently (at least as frequently as it
		can conveniently stop). This function can allow the front end to perfom short operations which
		require no access to the simulator (window redraws by the back end, for example), and to indicate by
		a non-zero retum value that it wants total control at the simulator’s eariiest convenience.
	*/
	int((*IFpauseTest)(void));	// TODO: Find this function




	/*
		This function is provided to allow simulaton and front ends which agree to do so to provide the
		facilities for statistics gathering. This function should ~ t umthe run time for the job in seconds as a
		double precision floating point number. The run time does not have to be absolute, but the difference
		between successive calls should provide accurate elapsed CFW time. If the front end does not wish to
		provide such capabilities or is unable to do so because of the operating system, it may return the constant
		0.0, and should expect and document that all time related statistics from the simulator will be
		meaningless.
	*/
	double((*IFseconds)(void));	// TODO: Find this function	



	/* 
		This function provides a way for the simulator to output messages to the user through the front
		end without interfering with whatever the front end may be doing with the terminal display. fIags is
		one of ERR_INFO, ERR_WARNING, ERR_FATAL, or ERR_PANIC, indicating that the message is a simple
		informational status message that the front end should provide a way of enabling and disabling
		based on user preference, a waming message, an error message that will probably cause the simulator
		to fail, and an extremely serious error from which the simulator won’t even try to recover. Note that
		after an EBR-PMC, the simulator may be in such a bad state that it is impossible to perfom funher
		operations on the current circuit. Formut is a textual message that should be displayed to the user.
		The format string will be processed by a mechanism similar to printf, and all printf conventions
		should be observed, including modifiers on %s and using %% to place a % in the output. Only %s
		format items will be interpreted properly, and the data for them comes from the array of &id’s
		pointed to by names. This function is provided in this form to allow for the greatest flexibility in
		error message output, since it permits the front end to get the Fuid’s directly. One benefit of this is
		that a graphic front end may wish to highlight the objects corresponding to the Guid’s in different
		colors and fill in some descriptive information in the message rather than using a possibly cryptic
		name which the user may not understand in the message itself.
	*/
	int((*IFerror)(int, char*, IFuid*));// TODO: Find this function



	/* start pointwise output plot */
	int((*OUTpBeginPlot)(GENERIC*, GENERIC*, IFuid, IFuid, int, int, IFuid*, int, GENERIC**));	



	/* data for pointwise plot */
	int((*OUTpData)(GENERIC*, IFvalue*, IFvalue*));	



	/* start windowed output plot */
	int((*OUTwBeginPlot)(GENERIC*, GENERIC*, IFuid, IFuid, int, int, IFuid*, int, GENERIC**));    



	/* independent vector for windowed plot */
	int((*OUTwReference)(GENERIC*, IFvalue*, GENERIC**));		



	/* data for windowed plot */
	int((*OUTwData)(GENERIC*, int, IFvalue*, GENERIC*));		



	/* signal end of windows */
	int((*OUTwEnd)(GENERIC*));	



	/* end of plot */
	int((*OUTendPlot)(GENERIC*));	



	/* start nested domain */
	int((*OUTbeginDomain)(GENERIC*, IFuid, int, IFvalue*));		



	/* end nested domain */
	int((*OUTendDomain)(GENERIC*));						



	/* specify output attributes of node */
	int((*OUTattributes)(GENERIC *, IFuid*, int, IFvalue*));									
} IFfrontEnd;

/* flags for the first argument to IFerror */
#define ERR_WARNING 0x1
#define ERR_FATAL 0x2
#define ERR_PANIC 0x4
#define ERR_INFO 0x8

    /* valid values for the second argument to doAnalyses */

    
#define RESUME 0 /* continue the analysis from where we left off */
    
#define RESTART 1 /* start everything over from the beginning of this task*/
    
#define SKIPTONEXT 2 /* abandon the current analysis and go on the the next in the task*/

#define OUT_SCALE_LIN   1
#define OUT_SCALE_LOG   2

#endif /*IFSIMULATOR*/
