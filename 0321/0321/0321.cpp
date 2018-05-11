#include<iostream>
#include<string>
#include<vector>
#include<time.h>
#include<cstdlib>
using namespace std;

class Solution {
public:
	vector<string> Permutation(string str) {
		if (str.size() == 0)
			return res;
		if (str.size() == 1)
			return{ str };
		sort(str, 0, str.size() - 1);             //快排
		res.push_back(str);       //先把第一个放进去
		int len = str.size();
		int changeIndex = 0, preIndex = len - 1, postIndex;
		while (true) {
			for (preIndex = len - 1;str[preIndex - 1] >= str[preIndex];preIndex--);   //从后向前找第一个顺序对
			changeIndex = preIndex - 1;
			if (changeIndex < 0)                                                                            //如果不存在顺序对，迭代结束
				break;
			for (postIndex = preIndex;str[postIndex] > str[changeIndex];postIndex++);   //从顺序对的第二个数开始，找最后一个比顺序对第一个数小的数
			swap(str[changeIndex], str[postIndex - 1]);
			invertString(str, preIndex, len - 1);
			res.push_back(str);
		}
	}
private:
	void invertString(string& str, int left, int right) {
		while (left <= right) {
			swap(str[left++], str[right--]);
		}
	}

	void sort(string& str, int left, int right) {
		if (left >= right)
			return;
		srand((unsigned)time(nullptr));
		int radom = left + rand() % (right - left + 1);
		swap(str[radom], str[right]);
		int pos = partion(str, left, right);
		sort(str, left, pos - 1);
		sort(str, pos + 1, right);
	}

	int partion(string& str, int left, int right) {
		int cur = left - 1;
		while (left <= right) {
			if (str[left] <= str[right]) {
				cur++;
				swap(str[cur], str[left]);
			}
			left++;
		}
		return cur;
	}

private:
	vector<string> res;
};

int main() {
	Solution s;
	string str("bac");
	vector<string>	a = s.Permutation(str);
	for (auto k : a)
		cout << k << endl;
}