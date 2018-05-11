#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



void rrank(vector<int>& vec, int start, int end) {
	if (start > end) {
		for (auto v : vec)
			cout << v << "\t";
		cout << endl;
	}
	else {
		for (int i = start;i <= end;i++) {
			swap(vec[i], vec[start]);
			rrank(vec, start + 1, end);
			swap(vec[i], vec[start]);
		}
	}
}

void rrank(vector<int> vec) {
	if (vec.size() == 0)
		return;
	rrank(vec, 0, vec.size() - 1);
}

void com(const vector<int>& vec, int comlen, int start, int end, vector<int>& res) {
	if (comlen == 0) {
		for (auto v : res)
			cout << v << "\t";
		cout << endl;
		return;
	}
	if (start > end)
		return;
	else {
		res.push_back(vec[start]);
		com(vec, comlen - 1, start+1,end, res);
		res.pop_back();
		com(vec, comlen, start+1,end, res);
	}
}

void com(const vector<int>& vec) {
	if (vec.size() == 0)
		return;
	int len = vec.size();
	vector<int> res;
	for (int comlen = 1;comlen <= len;comlen++) {
		com(vec, comlen, 0, len-1,res);
	}
}



int main() {
	vector<int> vec{ 1,2,3};
	rrank(vec);
}