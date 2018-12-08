/*
 * Author: Mohammed Hossain
 * file: complex.cpp
 * This is the implementation of our complex number
 * class whose interface resides in the file complex.h
 */

#include "complex.h"

#include <cmath> // for the square root function needed for norm()

complex::complex(double re, double im)
{
	//initialize the real and imaginary parts:
	real = re;
	imag = im;
}

complex::complex(const complex& z)
{
	//we need to make *this a copy of z:
	real = z.real;
	imag = z.imag;
}

/* OVERLOADING THE ORIGINAL C++ OPERATORS */
ostream& operator<<(ostream& o, const complex& z)
{
	o << "(" << z.real;
	if(z.imag>=0)
		o << " + " << z.imag;
	else
		o << " - " << -z.imag;
	o << "i)";
	return o;
}

istream& operator>>(istream& i, complex& z)
{
	return (i>> z.real >> z.imag);
}

/* returns the conjugate of a complex number */
complex complex::conj()
{
	complex temp; // this will be our return value
	temp.real = real;
	temp.imag = -imag;
	return temp;
}

/* basic constructor with no parameters, equal to 0 */
complex::complex()
{
	real = 0;
	imag = 0;
}

/* magnitude of a complex number */
double complex::norm()
{
	return sqrt(real*real + imag*imag);
}

/* MORE OVERLOADING OF C++ OPERATORS */
complex operator+(const complex& w, const complex& z)
{
	complex retVal;
	retVal.real = w.real + z.real;
	retVal.imag = w.imag + z.imag;
	return retVal;
}

complex operator-(const complex& w)
{
	complex retVal;
	retVal.real = -w.real;
	retVal.imag = -w.imag;
	return retVal;
}

complex operator-(const complex& w, const complex& z)
{
	return (w+(-z));
}

complex operator*(const complex& w, const complex& z)
{
	// TODO: write this function.
	complex retVal;
	retVal.real = (w.real * z.real) - (w.imag * z.imag);
	retVal.imag = (w.real * z.imag) + (w.imag * z.real);
	return retVal;
}

complex operator/(complex& w, complex& z)
{
	// TODO: write this function.
	complex retVal;
	// z is the denominator, so we need the conjugate of z
	complex zConj = z.conj();

	retVal = w * zConj;
	double demoninator = (z * zConj).real; // imaginary part cancels out
	retVal.real /= demoninator;
	retVal.imag /= demoninator;

	return retVal;
}

complex operator^(const complex& w, int a)
{
	// there are much more efficient ways to do exponentiation,
	// but this one is at least easy to understand.
	complex retVal(1,0); //initialize it to 1
	for(int i=0; i<a; i++)
		retVal = retVal*w;
	return retVal;
}
