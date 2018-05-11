#include<iostream>
using namespace std;

class Fraction{
public:
	Fraction() {}
	Fraction(int numerator, int denominator) :_numerator(numerator), _denominator(denominator) {}
	friend ostream& operator<<(ostream& os, const Fraction& f);
	friend  Fraction operator+(Fraction& f1, Fraction& f2);
	friend  Fraction operator-(Fraction& f1, Fraction& f2);
	friend  Fraction operator*(Fraction& f1, Fraction& f2);
	int ged();
private:
	int _numerator;
	int _denominator;
};

/*
int Fraction::ged()
{
	for (int i = (_numerator<_denominator ? _numerator : _denominator); i >= 2; i--)
	{
		if (_numerator%i == 0 && _numerator%i == 0)
			return i;
	}
	return 0;
}
*/

ostream& operator<<(ostream& os, const Fraction& f)
{
	os << f._numerator << "/" << f._denominator;
	return os;
}

Fraction operator+(Fraction& f1, Fraction& f2)
{
	int numerator = f1._numerator*f2._denominator + f2._numerator*f1._denominator;
	int denominator = f1._denominator*f2._denominator;
	Fraction f3(numerator, denominator);
	return f3;
}

Fraction operator-(Fraction& f1, Fraction& f2)
{
	int numerator = f1._numerator*f2._denominator - f2._numerator*f1._denominator;
	int denominator = f1._denominator*f2._denominator;
	Fraction f3(numerator, denominator);
	return f3;
}

Fraction operator*(Fraction& f1, Fraction& f2)
{
	int numerator = f1._numerator* f2._numerator;
	int denominator = f1._denominator * f2._denominator;
	Fraction f3(numerator, denominator);
	return f3;
}

int main()
{
	Fraction f1(3, 5), f2(2, 7);
	cout << "f1=" << f1 << " " << "f2=" << f2 << endl;
	cout << "f1+f2=" << f1 + f2 << endl;
	cout << "f1-f2=" << f1 - f2 << endl;
	cout << "f1xf2=" << f1 * f2 << endl;
}