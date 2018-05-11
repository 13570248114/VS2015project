/*
  listIteratorInt.c : list Iterator ADT implementation
  Written by .... 
  Date: ....
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "listIteratorInt.h"

typedef struct Node {

	struct Node *prev, *next;                     //�ֱ�ָ��ǰ��node��ÿһ��cursor��һ��Node
	int prevElement, nextElement;              //Iteratorǰ���������Iterator���������

} Node;

typedef struct IteratorIntRep {
	
	Node *currentNode, *head;                   //��ǰcursor position��head��ʾ����ͷ������ڵ�λ��
	int  flag;                                              //�ڵ���set��delete����ǰҪȷ��֮ǰ���޵���next/findnext/previous/findPrevious��
                                                              //�ʵ���next/findPreviousʱʹflag=1, ����findnext/previousʱ��ʹflag=-1,��������������ʹflag=0;
} IteratorIntRep;



/*

  Your local functions here, if any.... 


 */



IteratorInt IteratorIntNew(){

	IteratorInt it = (IteratorInt)malloc(sizeof(IteratorIntRep));            //����ռ�
	it->currentNode = (Node*)malloc(sizeof(Node));
	it->currentNode->prev = it->currentNode->next = NULL;
	it->currentNode->prevElement = it->currentNode->nextElement = 0;
	it->flag = 0;
	it->head = it->currentNode;
	return it;
}

void reset(IteratorInt it){

	/*
	while (it->currentNode->prev != NULL)                     //ʹcursor������previous�ƶ�ֱ������ʼ�㡣
		it->currentNode = it->currentNode->prev;
	it->flag = 0;
	*/
	it->currentNode = it->head;                                     //�ѵ�ǰ��cursor����Ϊhead�ڵ�
	it->flag = 0;
}


int add(IteratorInt it, int v){
  
	it->flag = 0;
	Node* node = (Node*)malloc(sizeof(Node));
	if (node)                                                                //�ڵ�ǰcursorǰ�����һ����cursor
	{	
		node->nextElement= v;                                      
		node->prev = it->currentNode->prev;                 //�������ڵ�ָ��Ĺ�ϵ
		node->next = it->currentNode;
		if (hasPrevious(it)){
			it->currentNode->prev->next = node;
			node->prevElement = it->currentNode->prev->nextElement;
		}
		else {
			node->prevElement = 0;
		}
		it->currentNode->prev = node;
		it->currentNode->prevElement = v;

		if (node->prev == NULL)                                       //����ǲ��ǲ����ͷ���
			it->head = node;
		return 1;
	}
	return 0;
}


int hasNext(IteratorInt it){

	it->flag = 0;
	return it->currentNode->next != NULL ? 1 : 0;
  
}

int hasPrevious(IteratorInt it){
  
	it->flag = 0;
	return it->currentNode->prev != NULL ? 1 : 0;
}


int *next(IteratorInt it){
  
	if (hasNext(it))
	{
		int *result = &(it->currentNode->nextElement);
		it->currentNode = it->currentNode->next;
		it->flag = 1;
		return result;
	}
	else
		return NULL;
}

int *previous(IteratorInt it){

	
	if (hasPrevious(it))
	{
		int *result = &(it->currentNode->prevElement);
		it->currentNode = it->currentNode->prev;
		it->flag = -1;
		return result;
	}
	else
		return NULL;

}


int deleteElm(IteratorInt it){
  
	if (it->flag != 0 )                                         //���it->flag����0��˵���ڵ���deleteElm֮ǰû�е���next/findnext/previous/findPrevious���ĸ������е�һ��
	{
		if (it->flag == -1)                                  //����it->flag����1����-1��ɾ��ǰ���cursor������cursor                       
		{
			Node* node = it->currentNode->next;
			it->currentNode->next = node->next;
			if (node->next!=NULL){
				node->next->prev = it->currentNode;
				it->currentNode->nextElement = node->next->prevElement;
			}
			else {
				it->currentNode->nextElement = 0;
			}
			free(node);
		}
		else if(it->flag == 1)
		{
			Node* node = it->currentNode->prev;
			it->currentNode->prev=node->prev;
			if (it->currentNode->prev == NULL)                   //�ж�it->currentNode���ޱ��ͷ���
				it->head = it->currentNode;
			if (node->prev!=NULL) {
				node->prev->next = it->currentNode;
				it->currentNode->prevElement = node->prev->nextElement;
			}
			else {
				it->currentNode->prevElement = 0;
			}
			free(node);
		}
		it->flag = 0;
		return 1;
	}
	else
		return 0;
 
}


int set(IteratorInt it, int v){
  
	if (it->flag != 0)                                 //���it->flag����0��˵���ڵ���deleteElm֮ǰû�е���next/findnext/previous/findPrevious���ĸ������е�һ��
	{
		{
			if (it->flag == -1)                         //����it->flag����1����-1���޸�ǰ���cursor������cursor 
			{
				it->currentNode->nextElement = v;
				it->currentNode->next->prevElement = v;
			}
			else if (it->flag == 1)
			{
				it->currentNode->prevElement = v;
				it->currentNode->prev->nextElement = v;
			}
		}
		it->flag = 0;
		return 1;
	}
	else
		return 0;
}

int *findNext(IteratorInt it, int v){

	Node* currentNode = it->currentNode;
	if(it->currentNode->prevElement == v&&it->currentNode->next != NULL)                      //����Ϊ�˴���������ͬ�������ڵ���������ƶ�һ���α�λ
		it->currentNode = it->currentNode->next;

	while (it->currentNode->prevElement != v&&it->currentNode->next != NULL)            //����
		it->currentNode = it->currentNode->next;
	if (it->currentNode->prevElement == v&&it->currentNode->next != NULL)
	{
		it->flag = -1;
		return &(it->currentNode->nextElement);
	}
	else
	{
		it->flag = 0;
		it->currentNode = currentNode;
		return NULL;
	}
}

int *findPrevious(IteratorInt it, int v){
  
	Node* currentNode = it->currentNode;
	if(it->currentNode->nextElement == v&&it->currentNode->prev != NULL)                   //����Ϊ�˴���������ͬ�������ڵ���������ƶ�һ���α�λ
		it->currentNode = it->currentNode->prev;

	while (it->currentNode->nextElement != v&&it->currentNode->prev != NULL)
		it->currentNode = it->currentNode->prev;
	if (it->currentNode->nextElement == v&&it->currentNode->prev != NULL)
	{
		it->flag = 1;
		return &(it->currentNode->prevElement);
	}
	else
	{
		it->flag = 0;
		it->currentNode = currentNode;
		return NULL;
	}
}

void freeIt(IteratorInt it){

	reset(it);
	Node *head = it->currentNode , *deleteNode;
	while (head != NULL)
	{
		deleteNode = head;
		head = head->next;
		free(deleteNode);
	}
}





