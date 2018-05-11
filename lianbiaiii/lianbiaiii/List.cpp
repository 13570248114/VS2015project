#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x):val(x),next(NULL){}
};

class InsertValue {
public:
	ListNode* insert(vector<int> A, vector<int> nxt, int val) {
		ListNode* now = new ListNode(val);
		int n = A.size();
		if (A.size() == 0) {
			now->next = now;
			return now;
		}
		ListNode* head = new ListNode(A[0]);
		ListNode* pre = head;
		for (int i = 0;i<n - 1;i++) {
			pre->next = new ListNode(A[nxt[i]]);
			pre = pre->next;
		}
		if (val <= head->val || val >= pre->val) {
			pre->next = now;
			now->next = head;
			return (val <= head->val) ? now : head;
		}
		else
			pre->next = head;
		pre = head;
		ListNode* cur = head->next;
		while (cur != head) {
			if (pre->val <= now->val&&now->val <= pre->next->val)
			{
				now->next = pre->next;
				pre->next = now;
				break;
			}
			pre = pre->next;
		}
		return head;
	}
};

class Divide {
public:
	ListNode* listDivide(ListNode* head, int pivot) {
		ListNode *Lhead = nullptr, *Ltail = nullptr;
		ListNode *Mhead = nullptr, *Mtail = nullptr;
		ListNode *Rhead = nullptr, *Rtail = nullptr;
		for (ListNode* node = head; node != nullptr;node = node->next) {
			if (node->val < pivot) {
				if (Lhead == nullptr)
					Lhead = Ltail = node;
				else {
					Ltail->next = node;
					Ltail = node;
				}
			}
			else if (node->val == pivot) {
				if (Mhead == nullptr)
					Mhead = Mtail = node;
				else {
					Mtail->next = node;
					Mtail = node;
				}
			}
			else {
				if (Rhead == nullptr)
					Rhead = Rtail = node;
				else {
					Rtail->next = node;
					Rtail = node;
				}
			}
		}
		if (Lhead){
			if (Mhead) {
				if (Rhead) {
					Ltail->next = Mhead;
					Mtail->next = Rhead;
					Rtail->next = nullptr;
				}
				else {
					Ltail->next = Mhead;
					Mtail->next = nullptr;
				}
			}
			else {
				if (Rhead) {
					Ltail->next = Rhead;
					Rtail->next = nullptr;
				}
				else {
					Ltail->next = nullptr;
				}
			}
			return Lhead;
		}
		else {
			if (Mhead) {
				if (Rhead) {
					Mtail->next = Rhead;
					Rtail->next = nullptr;
				}
				else {
					Mtail->next = nullptr;
				}
				return Mhead;
			}
			else {
				Rtail = nullptr;
				return Rhead;
			}
		}
	}
};

int main()
{
	vector<int> a{ 1,3,4,5,7 };
	vector<int> b{ 1,2,3,4,0 };
	InsertValue i;
	ListNode* l = i.insert(a, b, 2);
	while (l != nullptr)
		cout << l->val << "\t", l = l->next;
}