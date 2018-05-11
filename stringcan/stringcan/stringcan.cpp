// stringcan.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
using namespace std;

void changString(string &str)
{
	for (auto &c : str)
		if (c >= 'A'&&c <= 'Z')
			c += 'a' - 'A';
}
int main()
{
	string str;
	cin >> str;
	changString(str);
	cout << str << endl;
    return 0;
}

