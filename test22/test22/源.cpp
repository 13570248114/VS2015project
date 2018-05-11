
#include<iostream>
#include<algorithm>
using std::min;
using std::cout;

int getv(int x, int y, int n) //螺旋矩阵（由内向外扩散）
{
	int t = (n - 1) | 1;
	if (x <= y) {
		int k = min(x, t - y);
		return (t - 2 * k) * (t - 2 * k - 1) + 1 + (x + y - 2 * k);
	}
	int k = min(y + 1, t - x) - 1;
	return (t - 2 * k) * (t - 2 * k - 1) + 1 - (x + y - 2 * k);
}

void test(int n) {
	for (int i = 0; i < 2*n-1; ++i) {
		for (int j = 0; j < 2*n-1; ++j) {
			cout.width(4);
			cout << getv(i, j, 2 * n - 1) << " ";
		}
		cout << "\n";
	}
}


int main()
{
	test(3);

}

