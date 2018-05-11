// ouchuang.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
using namespace std;

bool ouchuang(string str)
{
	string son1, son2;
	if (str.length() % 2)
		return 0;
	else
	{
		son1 = str.substr(0, str.length()/2 );
		son2 = str.substr(str.length() / 2, str.length() / 2);
		if (son1 == son2)
			return 1;
		else
			return 0;
	}
}
int main()
{
	string str = "abaababaab";
	string temp;
	int len = str.length()-2;
	temp = str.substr(0, len );
	while (!ouchuang(temp))
	{
		len--;
		if (len < 0)
			break;
		temp = str.substr(0, len );
	}
	if (len < 0)
		cout << str.length() << endl;
	else
		cout << len  << endl;
    return 0;
}

