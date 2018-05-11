#include<iostream>
#include<string>
using namespace std;

class KMP
{
public:
	int operator()(const string S, const string T);
private:
	int* getNext(string T);
};

int* KMP::getNext(const string T)
{
	int size = T.size();
	int * next = new int[size];
	next[0] = -1;
	int i = 0;
	int j = -1;
	while (i < size -1)
	{
		if (j == -1 || T[i] == T[j])
		{
			j++;
			i++;
			if (T[i] != T[j])
				next[i] = j;
			else
				next[i] = next[j];
		}
		else
			j = next[j];
	}
	return next;
}

int KMP::operator()(const string S, const string T)
{
	int * next = getNext(T);
	int i = 0;
	int j = 0;
	int size = T.size();
	while (i < S.size() && j < size)
	{
		if (j == -1 || S[i] == T[j])
		{
			i++;
			j++;
		}
		else
			j = next[j];
	}
	if (j == size)
		return i - size;
	else
		return -1;
}

bool chkTransform(string A, int lena, string B, int lenb) {
	// write code here
	if (A == "" || B == "" || lena != lenb)
		return false;
	else
	{
		int map[256];
		for (int i = 0;i < 256;i++)
		{
			map[i] = 0;
		}
		for (int i = 0;i < lena;i++)
			map[A[i]]++;
		for (int i = 0;i < lenb;i++)
			if (map[B[i]--] == 0)
				return false;
		return true;
	}
}

bool chkRotation(string A, int lena, string B, int lenb) {
	// write code here
	if (lena != lenb)
		return false;
	else
	{
		string temp = A + A;
		return kmp(temp, B) != -1;
	}
}

int* next(const string& B)
{
	int size = B.size();
	int* next = new int[size];
	next[0] = -1;
	int i = 0, j = -1;
	while (i < size - 1)
	{
		if (j == -1 || B[i] == B[j])
		{
			i++;j++;
			if (B[i] != B[j]) {
				next[i] = j;
			}
			else
				next[i] = next[j];
		}
		else
			j = next[j];
	}
	return next;
}

int kmp(const string& A, const string& B)
{
	int Bsize = B.size(), i = 0, j = 0;
	int *jnext = next(B);
	while (i < A.size() && j < Bsize)
	{
		if (j == -1 || A[i] == B[j])
		{
			i++;j++;
		}
		else
			j = jnext[j];
	}
	delete[] jnext;
	if (j == Bsize)
		return i - Bsize;
	else
		return -1;
}

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
	change(words);
	int start = 0;
	while (words[start] == ' ')
		start++;
	int end = start;
	int len = words.length();
	while (start < len)
	{
		for (end = start; end<len&&words[end] !=' '; end++);
		change(words, start, end - 1);
		for (start = end;start < len&&words[start] != ' ';start++);
	}
}
int main()
{
	KMP kmp;
	cout << kmp("abcabxabdabx", "abxabd") << endl;
}