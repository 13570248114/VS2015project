// 111.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;


int main()
{
	int n;
	cin >> n;
	int s8, s6,yu;
	int i = 0;
	do {
		s8 = n  / 8 - i;
		yu = n % 8 + 8 * i;
		s6 = yu / 6;
		yu = yu % 6;
		i++;
	} while (yu != 0 && s8 >= 0);
	if (yu == 0)
		cout << s6 + s8 << endl;
	else
		cout << -1 << endl;
    return 0;
}

