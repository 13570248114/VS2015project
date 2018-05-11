#ifndef READDATA_H
#define READDATA_H
#include<stdio.h>

typedef struct urlNode {                  //����url������ڵ�
	char url[20];                              //url
	int vertex;                                  //��url����Ӧ��ͼ�ϵĶ�����
	double PR;
	struct urlNode *next;
}urlNode;

typedef struct urlL {                         //����url������
	urlNode* head;                            //ָ���һ���ڵ�
	urlNode* tail;                               //ָ�����һ���ڵ�
	int num_of_node;                         //�ڵ������
}urlL;

typedef urlL* urlList;


urlList insertNode(urlList List_of_Urls, char *url);        //����ڵ�
urlList GetCollection();                                               //����collection.txt�ļ���������
void freeList(urlList List_of_Urls);                                //�ͷ�����
urlList insertNode_sort(urlList List_of_Urls, char *url);        //���ֵ������ڵ�
void sort(urlList List_of_Urls);
void exchangeNode(urlNode* n1, urlNode* n2);
void printURLs(urlList List_of_Urls);

#endif // !READDATA_H
