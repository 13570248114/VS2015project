#include"head.h"

void count(Plist* list, int n)
{
	int k, y, select;
	char temp[20],max[20],min[20];
	Plist *p;
	system("cls");

	do {
		k = 0;
		//��������Ƿ�Ϸ�////////////////////////////////////
		printf("\n������Ҫͳ�Ƶļ�ʻԱ����:");
		scanf("%s", temp);
		printf("������ĳ��ʱ��ε����,��ʽҪ��Ϊ��20170707(2017��7��7��)��ͬ��\n");
		scanf("%s", min);
		while (check_no_num(min, 8))
		{
			printf("���벻�Ϸ������������룡<<endl");
			scanf("%s", min);
		}
		while (check_data(min, 8))
		{
			printf("�������벻�Ϸ�����������������,����ʱ���Ƿ���ϳ���\n");
			scanf("%s", min);
		}

		printf("������ĳ��ʱ��ε��յ�,��ʽҪ��Ϊ��20170707(2017��7��7��)��ͬ��\n");
		scanf("%s", max);
		while (check_no_num(max, 8))
		{
			printf("���벻�Ϸ������������룡<<endl");
			scanf("%s", max);
		}
		while (check_data(max, 8))
		{
			printf("�������벻�Ϸ�����������������,����ʱ���Ƿ���ϳ���\n");
			scanf("%s", max);
		}
		while (strcmp(max, min) < 0)
		{
			printf("�յ������磬���벻�Ϸ������������룡\n");
			scanf("%s", max);
		}
		//////////////////////////////////////////////////////////////////

		//��������/////////////////////////////////////////////////////////////////
		for (p = list;p<list + n;p++)
			if ((!strcmp(temp, p->dname))&&(strcmp(max, p->date)>=0)&& (strcmp(min, p->date) <= 0))  //��������������ʱ��Ҫ��Ļ�
			{
				if (!k)printf("���ҵ�:\n���ƺ�\t��ʻԱ����\t��������\t�������\t���������\t��������\n");
				k = 1;                        //�ҵ���ѱ�־λ��Ϊ1
				printf("%s\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n", p->vno, p->dname, p->pname, p->pno, p->no, p->date);
			}

		if (!k)
			printf("�ڸ�ʱ����ڸó���û�д�����¼!\n");

		printf("�Ƿ��������\nYES/1 or NO/0:\n");
		scanf("%d", &y);
	} while (y);

	printf("�����������:");
	getch();
}