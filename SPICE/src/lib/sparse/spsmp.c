/*
 *  Spice3 COMPATIBILITY MODULE
 *
 *  Author:                     Advising professor:
 *     Kenneth S. Kundert           Alberto Sangiovanni-Vincentelli
 *     UC Berkeley
 *
 *  This module contains routines that make Sparse1.3 a direct
 *  replacement for the SMP sparse matrix package in Spice3c1 or Spice3d1.
 *  Sparse1.3 is in general a faster and more robust package than SMP.
 *  These advantages become significant on large circuits.
 *
 *  >>> User accessible functions contained in this file:
 *  SMPaddElt
 *  SMPmakeElt
 *  SMPcClear
 *  SMPclear
 *  SMPcLUfac
 *  SMPluFac
 *  SMPcReorder
 *  SMPreorder
 *  SMPcaSolve
 *  SMPcSolve
 *  SMPsolve
 *  SMPmatSize
 *  SMPnewMatrix
 *  SMPdestroy
 *  SMPpreOrder
 *  SMPprint
 *  SMPgetError
 *  SMPcProdDiag
 *  LoadGmin
 *  SMPfindElt
 */

/*
 *  To replace SMP with Sparse, rename the file spSpice3.h to
 *  spMatrix.h and place Sparse in a subdirectory of SPICE called
 *  `sparse'.  Then on UNIX compile Sparse by executing `make spice'.
 *  If not on UNIX, after compiling Sparse and creating the sparse.a
 *  archive, compile this file (spSMP.c) and spSMP.o to the archive,
 *  then copy sparse.a into the SPICE main directory and rename it
 *  SMP.a.  Finally link SPICE.
 *
 *  To be compatible with SPICE, the following Sparse compiler options
 *  (in spConfig.h) should be set as shown below:
 *
 *      REAL                            YES
 *      EXPANDABLE                      YES
 *      TRANSLATE                       NO
 *      INITIALIZE                      NO or YES, YES for use with test prog.
 *      DIAGONAL_PIVOTING               YES
 *      ARRAY_OFFSET                    YES
 *      MODIFIED_MARKOWITZ              NO
 *      DELETE                          NO
 *      STRIP                           NO
 *      MODIFIED_NODAL                  YES
 *      QUAD_ELEMENT                    NO
 *      TRANSPOSE                       YES
 *      SCALING                         NO
 *      DOCUMENTATION                   YES
 *      MULTIPLICATION                  NO
 *      DETERMINANT                     YES
 *      STABILITY                       NO
 *      CONDITION                       NO
 *      PSEUDOCONDITION                 NO
 *      FORTRAN                         NO
 *      DEBUG                           YES
 *      spCOMPLEX                       1
 *      spSEPARATED_COMPLEX_VECTORS     1
 *      spCOMPATIBILITY                 0
 *
 *      spREAL  double
 */

/*
 *  Revision and copyright information.
 *
 *  Copyright (c) 1985,86,87,88,89,90
 *  by Kenneth S. Kundert and the University of California.
 *
 *  Permission to use, copy, modify, and distribute this software and its
 *  documentation for any purpose and without fee is hereby granted, provided
 *  that the above copyright notice appear in all copies and supporting
 *  documentation and that the authors and the University of California
 *  are properly credited.  The authors and the University of California
 *  make no representations as to the suitability of this software for
 *  any purpose.  It is provided `as is', without express or implied warranty.
 */

#ifdef notdef
static char copyright[] =
    "Sparse1.3: Copyright (c) 1985,86,87,88,89,90 by Kenneth S. Kundert";
static char RCSid[] =
    "@(#)$Header: spSMP.c,v 1.2 88/06/24 05:02:42 kundert Exp $";
#endif




/*
 *  IMPORTS
 *
 *  >>> Import descriptions:
 *  spMatrix.h
 *     Sparse macros and declarations.
 *  SMPdefs.h
 *     Spice3's matrix macro definitions.
 */

#include "spice.h"
#include <stdio.h>
#include "spmatrix.h"
#include "smpdefs.h"
#include "spdefs.h"

