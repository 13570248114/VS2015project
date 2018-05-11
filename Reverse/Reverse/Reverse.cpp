#include<iostream>
#include<string>
using namespace std;

class Reverse {
public:
	string reverseSentence(string A, int n) {
		// write code here
		rotate(A);
		return A;
	}

private:
	void change(string& str, int start, int end)
	{
		while (start < end)
		{
			char ch = str[start];
			str[start] = str[end];
			str[end] = ch;
			start++;
			end--;
		}
	}

	void rotate(string& words)
	{
		int len = words.length();
		change(words, 0, len - 1);
		int start = 0;
		while (words[start] == ' ')
			start++;
		int end = start;
		while (start < len)
		{
			for (end = start ; end<len&&words[end] != ' '; end++);
			change(words, start, end - 1);
			for (start = end ; start < len&&words[start] == ' ';start++);
		}
	}
};

class Translation {
public:
	string stringTranslation(string A, int n, int len) {
		// write code here
		roate(A, 0, len - 1);
		roate(A, len, n - 1);
		roate(A, 0, n - 1);
		return A;
	}
private:
	void roate(string& str, int start, int end) {
		while (start < end)
		{
			str[start] = str[start] + str[end];
			str[end] = str[start] - str[end];
			str[start] = str[start] - str[end];
			start++;
			end--;
		}
	}
};

int main()
{
	string w = string("dog loves pig");
	Reverse r;
	r.reverseSentence(w, w.length());
}