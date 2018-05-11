#include<iostream>
#include<string>
#include<vector>
#include<time.h>
#include<cstdlib>
#include<algorithm>
using namespace std;

class Prior {
public:
	string findSmallest(vector<string>& strs, int n) {
		// write code here
		//quickSort(strs);
		sort(strs.begin(), strs.end(), cmp);
		string result;
		for (auto str : strs)
		{
			result += str;
		}
		return result;
	}
private:

	static bool cmp(string& str1, string& str2)  //必须是static,cmp的地址要先知道
	{
		return str1 + str2 < str2 + str1;
	}

	void quickSort(vector<string>& strs)
	{
		srand((unsigned)time(NULL));
		quickSort(strs, 0, strs.size() - 1);
	}

	void quickSort(vector<string>& strs,int start,int end)
	{
		if (end > start)
		{
			int randomPos = rand() % (end - start+1) + start;
			swap(strs, randomPos, end);
			int pos = partion(strs, start, end);
			quickSort(strs, start, pos - 1);
			quickSort(strs, pos + 1, end);
		}
	}

	int partion(vector<string>& strs, int start, int end)
	{
		int pos = start -1;
		int index = start;
		int right = end;
		while (index <= right)
		{
			if (strs[index] + strs[right] <= strs[right] + strs[index])
			{
				pos++;
				swap(strs, index, pos);
			}
			index++;
		}
		return pos;
	}

	void swap(vector<string>& strs, int i, int j)
	{
		string temp = strs[i];
		strs[i] = strs[j];
		strs[j] = temp;
	}

};

int main()
{
	vector<string> tr = { "b","ba","abc" };
	Prior p;
	p.findSmallest(tr, tr.size());
	for (auto s : tr)
		cout << s << "\t";
}