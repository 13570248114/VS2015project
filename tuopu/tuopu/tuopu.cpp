#include<iostream>
#include<string>
using namespace std;

struct TreeNode {
	struct TreeNode* left;
	struct TreeNode* right;
	int val;
	TreeNode(int val) :val(val), left(nullptr), right(nullptr) {}
};

class IdenticalTree {
public:
	bool chkIdentical(TreeNode* A, TreeNode* B) {
		string a, b;
		TreeToString(A, a);
		TreeToString(B, b);
		return KMP(a, b) == -1 ? false : true;
	}
private:
	void TreeToString(TreeNode* A , string& str) {
		if (A == nullptr)
			str += '#';
		else
		{
			str += to_string(A->val) + '!';
			TreeToString(A->left, str);
			TreeToString(A->right, str);
		}
	}

	int* GetKMPnext(const string T)
	{
		int size = T.size();
		int* next = new int[size];
		int i = 0;
		int j = -1;
		next[0] = -1;
		while (i < size -1 )
		{
			if (j == -1 || T[i] == T[j])
			{
				i++;
				j++;
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

public:
	int KMP(const string S, const string T)
	{
		int size = T.size();
		int i = 0;
		int j = 0;
		int *next = GetKMPnext(T);
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
};

int main()
{
	IdenticalTree id;
	cout << id.KMP("a!bc#acd##", "ac") << endl;
}