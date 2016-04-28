#include "common/Vector.h"

Vector::Vector(double x, double y)
{
	xComponent = x;
	yComponent = y;
}

Vector::Vector()
{
	xComponent = 0.0d;
	yComponent = 0.0d;
}


Vector Vector::Sqrt()
{

}



double Vector::Abs()
{
	return 0.0d;
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

double Vector::getXComponent() const
{
	return xComponent;
}

double Vector::getYComponent() const
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
	Vector *tempVect = new Vector(xComponent + z.getXComponent(), yComponent + z.getYComponent());
	return *tempVect;
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
	return Vector(x.getXComponent() + y.getXComponent(), x.getYComponent() + y.getYComponent());
}


//******* Subtraction ***************************************************
Vector Vector::operator-()
{
	return Vector(-xComponent, -yComponent);
}

Vector Vector::operator-(const Vector &z)
{
	return Vector(xComponent - z.getXComponent(), yComponent - z.getYComponent());
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
	xComponent -= z;
};

void Vector::operator-=(int z)
{
	xComponent -= (double)z;
};

Vector operator-(int x, const Vector &y)
{
	return Vector(((double)x) - y.getXComponent(), -y.getYComponent());
}

Vector operator-(double x, const Vector &y)
{
	return Vector(x - y.getXComponent(), -y.getYComponent());
}

Vector operator-(const Vector &x, const Vector &y)
{
	return Vector(x.getXComponent() - y.getXComponent(), x.getYComponent() - y.getYComponent());
}

Vector operator-(const Vector &y)
{
	return Vector(-y.getXComponent(), -y.getYComponent());
}
//******* Multiplication ***************************************************

Vector Vector::operator*(const Vector &z)
{
	return Vector(xComponent * z.getXComponent() - yComponent * z.getYComponent(), xComponent * z.getYComponent() + yComponent * z.getXComponent());
};

Vector Vector::operator*(int z)
{
	return Vector(xComponent * ((double)z), yComponent * ((double)z));
};

Vector Vector::operator*(double z)
{
	return Vector(xComponent * z, yComponent * z);
};

void Vector::operator*=(const Vector &z)
{
	Vector x(xComponent * z.getXComponent() - yComponent * z.getYComponent(), xComponent * z.getYComponent() + yComponent * z.getXComponent());
	xComponent = x.getXComponent(); yComponent = x.getYComponent();
};

void Vector::operator*=(double z)
{
	xComponent *= z; 
	yComponent *= z;
};

void Vector::operator*=(int z)
{
	xComponent *= (double)z;
	yComponent *= (double)z;
};

Vector operator*(int x, const Vector &y)
{
	return Vector(((double)x) * y.getXComponent(), ((double)x) * y.getYComponent());
}

Vector operator*(double x, const Vector &y)
{
	return Vector(x * y.getXComponent(), x * y.getYComponent());
}

Vector operator*(const Vector &x, const Vector &y)
{
	Vector *tempVector = new Vector(x.getXComponent() * y.getXComponent() - x.getYComponent() * y.getYComponent(), x.getXComponent()* y.getYComponent() + x.getYComponent() * y.getXComponent());
	return (*tempVector);
}

//******* Division ***************************************************

Vector Vector::operator/(const Vector &z)
{
	double c;
	Vector y;

	if (fabs(z.getXComponent()) > fabs(z.getYComponent()))
	{
		c = z.getYComponent() / z.getXComponent();
		y.Set(1. / (z.getXComponent() * (1. + c * c)), (-c) * y.getXComponent());
	}
	else
	{
		c = z.getXComponent() / z.getYComponent();
		y.Set((-1.) / (z.getYComponent() * (1. + c * c)), (-c) * y.getYComponent());
	}
	Vector test1 = *this;
	
	return test1.operator *(y);
};


Vector Vector::operator/(int z)
{
	return Vector(xComponent / ((double)z), yComponent / ((double)z));
};

Vector Vector::operator/(double z)
{
	return Vector(xComponent / z, yComponent / z);
};

void  Vector::operator/=(const Vector &z)
{
	*this = this->operator/(z);
//	*this = *this / z;
};

void Vector::operator/=(double z)
{
	xComponent /= z;
	yComponent /= z;
};

void Vector::operator/=(int z)
{
	xComponent /= (double)z;
	yComponent /= (double)z;
};

Vector operator/(int x, const Vector &z)
{ 
	double c;
	Vector y;

	if (fabs(z.getXComponent()) > fabs(z.getYComponent()))
	{
		c = z.getYComponent() / z.getXComponent();
		y.Set(1. / (z.getXComponent() * (1. + c * c)), (-c) * y.getXComponent());
	}
	else
	{
		c = z.getXComponent() / z.getYComponent();
		y.Set((-1.) / (z.getYComponent() * (1. + c * c)), (-c) * y.getYComponent());
	}

	y.Set(y.getXComponent() * (double)x, y.getYComponent() * (double)x);
	return y;
}

Vector operator/(double x, const Vector &z)
{
	double c;
	Vector y;

	if (fabs(z.getXComponent()) > fabs(z.getYComponent()))
	{
		c = z.getYComponent() / z.getXComponent();
		y.Set(1. / (z.getXComponent() * (1. + c * c)), (-c) * y.getXComponent());
	}
	else
	{
		c = z.getXComponent() / z.getYComponent();
		y.Set((-1.) / (z.getYComponent() * (1. + c * c)), (-c) * y.getYComponent());
	}
	y.Set(y.getXComponent() * x, y.getYComponent() * x);
	return y;
}

