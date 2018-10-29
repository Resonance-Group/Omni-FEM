#ifndef Vector_H_
#define Vector_H_

#include "stdio.h"
#include "math.h"

const double PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;
#define SmallNo 1.e-14
#define DEG 0.01745329251994329576923690768

#define JI Vector(0,1)

/*! /class Vector
	/brief	This is the class that will handle all Vector related functions
			This function was originally found in FEMM and it was decided to be used in Omni-FEM due to the extensive
			support for the Vector math.
			There are many functions (and data types) that reference re (meaning real) and im (imaginery).
			Technically, this would be considered a complex number; however, a more base userage for this data type would be a Vector.
			A point in imagnergy space is also a Vector.
			In cartesian coordiantes, a Vector consists of an x-point and a y-point.
			In the imagneray plane, a vecotr consists of a real component and an imaginery component.
			When the class is used as a Vector in the cartesian plane, the re datatype is the x-component 
			and the im datatype is that y-component
*/
class Vector
{
	public:
		// member functions
		explicit Vector(double x, double y);
		explicit Vector();
		
		//! This function is used to find the square root of a number.
		/*!
			Note that the base class does not have this function defined.
			The definition will be in the child classes
		*/
		virtual Vector Sqrt();
		virtual Vector Inv();
		void Set(double x, double y);
		virtual double Abs();
		double Arg();
		double getXComponent() const;
		double getYComponent() const;
		char* ToString(char *s);
		char* ToStringAlt(char *s);
		
	//operator redefinition
		//Addition
		Vector operator+(const Vector &z);
		Vector operator+(double z);
		Vector operator+(int z);
		friend Vector operator+(int x, const Vector &y);
		friend Vector operator+(double x, const Vector &y);
		friend Vector operator+(const Vector &x, const Vector &y);
		void operator+=(const Vector &z);
		void operator+=(double z);
		void operator+=(int z);

		//Subtraction
		Vector operator-();
		Vector operator-(const Vector &z);
		Vector operator-(double z);
		Vector operator-(int z);
		friend Vector operator-(int x, const Vector &y);
		friend Vector operator-(double x, const Vector &y);
		friend Vector operator-(const Vector &x, const Vector &y);
		friend Vector operator-(const Vector &x );
		void operator-=(const Vector& z);
		void operator-=(double z);
		void operator-=(int z);

		//MultiplicationVector Vsin(const Vector &x) 
		Vector operator*(const Vector &z);
		Vector operator*(double z);
		Vector operator*(int z);
		friend Vector operator*(int x, const Vector &y);
		friend Vector operator*(double x, const Vector &y);
		friend Vector operator*(const Vector &x, const Vector &y);
		void operator*=(const Vector &z);
		void operator*=(double z);
		void operator*=(int z);

		//Division
		Vector operator/(const Vector &z);
		Vector operator/(double z);
		Vector operator/(int z);
		friend Vector operator/(int x, const Vector &y);
		friend Vector operator/(double x, const Vector &y);
		friend Vector operator/(const Vector &x, const Vector &y);
		void operator/=(const Vector &z);
		void operator/=(double z);
		void operator/=(int z);

		//Equals
		void operator=(double z);
		void operator=(int z);

		//Tests
		bool operator==(const Vector &z);
		bool operator==(double z);
		bool operator==(int z);
		
		bool operator!=(const Vector &z);
		bool operator!=(double z);
		bool operator!=(int z);

		bool operator<(const Vector &z);
		bool operator<(double z);
		bool operator<(int z);

		bool operator<=(const Vector &z);
		bool operator<=(double z);
		bool operator<=(int z);

		bool operator>(const Vector &z);
		bool operator>(double z);
		bool operator>(int z);

		bool operator>=(const Vector &z);
		bool operator>=(double z);
		bool operator>=(int z);


protected:

		//! For the Vector, this is the x coordinate.
		/*!
			Depending on the child class (RealVector/ComplexNumber) the x and y will have different meanings
			However, the meaning of the x does not change
		*/
		double xComponent;
		
		//! For the Vector, this is the y coordinate.
		/*!
			Depending on the child class (RealVector/ComplexNumber) the x and y will have different meanings
			For the y component, this will change to be the imagary number.
		*/
		double yComponent;

};

//Vector JI = Vector(0, 1);


/*! /class ComplexNumber
	/brief	This class is designed to handle all complex numbers. 
			The class inherits from the Vector class since complex numbers are (in theory) a small extension of Vectors.
			However, there are some complex number specific functions inside of this class. 
			There are also some functions which seem unnecessary as they do the same thing as their counter-parts in the Vector class.
			This is such for the sake of sanity. 
			For example, in the Vector class, there is a function for getting the xComponent and the yComponent. In the ComplexNumber class,
			there are functions for getting the real and imaginary components. Technically, these two will both return the same variable.
			In a Complex Number, the xComponent is the real component and the yComponent is the imaginary.
			However, it does not make much sense to call a function to get the yComponent for a complex number since technically the yComponent is the 
			imagery number. Therefor, another function is created call getIMaginaryComponent for the sake of ease of understanding (again, getYComponent and getImaginaryComponent
			return the same datatype but the naming of one makes more sense then the other)
*/

class ComplexNumber : public Vector
{
public:
	//! The ructor
	ComplexNumber(double realComponent, double imaginaryComponent);
	ComplexNumber();
	
	//! This function will calculate and return the conjugate of the Complex number
	ComplexNumber getConjugate();
	
	//! This function will return the real component of the complex number
	double getRealComponent();
	
	//! This function will return the imaginary component of the complex number
	double getImaginaryComponent();
	
	//! This function will calculate the square root of the complex number and return it
	Vector Sqrt();
	
	//! This function will compute and return the inverse of the complex number
	ComplexNumber getInverse();
	
	//! This function is called in order to set the real and imaginary components of the complex number
	void setComplexNumber(double realComponent, double imaginaryComponent);
	
	double Abs();
	
private:
	
};

/*! Defining the imagnary number */
//Vector *J = new Vector(0.0, 1.0);

/* This functions are defined specifically for vector math. They are labeled with a V for vector so that the compiler or developer does not get this confused with the math.h functions */
double Varg(const Vector &x);
double Vabs(const Vector &x);
Vector Vexp(const Vector &x);

Vector Vsqrt(Vector &x);
Vector Vsin(const Vector &z);


//TODO: These functions need to be integrated into the base class
// useful functions...
/*
double abs(  Vector& x );
double absq(  Vector& x );
double arg(  Vector& x );
Vector conj(  Vector& x);
Vector sqrt(  Vector& x );
Vector tanh(  Vector& x );
Vector sinh(  Vector& x );
Vector cosh(  Vector& x );
Vector cos(  Vector& x );
Vector acos(  Vector& x );
Vector sin(  Vector& x );
Vector asin(  Vector& x );
Vector tan(  Vector& x );
Vector atan(  Vector& x );
Vector atan2(  Vector& y,  Vector &x);
Vector log(  Vector& x );
Vector pow(  Vector& x, int y);
Vector pow(  Vector& x, double y);
Vector pow(  Vector& x,   Vector &y);
Vector Chop(  Vector& a, double tol = 1.e-12);
*/



#endif // Vector check