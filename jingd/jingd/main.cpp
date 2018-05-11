
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;


bool huiwen(string& a) {
	int size = a.size();
	int left = 0;
	int right = size - 1;
	while (left < right) {
		if (a[left] == a[right])
		{
			left++;
			right--;
		}
		else
			return false;
	}
	return true;
}

string rec(string a) {
	int size = a.size();
	int left = 0;
	int right = size - 1;
	char temp;
	while (left < right) {
		temp = a[left];
		a[left] = a[right];
		a[right] = temp;
		left++;
		right--;
	}
	return a;
}


inline int max(int a, int b) {
	return a>b ? a : b;
}


int LCS(string str1, string str2) {
	int size = str1.size();
	int cMax = 0;
	vector<vector<int> > DP(size + 1, vector<int>(size + 1, 0));
	for (int i = 0; i <= size; i++)
	{
		DP[i][0] = 0;
		DP[0][i] = 0;
	}
	for (int i = 1; i <= size; i++)
		for (int j = 1; j <= size; j++) {
			if (str1[i - 1] == str2[j - 1])
				DP[i][j] = DP[i - 1][j - 1] + 1;
			else
				DP[i][j] = max(DP[i][j - 1], DP[i - 1][j]);
			if (DP[i][j] > cMax)
				cMax = DP[i][j];
		}
	return cMax;
}

int count(int size) {
	int half = size / 2;
	return  pow(2, half);
}

int main() {
	string a,res;
	cin >> a;
	int size = a.size();
	if (huiwen(a))
		cout << size+count(size) << endl;
	else {
		string b = rec(a);
		int nsize = LCS(a, b);
		cout << size+count(nsize) << endl;
	}
	return 0;
}