// C++chaper3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<string>
#include<iterator>
using namespace std;

int main()
{
	int a[5] = { 1,2,3,4,5 };
	vector<int> vet(begin(a), end(a));
	for (auto v : vet)
		cout << v<<'\t';
	cout << endl;
	char c[5] = { 'a','a', 'a', 'a', '\0' };
	string str(c);
	cout << str << endl;
    return 0;
}

