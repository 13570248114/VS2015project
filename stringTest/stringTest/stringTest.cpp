// stringTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;



void toUpper()
{
	string str;
	cin >> str;
	for (char &c : str)
	{
		c ='x';
		c = toupper(c);
	}
	cout << str<<endl;
}

void qubiaodian()
{
	string str;
	cin >> str;
	string result(str.length(),'\0');
	string::size_type i = 0;
	for (auto c : str)
		if (!ispunct(c))
			result[i++] = c;
	cout << result<<endl;
}

void vector_push_back()
{
	vector<int> int_vector;
	int num;
	cout << "Input the number,let '.' be the end input" << endl;
	while (cin>>num)
	{
		int_vector.push_back(num);
	}
	for (auto num : int_vector)
		cout << num << "\t";
	cout << endl;
}

int main()
{
	//toUpper();
	//qubiaodian();
	vector_push_back();
    return 0;
}

