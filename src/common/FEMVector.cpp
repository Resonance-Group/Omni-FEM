#include "common/Vector.h"

Vector::Vector(double x, double y)
{
	xComponent = x;
	yComponent = y;
}

Vector Vector::sqrt()
{

}



double Vector::Abs()
{
	
}

/* Calculates the angle between the real and yComponentagnary part */
double Vector::Arg()
{
	if ((xComponent == 0) && (yComponent == 0))
		return 0.;

	return atan2(yComponent, xComponent);
}

Vector Vector::Inv()
{
	
}

double Vector::getXComponent()
{
	return xComponent;
}

double Vector::getYComponent()
{
	return yComponent;
}

void Vector::Set(double x, double y)
{
	xComponent = x; 
	yComponent = y;
}

char* Vector::ToString(char *s)
{
	if (yComponent < 0)
		sprintf(s, "%.3e - j %.3e", xComponent, fabs(yComponent));
	else
		sprintf(s, "%.3e + j %.3e", xComponent, yComponent);
	return s;
}

//******* Addition ***************************************************

Vector Vector::operator+(const Vector &z)
{
	return Vector(xComponent + z.getXComponent(), yComponent + z.getYComponent());
};

Vector Vector::operator+(int z)
{
	return Vector(xComponent + ((double)z), yComponent);
};

Vector Vector::operator+(double z)
{
	return Vector(xComponent + z, yComponent);
};

void Vector::operator+=(const Vector &z)
{
	xComponent += z.getXComponent();
	yComponent += z.getYComponent();
};

void Vector::operator+=(double z)
{
	xComponent += z;
};

void Vector::operator+=(int z)
{
	xComponent += (double)z;
};

Vector operator+(int x, const Vector &y)
{
	return Vector(((double)x) + y.getXComponent(), y.getYComponent());
}

Vector operator+(double x, const Vector &y)
{
	return Vector(x + y.xComponent, y.getYComponent());
}

Vector operator+(const Vector &x, const Vector &y)
{
	return Vector(x.xComponent + y.xComponent, x.getYComponent() + y.getYComponent());
}


//******* Subtraction ***************************************************
Vector Vector::operator-()
{
	return Vector(-xComponent, -yComponent);
}

Vector Vector::operator-(const Vector &z)
{
	return Vector(xComponent - z.xComponent, yComponent - z.getYComponent());
};

Vector Vector::operator-(int z)
{
	return Vector(xComponent - ((double)z), yComponent);
};

Vector Vector::operator-(double z)
{
	return Vector(xComponent - z, yComponent);
};

void Vector::operator-=(const Vector &z)
{

	xComponent -= z.getXComponent();
	yComponent -= z.getYComponent();
};

void Vector::operator-=(double z)
{
	re -= z;
};

void Vector::operator-=(int z)
{
	re -= (double)z;
};

Vector operator-(int x, const Vector &y)
{
	return Vector(((double)x) - y.re, -y.getYComponent());
}

Vector operator-(double x, const Vector &y)
{
	return Vector(x - y.re, -y.getYComponent());
}

Vector operator-(const Vector &x, const Vector &y)
{
	return Vector(x.re - y.re, x.getYComponent() - y.getYComponent());
}

Vector operator-(const Vector &y)
{
	return Vector(-y.re, -y.getYComponent());
}
//******* Multiplication ***************************************************

Vector Vector::operator*(const Vector &z)
{
	return Vector(re * z.re - yComponent * z.getYComponent(), re * z.getYComponent() + yComponent * z.re);
};

Vector Vector::operator*(int z)
{
	return Vector(re * ((double)z), yComponent * ((double)z));
};

Vector Vector::operator*(double z)
{
	return Vector(re * z, yComponent * z);
};

void Vector::operator*=(const Vector &z)
{
	Vector x(re * z.re - yComponent * z.getYComponent(), re * z.getYComponent() + yComponent * z.re);
	re = x.re; yComponent = x.getYComponent();
};

void Vector::operator*=(double z)
{
	re *= z; yComponent *= z;
};

void Vector::operator*=(int z)
{
	re *= (double)z;
	yComponent *= (double)z;
};

