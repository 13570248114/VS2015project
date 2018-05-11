#include<iostream>
#include<string>
using namespace std;

string schoolAdd(const string A, const string B,int base);

int main()
{
	string A, B;
	cin >> A >> B;
	cout << schoolAdd(A, B, 10)<<endl;
}

string schoolAdd(const string A, const string B,int base)
{
	int len1 = A.length();
	int len2 = B.length();
	int len = len1 > len2 ? len1 : len2;
	int i = len1 - 1;
	int j = len2 - 1;
	int k = 0;
	string temp(len + 2, '0');
	char x, y, z;
	int carryBit = 0;

	while (i >= 0 || j >= 0)
	{
		x = i < 0 ? '0' : A[i] ;
		y = j < 0 ? '0' : B[j];

		z = x - '0' + y - '0' + carryBit;
		temp[k] = z % base + '0';
		carryBit = z / 10;
		k++;

		i--;
		j--;
	}

	while (carryBit)
	{
		temp[k] = carryBit % base + '0';
		carryBit / base;
		k++;
	}

	string result(k, '0');
	for (--k, i = 0;k >= 0;k--, i++)
	{
		result[i] = temp[k];
	}
	result[i] = '\0';
	return result;
}



