#include "common/FEMVector.h"

FEMVector::FEMVector(double x)
{
	re = x;
	im = 0.;
}

FEMVector::FEMVector(int x)
{
	re = (double)x;
	im = 0.;
}

FEMVector::FEMVector()
{
	re = 0.;
	im = 0.;
}

FEMVector::FEMVector(double x, double y)
{
	re = x;
	im = y;
}

FEMVector FEMVector::Sqrt()
{
	double w, z;
	FEMVector y;

	if ((re == 0) && (im == 0))
		w = 0;
	else if (fabs(re) > fabs(im))
	{
		z = im / re;
		w = sqrt(fabs(re))*sqrt((1. + sqrt(1. + z*z)) / 2.);
	}
	else
	{
		z = re / im;
		w = sqrt(fabs(im))*sqrt((fabs(z) + sqrt(1. + z*z)) / 2.);
	}

	if (w == 0)
	{
		y.re = 0;
		y.im = 0;
		return y;
	}

	if (re >= 0)
	{
		y.re = w;
		y.im = im / (2.*w);
		return y;
	}

	if (im >= 0)
	{
		y.re = fabs(im) / (2.*w);
		y.im = w;
		return y;
	}

	y.re = fabs(im) / (2.*w);
	y.im = (-w);
	return y;
}

FEMVector FEMVector::Conj()
{
	return FEMVector(re, -im);
}

double FEMVector::Abs()
{
	if ((re == 0) && (im == 0))
		return 0.;

	if (fabs(re) > fabs(im))
		return fabs(re)*sqrt(1. + (im / re)*(im / re));
	else
		return fabs(im)*sqrt(1. + (re / im)*(re / im));
}

/* Calculates the angle between the real and imagnary part */
double FEMVector::Arg()
{
	if ((re == 0) && (im == 0))
		return 0.;

	return atan2(im, re);
}

FEMVector FEMVector::Inv()
{
	double c;
	FEMVector z;

	if (fabs(re) > fabs(im))
	{
		c = im / re;
		z.re = 1. / (re*(1. + c*c));
		z.im = (-c)*z.re;
	}
	else 
	{
		c = re / im;
		z.im = (-1.) / (im*(1. + c*c));
		z.re = (-c)*z.im;
	}

	return z;
}

double FEMVector::Re()
{
	return re;
}

double FEMVector::Im()
{
	return im;
}

void FEMVector::Set(double x, double y)
{
	re = x; 
	im = y;
}

char* FEMVector::ToString(char *s)
{
	if (im < 0)
		sprintf(s, "%.3e - j %.3e", re, fabs(im));
	else
		sprintf(s, "%.3e + j %.3e", re, im);
	return s;
}

//******* Addition ***************************************************

FEMVector FEMVector::operator+(const FEMVector& z)
{
	return FEMVector(re + z.re, im + z.im);
};

FEMVector FEMVector::operator+(int z)
{
	return FEMVector(re + ((double)z), im);
};

FEMVector FEMVector::operator+(double z)
{
	return FEMVector(re + z, im);
};

void FEMVector::operator+=(const FEMVector& z)
{
	re += z.re;
	im += z.im;
};

void FEMVector::operator+=(double z)
{
	re += z;
};

void FEMVector::operator+=(int z)
{
	re += (double)z;
};

FEMVector operator+(int x, const FEMVector& y)
{
	return FEMVector(((double)x) + y.re, y.im);
}

FEMVector operator+(double x, const FEMVector& y)
{
	return FEMVector(x + y.re, y.im);
}

FEMVector operator+(const FEMVector& x, const FEMVector& y)
{
	return FEMVector(x.re + y.re, x.im + y.im);
}


//******* Subtraction ***************************************************
FEMVector FEMVector::operator-()
{
	return FEMVector(-re, -im);
}

FEMVector FEMVector::operator-(const FEMVector& z)
{
	return FEMVector(re - z.re, im - z.im);
};

FEMVector FEMVector::operator-(int z)
{
	return FEMVector(re - ((double)z), im);
};

FEMVector FEMVector::operator-(double z)
{
	return FEMVector(re - z, im);
};

void FEMVector::operator-=(const FEMVector& z)
{
	re -= z.re;
	im -= z.im;
};

void FEMVector::operator-=(double z)
{
	re -= z;
};

void FEMVector::operator-=(int z)
{
	re -= (double)z;
};

FEMVector operator-(int x, const FEMVector& y)
{
	return FEMVector(((double)x) - y.re, -y.im);
}

FEMVector operator-(double x, const FEMVector& y)
{
	return FEMVector(x - y.re, -y.im);
}

