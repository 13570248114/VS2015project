#ifndef READDATA_H
#define READDATA_H
#include<stdio.h>

typedef struct urlNode {
	char url[20];                              //url
	int vertex;                                  //The url corresponding to the vertex label on the map
	double PR;
	struct urlNode *next;
}urlNode;

typedef struct urlL {
	urlNode* head;                            //Point to the first node
	urlNode* tail;                               //Point to the last node
	int num_of_node;                         //The number of nodes
}urlL;

typedef urlL* urlList;


urlList insertNode(urlList List_of_Urls, char *url);
urlList GetCollection();
void freeList(urlList List_of_Urls);                                //free
urlList insertNode_sort(urlList List_of_Urls, char *url);
void sort(urlList List_of_Urls);                                       //sort
void exchangeNode(urlNode* n1, urlNode* n2);                //exchange
void printURLs(urlList List_of_Urls);                          //print

#endif // !READDATA_H
