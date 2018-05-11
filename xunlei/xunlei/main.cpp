#include<iostream>
#include<string>
#include<vector>
using namespace std;

bool combine(string s1, string s2,string& s3)
{
	string s1s, s1e, s2s, s2e;
	for (auto c : s1) {
		if (c != ',')
			s1e += c;
		else {
			s1s = s1e;
			s1e.clear();
		}
	}
	for (auto c : s2) {
		if (c != ',')
			s2e += c;
		else {
			s2s = s2e;
			s2e.clear();
		}
	}
	int a1, a2, b1, b2;
	a1 = stoi(s1s);
	a2 = stoi(s1e);
	b1 = stoi(s2s);
	b2 = stoi(s2e);
	if ( a1>b2 ||a2 <b1 )
		return false;
	else
	{
		if (a1 > b1&&a2 < b2)
		{
			s3 = s2;
			return true;
		}
		else if (b1 > a1&&b2 < a2) {
			s3 = s1;
			return false;
		}
		else if (a1<b1&&a2>b1) {
			s3 = s1s + "," + s2e;
			return true;
		}
		else if (b1<a1&&b2>a1) {
			s3 = s2s + "," + s1e;
			return true;
		}
	}
}

int main() {
	string str,temp;
	vector<string> vec,result;
	getline(cin, str);
	for (auto c : str) {
		if (c != ' ')
			temp += c;
		else {
			vec.push_back(temp);
			temp.clear();
		}
	}
	vec.push_back(temp);

	string str1 = vec.back(),str2;
	vec.pop_back();
	bool flag = false;
	while (!vec.empty()) {
		for (auto it = vec.begin(); it != vec.end();) {
			string temp=*it;
			if (combine(temp, str1, str2)) {
				str1 = str2;
				flag = true;
				it = vec.erase(it);
				if (vec.empty())
					result.push_back(str1);
				break;
			}
			else
				it++;
		}
		if (!flag) {
			result.push_back(str1);
			str1 = vec.back();
			vec.pop_back();
		}
	}
	for (auto str : result)
		cout << str << " ";
}

