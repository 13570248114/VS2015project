// 33.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

bool suhu(int num)
{
	for (int i = 2;i <= num ;i++)
		if (num%i == 0)
			return 0;
	return 1;
}

int count(int num, vector<int> v)
{
	int count = 0;
	int temp = num;
	for (auto i:v)
	{
		if (temp%i == 0)
		{
			temp = temp / i;
			count++;
		}	
	}
	return count;
}

int main()
{
	vector<int> v;
	int n = 5;
	
	for (int i = 2;i <= n;i++)
		if (suhu(i))
			v.push_back(i);


	int countt = pow(2, v.size());
	for (int i = 2;i <= n;i++)
		if (!suhu(i))
			countt += pow(2, v.size() - count(i,v));
	cout << countt << endl;

    return 0;

}

