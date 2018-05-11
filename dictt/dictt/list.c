#include"head.h"

//链表操作函数

location* createlocate(int loca)     //创建链表节点
{
	location* locate = (location*)malloc(sizeof(location));
	locate->locate = loca;
	locate->next = NULL;
	return locate;
}

void addlocate(location* head, int loca)  //正序链表插入操作
{
	location* locate=createlocate(loca);
	location* per = head;
	while (per->next)
		per=per->next;
	per->next = locate;
}