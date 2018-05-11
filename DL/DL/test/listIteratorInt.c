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

	struct Node *prev, *next;                     //分别指向前后node，每一个cursor是一个Node
	int prevElement, nextElement;              //Iterator前面的整数和Iterator后面的整数

} Node;

typedef struct IteratorIntRep {
	
	Node *currentNode, *head;                   //当前cursor position，head表示链表头结点所在的位置
	int  flag;                                              //在调用set、delete函数前要确定之前有无调用next/findnext/previous/findPrevious，
                                                              //故调用next/findPrevious时使flag=1, 调用findnext/previous时，使flag=-1,调用其他函数则使flag=0;
} IteratorIntRep;



/*

  Your local functions here, if any.... 


 */



IteratorInt IteratorIntNew(){

	IteratorInt it = (IteratorInt)malloc(sizeof(IteratorIntRep));            //申请空间
	it->currentNode = (Node*)malloc(sizeof(Node));
	it->currentNode->prev = it->currentNode->next = NULL;
	it->currentNode->prevElement = it->currentNode->nextElement = 0;
	it->flag = 0;
	it->head = it->currentNode;
	return it;
}

void reset(IteratorInt it){

	/*
	while (it->currentNode->prev != NULL)                     //使cursor不断往previous移动直至到开始点。
		it->currentNode = it->currentNode->prev;
	it->flag = 0;
	*/
	it->currentNode = it->head;                                     //把当前的cursor设置为head节点
	it->flag = 0;
}


int add(IteratorInt it, int v){
  
	it->flag = 0;
	Node* node = (Node*)malloc(sizeof(Node));
	if (node)                                                                //在当前cursor前面插入一个新cursor
	{	
		node->nextElement= v;                                      
		node->prev = it->currentNode->prev;                 //处理插入节点指针的关系
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

		if (node->prev == NULL)                                       //检查是不是插入的头结点
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
  
	if (it->flag != 0 )                                         //如果it->flag等于0则说明在调用deleteElm之前没有调用next/findnext/previous/findPrevious这四个函数中的一个
	{
		if (it->flag == -1)                                  //根据it->flag等于1还是-1来删除前面的cursor或后面的cursor                       
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
			if (it->currentNode->prev == NULL)                   //判断it->currentNode有无变成头结点
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
  
	if (it->flag != 0)                                 //如果it->flag等于0则说明在调用deleteElm之前没有调用next/findnext/previous/findPrevious这四个函数中的一个
	{
		{
			if (it->flag == -1)                         //根据it->flag等于1还是-1来修改前面的cursor或后面的cursor 
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
	if(it->currentNode->prevElement == v&&it->currentNode->next != NULL)                      //这是为了处理两个相同的数相邻的情况，先移动一个游标位
		it->currentNode = it->currentNode->next;

	while (it->currentNode->prevElement != v&&it->currentNode->next != NULL)            //查找
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
	if(it->currentNode->nextElement == v&&it->currentNode->prev != NULL)                   //这是为了处理两个相同的数相邻的情况，先移动一个游标位
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





