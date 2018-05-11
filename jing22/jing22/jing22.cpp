// jing22.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<vector>;
#include<stack>
#include<iostream>
#include<algorithm>
using namespace std;

bool addSum(vector<int> & v, int dest_sum)
{
	typedef int Value;
	typedef int Loc;
	sort(v.begin(), v.end());
	stack<pair<Value, Loc>> sta;
	int loc = 0;
	int init_loc = 0;
	int sum = v[loc];
	sta.push({ v[loc],loc });
	++loc;

	while (sum != dest_sum&&loc<=v.size())
	{
		if (loc < v.size() && sum + v[loc] <= dest_sum)
		{
			sum += v[loc];
			sta.push({ v[loc], loc });
			++loc;
		}
		else
		{
			if (!sta.empty())
			{
				auto v = sta.top();
				sum -= v.first;
				sta.pop();
				loc = v.second + 1;
			}
			else
			{
				sum = 0;
				loc = ++init_loc;
			}
		}
	}
	if (sum == dest_sum&&loc <= v.size())
		return true;
	else
		return false;

}

int sum(vector<int>  v) 
{
	int sum=0;
	for (auto u : v)
		sum += u;
	return sum;
}

vector<int> fenjie(int num)
{
	vector<int> i;
	i.push_back(num % 10);
	while (num / 10) {
		num = num / 10;
		i.push_back(num % 10);
	}
	return i;
}


int main()
{
	long l, r,count=0;
	cin >> l >> r;
	vector<int> i;
	for (int x = l;x <= r;x++)
	{
		i = fenjie(x);
		if (sum(i) % 2)
			continue;
		if (addSum(i, sum(i) / 2))
			count++;

	}
	cout << count;
		

    return 0;
}