Vector operator/(const Vector &x, const Vector &z)
{
	double c;
	Vector y;

	if (fabs(z.getXComponent()) > fabs(z.getYComponent()))
	{
		c = z.getYComponent() / z.getXComponent();
		y.Set(1. / (z.getXComponent() * (1. + c * c)), (-c) * y.getXComponent());
	}
	else
	{
		c = z.getXComponent() / z.getYComponent();
		y.Set((-1.) / (z.getYComponent() * (1. + c*c)), (-c) * y.getYComponent());
	}

	return x * y;
}

//****** Equals definitions ********************************

void Vector::operator=(double z)
{
	xComponent = z;
	yComponent = 0;
}

void Vector::operator=(int z)
{
	xComponent = (double)z;
	yComponent = 0;
}

//***** Tests ***********************************************
bool Vector::operator==(const Vector& z) 
{
	if ((z.getYComponent() == yComponent) && (z.getXComponent() == xComponent))
		return true;

	return false;
}

bool Vector::operator==(double z)
{
	if ((z == xComponent) && (yComponent == 0))
		return true;

	return false;
}

bool Vector::operator==(int z)
{
	if ((xComponent == (double)z) && (yComponent == 0))
		return true;

	return false;
}

bool Vector::operator!=(const Vector &z)
{
	if ((z.getXComponent() == xComponent) && (z.getYComponent() == yComponent))
		return false;

	return true;
}

bool Vector::operator!=(double z)
{
	if ((xComponent != z) || (yComponent != 0))
		return true;

	return false;
}

bool Vector::operator!=(int z) 
{
	if ((xComponent != (double)z) || (yComponent != 0)) 
		return true;

	return false;
}

//***** Useful functions ************************************
/*
Vector conj( Vector &x)
{
	return Vector(x.getXComponent(), -x.getYComponent());
}

Vector exp( Vector &x)
{
	Vector y;

	y.Set(cos(x.getYComponent()) * exp(x.getXComponent()), sin(x.getYComponent()) * exp(x.getXComponent()));
	return y;
}

Vector sqrt( Vector &x)
{
	double w, z;
	Vector y;

	if ((x.getXComponent() == 0) && (x.getYComponent() == 0))
		w = 0;

	else if (fabs(x.getXComponent()) > fabs(x.getYComponent()))
	{
		z = x.getYComponent() / x.getXComponent();
		w = sqrt(fabs(x.getXComponent())) * sqrt((1. + sqrt(1. + z * z)) / 2.);
	}
	else
	{
		z = x.getXComponent() / x.getYComponent();
		w = sqrt(fabs(x.getYComponent())) * sqrt((fabs(z) + sqrt(1. + z * z)) / 2.);
	}

	if (w == 0)
	{
		y.Set(0.0d, 0.0d);
		return y;
	}

	if (x.getXComponent() >= 0)
	{
		y.Set(w, x.getYComponent() / (2. * w))
		return y;
	}

	if (x.getYComponent() >= 0)
	{
		y.Set(fabs(x.getYComponent()) / (2. * w), w);
		return y;
	}

	y.Set(fabs(x.getYComponent()) / (2. * w), w);
	return y;
}

Vector tanh( Vector &x)
{
	Vector y;

	if (x.getXComponent() > 0)
	{
		y = (1 - exp(-2 * x)) / (1 + exp(-2 * x));
	}
	else
	{
		y = (exp(2 * x) - 1) / (exp(2 * x) + 1);
	}

	return y;
}

Vector sinh( Vector &x)
{
	return (exp(x) - exp(-x)) / 2;
}

Vector cosh( Vector &x)
{
	return (exp(x) + exp(-x)) / 2;
}


Vector cos( Vector &x)
{
	return (exp(I * x) + exp(-I * x)) / 2;
}

Vector acos( Vector& x)
{
	return PI / 2. - arg(I * x + sqrt(1 - x * x)) + I * log(abs(I * x + sqrt(1 - x * x)));
}

Vector sin( Vector &x)
{
	return (exp(I * x) - exp(-I * x)) / (2 * I);
}

Vector asin( Vector &x)
{
	return arg(I * x + sqrt(1 - x * x)) - I * log(abs(I * x + sqrt(1 - x * x)));
}

Vector tan( Vector &x)
{
	return sin(x) / cos(x);
}

Vector atan( Vector &x)
{
	return (arg(1 + I * x) - arg(1 - I * x) - I * (log(abs(1 + I * x) / abs(1 - I * x)))) / 2;
}

double abs( Vector &x)
{
	if ((x.getXComponent() == 0) && (x.getYComponent() == 0))
		return 0.;

	if (fabs(x.getXComponent()) > fabs(x.getYComponent()))
		return fabs(x.getXComponent()) * sqrt(1. + (x.getYComponent() / x.getXComponent()) * (x.getYComponent() / x.getXComponent()));
	else
		return fabs(x.getYComponent()) * sqrt(1. + (x.getXComponent() / x.getYComponent()) * (x.getXComponent() / x.getYComponent()));
}

double arg( Vector &x)
{
	if ((x.getXComponent() == 0) && (x.getYComponent() == 0))
		return 0.;

	return atan2(x.getYComponent(), x.getXComponent());
}

Vector log( Vector &x)
{
	Vector y;

	y.getYComponent() = arg(x);
	y.getXComponent() = log(abs(x));

	return y;
}

Vector pow( Vector &x, double y)
{
	return exp(y * log(x));
}

Vector pow( Vector &x, int y)
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

Vector pow( Vector &x,  Vector &y)
{
	return exp(y * log(x));
}
*/

