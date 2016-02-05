/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "util.h"
#include "ifsim.h"
#include "iferrmsg.h"
#include "inpptree.h"
#include "suffix.h"


static int PTeval(INPparseNode*, double, double*, double*);
extern double PTfudge_factor;


/*
	This function is part of the parse tree package whcih evaluates the parse tree.
	Using a list of names proided in the IFparseTree structure, the vals vector must be filled in with the actual values
	of the named variables before calling.
	Upon the return of the call, result will be the value of the equation and derivs wil be a vector of partial derivatives of the equation
	to each of the named values.

	This function is a generic function passed by the front end in the IFparseTree structure which is
	used to evaluate the parse tree given. The given parse tree is to be evaluated with its tree->nwnVurs
	variables given the values from the vector vals. The scalar result of evaluating the tree is placed in
	result, while a set of partial derivatives with respect to the input variables is placed in the vector
	derivs.
*/
///<param name = "*tree"> The oarse tree to evaluate </param>
///<param name = "*result"> The value of the equation </param>
///<param name = "*vals"> The values needed for the evaluation </param>
///<param name = "*derivs"> THe derivatives computes during evaluation </param>
int IFeval(IFparseTree *tree, double gmin, double *result, double *vals, double *derivs)
{
	int i, err;
	INPparseTree *myTree = (INPparseTree*)tree;;

	/*
	INPptPrint("calling PTeval, tree = ", myTree);
	printf("values:");
	for (i = 0; i < myTree->p.numVars; i++)
	printf("\tvar%d = %lg\n", i, vals[i]);
	*/

	if ((err = PTeval(myTree->tree, gmin, result, vals)) != OK)
		return (err);

	for (i = 0; i < myTree->p.numVars; i++)
	{
		if ((err = PTeval(myTree->derivs[i], gmin, &derivs[i], vals)) != OK)
			return (err);
	}


	/*
	printf("results: function = %lg\n", *result);
	for (i = 0; i < myTree->p.numVars; i++)
	printf("\td / d var%d = %lg\n", i, derivs[i]);
	*/

	return (OK);
}



/*
	Is an internal function used by the parse tree evaluation function IFeval to evaluate each of the
	individual subtress of the IFparseTree structure to get the values for the overall equation
	and for each of the derivatives
	This fucntion can not be called by any function other than IFeval
*/
///<param name = "*tree"> Tree to evaluate </param>
///<param name = "gmin"> unkown </param>
///<param name = "*res"> Result of evalutaing tree </param>
///<param name = "*vals"> VAlues needed to evaluate tree </param>
static int PTeval(INPparseNode *tree, double gmin, double *res, double *vals)
{
	double r1, r2;
	int err;

	PTfudge_factor = gmin;
	switch (tree->type)
	{
	case PT_CONSTANT:
		*res = tree->constant;
		break;

	case PT_VAR:
		*res = vals[tree->valueIndex];
		break;

	case PT_FUNCTION:
		err = PTeval(tree->left, gmin, &r1, vals);

		if (err != OK)
			return (err);

		*res = (*tree->function)(r1);

		if (*res == HUGE)
		{
			fprintf(stderr, "Error: %lg out of range for %s\n", r1, tree->funcname);
			return (E_PARMVAL);
		}
		break;

	case PT_PLUS:
	case PT_MINUS:
	case PT_TIMES:
	case PT_DIVIDE:
	case PT_POWER:
		err = PTeval(tree->left, gmin, &r1, vals);
		if (err != OK)
			return (err);
		err = PTeval(tree->right, gmin, &r2, vals);
		if (err != OK)
			return (err);
		*res = (*tree->function)(r1, r2);
		if (*res == HUGE)
		{
			fprintf(stderr, "Error: %lg, %lg out of range for %s\n", r1, r2, tree->funcname);
			return (E_PARMVAL);
		}
		break;

	default:
		fprintf(stderr, "Internal Error: bad node type %d\n", tree->type);
		return (E_PANIC);
	}

	return (OK);
}

