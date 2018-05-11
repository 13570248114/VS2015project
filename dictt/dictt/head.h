#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define TRUE 1                  
#define FALSE 0
#define COUNT 26                  //分支的数量



typedef struct tree {             //用于保存错误单词位置的链表
	int locate;
	struct tree* next;
}location;

location* createlocate(int loca);            //创建链表节点
void addlocate(location* head, int loca);    //正序链表插入操作

typedef struct Tries_node {                  //字典树节点结构
    struct Tries_node* child[COUNT];
    int isEnd;
    char ch;
	location* head;
} Node;

Node* create_node(char c, int flag);         //创建节点
int insert_node(Node* n, char ch);           //插入节点
int insert_word(Node* root, char* str, int loca);   //插入单词，loca是单词在文章中的位置
int check(Node* root, char* word);                 //检查单词是否在字典树上
void traversal(Node* root, char* str, FILE* fp3);   //深度优先遍历函数，用于按字典顺序输出结果


