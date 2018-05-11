// 6.32.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
using namespace std;

int &get(int* arry, int index) { return arry[index]; }
void x6t32()
{
	int ia[10];
	for (int i = 0;i != 10;i++)
		get(ia, i) = i;
	for (auto k : ia)
		cout << k << '\t';
	cout << endl;
}

void x6t33(const vector<int> ver, int index)
{
	if (index == 0)
		cout<< ver[index]<<'\t';
	else
	{
		x6t33(ver, index-1);
		cout << ver[index] << '\t';
	}
	
}

int F1(int a, int b)
{
	return a + b;
}

int F2(int a, int b)
{
	return a - b;
}

int F3(int a, int b)
{
	return a * b;
}

int F4(int a, int b)
{
	return a / b;
}

void x6t7()
{
	using F = int(*)(int, int);
	vector<F> ver;
	ver.push_back(F1);
	ver.push_back(F2);
	ver.push_back(F3);
	ver.push_back(F4);

	int a = 4, b = 2;
	for (auto Fun : ver)
		cout << Fun(a, b) << "\t";
	cout << endl;
}
int main()
{
	//x6t32();
	//vector<int> ver = { 1,2,3,4,5,6 };
	//x6t33(ver, ver.size()-1);
	//cout << endl;
	x6t7();
    return 0;
}

