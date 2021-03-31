#include <iostream>

#include <cmath>

using namespace std;

class Rational {
private:

	int numerator;//����

	int denominator;//��ĸ

	int gcd(int i1, int i2);//�����Լ��

	int lcf(int i1, int i2) const;//��С������

	void standardize(void);//��׼������

public:
	Rational(void) {
		numerator = 1;
		denominator = 1;
	}
	Rational(const Rational& rational);
	Rational(int numerator, int denominator);

	float getValue() const;
	int getNumerator() const;
	void setNumerator(int numerator);
	int getDenominator() const;
	void setDenominator(int denominator);

	friend ostream& operator<<(ostream& out, Rational& rat);

	friend istream& operator>>(istream& in, Rational& rat);

	friend Rational operator+(const Rational& rat1, const Rational& rat2);
	friend Rational operator+(const Rational& rat1, double fraction);

	friend Rational operator-(const Rational& rat1, const Rational& rat2);

	friend Rational operator-(const Rational& rat);

	friend Rational operator*(const Rational& rat1, const Rational& rat2);
	friend Rational operator*(const Rational& rat1, double fraction);

	friend Rational operator/(const Rational& rat1, const Rational& rat2);

	int operator[](int in);

	operator float() { 
		return this->getValue(); 
	}

	friend ostream &operator<<(ostream &out, const Rational &rat) {
		if (rat.getDenominator() == 1) {
			out << rat.getNumerator();
		}
		else {
			out << rat.getNumerator() << "/" << rat.getDenominator();
		}
		
		return out;
	}

	double floating() { return this->getValue(); }

	Rational(float xiaoshu);
	void reduce();

	void print() {
		cout << "***" << getNumerator() << "/" << getDenominator() << endl;
	}
};