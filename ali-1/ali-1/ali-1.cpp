// ali-1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include<iostream>
#include<string>
#include<vector>
using namespace std;

#define COUNT 26                  //��֧������

typedef struct Tries_node {                  //�ֵ����ڵ�ṹ
	struct Tries_node* child[COUNT];
	int isEnd;
	char ch;
} Node;

typedef struct stringnode {
	struct stringnode* b;
	struct stringnode* c;
}stringNode;


class tree {
private:
	Node* Head;
	Node* create_node(char c, int flag);         //�����ڵ�
	int insert_node(Node* n, char ch);
public:
	int insert_word(string str);   //���뵥�ʣ�loca�ǵ����������е�λ��
	int check(string str);                 //��鵥���Ƿ����ֵ�����
	Node* getHead() { return Head; }
};

Node* tree::create_node(char c, int flag) {      //�����ڵ㣬һЩ��ʼ������
	int i;
	Node* node = new Node;
	node->ch = c;
	node->isEnd = flag;

	for (i = 0; i < COUNT; i++) {
		node->child[i] = NULL;
	}

	return node;
}

int tree::insert_node(Node* n, char ch) {        //����ڵ㣬����ַ�ch�������е����ϣ��򷵻�TRUE������FALSE

	Node* child_ptr = n->child[ch - 'a'];

	if (child_ptr) {
		return false;
	}
	else {
		n->child[ch - 'a'] = create_node(ch, false);
		return true;
	}
}

int tree::insert_word(string str) {      //���뵥�ʣ�loca�ǵ����������е�λ�ã��ɹ�����TRUE
	Node* father = Head;
	int flag = true;
	for (auto ch : str)
	{
		if (!insert_node(father, ch)) {
			flag = false;
		}
		father = father->child[ch - 'a'];
	}

	if (!father->isEnd) {
		flag = false;                          //����������ֵ��������е��ʵ�ǰ׺�����޸ı�־λ
		father->isEnd = true;
	}
}

int tree::check(string word) {              //��鵥���Ƿ����ֵ����ϣ����򷵻�TRUE
	Node* ptr = Head;
	int slen = word.length();
	int i;

	for (i = 0; i < slen; i++) {            //�����ĸ��ʼ������
		if (!ptr) {
			return false;
		}
		if (word[i] > 'z' || word[i] < 'a')
			return false;
		ptr = ptr->child[word[i] - 'a'];
	}

	if (ptr && ptr->isEnd) {                 //���������ĸ���ڽ�β��־���򷵻���         
		return true;
	}
	else {
		return false;
	}
}

stringnode* insert(string str)
{

}









