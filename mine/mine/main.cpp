#include<iostream>
#include<string>
using namespace std;

string schoolAdd(string A, string B, int base);     //School Method for Integer Addition
int makeSameLen(string& A, string& B);              //让字符串A和B一样的长度
string shift(string A, int len);                    //在字符串后面添加len个0来移位
string schoolSub(string A, string B, int base);     //School Method for Integer Subtraction
string KarastbaMul(string A, string B, int base);   //Karatsuba Algorithm for Integer Multiplication

inline bool check(string A, int base)               //用于输入检查的内联函数，即字符串内的单个字符的值不能大于等于base
{
	for (auto ch : A)
		if (ch < '0' || ch >= base + '0')
			return false;
	return true;
}

inline void deleteZero(string& A)                    //用于清除字符串的前缀0,例如：0023->23
{
	string::iterator it;
	for (it = A.begin();it != A.end() && *it == '0';it++);
	A.erase(A.begin(), it);
	if (A.empty())
		A = "0";
}

int main()
{
	int base;                                        //基
	string A, B;                                     //字符串表示的两个数字
	cin >> A >> B>>base;
	if (base < 2 || base>10)                         //输入检查      
		cout << "base must between 2 and 10!" << endl;
	else if (!check(A, base) || !check(B, base))
		cout << "wrong input" << endl;
	else
	{
		string resultAdd = schoolAdd(A, B, base);
		deleteZero(resultAdd);
		string resultMul = KarastbaMul(A, B, base);
		deleteZero(resultMul);
		cout << resultAdd << " ";
		cout << resultMul << endl;   //输出结果
	}
}

string schoolAdd(string A, string B, int base)        //School Method for Integer Addition

{
	int len1 = A.length();                            
	int len2 = B.length();

	if (len1 <= 0)                                    //容错处理
		return B;
	if (len2 <= 0)
		return A;

	int i = len1 - 1;
	int j = len2 - 1;
	string sum;                                       //用于储存和
	char x, y;
	int carryBit = 0, z;

	while (i >= 0 || j >= 0||carryBit> 0 )            //两个整数的字符串按位逆序相加，因为数字的最低位在字符串最后一位
	{
		x = i < 0 ? '0' : A[i];                       //抽出对应位给x,y
		y = j < 0 ? '0' : B[j];

		z = x - '0' + y - '0' + carryBit;             //z是这一位的和
		sum.insert(sum.begin(), z%base + '0');        //把结果插入到结果字符串的头，效果相当于是从低位向高位计算
		carryBit = z / base;                          //给进位值carryBit赋值
		i--;
		j--;
	}
	//deleteZero(sum);                                  //删除结果的前缀0
	return sum;	
}

string KarastbaMul(string A, string B, int base)      //Karatsuba Algorithm for Integer Multiplication
{
	int len = makeSameLen(A, B);                      //先让两个整数字符串有相同的长度
	if (len == 0)                                     
		return 0;
	if (len == 1)                                     //递归的基本情况是两个整数字符串均只有一位
	{
		int temp = (A[0] - '0')*(B[0] - '0');         //先获得两个数的积
		return to_string(temp / base) + to_string(temp%base);      //这里按进制base的值返回结果字符串
	}

	int mid = len / 2;                                //分位点
	string x1 = A.substr(0, mid);                     //下面对两个整数在分位点进行分割
	string x0 = A.substr(mid, len - mid);
	string y1 = B.substr(0, mid);
	string y0 = B.substr(mid, len - mid);

	string z0 = KarastbaMul(x0, y0,base);             //计算3个子问题的积
	string z1 = KarastbaMul(schoolAdd(x1, x0,base), schoolAdd(y1, y0,base),base);
	string z2 = KarastbaMul(x1, y1, base);

	string result1 = shift(z2, 2 * (len - mid));      //按公式结合3个子问题的积即得到结果
	string tmp = schoolSub(z1, z2, base);
	tmp = schoolSub(tmp, z0, base);
	string result2 = shift(tmp, len - mid);
	string resultMul= schoolAdd(schoolAdd(result1, result2, base), z0, base);

	//deleteZero(resultMul);                            //删除结果的前缀0
	return resultMul;
}

int makeSameLen(string& A, string& B)                 //AB相同长度的函数
{
	int len1 = A.length(), len2 = B.length();
	if (len1 < len2)                                  //如果字符串A比较短，就在A前面补len2-len1个0
	{
		for (int i = 0;i < len2 - len1;i++)
			A = "0" + A;
		return len2;
	}
	else                                              //与上同理
	{
		for (int i = 0;i < len1 - len2;i++)
			B = "0" + B;
		return len1;
	}
}

string schoolSub(string A, string B, int base)        //两个整数的减法
{
	string C = A;
	string D = B;
	deleteZero(C);                                    //删除前缀0
	deleteZero(D);

	if (C == D)
		return "0";

	bool positive = true;                             //结果是否为正数的标志位
	int len1 = C.length(), len2 = D.length();
	if (len1 < len2 || (len1 == len2&&C < D))         //让较大的数作为被减数
	{
		positive = false;                             //被减数较小，符号为为负
		string temp = C;                              //交换减数和被减数
		C = D;
		D = temp;
		int t = len1;
		len1 = len2;
		len2 = t;
	}

	int i = len1 - 1, j = len2 - 1;                   //下面的步骤与加法同理
	char x, y;
	int carryBit = 0,z;
	string result;

	while (i >= 0 || j >= 0)
	{
		x = i < 0 ? '0' : C[i];
		y = j < 0 ? '0' : D[j];

		z =( x - '0') - (y - '0') + carryBit;
		carryBit = 0;
		if (z < 0)                                   //检查是否需要向高位借位
		{
			z += base;
			carryBit = -1;
		}
		result.insert(result.begin(), z + '0');      
		i--;
		j--;
	}
	deleteZero(result);                              //清除前缀0

	if (positive)                                    //给符号位
		return result;
	else
		return "-" + result;
}

string shift(string A, int len)                      //移位，在A后面加len个0
{
	if (A == "0")
		return A;
	for (int i = 0;i < len;i++)
		A = A + "0";
	return A;
}





