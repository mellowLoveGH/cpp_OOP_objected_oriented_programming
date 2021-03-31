#include <iostream>
#include <cstdlib>
#include <math.h>
#include "Complex.h"

using namespace std;

Complex::Complex(double r = 0, double i = 0) {
	real = r;
	imag = i;
}

Complex::~Complex() {

}

Complex Complex::operator*(const Complex& com) {

	return Complex(getReal()*com.real - getImag()*com.imag, getReal()*com.imag + getImag()*com.real);
}

Complex Complex::operator/(const Complex& com) {
	double r = getReal()*com.real + getImag()*com.imag;
	double i = getImag()*com.real - getReal()*com.imag;
	double sq = com.real*com.real + com.imag*com.imag;
	return Complex(r/sq, i/sq);
}

Complex Complex::operator+(const Complex& com) {

	return Complex(getReal() + com.real, getImag() + com.imag);
}

Complex Complex::operator+(double real) {
	return Complex(getReal() + real, getImag());
}

Complex Complex::operator-(const Complex& com) {

	return Complex(getReal() - com.real, getImag() - com.imag);
}

bool Complex::operator==(const Complex& com) {
	
	return (getReal() == com.real && getImag() == com.imag);
}

Complex Complex::operator~() {
	return Complex(getReal(), -getImag());
}

double Complex::abs() {
	return sqrt(getReal()*getReal() + getImag()*getImag());
}

double Complex::operator[](int in) {
	if (in == 0) {
		return getReal();
	}
	return getImag();
}

double Complex::getReal() {
	return real;
}

double Complex::getImag() {
	return imag;
}