Vector operator*(int x, const Vector &y)
{
	return Vector(((double)x) * y.re, ((double)x) * y.getYComponent());
}

Vector operator*(double x, const Vector &y)
{
	return Vector(x * y.re, x * y.getYComponent());
}

Vector operator*(const Vector &x, const Vector &y)
{
	return Vector(x.re * y.re - x.getYComponent() * y.yComponent, x.re * y.getYComponent() + x.getYComponent() * y.re);
}

//******* Division ***************************************************

Vector Vector::operator/(const Vector &z)
{
	double c;
	Vector y;

	if (fabs(z.re) > fabs(z.getYComponent()))
	{
		c = z.getYComponent() / z.re;
		y.re = 1. / (z.re * (1. + c * c));
		y.getYComponent() = (-c) * y.re;
	}
	else
	{
		c = z.re / z.getYComponent();
		y.getYComponent() = (-1.) / (z.getYComponent() * (1. + c * c));
		y.re = (-c) * y.getYComponent();
	}

	return *this * y;
};


Vector Vector::operator/(int z)
{
	return Vector(re / ((double)z), yComponent / ((double)z));
};

Vector Vector::operator/(double z)
{
	return Vector(re / z, yComponent / z);
};

void Vector::operator/=(const Vector &z)
{
	*this = *this / z;
};

void Vector::operator/=(double z)
{
	re /= z;
	yComponent /= z;
};

void Vector::operator/=(int z)
{
	re /= (double)z;
	yComponent /= (double)z;
};

Vector operator/(int x, const Vector& z)
{
	double c;
	Vector y;

	if (fabs(z.re) > fabs(z.getYComponent()))
	{
		c = z.getYComponent() / z.re;
		y.re = 1. / (z.re * (1. + c * c));
		y.getYComponent() = (-c) * y.re;
	}
	else
	{
		c = z.re / z.getYComponent();
		y.getYComponent() = (-1.) / (z.getYComponent() * (1. + c * c));
		y.re = (-c) * y.getYComponent();
	}

	y.re *= (double)x;
	y.yComponent *= (double)x;

	return y;
}

Vector operator/(double x, const Vector& z)
{
	double c;
	Vector y;

	if (fabs(z.re) > fabs(z.getYComponent()))
	{
		c = z.getYComponent() / z.re;
		y.re = 1. / (z.re * (1. + c * c));
		y.getYComponent() = (-c) * y.re;
	}
	else
	{
		c = z.re / z.getYComponent();
		y.getYComponent() = (-1.) / (z.getYComponent() * (1. + c * c));
		y.re = (-c) * y.getYComponent();
	}

	y.re *= x;
	y.getYComponent() *= x;

	return y;
}

Vector operator/(const Vector &x, const Vector &z)
{
	double c;
	Vector y;

	if (fabs(z.re) > fabs(z.getYComponent()))
	{
		c = z.getYComponent() / z.re;
		y.re = 1. / (z.re * (1. + c * c));
		y.getYComponent() = (-c) * y.re;
	}
	else
	{
		c = z.re / z.getYComponent();
		y.getYComponent() = (-1.) / (z.getYComponent() * (1. + c*c));
		y.re = (-c) * y.getYComponent();
	}

	return (x * y);
}

//****** Equals definitions ********************************

void Vector::operator=(double z)
{
	re = z;
	yComponent = 0;
}

void Vector::operator=(int z)
{
	re = (double)z;
	yComponent = 0;
}

//***** Tests ***********************************************
bool Vector::operator==(const Vector& z) 
{
	if ((z.getYComponent() == yComponent) && (z.re == re))
		return true;

	return false;
}

bool Vector::operator==(double z)
{
	if ((z == re) && (yComponent == 0))
		return true;

	return false;
}

bool Vector::operator==(int z)
{
	if ((re == (double)z) && (yComponent == 0))
		return true;

	return false;
}

bool Vector::operator!=(const Vector& z)
{
	if ((z.re == re) && (z.getYComponent() == yComponent))
		return false;

	return true;
}

bool Vector::operator!=(double z)
{
	if ((re != z) || (yComponent != 0))
		return true;

	return false;
}

