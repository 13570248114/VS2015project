#include"head.h"

//�����������

location* createlocate(unsigned long loca)     //��������ڵ�
{
	location* locate = (location*)malloc(sizeof(location));
	locate->locate = loca;
	locate->next = NULL;
	return locate;
}

void addlocate(location* head, unsigned long loca)  //��������������
{
	location* locate=createlocate(loca);
	/*
	location* per = head;
	while (per->next)
		per=per->next;
	per->next = locate;
	*/
	locate->next = head->next;
	head->next = locate;
}