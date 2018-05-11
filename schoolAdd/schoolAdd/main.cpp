#include<iostream>
#include<string>
using namespace std;

string schoolAdd(string A, string B, int base);
int makeSameLen(string& A, string& B);
string shift(string A, int len);
string schoolSub(string A, string B, int base);
string KarastbaMul(string A, string B, int base);

inline bool check(string A, int base)
{
	for (auto ch : A)
		if (ch < '0' || ch >= base + '0')
			return false;
	return true;
}

inline void deleteZero(string& A)
{
	string::iterator it;
	for (it = A.begin();it != A.end() && *it == '0';it++);
	A.erase(A.begin(), it);
}

int main()
{
	int base;
	string A, B;
	cin >> A >> B>>base;
	if (base < 2 || base>10)
		cout << "base must between 2 and 10!" <<endl;
	else if (!check(A, base) || !check(B, base))
		cout << "wrong input" << endl;
	else	
		cout << schoolAdd(A, B, base) <<" "<<KarastbaMul(A, B, base)<<endl;
		//cout << schoolSub(A, B, base) << endl;
		//cout << KarastbaMul(A, B, base) << endl;
}

string schoolAdd(string A, string B, int base)
{
	int len1 = A.length();
	int len2 = B.length();

	if (len1 <= 0)
		return B;
	if (len2 <= 0)
		return A;

	int i = len1 - 1;
	int j = len2 - 1;
	string sum;
	char x, y;
	int carryBit = 0, z;

	while (i >= 0 || j >= 0||carryBit> 0 )
	{
		x = i < 0 ? '0' : A[i];
		y = j < 0 ? '0' : B[j];

		z = x - '0' + y - '0' + carryBit;
		sum.insert(sum.begin(), z%base + '0');
		carryBit = z / base;
		i--;
		j--;
	}
	deleteZero(sum);
	return sum;	
}

string KarastbaMul(string A, string B, int base)
{
	int len = makeSameLen(A, B);
	if (len == 0)
		return 0;
	if (len == 1)
	{
		int temp = (A[0] - '0')*(B[0] - '0');
		return to_string(temp / base) + to_string(temp%base);
	}

	int mid = len / 2;
	string x1 = A.substr(0, mid);
	string x0 = A.substr(mid, len - mid);
	string y1 = B.substr(0, mid);
	string y0 = B.substr(mid, len - mid);

	string z0 = KarastbaMul(x0, y0,base);
	string z1 = KarastbaMul(schoolAdd(x1, x0,base), schoolAdd(y1, y0,base),base);
	string z2 = KarastbaMul(x1, y1, base);

	string result1 = shift(z2, 2 * (len - mid));
	string tmp = schoolSub(z1, z2, base);
	tmp = schoolSub(tmp, z0, base);
	string result2 = shift(tmp, len - mid);
	string resultMul= schoolAdd(schoolAdd(result1, result2, base), z0, base);
	deleteZero(resultMul);
	return resultMul;
}

int makeSameLen(string& A, string& B)
{
	int len1 = A.length(), len2 = B.length();
	if (len1 < len2)
	{
		for (int i = 0;i < len2 - len1;i++)
			A = "0" + A;
		return len2;
	}
	else
	{
		for (int i = 0;i < len1 - len2;i++)
			B = "0" + B;
		return len1;
	}
}

string schoolSub(string A, string B, int base)
{
	string C = A;
	string D = B;
	deleteZero(C);
	deleteZero(D);
	if (C == D)
		return "0";

	bool positive = true;
	int len1 = C.length(), len2 = D.length();
	if (len1 < len2 || (len1 == len2&&C < D))
	{
		positive = false;
		string temp = C;
		C = D;
		D = temp;
		int t = len1;
		len1 = len2;
		len2 = t;
	}

	int i = len1 - 1, j = len2 - 1;
	char x, y;
	int carryBit = 0,z;
	string result;

	while (i >= 0 || j >= 0)
	{
		x = i < 0 ? '0' : C[i];
		y = j < 0 ? '0' : D[j];

		z =( x - '0') - (y - '0') + carryBit;
		carryBit = 0;
		if (z < 0)
		{
			z += base;
			carryBit = -1;
		}
		result.insert(result.begin(), z + '0');
		i--;
		j--;
	}
	deleteZero(result);
	if (positive)
		return result;
	else
		return "-" + result;
}

string shift(string A, int len)
{
	if (A == "0")
		return A;
	for (int i = 0;i < len;i++)
		A = A + "0";
	return A;
}





