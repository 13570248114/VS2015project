// FENGEFU.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
using namespace std;


int main()
{
	string str,result;
	char fen;
	cin >> str >> fen;
	result.clear();
	auto it = str.begin();
	bool first;
	for (; it!=str.end(); )
	{
		if (*it != fen) {
			result += *it;
			it++;
		}
		else if (*it == fen)
		{
			while (*it == fen)it++;
			result += '\n';
			cout << result;
			result.clear();
		}
	}
	if (it == str.end()) {
		result += '\n';
		cout << result << endl;
	}
    return 0;
}

