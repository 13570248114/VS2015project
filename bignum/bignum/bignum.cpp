#include<iostream>
#include<string>
using namespace std;

void printNum(const string& num) {
	int len = num.size();
	if (len <= 1)
		throw "error";
	int cur = 1;
	while (cur < len&&num[cur] == '0')
		cur++;
	if (cur == len)
		cout << "0";
	else {
		while (cur < len)
			cout << num[cur];
	}
	cout << endl;
}


string add(const string& num1, const string& num2) {
	int len1 = num1.size();
	int len2 = num2.size();
	int reslen = len1 > len2 ? len1 + 1: len2 + 1;
	string res(reslen,'0');
	int index = reslen - 1;
	int i = len1 - 1, j = len2 - 1;
	for (;i >= 0 && j >= 0;i--, j--) {
		res[index] = num1[i] - '0' + num2[j]-'0';
		index--;
	}
	for(;	i>=0	;i--)
		res[index--] = num1[i] - '0';
	for (; j >= 0;j--)
		res[index--] = num2[j] - '0';
	for (index = reslen - 1;index > 0;index--) {
		res[index - 1] = res[index - 1] + res[index] / 10;
		res[index] = res[index] % 10 + '0';
	}
	if(res[0]=='0')
		res = res.substr(1, reslen - 1);
	return res;
}

inline int chang(int last, int cur) {
	return last-cur;
}

string mul(const string& num1, const string& num2) {
	string::size_type len1 = num1.size();
	string::size_type len2 = num2.size();
	string res(len1 + len2, 0);
	for(int i=len1-1;i>=0;i--)
		for (int j = len2-1;j >=0;j--) {
			res[i+j+1] += (num1[i] - '0')*(num2[j] - '0');
			if (res[i+j+1]) {
				res[i+j] = res[i+j] + res[i+j+1] / 10;
				res[i+j+1] = res[i+j+1]%10;
			}
		}
	for (int i = 0;i < len1 + len2;i++)
		res[i] += '0';
	int index = 0;
	while (index < len1 + len2&&res[index] == '0')
		index++;
	if (index == len1 + len2)
		return "0";
	res = res.substr(index, len1 + len2 - index);
	return res;
}

string fac(int num) {
	string res("1");
	for (int i = 2;i <= num;i++)
		res = mul(res, to_string(i));
	return res;
}

string sub(const string& num1, const string& num2) {
	bool neg = num1 < num2 ? true : false;
	string max, min;
	if (neg) {
		max = num2;
		min = num1;
	}
	else {
		max = num1;
		min = num2;
	}
	int len1 = max.size();
	int len2 = min.size();
	string res(len1, '0');
	int index = len1 - 1;
	for (int i = len1 - 1, j = len2 - 1;i >= 0 && j >= 0;i--, j--) {
		if (max[i] >= min[j]) {
			res[index] = max[i] - min[j];
		}
		else {
			res[index] = max[i] - min[j] + 10;
			res[index - 1]--;
		}
		res[index] += '0';
		index--;
	}
	for (index = 0;index < len1&&res[index] == '0';)
		index++;
	if (index == len1)
		return "0";
	res = res.substr(index, len1 - index);
	res = neg ? "-" + res : res;
	return res;
}

bool check(const string& num) {
	if (num.size() == 0|| (num.size() == 1 && num[0] == '-'))
		throw "error input";
	if(num[0]!='-'&&(num[0]<'0'||num[0]>'9'))
		throw "error input";
	for (int i = 1;i < num.size();i++) {
		if(num[i]<'0'||num[i]>'9')
			throw "error input";
	}
	return true;
}

string Add(const string& num1, const string& num2) {
	try {
		check(num1);
		check(num2);
	}
	catch (const char* msg) {
		cout << msg << endl;
		return msg;
	}
	if (num1[0] != '-'&&num2[0] != '-') {
		return add(num1, num2);
	}
	else if (num1[0] == '-'&&num2[0] != '-') {
		return sub(num2, num1);
	}
	else if (num1[0] != '-'&&num2[0] == '-') {
		return sub(num1, num2);
	}
	else
		return "-"+ add(num1, num2);
}

int main() {
	string num1, num2;
	cin >> num1 >> num2;
	int len1 = num1.size();
	int len2 = num2.size();
	if (num1[0] == '-'&&num2[0] == '-')
		cout << mul(num1.substr(1, len1 - 1), num2.substr(1, len2 - 1)) << endl;
	else if (num1[0] != '-'&&num2[0] != '-')
		cout << mul(num1, num2) << endl;
	else if (num1[0] == '-'&&num2[0] != '-') {
		cout << "-"<<mul(num1.substr(1, len1 - 1),num2) << endl;
	}
	else if (num1[0] != '-'&&num2[0] == '-') {
		cout <<"-"<<mul(num1, num2.substr(1, len2 - 1)) << endl;
	}
}