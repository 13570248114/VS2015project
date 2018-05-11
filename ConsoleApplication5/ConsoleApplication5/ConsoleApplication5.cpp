// ConsoleApplication5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<map>
#include<vector>
using namespace std;

int main()
{
	int num=0;
	map<char, int> m;
	string str = "abcb";
	for (char c : str)
		++m[c];
	for (auto n : m)
		if (n.second % 2)
			num++;
	cout << num << endl;
    return 0;
}

