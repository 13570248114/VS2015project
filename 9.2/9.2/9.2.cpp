// 9.2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<iterator>
#include<vector>
#include<string>
#include<list>
#include<deque>
#include<forward_list>
#include<array>
using namespace std;

void init()
{
	list<int> li{ 1,2,3,4,5,6 };
	vector<double> vec(li.cbegin(), li.cend());
	for (double d : vec)
		cout << d << '\t';
}

void fuzhi()
{
	list<char*> ch{ "abs","ddd" };
	vector<string> str;
	str.assign(ch.cbegin(), ch.cend());
	for (auto d : str)
		cout << d << '\t';
}

void equit()
{
	vector<int> ve1{ 1,2 };
	vector<int> ve2{ 1,3 };
	if (ve1 == ve2)
		cout << 1 << endl;
	else
		cout << 0 << endl;
}

void equit1()
{
	vector<int> ve1{ 1,2 };
	list<int> ve2{ 1,2 ,3};
	bool flag = true;
	decltype(ve1.cbegin()) i;
	decltype(ve2.cbegin()) j;
	for (i = ve1.cbegin(), j = ve2.cbegin(); i != ve1.cend() && j != ve2.cend();i++, j++)
	{
		if (*i != *j)
			flag = false;

	}
	if (i == ve1.cend() && j != ve2.cend()||i != ve1.cend() && j== ve2.cend())
		flag = false;
	cout << flag << endl;
}

void x9t18()
{
	deque<string> de;
	string temp;
	while (cin >> temp&&temp!="1")
		de.push_back(temp);
	for (auto it = de.cbegin();it != de.cend();it++)
		cout << *it << '\t';
}

void x9t19()
{
	list<string> de;
	string temp;
	while (cin >> temp&&temp != "1")
		de.push_back(temp);
	for (auto it = de.cbegin();it != de.cend();it++)
		cout << *it << '\t';
}

void x9t20()
{
	list<int> de{1,3,2,5};
	deque<int> de1, de2;
	for (auto it = de.cbegin();it != de.cend();it++)
	{
		if (*it % 2)
			de1.push_back(*it);
		else
			de2.push_back(*it);
	}
	for (auto it : de1)
		cout << it << '\t';
	for (auto it : de2)
		cout << it << '\t';
}

void x9t26()
{
	int ia[] = { 0,1,2,3,4,5,6,7,8,9 };
	vector<int> ve(begin(ia),end(ia));
	list<int> li(begin(ia), end(ia));
	auto it2 = ve.begin();
	auto it3 = li.begin();
	while (it2 != ve.end())
		if (*it2 % 2==0)
			it2 = ve.erase(it2);
		else
			++it2;
	while (it3 != li.end())
		if (*it3 % 2)
			it3 = li.erase(it3);
		else
			++it3;
	
	for (auto it : ve)
		cout << it << '\t';
	cout << endl;
	for (auto it : li)
		cout << it << '\t';

}

void x9t27()
{
	forward_list<int> flst = { 0,1,2,3,4,5,6,7,8,9 };
	auto prev = flst.before_begin();
	auto curr = flst.begin();
	while (curr != flst.end())
	{
		if (*curr % 2)
			curr = flst.erase_after(prev);
		else
		{
			prev = curr;
			curr++;
		}
	}
	for (auto it : flst)
		cout << it << '\t';
}

void x9t28()
{
	forward_list<string> str{ "aaa","bbb","ccc" };
	string str1("fff");
	string str2("eee");
	forward_list<string>::iterator it;
	decltype(it) pit = str.before_begin();
	decltype(it) it2 = str.begin();
	for(;it2!=str.end();pit=it2,it2++)
		if (*it2 == str1)
		{
			it = it2;
			break;
		}
	if (it2 == str.end()) it = pit;

	str.insert_after(it, str2);
	for (auto it : str)
		cout << it << '\t';
}

void x9t41()
{
	vector<char> c{'a','b'};
	string s(c.begin(),c.end());
	cout << s << endl;

}

void x9t45()
{
	string s("aa");
	s.insert(0, "Mrs");
	s.append("Jr");
	cout << s << endl;
}

void x9t47()
{
	string s("ab2c3d7R4E6");
	cout << s << endl;
	string snum("0123456789");
	string::size_type pos = 0;
	while ((pos = s.find_first_of(snum, pos)) != string::npos)
	{
		cout << s[pos] << " at " << pos << endl;
		++pos;
	}
	 pos = 0;
	while ((pos = s.find_first_not_of(snum, pos)) != string::npos)
	{
		cout << s[pos] << " at " << pos << endl;
		++pos;
	}
}

void x9t48()
{
	string snum("0123456789");
	string name("AnnaBelle");
	cout << snum.find(name) << endl;;
}

void x9t50()
{
	vector<string> num{ "1","2","3" };
	int sum = 0;
	for (auto nu : num)
		sum += stoi(nu);
	double sumd = 0.0;
	for (auto nu : num)
		sumd += stod(nu);
	cout << sum << '\t' << sumd << endl;
}



int main()
{
	x9t50();
    return 0;
}

