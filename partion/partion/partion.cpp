#include<iostream>
#include<vector>
#include<time.h>
#include<cstdlib>
#include<algorithm>
using namespace std;

class partion {
public:
	int operator()(vector<int> vec, int cur);
private:
	int parting(vector<int>& vec, int left, int right);
	void part(vector<int>& vec, int left, int right, int cur);
	void swap(vector<int>& A, int i , int j);
};

int partion::operator()(vector<int> vec, int cur) {
	srand((unsigned)time(nullptr));
	if (cur >= vec.size())
		return -1;
	part(vec, 0, vec.size() - 1, cur);
	return vec[cur];
}

void partion::part(vector<int>& vec, int left, int right, int cur) {
	int random = left + rand() % (right - left + 1);
	swap(vec,random,right);
	int pivot = parting(vec, left,right);
	if (cur > pivot)
		part(vec, pivot + 1, right, cur);
	else if(cur < pivot)
		part(vec, left, pivot - 1, cur);
}

int partion::parting(vector<int>& vec, int left, int right){
	int pivot = left -1;
	while (left <= right) {
		if (vec[left] <= vec[right]) {
			pivot++;
			swap(vec,left,pivot);
		}
		left++;
	}
	return pivot;
}

void partion::swap(vector<int>& A, int i, int j) {
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

int main() {
	partion p;
	vector<int> a{ 1,3,2,5,7,4};
	cout << p(a, 0) << endl;
}



