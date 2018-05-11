#include"head.h"
void display(Plist* list, int n)
{
	Plist *p;
	system("cls");
	printf("当前处罚单的信息如下:\n");
	printf("\n车牌号\t驾驶员姓名\t交警姓名\t交警编号\t处罚单编号\t处罚日期\n");
	for(p=list;p<list+n;p++)
	{	
		printf("%s\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n", p->vno, p->dname, p->pname, p->pno, p->no, p->date);
	}
	printf("\n");
}