#include<iostream>
#include<string>
#include<stack>
#include<vector>
using namespace std;

class Replacement {
public:
	string replaceSpace(string iniString, int length)
	{
		int spaceNum = 0;
		for (int i = 0;i < length;i++)
			if (iniString[i] == ' ')
				++spaceNum;
		int newLength = length + 2 * spaceNum;
		for (int i = length;i < newLength;i++)        //扩大string,用字符'a'占位
			iniString += 'a';
		for (int i = newLength - 1 , j = length - 1 ; j >= 0 && i >= 0; j--)
		{
			if (iniString[j] != ' ')
				iniString[i--] = iniString[j];
			else
			{
				iniString[i--] = '0';
				iniString[i--] = '2';
				iniString[i--] = '%';
			}
		}
		return iniString;
	}
};

class Parenthesis {
public:
	bool chkParenthesis(string A, int n) {
		int check = 0;
		for (auto ch : A)
		{
			if (ch != '('&&ch != ')')
				return false;
			else
			{
				if (ch == '(')
					check++;
				else if (check-- < 0)
					return false;
			}
		}
		return check == 0;
	}
};

class DistinctSubstring {
public:
	int longestSubstring(string A, int n)
	{
		int map[256];
		for (int i = 0;i < 256;i++)
			map[i] = -1;
		int maxLength = -1;
		int curLength = 0;
		int prePos = -1;
		for (int i = 0; i < n ; i++)
		{
			prePos = prePos > map[A[i]] ? prePos : map[A[i]];
			curLength = i - prePos;
			maxLength = maxLength > curLength ? maxLength : curLength;
			map[A[i]] = i;
		}
		return maxLength;
	}
};

class Sotion {
public:
	void push(int num)
	{
		data.push(num);
		if (mindata.empty() || mindata.top() > num)
			mindata.push(num);
	}

	void pop()
	{
		if (data.top() == mindata.top())
			mindata.pop();
		data.pop();
	}

	int top()
	{
		return data.top();
	}

	int min()
	{
		return mindata.top();
	}
private:
	stack<int> data, mindata;
};

class queue {
public:
	vector<int> twoStack(vector<int> ope, int n) {
		// write code here
		vector<int> result;
		for (auto num : ope)
		{
			if (num > 0)
				push(num);
			else
				result.push_back(pop());
		}
		return result;
	}
	void push(int num)
	{
		stackPush.push(num);
	}

	int pop()
	{
		if (stackPop.empty())
		{
			while (!stackPush.empty())
			{
				stackPop.push(stackPush.top());
				stackPush.pop();
			}
		}
		int result = stackPop.top();
		stackPop.pop();
		return result;
	}

private:
	stack<int> stackPush, stackPop;
};


int main()
{
	string s = string("Mr John Smith");
	Replacement r;
	//cout << r.replaceSpace(s, 13) << endl;
	//string ss("()a()()");
	//Parenthesis p;
	//cout << p.chkParenthesis(ss, 7) << endl;
	//DistinctSubstring d;
	//cout << d.longestSubstring("aabcb", 5) << endl;
}