/* #define NO   0 */
/* #define YES  1 */


static void LoadGmin( char * /*eMatrix*/, double /*Gmin*/ );


/*
	Adds the specified value value to the sparse matrix Matrix at the position of (row, column).
	If necessary, the new element is allocated automatically.
	Returns 0 for success, E_NOMEM for insufficient memory to allocate a new matrix element.
*/
int SMPaddElt(SMPmatrix *Matrix, int row, int column, double value)
{
	*spGetElement((char *)Matrix, row, column) = value;
	return spError((char *)Matrix);
}




/*
	Returns a pointer to the double precision value field  at the location (row, column) in 
	the matrix Matrix. If the location does not exist, it is added.
	If the matrix does not contain the specified row or column it is expanded to encompass it.
	If the allocation to add the element or to expand the matrix fails, NULL is returned, and
	the matric may be corrupted.
*/
double *SMPmakeElt(SMPmatrix *Matrix, int row, int column)
{
	return spGetElement((char *)Matrix, row, column);
}



/*
	Clears to zero both the real and imaginery parts of all
	entries in the specified sparse matrix matrix
*/
void SMPcClear(SMPmatrix *matrix)
{
    spClear( (char *)matrix );
}



/*
	Clears to zero the real part of all entries in the 
	specified matrix Matrix
*/
///<param name = "*Matrix"> The matrix to clear </param>
void SMPclear(SMPmatrix *Matrix)
{
	spClear((char *)Matrix);
}



/*
	Performs the same operations as SMPluFac does but 
	operates on the full complex matrix instead of only the real part of the matrix
*/
int SMPcLUfac(SMPmatrix *matrix, double pivTol)
{
	spSetComplex((char *)matrix);
	return spFactor((char *)matrix);
}




/*
	Performs an LU decomposition of the sparse matrix Matrix. Pictol is the 
	minimum absolute value whcih will be accepted as a pivot element during the 
	factorization.
	If a smaller pivot is found, the decomposition will be aborted and the error code
	E_SINGULAR returned.
	As an aid to Gmin stepping, the value gmin is added to each diagonal element in the
	matrix before using it in the calculations
*/
int SMPluFac(SMPmatrix *Matrix, double PivTol, double Gmin)
{
    spSetReal( (char *)Matrix );
    LoadGmin( (char *)Matrix, Gmin );
    return spFactor( (char *)Matrix );
}



/*
	Performs a reordering and LU factorization of the complex sparse matrix Matrix.
	As in SMPreorder, pivtol is the minimum magnitude which is acceptable for a 
	diagonal element in the decomposition and pivrel is the factor by which a pivot
	element my be numerically non-optimal and still be selected to maintain sparsity
	Additionally, numswaps is multiplied by (-1) ^ (# row swaps + # column swaps).
*/
int SMPcReorder(SMPmatrix *Matrix, double PivTol, double PivRel, int *NumSwaps)
{
	*NumSwaps = 1;
	spSetComplex((char *)Matrix);
	return spOrderAndFactor((char *)Matrix, (spREAL*)NULL, (spREAL)PivRel, (spREAL)PivTol, YES);
}

/*
	Performs a reordering and L-U factorization of the sparse matrix.
	Pivtol is the minumu aboslute value which is accpetable for a diagonal element in the decomponsition and pivrel is teh factor
	by which a pivot element may be non-optimal numerically and yet still be selected to maintain
	sparsity.
	Gmin will be added to each diagonal element before computation to allow the 
	Gmin stepping convergence aid.
*/
int SMPreoder(SMPmatrix *Matrix, double pivTol, double pivRel, double Gmin)
{
	spSetReal((char *)Matrix);
	LoadGmin((char *)Matrix, Gmin);
	return spOrderAndFactor((char *)Matrix, (spREAL*)NULL, (spREAL)pivRel, (spREAL)pivTol, YES);
}



/*
 * SMPcaSolve()
 */
