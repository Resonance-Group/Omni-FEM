#ifndef VECTOR_H_
#define VECTOR_H_

#include "stdio.h"
#include "math.h"

#define PI 3.141592653589793238462643383
#define SmallNo 1.e-14
#define DEG 0.01745329251994329576923690768


/*! /class FEMVector
	/brief	This is the class that will handle all vector related functions
			This function was originally found in FEMM and it was decided to be used in Omni-FEM due to the extensive
			support for the vector math.
			There are many functions (and data types) that reference re (meaning real) and im (imaginery).
			Technically, this would be considered a complex number; however, a more base userage for this data type would be a vector.
			A point in imagnergy space is also a vector.
			In cartesian coordiantes, a vector consists of an x-point and a y-point.
			In the imagneray plane, a vecotr consists of a real component and an imaginery component.
			When the class is used as a vector in the cartesian plane, the re datatype is the x-component 
			and the im datatype is that y-component
*/
class FEMVector
{
	public:
		
		

		// member functions
		FEMVector();
		FEMVector(double x);
		FEMVector(int x);
		FEMVector(double x, double y);
		FEMVector Sqrt();
		FEMVector Conj();
		FEMVector Inv();
		void Set(double x, double y);
		double Abs();
		double Arg();
		double Re();
		double Im();
		char* ToString(char *s);
		char* ToStringAlt(char *s);
		
	//operator redefinition
		//Addition
		FEMVector operator+( const FEMVector& z );
		FEMVector operator+(double z);
		FEMVector operator+(int z);
		friend FEMVector operator+( int x,  const FEMVector& y );
		friend FEMVector operator+( double x,  const FEMVector& y );
		friend FEMVector operator+( const FEMVector& x,  const FEMVector& y );
		void operator+=( const FEMVector& z);
		void operator+=(double z);
		void operator+=(int z);

		//Subtraction
		FEMVector operator-();
		FEMVector operator-( const FEMVector& z );
		FEMVector operator-(double z);
		FEMVector operator-(int z);
		friend FEMVector operator-( int x,  const FEMVector& y );
		friend FEMVector operator-( double x,  const FEMVector& y );
		friend FEMVector operator-( const FEMVector& x,  const FEMVector& y );
		friend FEMVector operator-( const FEMVector& x );
		void operator-=( const FEMVector& z);
		void operator-=(double z);
		void operator-=(int z);

		//Multiplication
		FEMVector operator*( const FEMVector& z );
		FEMVector operator*(double z);
		FEMVector operator*(int z);
		friend FEMVector operator*( int x,  const FEMVector& y );
		friend FEMVector operator*( double x,  const FEMVector& y );
		friend FEMVector operator*( const FEMVector& x,  const FEMVector& y );
		void operator*=( const FEMVector& z);
		void operator*=(double z);
		void operator*=(int z);

		//Division
		FEMVector operator/( const FEMVector& z );
		FEMVector operator/(double z);
		FEMVector operator/(int z);
		friend FEMVector operator/( int x,  const FEMVector& y );
		friend FEMVector operator/( double x,  const FEMVector& y );
		friend FEMVector operator/( const FEMVector &x,  const FEMVector& y );
		void operator/=( const FEMVector& z);
		void operator/=(double z);
		void operator/=(int z);

		//Equals
		void operator=(double z);
		void operator=(int z);

		//Tests
		bool operator==( const FEMVector& z);
		bool operator==(double z);
		bool operator==(int z);
		
		bool operator!=( const FEMVector& z);
		bool operator!=(double z);
		bool operator!=(int z);

		bool operator<( const FEMVector& z);
		bool operator<( double z);
		bool operator<( int z);

		bool operator<=( const FEMVector& z);
		bool operator<=( double z);
		bool operator<=( int z);

		bool operator>( const FEMVector& z);
		bool operator>( double z);
		bool operator>( int z);

		bool operator>=( const FEMVector& z);
		bool operator>=( double z);
		bool operator>=( int z);


private:

		double re;
		
		//! This is the imagnery component of the complex vector. When used 
		double im;

};

// useful functions...
#define I FEMVector(0,1)
double Re( const FEMVector& a);
double Im( const FEMVector& a);
double abs( const FEMVector& x );
double absq( const FEMVector& x );
double arg( const FEMVector& x );
FEMVector conj( const FEMVector& x);
FEMVector exp( const FEMVector& x );
FEMVector sqrt( const FEMVector& x );
FEMVector tanh( const FEMVector& x );
FEMVector sinh( const FEMVector& x );
FEMVector cosh( const FEMVector& x );
FEMVector cos( const FEMVector& x );
FEMVector acos( const FEMVector& x );
FEMVector sin( const FEMVector& x );
FEMVector asin( const FEMVector& x );
FEMVector tan( const FEMVector& x );
FEMVector atan( const FEMVector& x );
FEMVector atan2( const FEMVector& y, const FEMVector &x);
FEMVector log( const FEMVector& x );
FEMVector pow( const FEMVector& x, int y);
FEMVector pow( const FEMVector& x, double y);
FEMVector pow( const FEMVector& x,  const FEMVector &y);
FEMVector Chop( const FEMVector& a, double tol = 1.e-12);




#endif // FEMVector check