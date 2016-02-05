/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1987 Wayne A. Christopher, U. C. Berkeley CAD Group 
**********/

/*
	These functions are all used to implement that parse trees and actually perform the operations
	represented by varios nodes within the trees. 
	Many of these are simply wrappers around math library routines,
	while others are actual implementations of the desired functions.
	These functions return HUGE if their argument is out of range.
*/

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "inpptree.h"
#include "suffix.h"

/* XXX These should be in math.h */

#ifdef HAS_ATRIGH
#  ifdef HAS_NO_ATRIGH_DECL
extern double asinh(), acosh(), atanh();
#  endif
#endif /* HAS_ATRIGH */

double PTfudge_factor;

#define	MODULUS(NUM,LIMIT)	((NUM) - ((int) ((NUM) / (LIMIT))) * (LIMIT))

double
PTabs(arg)
    double arg;
{
    return arg >= 0.0 ? arg : -arg;
}

double
PTsgn(arg)
    double arg;
{
    return arg > 0.0 ? 1.0 : arg < 0.0 ? -1.0 : 0.0;
}



/*
	Implements simple addition and returns arg1 + arg2
*/
///<param name = "arg1"> Left arguement </param>
///<param name = "arg2"> Right argument </param>
double PTplus(double arg1, double arg2)
{
	return (arg1 + arg2);
}



/*
	Implements simple subtraction and returns arg1 - arg2
*/
///<param name = "arg1"> Left arguement </param>
///<param name = "arg2"> Right argument </param>
double PTminus(double arg1, double arg2)
{
	return (arg1 - arg2);
}



/*
	Implements simple multiplication and returns arg1 * arg2
*/
///<param name = "arg1"> Left arguement </param>
///<param name = "arg2"> Right argument </param>
double PTtimes(double arg1, double arg2)
{
	return (arg1 * arg2);
}



/*
	Implements simple division and returns arg1 / arg2
*/
///<param name = "arg1"> Left arguement </param>
///<param name = "arg2"> Right argument </param>
double PTdivide(double arg1, double arg2)
{
	if (arg2 >= 0.0)
		arg2 += PTfudge_factor;
	else
		arg2 -= PTfudge_factor;

	if (arg2 == 0.0)
		return (HUGE);

	return (arg1 / arg2);
}



/*
	Implements simple exponentiation and returns arg1 ^ arg2
*/
double PTpower(double arg1, double arg2)
{
	if (arg1 < 0.0)
	{
		if (fabs(arg2 - ((int)arg2)) / (arg2 + 0.001) < 0.000001)
		{
			arg2 = (int)arg2;
		}
		else
		{
			arg1 = -arg1;
		}
	}
	return (pow(arg1, arg2));
}



/*
	Implement the arc cosine function by calling the corresponding function from the math library.
*/
///<param name = "arg"> Argument </param>
double PTacos(double arg)
{
	return (acos(arg));
}



/*
	Implements the hyperbolic arc cosine function by calling the corresponding function from the math library.
	If the #define name HASATRIGH is define, this function will be avaailable.
	If this name is not defined at compile time, this function and all internal references to it will be
	deleted automatically, since acosh is not a standard part of the C math library
*/
///<param name = "arg"> Argument </param>
double PTacosh(double arg)
{
#ifdef HAS_ATRIGH
	return (acosh(arg));
#else
	if (arg < 1.0)
		arg = 1.0;
	return (log(arg + sqrt(arg*arg - 1.0)));
#endif /* HAS_ATRIGH */
}



/*
	
*/
///<param name = "arg"> Argument </param>
double PTasin(double arg)
{
	return (asin(arg));
}



/*
	Implements the hyperbolic arc sine function using the corresponding function from the
	math library.
	If the #define name HASATRIGH is defined, this function will be available.
	If this name is not defined at compile time, this function and all internal references to it will be deleted
	automatically, since acosh is not a standard part of the C math library.
*/
///<param name = "arg"> Argument </param>
double PTasinh(double arg)
{
#ifdef HAS_ATRIGH
	return (asinh(arg));
#else
	return log(arg + sqrt(arg * arg + 1.0));
#endif /* HAS_ATRIGH */
}



/*
	Implements the arc tangent function using the corresponding function from the math libary.
*/
///<param name = "arg"> Argument </param>
double PTatan(double arg)
{
	return (atan(arg));
}



/*
	Implements the hyperbolic arc tangent function using the corresponding function from the
	math library.
	If the #define name HASATRIGH is defined, this function will be available.
	If this name is not defined at compile time, this function and all internal references to it will be deleted
	automatically, since acosh is not a standard part of the C math library.
*/
///<param name = "arg"> Argument </param>
double PTatanh(double arg)
{
#ifdef HAS_ATRIGH
	return (atanh(arg));
#else
	if (arg < -1.0)
		arg = -1.0 + PTfudge_factor + 1e-10;
	else if (arg > 1.0)
		arg = 1.0 - PTfudge_factor - 1e-10;
	return (log((1.0 + arg) / (1.0 - arg)) / 2.0);
#endif /* HAS_ATRIGH */
}



double PTustep(double arg)
{
	if (arg < 0.0)
		return 0.0;
	else if (arg > 0.0)
		return 1.0;
	else
		return 0.5; /* Ick! */
}



double PTuramp(double arg)
{
	if (arg < 0.0)
		return 0.0;
	else
		return arg;
}



/*
	Implements the cosine function
*/
///<param name = "arg"> Argument </param>
double PTcos(double arg)
{
	return (cos(MODULUS(arg, 2 * M_PI)));
}



/*
	Implements the hyberbolic cosine function
*/
///<param name = "arg"> Argument </param>
double PTcosh(double arg)
{
	return (cosh(arg));
}



/*
	Imeplements the e^arg function
*/
///<param name = "arg"> Argument </param>
double PTexp(double arg)
{
	return (exp(arg));
}



/*
	Implements the natural log function
*/
///<param name = "arg"> Argument </param>
double PTln(double arg)
{
	if (arg < 0.0)
		arg = -arg;

	return (log(arg));
}



/*
	Implements the base 10 logarithm function
*/
///<param name = "arg"> Argument </param>
double PTlog(double arg)
{
	if (arg < 0.0)
		arg = -arg;

	return (log10(arg));
}



/*
	Implements the sine function
*/
///<param name = "arg"> Argument </param>
double PTsin(double arg)
{
	return (sin(MODULUS(arg, 2 * M_PI)));
}



/*
	Implements the hyperbolic sine function
*/
///<param name = "arg"> Argument </param>
double PTsinh(double arg)
{
	return (sinh(arg));
}



/*
	Implements the square root function
*/
///<param name = "arg"> Argument </param>
double PTsqrt(double arg)
{
	if (arg < 0.0)
		arg = -arg;

	return (sqrt(arg));
}



/*
	Implements the tangent fucntion
*/
///<param name = "arg"> Argument </param>
double PTtan(double arg)
{
	return (tan(MODULUS(arg, M_PI)));
}



/*
	Implements the hyperbolic tangent fuction
*/
///<param name = "arg"> Argument </param>
double PTtanh(double arg)
{
	return (tanh(arg));
}



/*
	Implements the unary minus function, returning the negative of its argument.
*/
///<param name = "arg"> Argument </param>
double PTuminus(double arg)
{
	return (-arg);
}

