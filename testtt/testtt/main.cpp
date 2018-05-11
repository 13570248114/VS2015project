#include<iostream>
using namespace std;

class Date {
public:
	Date() {};
	Date(int year, int month, int day);
	void print();
private:
	int _year;
	int _month;
	int _day;
};

Date::Date(int year, int month, int day):_year(year)
{
	_month = month < 1 || month>12 ? 1 : month;
	_day = day < 1 || day>31 ? 1 : day;

	if (month == 2)
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		{
			_day = _day > 28 ? 1 : _day;
		}
		else
			_day = _day > 29 ? 1 : _day;
	}
}

void Date::print()
{
	cout << _year << "-" << _month << "-" << _day << endl;
}

int main()
{
	Date d1(2017, 1, 8);
	d1.print();
	Date d2(2017, 13, 32);
	d2.print();
}