void SMPcaSolve(SMPmatrix *Matrix, double RHS[], double iRHS[], double spare[], double iSpare[])
{
	spSolveTransposed((char *)Matrix, RHS, RHS, iRHS, iRHS);
}



/*
	Works exactly as SMPsolve, but operates on the complex sparse matrix matrix with the
	right hand side and solution vecotrs being the complex pair (rhs + irhs), and two scratch vectors
	spare and ispare being required <- Really?
*/
void SMPcSolve(SMPmatrix *Matrix, double RHS[], double iRHS[], double spare[], double iSpare[])
{
	spSolve((char *)Matrix, RHS, RHS, iRHS, iRHS);
}




/*
	Solves the equation Ax=b where A is a sparse matrix.
	Matrix is a sparse matrix which has already been LU factored by SMPluFac or SMPreorder.
	RHS is the column vector b on in input and is replaced by the row vector x
	by SMPsolve.
	To provide working room for vector permutation and solution, a scratch vector 
	the same size as RHS, called spare, must be supplied.
	The contents of spare will not be used but will be destoryed.
	Dynamic allocation of this vector is possible, but not acceptable since this routine will 
	appear inside the inner loop of the Newton-Raphson iteration with the same temperory space
	needs each time, thus making the use of an externally supplied vector preferable.
*/
void SMPsolve(SMPmatrix *Matrix, double RHS[], double Spare[])
{
	spSolve((char *)Matrix, RHS, RHS, (spREAL*)NULL, (spREAL*)NULL);
}



/*
	Returns the number of rows and columns in the sparse matrix Matrix
*/
int SMPmatSize(SMPmatrix *Matrix)
{
	return spGetSize((char *)Matrix, 1);
}



/*
	Allocates a new set of data structures for a sparse matric to be managed by the SMP package.
	Matrix is set to point to the newly allocated structure.
	No use is made of the current value of matrix.
	SMPnewMatrix returns 0 for success, E_NOMEM for failure to allocate the required space.

	THe allocated matrix will consist of only the basic SMPmatri structure initilized as necessary.
	No elements are created, but a token allocation do not perform correctly when given a null pointer or
	a request for an allocation of size zero
*/
///<param name = "**pMatrix"> Pointer to point to the newly allocated structure </param>
int SMPnewMatrix(SMPmatrix **pMatrix)
{
	int Error;
	*pMatrix = (SMPmatrix *)spCreate(0, 1, &Error);
	return Error;
}




/*
	Dismantles and frees the data structures allocated to the sparse matrix Matrix
*/
///<param name = "*Matrix"> The matrix to free </param>
void SMPdestroy(SMPmatrix *Matrix)
{
	spDestroy((char *)Matrix);
}



/*
	Performs preliminary reordering of the sparse matrix Matrix based on
	knowledge of the characteristics of MNA matrices.
	Voltage sources cause zero valued entried on the diagonal which can cause sever
	problems during the decomposition but the source must also have a corresponding pair of 
	summetric off-diagonal entried which a simple row swap can put on the diagonal.
	This routine locates these structure purely from information in the matrix and 
	performs the necessary row swaps.
*/
int SMPpreOrder(SMPmatrix *Matrix)
{
	spMNA_Preorder((char *)Matrix);
	return spError((char *)Matrix);
}



/*
	A diagnostic routine intended primarly for matrix package debugging, although it
	has also proven useful in debugging matrix loading routines.
	The contents of the matrix matrix will be dumped to the standard I/O system FILE 
	pointer file in a reasonably human-readable format.
	The dump will include all row and column premutation data, pointers, and the real
	and imaginary parts of the matrix.
	Because of the quantity of data printed and the size of "interesting" matrices, no
	attempt is made to print the matrix as an array but simply as row, column
	corrdinates and contents.
*/
void SMPprint(SMPmatrix *matrix, FILE *file)
{
	spPrint((char *)matrix, 0, 1, 1);
}

