/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1987 Wayne A. Christopher, U. C. Berkeley CAD Group 
**********/

/*
 *   faustus@cad.berkeley.edu, ucbvax!faustus
 *
 * These definitions specify the format of the parse tree parameter type.
 * The first four are the elements of IFparseTree, defined in IFsim.h.
 */

#include "ifsim.h"

#ifndef INP_PARSE
#define INP_PARSE


/* This is the parameter value passed to the device routines.  To get the
 * value of the function, where tree is a pointer to the INPparseTree,
 * result is a pointer to where you want the result, derivs is a pointer to
 * an vector of numVars doubles, and vals is a pointer to the selected
 * elements from the RHS, do
 *  tree->p.IFeval(&tree, result, vals, derivs)
 * This routine will return either OK, E_PARMVAL, or E_PANIC.  If an error
 * is reported the eval function will have printed something to standard
 * out before returning.
 */
/*
	The INPparseTree structure contins data on a parse tree the front end has read
	and will later interpretively evaluate for the simualtor. The parse tree structure
	encapsuates te standard strcute defined by the front end interface, appending fields
	to it for internal use in the parser.
*/
typedef struct INPparseTree {
	/*
		The parse tree structure required by the front end
	*/
    IFparseTree p;



	/*
		The actual internal parse tree structure for the equation actual provided by the user
	*/
    struct INPparseNode *tree;  /* The real stuff. */



	/*
		An allocated array of pointer to interal parse tree structure for trees representing
		the partial derivatives of the original parse tree with respect to every variable used in the expression
	*/
    struct INPparseNode **derivs;   /* The derivative parse trees. */
} INPparseTree;

/* This is what is passed as the actual parameter value.  The fields will all
 * be filled in as needed.
 *
 * Values with names like v(something) and i(something) are treated specially.
 * They are considered voltages at nodes and branch currents through
 * voltage sources, respectively.  The corresponding parameters will be of
 * type IF_NODE and IF_INSTANCE, respectively.
 */
/*
	The structure which is used to build parse trees. 
	These structure are built up into a tree arrangement with each entry either representing a variable or constant, or a
	operator with one or two operands which are themselves INPparseNode structures
*/
typedef struct INPparseNode {
	/*
		This indicates the type of node the instance is, a simple operator such as +, -, or *, a constant
		or a function call
	*/
    int type;           /* One of PT_*, below. */



	/*
		The left operand of the operator in this node if it is a two operand operator, the only operand
		if it is a single operand operator and null if it is not an operator
	*/
    struct INPparseNode *left;  /* Left operand, or single operand. */
    
	
	
	/*
		The right operand of the operator in this node if it is a two operand operator, otherwise null
	*/
	struct INPparseNode *right; /* Right operand, if there is one. */
    
	
	
	/*
		The numeric value of a constant stored in the node
	*/
	double constant;        /* If INP_CONSTANT. */



	/*
		The index of the variable being placed in the tree at this point.
		The index is into the array of variable names in the IFparseTree structure in the INPparse tree
		structure this node is descended from.
	*/
    int valueIndex;         /* If INP_VAR, index into vars array. */
    
	
	
	/*
		The name of the function called from this node
	*/
	char *funcname;         /* If INP_FUNCTION, name of function, */
    
	
	
	/*
		The number of the function from an internal table.
		This is used to more rapidly process the functions using case statement instead of
		string comparison operations.
	*/
	int funcnum;            /* ... one of PTF_*, */
    
	
	
	/*
		A pointer to the interal function which actually implements the parse tree operation
	*/
	double (*function)();       /* ... and pointer to the function. */
} INPparseNode;

/* These are the possible types of nodes we can have in the parse tree.  The
 * numbers for the ops 1 - 5 have to be the same as the token numbers,
 * below.
 */

#define PT_PLACEHOLDER  0       /* For i(something) ... */
#define PT_PLUS     1
#define PT_MINUS    2
#define PT_TIMES    3
#define PT_DIVIDE   4
#define PT_POWER    5
#define PT_FUNCTION 6
#define PT_CONSTANT 7
#define PT_VAR      8
#define PT_COMMA    10

/* These are the functions that we support. */

#define PTF_ACOS    0
#define PTF_ACOSH   1
#define PTF_ASIN    2
#define PTF_ASINH   3
#define PTF_ATAN    4
#define PTF_ATANH   5
#define PTF_COS     6
#define PTF_COSH    7
#define PTF_EXP     8
#define PTF_LN      9
#define PTF_LOG     10
#define PTF_SIN     11
#define PTF_SINH    12
#define PTF_SQRT    13
#define PTF_TAN     14
#define PTF_TANH    15
#define PTF_UMINUS  16
#define PTF_ABS		17
#define PTF_SGN		18
#define PTF_USTEP	19
#define PTF_URAMP	20

/* The following things are used by the parser -- these are the token types the
 * lexer returns.
 */

#define TOK_END         0
#define TOK_PLUS        1
#define TOK_MINUS       2
#define TOK_TIMES       3
#define TOK_DIVIDE      4
#define TOK_POWER       5
#define TOK_UMINUS      6
#define TOK_LPAREN      7
#define TOK_RPAREN      8
#define TOK_VALUE       9
#define TOK_COMMA       10

/* And the types for value tokens... */

#define TYP_NUM         0
#define TYP_STRING      1
#define TYP_PNODE       2

/* A parser stack element. */


/*
	The PTelement structure is used to hold temporary data during the parsing of an expression into a parse tree.
	These are pushed onto a parse stack as parsing progresses and popped off as operations consume them.
*/
typedef struct PTelement {
	/*
		The lexical type of the token the lexical analyzer has found.
		This can be an operator, the end of the input, parenthese, or a value.
	*/
    int token;



	/*
		If token indicates a value, this will indicate the type of the value and will be one of TYP_NUM indicating a number,
		TYP_STRING indicating a character string, or TYP_PNODE indicating a parse tree node.
		The lexical analyzer will not generate TYP_PNODE but the parse will generate them internally and push them onto the stack
	*/
    int type;



	/*
		This is a union used to hold the value of the token. 
		Depending on the value of type, one of the 3 fields will be filled in.
	*/
    union {
		/*
			The character string found as a token
		*/
        char *string;



		/*
			The real number found by teh lexical analyzer
		*/
        double real;



		/*
			A parse tree internal node structure resulting from the combination of previously parsed elements
		*/
        INPparseNode *pnode;
    } value;
} PTelement;

#define PT_STACKSIZE 200

/* These are things defined in PTfunctions.c */

extern double PTplus();
extern double PTminus();
extern double PTtimes();
extern double PTdivide();
extern double PTpower();
extern double PTacos();
extern double PTabs();
extern double PTacosh();
extern double PTasin();
extern double PTasinh();
extern double PTatan();
extern double PTatanh();
extern double PTcos();
extern double PTcosh();
extern double PTexp();
extern double PTln();
extern double PTlog();
extern double PTsgn();
extern double PTsin();
extern double PTsinh();
extern double PTsqrt();
extern double PTtan();
extern double PTtanh();
extern double PTustep();
extern double PTuramp();
extern double PTuminus();

/* And in IFeval.c */

extern int IFeval(IFparseTree *, double, double*, double*, double*);


#endif

