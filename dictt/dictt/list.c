#include"head.h"

//�����������

location* createlocate(int loca)     //��������ڵ�
{
	location* locate = (location*)malloc(sizeof(location));
	locate->locate = loca;
	locate->next = NULL;
	return locate;
}

void addlocate(location* head, int loca)  //��������������
{
	location* locate=createlocate(loca);
	location* per = head;
	while (per->next)
		per=per->next;
	per->next = locate;
}