bool Vector::operator!=(int z) {
	if ((re != (double)z) || (yComponent != 0)) 
		return true;

	return false;
}

//***** Useful functions ************************************

Vector conj(const Vector &x)
{
	return Vector(x.re, -x.getYComponent());
}

Vector exp(const Vector &x)
{
	Vector y;

	y.re = cos(x.getYComponent()) * exp(x.re);
	y.getYComponent() = sin(x.getYComponent()) * exp(x.re);

	return y;
}

Vector sqrt(const Vector &x)
{
	double w, z;
	Vector y;

	if ((x.re == 0) && (x.getYComponent() == 0))
		w = 0;

	else if (fabs(x.re) > fabs(x.getYComponent()))
	{
		z = x.getYComponent() / x.re;
		w = sqrt(fabs(x.re)) * sqrt((1. + sqrt(1. + z * z)) / 2.);
	}
	else
	{
		z = x.re / x.getYComponent();
		w = sqrt(fabs(x.getYComponent())) * sqrt((fabs(z) + sqrt(1. + z * z)) / 2.);
	}

	if (w == 0)
	{
		y.re = 0;
		y.getYComponent() = 0;
		return y;
	}

	if (x.re >= 0)
	{
		y.re = w;
		y.getYComponent() = x.getYComponent() / (2. * w);
		return y;
	}

	if (x.getYComponent() >= 0)
	{
		y.re = fabs(x.getYComponent()) / (2. * w);
		y.getYComponent() = w;
		return y;
	}

	y.re = fabs(x.getYComponent()) / (2. * w);
	y.getYComponent() = (-w);

	return y;
}

Vector tanh(const Vector& x)
{
	Vector y;

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

Vector sinh(const Vector& x)
{
	return (exp(x) - exp(-x)) / 2;
}

Vector cosh(const Vector& x)
{
	return (exp(x) + exp(-x)) / 2;
}


Vector cos(const Vector& x)
{
	return (exp(I*x) + exp(-I*x)) / 2;
}

Vector acos(const Vector& x)
{
	return PI / 2. - arg(I*x + sqrt(1 - x*x)) + I*log(abs(I*x + sqrt(1 - x*x)));
}

Vector sin(const Vector& x)
{
	return (exp(I*x) - exp(-I*x)) / (2 * I);
}

Vector asin(const Vector& x)
{
	return arg(I*x + sqrt(1 - x*x)) - I*log(abs(I*x + sqrt(1 - x*x)));
}

Vector tan(const Vector& x)
{
	return sin(x) / cos(x);
}

Vector atan(const Vector& x)
{
	return (arg(1 + I*x) - arg(1 - I*x) - I*(log(abs(1 + I*x) / abs(1 - I*x)))) / 2;
}

double abs(const Vector& x)
{
	if ((x.re == 0) && (x.yComponent == 0))
		return 0.;

	if (fabs(x.re) > fabs(x.yComponent))
		return fabs(x.re)*sqrt(1. + (x.yComponent / x.re)*(x.yComponent / x.re));
	else
		return fabs(x.yComponent)*sqrt(1. + (x.re / x.yComponent)*(x.re / x.yComponent));
}

double arg(const Vector& x)
{
	if ((x.re == 0) && (x.yComponent == 0))
		return 0.;

	return atan2(x.yComponent, x.re);
}

Vector log(const Vector& x)
{
	Vector y;

	y.yComponent = arg(x);
	y.re = log(abs(x));

	return y;
}

Vector pow(const Vector& x, double y)
{
	return exp(y * log(x));
}

Vector pow(const Vector& x, int y)
{
	if (y == 0)
		return Vector(1, 0);

	int i;
	Vector z;

	if (y > 0)
	{
		z = x;
		for (i = 1; i < y; i++) 
			z *= x;
	}
	else
	{
		z = 1 / x;
		Vector w = z;
		for (i = 1; i < (-y); i++) 
			z *= w;
	}

	return z;
}

Vector pow(const Vector& x, const Vector& y)
{
	return exp(y * log(x));
}

double Re(const Vector& a)
{
	return a.re;
}

double yComponent(const Vector& a)
{
	return a.yComponent;
}

