#include <iostream>

#ifndef _Complex_H_
#define _Complex_H_

using namespace std;

class Complex
{
public:
	Complex(double real, double imag);
	~Complex();

	//
	Complex operator+(const Complex& com);
	Complex operator+(double real);
	Complex operator-(const Complex& com);
	Complex operator*(const Complex& com);
	Complex operator/(const Complex& com);
	Complex operator~();
	bool operator==(const Complex& com);

	friend ostream &operator<<(ostream &out, const Complex &com) {
		if (com.imag > 0) {
			out << "" << com.real << "+" << com.imag << "i";
		}
		else {
			out << "" << com.real << "" << com.imag << "i";
		}
		return out;
	}
	friend istream &operator>>(istream &in, Complex &com) {

	}

	//
	double abs();
	double operator[](int in);

	// additional functions
	double getReal();		// return the number of rows
	double getImag();		// return the number of columns


private:
	double real, imag;
	// add more private variables and functions if you need
};


#endif
