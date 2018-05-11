// 7.1.2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Persion
{
private:
	string name;
	string address;
public:
	Persion() = default;
	Persion(const string& name1, const string& address1) :name(name1), address(address1) {};
	string getName() const { return name; }
	string getAddress() const { return address; }
};

ostream &print(ostream&, const Persion&);
istream &read(istream&, Persion&);

istream &read(istream& is, Persion& p)
{
	is >> p.getName() >> p.getAddress();
	return is;
}

ostream &print(ostream& os, const Persion& p)
{
	os << p.getName() << '\t' << p.getAddress();
	return os;
}


class Sales_data
{
	friend Sales_data add(const Sales_data&, const Sales_data&);
	friend ostream &print(ostream&, const Sales_data&);
	friend istream &read(istream&, Sales_data&);

public:
	Sales_data() = default;
	Sales_data(const string& s) :bookNo(s) {};
	Sales_data(const string& s, unsigned n, double p) :bookNo(s), unit_sold(n), revenue(p*n) {};
	Sales_data(istream& = cin);
	string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);

private:
	string bookNo;
	unsigned unit_sold = 0;
	double revenue = 0.0;
	double avg_price() const;
};



Sales_data::Sales_data(istream& is)
{
	read(is, *this);
}

double Sales_data :: avg_price() const
{
	if (unit_sold)
		return revenue / unit_sold;
	else
		return 0;
}

Sales_data& Sales_data::combine(const Sales_data& rhs)
{
	unit_sold += rhs.unit_sold;
	revenue += rhs.revenue;
	return *this;
}

istream &read(istream &is, Sales_data &item)
{
	double price = 0;
	is >> item.bookNo >> item.unit_sold >> price;
	item.revenue = price*item.unit_sold;
	return is;
}

ostream &print(ostream& os, const Sales_data& item)
{
	os << item.isbn() << '\t' << item.unit_sold << '\t' << item.revenue << '\t' << item.avg_price();
	return os;
}

Sales_data add(const Sales_data& lhs, const Sales_data& rhs)
{
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}

class Screen
{
	friend class Window_mgr;
public:
	typedef string::size_type pos;
	Screen() = default;
	Screen(pos ht, pos wd, char c) :height(ht), width(wd), contents(ht*wd, c) {};
	char get() const { return contents[cursor]; }
	inline char get(pos r, pos c) const;
	Screen& move(pos r, pos c);
	void some_member() const;
	Screen& set(char);
	Screen &set(pos, pos, char);
	Screen& display(ostream& os) { do_display(os);return *this; }
	const Screen &display(ostream &os) const { do_display(os);return *this; }

private:
	mutable rsize_t access_ctr;
	pos cursor = 0;
	pos height = 0, width = 0;
	string contents;
	void do_display(ostream &os) const { os << contents; }
};

void Screen::some_member() const
{
	++access_ctr;
}

inline Screen& Screen::move(pos r, pos c)
{
	pos row = r*width;
	cursor = row + c;
	return *this;
}

char Screen::get(pos r, pos c) const
{
	pos row = r*width;
	return contents[row + c];
}

inline Screen& Screen::set(char c)
{
	contents[cursor] = c;
	return *this;
}

inline Screen& Screen::set(pos r, pos col,char c)
{
	contents[r*width+col] = c;
	return *this;
}

class Window_mgr
{
public:
	Window_mgr();
	~Window_mgr();
	using ScreenIndex = vector<Screen>::size_type;
	void clear(ScreenIndex);
private:
	vector<Screen> screens{ Screen(24,80,' ') };
};

Window_mgr::Window_mgr()
{
}

Window_mgr::~Window_mgr()
{
}

void Window_mgr::clear(ScreenIndex i)
{
	Screen &s = screens[i];
	s.contents = string(s.height*s.width, ' ');
}

class noDefault
{
public:
	noDefault(int i) :no(i) {};
	int get() { return no; }
private:
	int no;
};

class C
{
public:
	C(int i) :no(i) {};
	int get() { return no.get(); }
private:
	noDefault no;
};

int main()
{
	vector<noDefault> ver(10);
    return 0;
}

