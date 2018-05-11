// exception.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
using namespace std;

int main()
{
	int num1, num2;
	while (cin >> num1 >> num2)
	{
		try {
			if (num2 == 0)
				throw runtime_error("num2 can't be zero\n");
			cout << num1 / num2 << endl;
		}
		catch (runtime_error err)
		{
			cout << err.what() << "Try again?Entry y or n" << endl;
			char c;
			cin >> c;
			if (!cin || c == 'n')
				break;
		}
		
	}
    return 0;
}

