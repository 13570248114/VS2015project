// strB.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<string>
#include<initializer_list>
#include<memory>
using namespace std;

class strBlod {
public:
	typedef vector<string>::size_type size_type;
	strBlod();
	strBlod(initializer_list<string> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(string &t) { data->push_back(t); }
	void pop_back();

	string& front();
	string& back();

	void print();

private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const;
};

strBlod::strBlod() :data(make_shared<vector<string>> ()) {}
strBlod::strBlod(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}

void strBlod::check(size_type i, const string &msg) const
{
	if (i >= data->size())
		throw out_of_range(msg);
}

string& strBlod::front()
{
	check(0, "front of the empty");
	return data->front();
}

string& strBlod::back()
{
	check(0, "back of the empty");
	return data->back();
}

void strBlod::pop_back()
{
	check(0, "pop_back of the empty");
	data->pop_back();
}

void strBlod::print()
{
	for (auto i : (*data))
		cout << i << '\t';
}
int main()
{
	strBlod b1;
	{
		strBlod b2 = { "a","an","the" };
		b1 = b2;
		b2.push_back(string("about"));
		b2.print();
	}
	b1.print();
}
