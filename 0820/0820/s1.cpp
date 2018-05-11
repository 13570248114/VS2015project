#include<iostream>
#include<string>
using namespace std;

string add(const string& a, const string& b) {
	int len1 = a.size();
	int len2 = b.size();
	int maxlen = len1>len2 ? len1 : len2;
	string res(maxlen + 1, 0);
	int index = maxlen;
	int i = len1 - 1, j = len2 - 1;
	for (;i >= 0 && j >= 0;i--, j--) {
		res[index] = a[i] - '0' + b[j] - '0';
		index--;
	}
	while (i >= 0)
		res[index--] = a[i--] - '0';
	while (j >= 0)
		res[index--] = b[j--] - '0';
	res[maxlen] = res[maxlen] + '0';
	for (index = maxlen - 1;index >= 0;index--) {
		res[index] +=( res[index + 1] - '0')/ 10;
		res[index] = res[index] % 10+'0';
	}
	res[maxlen] = (res[maxlen] - '0')% 10+'0';
	return res[0] == '0' ? res.substr(1, maxlen) : res;
}

string sub(const string& a, const string& b) {
	bool neg = false;
	string max = a;
	string min = b;
	if (a.size()<b.size()||(a.size()==b.size()&&a<b)) {
		max = b;
		min = a;
		neg = true;
	}
	int maxlen = max.size();
	int minlen = min.size();
	string res(maxlen, 0);
	int index = maxlen - 1;
	int i = maxlen - 1, j = minlen - 1;
	for (;i >= 0 && j >= 0;i--, j--) {
		res[index] += max[i] - min[j];
		if (index>0&&res[index]<0) {
			res[index] += 10;
			res[index - 1]--;
		}
		index--;
	}
	while (i >= 0) {
		res[index] += max[i--] - '0';
		if (index>0 && res[index]<0) {
			res[index] += 10;
			res[index - 1]--;
		}
		index--;
	}
	index = 0;
	while (index<maxlen&&res[index] == 0)
		index++;
	if (index == maxlen)
		return "0";
	else {
		res = res.substr(index, maxlen - index);
		for (int k = 0; k < res.size();k++)
			res[k] += '0';
		return neg ? ("-" + res) : res;
	}
}

bool check(const string& num, bool& neg) {
	if (num.size() == 0) {
		return false;neg = false;
	}
	if (num[0] == '-'&&num.size() >= 2)
		neg = true;
	else if (num[0] <= '9'&&num[0] >= '0')
		neg = false;
	else
		return false;
	for (int i = 1;i<num.size();i++)
		if (num[i]>'9' || num[i]<'0')
			return false;
	return true;
}

int main() {
	string a, b;
	cin >> a >> b;
	bool a_neg, b_neg, atrue, btrue;
	atrue = check(a, a_neg);
	btrue = check(b, b_neg);
	if (!atrue && !btrue) {
		throw "error input!";
	}
	if (!a_neg && !b_neg)
		cout << add(a, b) << endl;
	else if (!a_neg&&b_neg)
		cout << sub(a, b.substr(1, b.size() - 1)) << endl;
	else if (a_neg && !b_neg)
		cout << sub(b, a.substr(1, a.size() - 1)) << endl;
	else {
		string res = add(a.substr(1, a.size() - 1), b.substr(1, b.size() - 1));
		if (res != "0")
			res = "-" + res;
		cout << res << endl;
	}
}