#include<iostream>
#include<stack>
#include<string>
using namespace std;

int main() {
	int N;
	cin >> N;
	char result;
	for (int i = 0;i<N;i++) {
		stack<char> sta;
		string str;
		cin >> str;
		sta.push(str[0]);
		int index = 1;
		while (sta.size() != 1 || sta.top() == '(') {
			while (index<str.size() && sta.top() != ')') {
				sta.push(str[index]);
				index++;
			}
			string str1;
			while (sta.top() != '(') {
				str1 += sta.top();
				sta.pop();
			}
			sta.pop();
			str1 = str1.substr(1, str1.size() - 1);
			if (str1 == "0!" || str1 == "1|0" || str1 == "0|1" || str1 == "1&1" || str1 == "1|1")
				sta.push('1');
			else
				sta.push('0');
		}
		result = sta.top();
		sta.pop();
	}
	cout << result << endl;
}