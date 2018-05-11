// testc++.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<string>
#include<cmath>
using namespace std;

/*
class Solution {
public:
	int MoreThanHalfNum_Solution(vector<int> numbers) {
		int mid;
		int n = numbers.size();
		int left = 0, right = n - 1;
		do {
			mid = partion(numbers, left, right);
			if (mid != -1 && mid>(n + 1) / 2)
				right = mid - 1;
			else if (mid != -1 && mid<(n + 1) / 2)
				left = mid + 1;
		} while (mid != (n + 1) / 2);
		int num = 0;
		for (int i = 0; i<n; i++) {
			if (numbers[i] == numbers[mid])
				num++;
		}
		if (num<n / 2)
			return 0;
		else
			return numbers[mid];
	}
private:
	int partion(vector<int>& numbers, int left, int right) {
		if (left>right)
			return -1;
		int cur = left - 1;
		int key = numbers[right];
		while (left <= right)
		{
			if (numbers[left] <= key) {
				cur++;
				swap(numbers, cur, left);
			}
			left++;
		}
		return cur;
	}

	void swap(vector<int>& numbers, int left, int right) {
		int temp = numbers[left];
		numbers[left] = numbers[right];
		numbers[right] = temp;
	}
};

*/

int huiwen(int n) {
	int count = 0;
	while (n != 0) {
		count++;
		n = n /2;
	}
	return count;
	
}
int main()
{
	int n;
	cin >> n;
	int count = huiwen(n);
	if (count == 1)
		cout << 2 << endl;
	else if (count == 2) {
		cout << 3 << endl;
	}
	else {
		int midlen, half;
		int sum = 3;
		for (int i = 3; i <= count; i++) {
			midlen = i - 2;
			if (midlen % 2)
				sum += 2;
			half = midlen / 2;
			if (half != 0)
				sum += pow(2, half);
		}
		cout << sum << endl;
	}
}