FEMVector operator-(const FEMVector& x, const FEMVector& y)
{
	return FEMVector(x.re - y.re, x.im - y.im);
}

FEMVector operator-(const FEMVector& y)
{
	return FEMVector(-y.re, -y.im);
}
//******* Multiplication ***************************************************

FEMVector FEMVector::operator*(const FEMVector& z)
{
	return FEMVector(re*z.re - im*z.im, re*z.im + im*z.re);
};

FEMVector FEMVector::operator*(int z)
{
	return FEMVector(re*((double)z), im*((double)z));
};

FEMVector FEMVector::operator*(double z)
{
	return FEMVector(re*z, im*z);
};

void FEMVector::operator*=(const FEMVector& z)
{
	FEMVector x(re*z.re - im*z.im, re*z.im + im*z.re);
	re = x.re; im = x.im;
};

void FEMVector::operator*=(double z)
{
	re *= z; im *= z;
};

void FEMVector::operator*=(int z)
{
	re *= (double)z;
	im *= (double)z;
};

FEMVector operator*(int x, const FEMVector& y)
{
	return FEMVector(((double)x) * y.re, ((double)x)*y.im);
}

FEMVector operator*(double x, const FEMVector& y)
{
	return FEMVector(x*y.re, x*y.im);
}

FEMVector operator*(const FEMVector& x, const FEMVector& y)
{
	return FEMVector(x.re*y.re - x.im*y.im, x.re*y.im + x.im*y.re);
}

//******* Division ***************************************************

FEMVector FEMVector::operator/(const FEMVector& z)
{
	double c;
	FEMVector y;

	if (fabs(z.re) > fabs(z.im))
	{
		c = z.im / z.re;
		y.re = 1. / (z.re*(1. + c*c));
		y.im = (-c)*y.re;
	}
	else
	{
		c = z.re / z.im;
		y.im = (-1.) / (z.im*(1. + c*c));
		y.re = (-c)*y.im;
	}

	return *this * y;
};


FEMVector FEMVector::operator/(int z)
{
	return FEMVector(re / ((double)z), im / ((double)z));
};

FEMVector FEMVector::operator/(double z)
{
	return FEMVector(re / z, im / z);
};

void FEMVector::operator/=(const FEMVector& z)
{
	*this = *this / z;
};

void FEMVector::operator/=(double z)
{
	re /= z;
	im /= z;
};

void FEMVector::operator/=(int z)
{
	re /= (double)z;
	im /= (double)z;
};

FEMVector operator/(int x, const FEMVector& z)
{
	double c;
	FEMVector y;

	if (fabs(z.re) > fabs(z.im))
	{
		c = z.im / z.re;
		y.re = 1. / (z.re*(1. + c*c));
		y.im = (-c)*y.re;
	}
	else
	{
		c = z.re / z.im;
		y.im = (-1.) / (z.im*(1. + c*c));
		y.re = (-c)*y.im;
	}

	y.re *= (double)x;
	y.im *= (double)x;

	return y;
}

FEMVector operator/(double x, const FEMVector& z)
{
	double c;
	FEMVector y;

	if (fabs(z.re) > fabs(z.im))
	{
		c = z.im / z.re;
		y.re = 1. / (z.re*(1. + c*c));
		y.im = (-c)*y.re;
	}
	else
	{
		c = z.re / z.im;
		y.im = (-1.) / (z.im*(1. + c*c));
		y.re = (-c)*y.im;
	}

	y.re *= x;
	y.im *= x;

	return y;
}

FEMVector operator/(const FEMVector& x, const FEMVector& z)
{
	double c;
	FEMVector y;

	if (fabs(z.re) > fabs(z.im))
	{
		c = z.im / z.re;
		y.re = 1. / (z.re*(1. + c*c));
		y.im = (-c)*y.re;
	}
	else
	{
		c = z.re / z.im;
		y.im = (-1.) / (z.im*(1. + c*c));
		y.re = (-c)*y.im;
	}

	return x*y;
}

//****** Equals definitions ********************************

void FEMVector::operator=(double z)
{
	re = z;
	im = 0;
}

void FEMVector::operator=(int z)
{
	re = (double)z;
	im = 0;
}

//***** Tests ***********************************************
bool FEMVector::operator==(const FEMVector& z) 
{
	if ((z.im == im) && (z.re == re))
		return TRUE;

	return FALSE;
}

bool FEMVector::operator==(double z)
{
	if ((z == re) && (im == 0))
		return TRUE;

	return FALSE;
}

bool FEMVector::operator==(int z)
{
	if ((re == (double)z) && (im == 0))
		return TRUE;

	return FALSE;
}

