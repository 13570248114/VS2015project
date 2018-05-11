// input.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>

int main()
{
	std::string num;
	std::cin >> num;
	bool isdouble=false;
	int i = 0;
	while (num[i] == ' '&&i<num.length())
		++i;
	num = num.substr(i, num.length() - i);
	if (num[0] == '.')
		return -1;
	i = 0;
	while (num[i] != ' '&&i<num.length())
		++i;
	num = num.substr(0, i);
	for (auto number : num) {
		if (number != '.' && !isdigit(number))
			return -1;
		if (number = '.')
			isdouble = true;
	}
	if (isdouble)
		std::cout << std::stod(num);
	else
		std::cout << std::stoi(num);
    return 0;
}