/*
	Used to query the matrix package for the location in the matrix Matrix where the last reordering failed.
	I and J will be set to the external row and column numbers of the point in the matrix
	where the reordering algorithm gave up and declared the matrix singular
*/
void SMPgetError(SMPmatrix *Matrix, int row, int column)
{
	spWhereSingular((char *)Matrix, row, column);
}



/*
	Computes the product of the diagonal items in the sparse matrix matrix.
	This product is reported as two numbers, an exponent power, which is the power
	of ten which the mantissa must be multiplied by, and the mantissa, which is 
	normalized so that the larger of its real and imaginary parts lies between 0.1 
	and 1.0. 
	If this is applied to an L-U factored matrix, this product is equal to the determinant of the matrix

	Obsolete for Spice3d2 and later
*/
int SMPcProdDiag(SMPmatrix *matrix, SPcomplex *pMantissa, int *pExponent)
{
	spDeterminant((char *)matrix, pExponent, &(pMantissa->real), &(pMantissa->imag));
	return spError((char *)matrix);
}



/*
 * SMPcDProd()
 */
int SMPcDProd(SMPmatrix *Matrix, SPcomplex *pMantissa, int *pExponent)\
{
	double	re, im, x, y, z;
	int		p;

	spDeterminant((char *)Matrix, &p, &re, &im);

#ifndef M_LN2
#define M_LN2   0.69314718055994530942
#endif
#ifndef M_LN10
#define M_LN10  2.30258509299404568402
#endif

#ifdef debug_print
	printf("Determinant 10: (%20g,%20g)^%d\n", re, im, p);
#endif

	/* Convert base 10 numbers to base 2 numbers, for comparison */
	y = p * M_LN10 / M_LN2;
	x = (int)y;
	y -= x;

	/* ASSERT
	 *	x = integral part of exponent, y = fraction part of exponent
	 */

	 /* Fold in the fractional part */
#ifdef debug_print
	printf(" ** base10 -> base2 int =  %g, frac = %20g\n", x, y);
#endif
	z = pow(2.0, y);
	re *= z;
	im *= z;
#ifdef debug_print
	printf(" ** multiplier = %20g\n", z);
#endif

	/* Re-normalize (re or im may be > 2.0 or both < 1.0 */
	if (re != 0.0)
	{
		y = logb(re);

		if (im != 0.0)
			z = logb(im);
		else
			z = 0;
	}
	else if (im != 0.0)
	{
		z = logb(im);
		y = 0;
	}
	else
	{
		/* Singular */
		/*printf("10 -> singular\n");*/
		y = 0;
		z = 0;
	}

#ifdef debug_print
	printf(" ** renormalize changes = %g,%g\n", y, z);
#endif
	if (y < z)
		y = z;

	*pExponent = x + y;
	x = scalb(re, (int)-y);
	z = scalb(im, (int)-y);
#ifdef debug_print
	printf(" ** values are: re %g, im %g, y %g, re' %g, im' %g\n",
		re, im, y, x, z);
#endif
	pMantissa->real = scalb(re, (int)-y);
	pMantissa->imag = scalb(im, (int)-y);

#ifdef debug_print
	printf("Determinant 10->2: (%20g,%20g)^%d\n", pMantissa->real,
		pMantissa->imag, *pExponent);
#endif
	return spError((char *)Matrix);
}



/*
 *  The following routines need internal knowledge of the Sparse data
 *  structures.
 */

/*
 *  LOAD GMIN
 *
 *  This routine adds Gmin to each diagonal element.  Because Gmin is
 *  added to the current diagonal, which may bear little relation to
 *  what the outside world thinks is a diagonal, and because the
 *  elements that are diagonals may change after calling spOrderAndFactor,
 *  use of this routine is not recommended.  It is included here simply
 *  for compatibility with Spice3.
 */

static void LoadGmin(char *eMatrix, register double Gmin)
{
	MatrixPtr Matrix = (MatrixPtr)eMatrix;
	register int I;
	register ArrayOfElementPtrs Diag;
	register ElementPtr diag;

	/* Begin `LoadGmin'. */
	ASSERT(IS_SPARSE(Matrix));

	if (Gmin != 0.0)
	{
		Diag = Matrix->Diag;

		for (I = Matrix->Size; I > 0; I--)
		{
			if (diag = Diag[I])
				diag->Real += Gmin;
		}
	}
	return;
}




