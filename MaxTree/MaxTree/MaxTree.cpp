#include<iostream>
#include<vector>
#include<stack>
using namespace std;

class MaxTree {
public:
	vector<int> buildMaxTree(vector<int> A, int n) {
		vector<int> father(n);
		stack<int> cmp;
		int top = -1;
		int pretop;
		vector<int> preTop(n);
		for (int i = 0;i<n;i++)
		{
			while (!cmp.empty() && cmp.top()<A[i])
			{
				cmp.pop();
				top = preTop[top];
			}
			cmp.push(A[i]);
			pretop = father[i] = top;
			top = i;
			preTop[top] = pretop;
		}
		top = -1;
		while (!cmp.empty()) cmp.pop();
		for (int i = n - 1;i >= 0;i--)
		{
			while (!cmp.empty() && cmp.top()<A[i])
			{
				cmp.pop();
				top = preTop[top];
			}
			cmp.push(A[i]);
			if (top != -1 && father[i] != -1)
				father[i] = A[top] < A[father[i]] ? top : father[i];
			else
				father[i] = top == -1 ? father[i] : top;
			pretop = top;
			top = i;
			preTop[top] = pretop;
		}
		return father;
	}
};

int main()
{
	vector<int> A{ 36,1173,934,436 };
	MaxTree m;
	m.buildMaxTree(A, 4);
}