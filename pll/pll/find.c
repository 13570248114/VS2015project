#include"head.h"
void find(Plist* list,int n)
{
	int k,y,select;
	char temp[20];
	Plist *p;
	system("cls");

	do{
		k=0;
		printf("\n������Ҫ���ҵĴ������ĵ���:");
		scanf("%s", temp);

		//��������
		for(p=list;p<list+n;p++)
			if(!strcmp(temp, p->no))
			{
				k=1;                        //�ҵ���ѱ�־λ��Ϊ1
				printf(" ���ҵ�:");
				printf("\n���ƺ�\t��ʻԱ����\t��������\t�������\t���������\t��������\n");
				printf("%s\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n", p->vno, p->dname, p->pname, p->pno, p->no, p->date);
				break;
			}

			if(!k)
			printf("�Ҳ���!\n");

		printf("�Ƿ��������\nYES/1 or NO/0:\n");
		scanf("%d",&y);
	}while(y);

	printf("�����������:");
	getch();
}