/*
 *  FIND ELEMENT
 *
 *  This routine finds an element in the matrix by row and column number.
 *  If the element exists, a pointer to it is returned.  If not, then NULL
 *  is returned unless the CreateIfMissing flag is true, in which case a
 *  pointer to the new element is returned.
 */


/*
	Finds the specified location in the sparese matrix eMatrix at poition (row, column) and
	returns a pointer to it.
	If the location is not present in the matrix, it will create be created if CreateIfMissing flag is non-zero.
	Returns NULL if the location is not present and CreateIfMissing flag is zero or if no memory is avaible 
	for allocation, otherwise returns a pointer to the internal matrix structure.

	Note: Row and Column are interpreted as internal row and column numbers, not external.
	This function is not intended for general use, but is an internal function within the 
	matrix package.
*/
SMPelement *SMPfindElt(SMPmatrix *eMatrix, int row, int column, int CreateIfMissing)
{
	MatrixPtr Matrix = (MatrixPtr)eMatrix;
	ElementPtr Element;

	/* Begin `SMPfindElt'. */
	ASSERT(IS_SPARSE(Matrix));
	row = Matrix->ExtToIntRowMap[row];
	column = Matrix->ExtToIntColMap[column];
	Element = Matrix->FirstInCol[column];
	Element = spcFindElementInCol(Matrix, &Element, row, column, CreateIfMissing);
	return (SMPelement *)Element;
}

/* XXX The following should probably be implemented in spUtils */

/*
 * SMPcZeroCol()
 */
int SMPcZeroCol(MatrixPtr Matrix, int Col)
{
	ElementPtr	Element;

	Col = Matrix->ExtToIntColMap[Col];

	for (Element = Matrix->FirstInCol[Col]; Element != NULL; Element = Element->NextInCol)
	{
		Element->Real = 0.0;
		Element->Imag = 0.0;
	}

	return spError((char *)Matrix);
}



/*
 * SMPcAddCol()
 */
int SMPcAddCol(MatrixPtr Matrix, int Accum_Col, int Addend_Col)
{
	ElementPtr	Accum, Addend, *Prev;

	Accum_Col = Matrix->ExtToIntColMap[Accum_Col];
	Addend_Col = Matrix->ExtToIntColMap[Addend_Col];

	Addend = Matrix->FirstInCol[Addend_Col];
	Prev = &Matrix->FirstInCol[Accum_Col];
	Accum = *Prev;;

	while (Addend != NULL)
	{

		while (Accum && Accum->Row < Addend->Row)
		{
			Prev = &Accum->NextInCol;
			Accum = *Prev;
		}

		if (!Accum || Accum->Row > Addend->Row)
		{
			Accum = spcCreateElement(Matrix, Addend->Row, Accum_Col, Prev, 0);
		}

		Accum->Real += Addend->Real;
		Accum->Imag += Addend->Imag;
		Addend = Addend->NextInCol;
	}

	return spError((char *)Matrix);
}



/*
 * SMPzeroRow()
 */
int SMPzeroRow(MatrixPtr Matrix, int Row)
{
	ElementPtr	Element;

	Row = Matrix->ExtToIntColMap[Row];

	if (Matrix->RowsLinked == NO)
		spcLinkRows(Matrix);

#if spCOMPLEX
	if (Matrix->PreviousMatrixWasComplex OR Matrix->Complex)
	{
		for (Element = Matrix->FirstInRow[Row]; Element != NULL; Element = Element->NextInRow)
		{
			Element->Real = 0.0;
			Element->Imag = 0.0;
		}
	}
	else
#endif
	{
		for (Element = Matrix->FirstInRow[Row]; Element != NULL; Element = Element->NextInRow)
		{
			Element->Real = 0.0;
		}
	}

	return spError((char *)Matrix);
}

