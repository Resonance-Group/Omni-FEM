#ifndef Vector_H_
#define Vector_H_

#include "stdio.h"
#include "math.h"

#define PI 3.141592653589793238462643383
#define SmallNo 1.e-14
#define DEG 0.01745329251994329576923690768


#define I Vector(0,1)

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
		Vector(double x, double y);
		
		//! This function is used to find the square root of a number.
		/*!
			Note that the base class does not have this function defined.
			The definition will be in the child classes
		*/
		virtual Vector sqrt();
		virtual Vector Inv();
		void Set(double x, double y);
		virtual double Abs();
		double Arg();
		double getXComponent();
		double getYComponent();
		char* ToString(char *s);
		char* ToStringAlt(char *s);
		
	//operator redefinition
		//Addition
		Vector operator+( const Vector& z );
		Vector operator+(double z);
		Vector operator+(int z);
		friend Vector operator+( int x,  const Vector& y );
		friend Vector operator+( double x,  const Vector& y );
		friend Vector operator+( const Vector& x,  const Vector& y );
		void operator+=( const Vector& z);
		void operator+=(double z);
		void operator+=(int z);

		//Subtraction
		Vector operator-();
		Vector operator-( const Vector& z );
		Vector operator-(double z);
		Vector operator-(int z);
		friend Vector operator-( int x,  const Vector& y );
		friend Vector operator-( double x,  const Vector& y );
		friend Vector operator-( const Vector& x,  const Vector& y );
		friend Vector operator-( const Vector& x );
		void operator-=( const Vector& z);
		void operator-=(double z);
		void operator-=(int z);

		//Multiplication
		Vector operator*( const Vector& z );
		Vector operator*(double z);
		Vector operator*(int z);
		friend Vector operator*( int x,  const Vector& y );
		friend Vector operator*( double x,  const Vector& y );
		friend Vector operator*( const Vector& x,  const Vector& y );
		void operator*=( const Vector& z);
		void operator*=(double z);
		void operator*=(int z);

		//Division
		Vector operator/( const Vector& z );
		Vector operator/(double z);
		Vector operator/(int z);
		friend Vector operator/( int x,  const Vector& y );
		friend Vector operator/( double x,  const Vector& y );
		friend Vector operator/( const Vector &x,  const Vector& y );
		void operator/=( const Vector& z);
		void operator/=(double z);
		void operator/=(int z);

		//Equals
		void operator=(double z);
		void operator=(int z);

		//Tests
		bool operator==( const Vector& z);
		bool operator==(double z);
		bool operator==(int z);
		
		bool operator!=( const Vector& z);
		bool operator!=(double z);
		bool operator!=(int z);

		bool operator<( const Vector& z);
		bool operator<( double z);
		bool operator<( int z);

		bool operator<=( const Vector& z);
		bool operator<=( double z);
		bool operator<=( int z);

		bool operator>( const Vector& z);
		bool operator>( double z);
		bool operator>( int z);

		bool operator>=( const Vector& z);
		bool operator>=( double z);
		bool operator>=( int z);


private:

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
	//! The constructor
	ComplexNumber(double realComponent, double imaginaryComponent);
	
	//! This function will calculate and return the conjugate of the Complex number
	ComplexNumber getConjugate();
	
	//! This function will return the real component of the complex number
	double getRealComponent();
	
	//! This function will return the imaginary component of the complex number
	double getImaginaryComponent();
	
	//! This function will calculate the square root of the complex number and return it
	Vector sqrt();
	
	//! This function will compute and return the inverse of the complex number
	ComplexNumber getInverse();
	
	//! This function is called in order to set the real and imaginary components of the complex number
	void setComplexNumber(double realComponent, double imaginaryComponent);
	
	
	
private:
	
};


// useful functions...

double Re( const Vector& a);
double Im( const Vector& a);
double abs( const Vector& x );
double absq( const Vector& x );
double arg( const Vector& x );
Vector conj( const Vector& x);
Vector exp( const Vector& x );
Vector sqrt( const Vector& x );
Vector tanh( const Vector& x );
Vector sinh( const Vector& x );
Vector cosh( const Vector& x );
Vector cos( const Vector& x );
Vector acos( const Vector& x );
Vector sin( const Vector& x );
Vector asin( const Vector& x );
Vector tan( const Vector& x );
Vector atan( const Vector& x );
Vector atan2( const Vector& y, const Vector &x);
Vector log( const Vector& x );
Vector pow( const Vector& x, int y);
Vector pow( const Vector& x, double y);
Vector pow( const Vector& x,  const Vector &y);
Vector Chop( const Vector& a, double tol = 1.e-12);




#endif // Vector check