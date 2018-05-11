#include<iostream>
#include<vector>
using namespace std;

class Parenthesis {
public:
	int countLegalWays(int n) {
		// write code here
		return comb(2 * n, n) / (n + 1);
	}
private:
	long fac(int n) {
		int res = 1;
		for (int i = 1; i <= n; i++)
			res *= i;
		return res;
	}

	long comb(int n, int m) {
		int a = fac(n);
		int b = fac(m);
		int c = fac(n - m);
		a = a / b;
		a = a / c;
		return a;
	}
};

class Championship {
public:
	vector<int> calc(int k) {
		// write code here
		int sum = 1;
		for (int i = 1;i <= 2 * k - 1;i = i + 2) {
			sum *= i;
		}
		int cnm = 1;
		for (int i = k + 1;i>2;i--)
			cnm *= i;
		int fenzi = sum - cnm;
		if (fenzi != 0) {
			int gcd = maxGcd(fenzi, sum);
			fenzi /= gcd;
			sum /= gcd;
		}
		vector<int> res;
		res.push_back(fenzi);
		res.push_back(sum);
		return res;
	}
private:
	int maxGcd(int x, int y) {
		if (y%x == 0)
			return x;
		else
			return maxGcd(y%x, x);
	}
};

int main() {
	Championship c;
	cout<<c.calc(2)[0]<<" "<< c.calc(2)[1]<<endl;
	
}