bool FEMVector::operator!=(const FEMVector& z)
{
	if ((z.re == re) && (z.im == im))
		return FALSE;

	return TRUE;
}

bool FEMVector::operator!=(double z)
{
	if ((re != z) || (im != 0))
		return TRUE;

	return FALSE;
}

bool FEMVector::operator!=(int z) {
	if ((re != (double)z) || (im != 0)) 
		return TRUE;

	return FALSE;
}

//***** Useful functions ************************************

FEMVector conj(const FEMVector& x)
{
	return FEMVector(x.re, -x.im);
}

FEMVector exp(const FEMVector& x)
{
	FEMVector y;

	y.re = cos(x.im)*exp(x.re);
	y.im = sin(x.im)*exp(x.re);

	return y;
}

FEMVector sqrt(const FEMVector& x)
{
	double w, z;
	FEMVector y;

	if ((x.re == 0) && (x.im == 0))
		w = 0;

	else if (fabs(x.re) > fabs(x.im))
	{
		z = x.im / x.re;
		w = sqrt(fabs(x.re))*sqrt((1. + sqrt(1. + z*z)) / 2.);
	}
	else
	{
		z = x.re / x.im;
		w = sqrt(fabs(x.im))*sqrt((fabs(z) + sqrt(1. + z*z)) / 2.);
	}

	if (w == 0)
	{
		y.re = 0;
		y.im = 0;
		return y;
	}

	if (x.re >= 0)
	{
		y.re = w;
		y.im = x.im / (2.*w);
		return y;
	}

	if (x.im >= 0)
	{
		y.re = fabs(x.im) / (2.*w);
		y.im = w;
		return y;
	}

	y.re = fabs(x.im) / (2.*w);
	y.im = (-w);

	return y;
}

FEMVector tanh(const FEMVector& x)
{
	FEMVector y;

	if (x.re > 0)
	{
		y = (1 - exp(-2 * x)) / (1 + exp(-2 * x));
	}
	else
	{
		y = (exp(2 * x) - 1) / (exp(2 * x) + 1);
	}

	return y;
}

FEMVector sinh(const FEMVector& x)
{
	return (exp(x) - exp(-x)) / 2;
}

FEMVector cosh(const FEMVector& x)
{
	return (exp(x) + exp(-x)) / 2;
}


FEMVector cos(const FEMVector& x)
{
	return (exp(I*x) + exp(-I*x)) / 2;
}

FEMVector acos(const FEMVector& x)
{
	return PI / 2. - arg(I*x + sqrt(1 - x*x)) + I*log(abs(I*x + sqrt(1 - x*x)));
}

FEMVector sin(const FEMVector& x)
{
	return (exp(I*x) - exp(-I*x)) / (2 * I);
}

FEMVector asin(const FEMVector& x)
{
	return arg(I*x + sqrt(1 - x*x)) - I*log(abs(I*x + sqrt(1 - x*x)));
}

FEMVector tan(const FEMVector& x)
{
	return sin(x) / cos(x);
}

FEMVector atan(const FEMVector& x)
{
	return (arg(1 + I*x) - arg(1 - I*x) - I*(log(abs(1 + I*x) / abs(1 - I*x)))) / 2;
}

double abs(const FEMVector& x)
{
	if ((x.re == 0) && (x.im == 0))
		return 0.;

	if (fabs(x.re) > fabs(x.im))
		return fabs(x.re)*sqrt(1. + (x.im / x.re)*(x.im / x.re));
	else
		return fabs(x.im)*sqrt(1. + (x.re / x.im)*(x.re / x.im));
}

double arg(const FEMVector& x)
{
	if ((x.re == 0) && (x.im == 0))
		return 0.;

	return atan2(x.im, x.re);
}

FEMVector log(const FEMVector& x)
{
	FEMVector y;

	y.im = arg(x);
	y.re = log(abs(x));

	return y;
}

FEMVector pow(const FEMVector& x, double y)
{
	return exp(y * log(x));
}

FEMVector pow(const FEMVector& x, int y)
{
	if (y == 0)
		return FEMVector(1, 0);

	int i;
	FEMVector z;

	if (y > 0)
	{
		z = x;
		for (i = 1; i < y; i++) 
			z *= x;
	}
	else
	{
		z = 1 / x;
		FEMVector w = z;
		for (i = 1; i < (-y); i++) 
			z *= w;
	}

	return z;
}

FEMVector pow(const FEMVector& x, const FEMVector& y)
{
	return exp(y * log(x));
}

double Re(const FEMVector& a)
{
	return a.re;
}

double Im(const FEMVector& a)
{
	return a.im;
}

