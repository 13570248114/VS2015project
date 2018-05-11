#include<iostream>
using namespace std;

typedef struct node {
	int val;
	struct node* next;
	node(int v) :val(v),next(nullptr){}
}node;

node* mid(node* head) {
	if (head == nullptr)
		return nullptr;
	if (head->next == nullptr)
		return head;
	node* fast, *slow;
	fast = slow = head;
	while (fast != nullptr&&fast->next!=nullptr) {
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}

void rev(node* head, node*& newHead, node*& newTail) {
	if (head==nullptr||head->next==nullptr) {
		newHead = head;
		newTail = head;
		return;
	}
	node* nhead, *ntail;
	rev(head->next, nhead, ntail);
	ntail->next = head;
	head->next = nullptr;
	newHead = nhead;
	newTail = head;
}

node* Rev(node* head) {
	if (head == nullptr)
		return nullptr;
	if (head->next == nullptr)
		return head;
	else {
		node* nhead, *ntail;
		rev(head, nhead, ntail);
		return nhead;
	}
}

int main() {
	node* a = new node(1);
	node* b = new node(2);
	node* c = new node(3);
	a->next = b;
	b->next = c;
	a = Rev(a);
	while (a) {
		cout << a->val << endl;
		a = a->next;
	}
}

