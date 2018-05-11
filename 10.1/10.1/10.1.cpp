// 10.1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<algorithm>
#include<numeric>
#include<vector>
#include<list>
#include<iterator>
#include<string>
#include<functional>
using namespace std;
using namespace placeholders;

void x10t1()
{
	vector<int> num{ 1,2,3,2,2 };
	cout << count(num.cbegin(), num.cend(), 2)<<endl;
}

void x10t3()
{
	vector<int> num{ 1,2,3,2,2 };
	int sum=accumulate(num.cbegin(),num.cend(),0);
	cout << sum << endl;;
}

void x10t4()
{
	vector<double> num{ 1.1,2,3,2,2 };
	auto sum = accumulate(num.cbegin(), num.cend(), 0);
	cout << sum << endl;;
}

void test_fill()
{
	vector<int> num{ 1,2,3,2,2 };
	fill(num.begin(), num.begin()+num.size()/2, 0);
	for (auto u : num)
		cout << u << '\t';
	cout << endl;
}

void test_backinsert()
{
	vector<int> vec;
	auto it = back_inserter(vec);
	fill_n(it, 10, 0);
	for (auto u : vec)
		cout << u << '\t';
	cout << endl;
	int a1[] = { 0,1,2,3 };
	int a2[sizeof(a1) / sizeof(*a1)];
	auto ret = copy(begin(a1), end(a1), a2);
	for (auto it = begin(a2);it != end(a2); it++)
		cout << *it << '\t';
	cout << endl;
	replace(begin(a2), end(a2), 0, 3);
	for (auto it = begin(a2);it != end(a2); it++)
		cout << *it << '\t';
	cout << endl;
}

void test_unique()
{
	vector<string> words{ "sa","sb","sc","sb" };
	sort(words.begin(), words.end());
	auto endl_flag = unique(words.begin(), words.end());
	words.erase(endl_flag, words.end());
	for (auto u : words)
		cout << u << '\t';
	cout << endl;
}

bool isShorter(const string&s1, const string &s2)
{
	return s1.size() < s2.size();
}

void test_stable_sort()
{
	vector<string> words{ "saw","sbe","scr","sb" };
	sort(words.begin(), words.end());
	auto endl_flag = unique(words.begin(), words.end());
	words.erase(endl_flag, words.end());
	stable_sort(words.begin(), words.end(), isShorter);
	for (auto u : words)
		cout << u << '\t';
	cout << endl;
}

bool longThan5(string s)
{
	return s.size() >= 5;
}

void x10t13()
{
	vector<string> words{ "sawee","sbe","screrr","sb" };
	auto it = partition(words.begin(), words.end(), longThan5);
	for (auto ite = words.begin();ite != it;ite++)
		cout << *ite << '\t';
	cout << endl;
	for (auto u : words)
		cout << u << '\t';
	cout << endl;
}

void x10t15()
{
	int num = 5;
	vector<int> re{ 5,2 };
	for_each(re.begin(),re.end(),[num](int num2) {cout<<(num + num2)<<'\t';});
}

void biggies( vector<string>::size_type sz)
{
	vector<string> words{ "saw","sbe","scr","sb" };
	sort(words.begin(), words.end());
	auto endl_flag = unique(words.begin(), words.end());
	words.erase(endl_flag, words.end());
	
	stable_sort(words.begin(), words.end(), [](const string& a, const string& b) {return a.size() < b.size();});
	auto wc = find_if(words.begin(), words.end(), [sz](const string& a) {return a.size() > sz;});
	auto count = words.end() - wc;
	
	for_each(wc, words.end(), [](const string &s) {cout << s << '\t';});
	cout << endl;
}

void x10t20()
{
	vector<string> words{ "sawewrwr","sbeewrwer","scr","sb" };
	auto num = count_if(words.begin(), words.end(), [](string s) {return s.size() >= 6;});
	cout << num << endl;
}

void x10t21()
{
	int num = 5;
	auto f = [&num]()->bool {if (num > 0) { num--;return false; } else return true;};
	while (!f());
	cout << num << endl;;
}

bool longer(string s, string::size_type sz)
{
	return s.size() <= sz;
}

void x10t22()
{
	vector<string> words{ "sawewrwr","sbeewrwer","scr","sb" };
	auto num = count_if(words.begin(), words.end(),bind(longer,_1,6));
	cout << num << endl;
}

void x10t24()
{
	vector<int> longn{ 1,2,3,4 };
	string a("aa");
	auto it = find_if(longn.begin(), longn.end(), bind(longer, a, _1));
	cout << *it << endl;
}

void x10t27()
{
	vector<int> longn{ 1,3,2,4, 3,4 };
	list<int> longu;
	unique_copy(longn.cbegin(), longn.cend(),inserter(longu,longu.begin()));
	for_each(longu.cbegin(), longu.cend(), [](int num) {cout << num << '\t';});
}

void x10t34()
{
	vector<int> i{ 1,2,3 };
	for_each(i.crbegin(), i.crend(), [](int num) {cout << num << '\t';});
	cout << endl;
}

void x10t36()
{
	list<int> i{ 1,2,0,3 };
	auto it = find(i.crbegin(), i.crend(), 0);
	cout << *it<<endl;
}

void x10t37()
{
	vector<int> i{ 1,2,0,3,5,6,7,8,9,4};
	list<int> li;
	copy(i.rbegin() +2, i.rbegin() + 6, inserter(li, li.begin()));
	for_each(li.crbegin(), li.crend(), [](int num) {cout << num << '\t';});
	cout << endl;
}

int main()
{
	x10t37();
    return 0;
}

