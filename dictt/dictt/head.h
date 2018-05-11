#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define TRUE 1                  
#define FALSE 0
#define COUNT 26                  //��֧������



typedef struct tree {             //���ڱ�����󵥴�λ�õ�����
	int locate;
	struct tree* next;
}location;

location* createlocate(int loca);            //��������ڵ�
void addlocate(location* head, int loca);    //��������������

typedef struct Tries_node {                  //�ֵ����ڵ�ṹ
    struct Tries_node* child[COUNT];
    int isEnd;
    char ch;
	location* head;
} Node;

Node* create_node(char c, int flag);         //�����ڵ�
int insert_node(Node* n, char ch);           //����ڵ�
int insert_word(Node* root, char* str, int loca);   //���뵥�ʣ�loca�ǵ����������е�λ��
int check(Node* root, char* word);                 //��鵥���Ƿ����ֵ�����
void traversal(Node* root, char* str, FILE* fp3);   //������ȱ������������ڰ��ֵ�˳��������


