#include"head.h"
void display(Plist* list, int n)
{
	Plist *p;
	system("cls");
	printf("��ǰ����������Ϣ����:\n");
	printf("\n���ƺ�\t��ʻԱ����\t��������\t�������\t���������\t��������\n");
	for(p=list;p<list+n;p++)
	{	
		printf("%s\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n", p->vno, p->dname, p->pname, p->pno, p->no, p->date);
	}
	printf("\n");
}