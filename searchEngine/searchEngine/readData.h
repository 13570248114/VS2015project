#ifndef READDATA_H
#define READDATA_H
#include<stdio.h>

typedef struct urlNode {                  //储存url的链表节点
	char url[20];                              //url
	int vertex;                                  //该url所对应的图上的顶点标号
	double PR;
	struct urlNode *next;
}urlNode;

typedef struct urlL {                         //储存url的链表
	urlNode* head;                            //指向第一个节点
	urlNode* tail;                               //指向最后一个节点
	int num_of_node;                         //节点的数量
}urlL;

typedef urlL* urlList;


urlList insertNode(urlList List_of_Urls, char *url);        //插入节点
urlList GetCollection();                                               //根据collection.txt文件建立链表
void freeList(urlList List_of_Urls);                                //释放链表
urlList insertNode_sort(urlList List_of_Urls, char *url);        //按字典序插入节点
void sort(urlList List_of_Urls);
void exchangeNode(urlNode* n1, urlNode* n2);
void printURLs(urlList List_of_Urls);

#endif // !READDATA_H
