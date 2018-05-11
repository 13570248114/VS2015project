// doubleTsst.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
double tt() {
	double t = -87.11;
	if (t < 0)
		t = 0;
	return t;
}
int main()
{
	double t = tt();
	cout << t;
    return 0;
}


