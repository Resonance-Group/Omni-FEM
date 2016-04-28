#include "common/FEMVector.h"

ComplexNumber(double realComponent, double imaginaryComponent) : Vector(realComponent, imaginaryComponent)
{
	
}



ComplexNumber ComplexNumber::getConjugate()
{
	return (*(new ComplexNumber(xComponent, -yComponent)));
}


double ComplexNumber::getRealComponent()
{
	return xComponent;
}



double ComplexNumber::getImaginaryComponent()
{
	return yComponent;
}



Vector ComplexNumber::sqrt()
{
	double w, z;
	ComplexNumber y;

	if ((re == 0) && (im == 0))
		w = 0;
	else if (fabs(xComponent) > fabs(yComponent))
	{
		z = yComponent / xComponent;
		w = sqrt(fabs(xComponent)) * sqrt((1. + sqrt(1. + z * z)) / 2.0d);
	}
	else
	{
		z = xComponent / yComponent;
		w = sqrt(fabs(yComponent)) * sqrt((fabs(z) + sqrt(1. + z * z)) / 2.0d);
	}

	if (w == 0)
	{
		y.setComplexNumber(0.0d, 0.0d);
		return y;
	}

	if (re >= 0)
	{
		y.setComplexNumber(w, yComponent / (2.0d * w));
		return y;
	}

	if (im >= 0)
	{
		y.setComplexNumber(fabs(yComponent) / (2.0d * w), w);
		return y;
	}
	
	y.setComplexNumber(fabs(yComponent) / (2.0d * w), -w);
	return y;
}



ComplexNumber ComplexNumber::getInverse()
{
	
}



void ComplexNumber::setComplexNumber(double realComponent, double imaginaryComponent)
{
	xComponent = realComponent;
	
	yComponent = imaginaryComponent;
}



double ComplexNumber::Abs()
{
	if ((xComponent == 0) && (yComponent == 0))
		return 0.;

	if (fabs(xComponent) > fabs(yComponent))
		return fabs(xComponent)*sqrt(1. + (yComponent / xComponent)*(yComponent / xComponent));
	else
		return fabs(yComponent)*sqrt(1. + (xComponent / yComponent)*(xComponent / yComponent));
}



Vector ComplexNumber::Inv()
{
	double c;
	Vector z;

	if (fabs(xComponent) > fabs(yComponent))
	{
		c = yComponent / xComponent;
		z.xComponent = 1.0d / (xComponent * (1.0d + c * c));
		z.yComponent = (-c) * z.xComponent;
	}
	else 
	{
		c = xComponent / yComponent;
		z.yComponent = (-1.0d) / (yComponent*(1.0d + c * c));
		z.xComponent = (-c) * z.yComponent;
	}

	return z;
}