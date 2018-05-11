#include<iostream>
#include<vector>
#include<string>
using namespace std;

/*
void ex(int num) {
	if (num < 0)
		throw "error!";
}

int main() {
	int num;
	try {
		cin >> num;
		ex(num);
		cout << num << endl;
	}
	catch (const char* msg) {
		cout << msg << endl;
	}
}
*/

/*
void sort(vector<int>& ages) {
	if (ages.size() == 0)
		return;
	int maxage = 99;
	vector<int> tong(maxage + 1,0);
	for (auto a : ages) {
		if (a<0 || a>maxage)
			throw "age out of age";
		tong[a]++;
	}
	int index = 0;
	for (int i = 0; i <= maxage;i++) {
		while (tong[i]-- > 0)
			ages[index++] = i;
	}
}

int main()
{
	vector<int> a{ 5,-4,3,2,1 };
	try {
		sort(a);
		for (auto i : a)
			cout << i << endl;
	}
	catch (const char* msg) {
		cout << msg << endl;
	}
}

*/

/*
bool invalid = false;

double abspower(double base, unsigned int absExponent) {
	if (absExponent == 0)
		return 1;
	if (absExponent == 1)
		return base;
	double res = abspower(base, absExponent >> 1);
	res *= res;
	if (absExponent & 1)
		res *= base;
	return res;
}
double power(double base, int exponent) {
	invalid = false;
	if (base > -0.0000001&&base < 0.0000001&&exponent < 0) {
		invalid = true;
		return 0.0;
	}
	unsigned int absExponent = exponent < 0 ? (unsigned int)-exponent : (unsigned int)exponent;
	double res = abspower(base, absExponent);
	return exponent < 0 ? 1 / res : res;
}

int main() {
	cout << power(0, -3) << endl;
	cout << invalid << endl;
}
*/

void print(const string& num) {
	if (num.size() == 0)
		return;
	int beginIndex = 0;
	while (beginIndex < num.size() && num[beginIndex] == '0')
		beginIndex++;
	if (beginIndex == num.size())
		cout << "0";
	else {
		while (beginIndex < num.size())
			cout << num[beginIndex++];
	}
	cout << "\n";
}

void printRec(string& num, int len, int index) {
	if (index == len - 1) {
		print(num);
		return;
	}
	for (int i = 0;i < 10;i++) {
		num[index + 1] = i+'0';
		printRec(num, len, index + 1);
	}
}

void printN(int n) {
	if (n <= 0)
		return;
	string num(n, 0);
	for (int i = 0;i < 10;i++) {
		num[0] = i+'0';
		printRec(num, n, 0);
	}
}

int main() {
	printN(5);
}
