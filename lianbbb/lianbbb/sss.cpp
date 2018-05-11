#include<iostream>
using namespace std;

/*
struct RandomListNode {
	int label;
	struct RandomListNode *next, *random;
	RandomListNode(int x) :
		label(x), next(NULL), random(NULL) {
	}
};

class Solution {
public:
	RandomListNode* Clone(RandomListNode* pHead)
	{
		RandomListNode* node = pHead;
		RandomListNode* newNode;
		while (node) {
			newNode = new RandomListNode(node->label);
			newNode->next = node->next;
			node->next = newNode;
			node = newNode->next;
		}
		node = pHead;
		while (node) {
			newNode = node->next;
			newNode->random = node->random ? node->random->next : nullptr;
			node = newNode->next;
		}
		RandomListNode* newHead = pHead->next;
		newNode = newHead;
		node = pHead;
		while (node->next->next) {
			node->next = node->next->next;
			newNode->next = newNode->next->next;
			node = node->next;
			newNode = newNode->next;
		}
		node->next = nullptr;
		newNode->next = nullptr;
		return newHead;
	}
};


int main()
{
	RandomListNode* node1 = new RandomListNode(1);
	RandomListNode* node2 = new RandomListNode(2);
	RandomListNode* node3 = new RandomListNode(3);
	node1->next = node2;
	node2->next = node3;
	node1->random = node3;
	node2->random = nullptr;
	node3->random = node1;
	Solution s;
	RandomListNode* h = s.Clone(node1);
	while (h) {
		cout << h->label << endl;
		h = h->next;
	}
}
*/


struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) : val(x), next(NULL) {}
};
class ChkIntersection {
public:
	ListNode* chkInter(ListNode* head1, ListNode* head2) {
		// write code here
		ListNode* inLoop1 = chkLoop(head1);
		ListNode* inLoop2 = chkLoop(head2);
		ListNode* first;
		if (inLoop1 == inLoop2) {
			first = chkIntersect(head1, head2, inLoop1);
			return first;
		}
		else {
			first = inLoop1->next;
			while (first != inLoop1) {
				if (first == inLoop2)
					return first;
				first = first->next;
			}
			return nullptr;
		}
	}
private:
	ListNode* chkLoop(ListNode* head) {
		ListNode *fast, *slow;
		fast = head;
		slow = head;
		while (fast&&fast->next) {
			fast = fast->next->next;
			slow = slow->next;
			if (fast == slow) {
				fast = head;
				while (fast != slow) {
					fast = fast->next;
					slow = slow->next;
				}
				return fast;
			}
		}
		return nullptr;
	}

	ListNode* chkIntersect(ListNode* head1, ListNode* head2, ListNode* end) {
		ListNode* node1 = head1;
		ListNode* node2 = head2;
		int len1 = 0, len2 = 0;
		while (node1!=end) {
			len1++;
			node1 = node1->next;
		}
		while (node2!=end) {
			len2++;
			node2 = node2->next;
		}
		if (len1>len2)
		{
			node1 = head1;
			for (int i = 0; i < len1 - len2; i++) {
				node1 = node1->next;
			}
			node2 = head2;
			while (node1 != node2) {
				node1 = node1->next;
				node2 = node2->next;
			}
			return node1;
		}
		else {
			node2 = head2;
			for (int i = 0; i < len2 - len1; i++) {
				node2 = node2->next;
			}
			node1 = head1;
			while (node1 != node2) {
				node1 = node1->next;
				node2 = node2->next;
			}
			return node1;
		}
	}
};

int main(){
	ListNode* n0 = new ListNode(0);
	ListNode* n1 = new ListNode(1);
	ListNode* n2 = new ListNode(2);
	ListNode* n3 = new ListNode(3);
	ListNode* n4 = new ListNode(4);
	ListNode* n5 = new ListNode(5);
	ListNode* n6 = new ListNode(6);
	ListNode* n7 = new ListNode(7);
	n0->next = n1;
	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->next = n2;
	n5->next = n6;
	n6->next = n7;
	n7->next = n3;
	ChkIntersection c;
	cout << c.chkInter(n0, n5)->val << endl;
}