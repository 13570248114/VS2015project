// ali-1.cpp : 定义控制台应用程序的入口点。
//

#include<iostream>
#include<string>
#include<vector>
using namespace std;

#define COUNT 26                  //分支的数量

typedef struct Tries_node {                  //字典树节点结构
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
	Node* create_node(char c, int flag);         //创建节点
	int insert_node(Node* n, char ch);
public:
	int insert_word(string str);   //插入单词，loca是单词在文章中的位置
	int check(string str);                 //检查单词是否在字典树上
	Node* getHead() { return Head; }
};

Node* tree::create_node(char c, int flag) {      //创建节点，一些初始化工作
	int i;
	Node* node = new Node;
	node->ch = c;
	node->isEnd = flag;

	for (i = 0; i < COUNT; i++) {
		node->child[i] = NULL;
	}

	return node;
}

int tree::insert_node(Node* n, char ch) {        //插入节点，如果字符ch不在现有的树上，则返回TRUE，否则FALSE

	Node* child_ptr = n->child[ch - 'a'];

	if (child_ptr) {
		return false;
	}
	else {
		n->child[ch - 'a'] = create_node(ch, false);
		return true;
	}
}

int tree::insert_word(string str) {      //插入单词，loca是单词在文章中的位置，成功返回TRUE
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
		flag = false;                          //如果单词是字典树上已有单词的前缀，则修改标志位
		father->isEnd = true;
	}
}

int tree::check(string word) {              //检查单词是否在字典树上，在则返回TRUE
	Node* ptr = Head;
	int slen = word.length();
	int i;

	for (i = 0; i < slen; i++) {            //逐个字母开始查找树
		if (!ptr) {
			return false;
		}
		if (word[i] > 'z' || word[i] < 'a')
			return false;
		ptr = ptr->child[word[i] - 'a'];
	}

	if (ptr && ptr->isEnd) {                 //如果最后的字母存在结尾标志，则返回真         
		return true;
	}
	else {
		return false;
	}
}

stringnode* insert(string str)
{

}









