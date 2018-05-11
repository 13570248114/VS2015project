// 8.1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
using namespace std;

istream& read(istream& s)
{
	int out;
	while (!s.eof())
	{
		s >> out;
		cout << out<<'\t';
	}
	s.clear();
	return s;
}

void read(string path)
{
	ifstream infile(path), infile2(path);
	vector<string> text1,text2;
	string line;
	while (getline(infile, line))
		text1.push_back(line);

	char c;
	string s;
	while (!infile2.eof())
	{
		infile2 >> c;
		if (c != ' ')
			s += c;
		else
		{
			text2.push_back(s);
			s = '\0';
		}
	}

	for (auto s : text1)
		cout << s << endl;
	for (auto s : text2)
		cout << s << '\t';
}

void filr_mode(string path)
{
	ofstream out;
	out.open(path,ofstream::app);
	out << "\ntest";
	out.close();
}

void filr_read(string path)
{
	vector<string> str;
	string line;
	ifstream in(path);
	while (getline(in, line))
		str.push_back(line);
	vector<string> words;
	for (auto s : str)
	{
		string word;
		istringstream is(s);
		while (is >> word)
			words.push_back(word);
	}
    
	for (auto s : str)
		cout << s << endl;
	for (auto s : words)
		cout << s << '\t';
}

void useOs()
{
	ostringstream out;
	out << " " << "test";
	cout << out.str() << endl;
}

int main()
{
	//string path;
	//cin >> path;
	useOs();
    return 0;
}

