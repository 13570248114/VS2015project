#include<iostream>
#include<set>
#include<functional>
#include<algorithm>
#include<vector>
using namespace std;

typedef multiset<int, greater<int>> intSet;
typedef multiset<int, greater<int>>::iterator setIterator;

void GetLeastNumbers(const vector<int>& vec, intSet& leastNumbers, int k) {
	leastNumbers.clear();
	if (k < 1 || vec.size() < k)
		return;
	vector<int>::const_iterator iter = vec.begin();
	for (;iter != vec.end();iter++) {
		if (leastNumbers.size() < k)
			leastNumbers.insert(*iter);
		else {
			setIterator iterGreatset = leastNumbers.begin();
			if (*iter < *iterGreatset) {
				leastNumbers.erase(iterGreatset);
				leastNumbers.insert(*iter);
			}
		}
	}
}

int main() {
	vector<int> a{ 3,2,5 };
	sort(a.begin(), a.end(), greater<int>());
	for (auto aa : a)
		cout << aa << "\t";
}