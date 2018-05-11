// 9.51.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;

string oops("0123456789");
class time {
public:
	time(const string &  ss);
	friend void display(time & t);

private:
	unsigned year;
	unsigned month;
	unsigned day;
};



int main()
{
    return 0;
}

