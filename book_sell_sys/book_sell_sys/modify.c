#include"head.h"
void modify(book_msg* books, int n)
{
	int i, j, k, x,select;
	book_msg* p;
	int num;
	
	system("cls");
	display(books, n);        //��ʾһ���鼮

	do {
		k = 0;
		//������޸��鼮�����
		printf("\n������Ҫ�޸��鼮�����:");
		scanf("%d", &num);
		if (num > n || num<1)
		{
			printf("������뷶Χ����ȷ������������;\n");
			scanf("%d", &num);
		}

		for (i = 0, p = books;i<n;i++)             //�����鼮��Ϣ�����Ҷ�Ӧ�鼮��ɾ��
			if (num == (p + i)->num)
			{
				k = 1;
				printf("\n���ҵ����鼮��������Ҫ�޸ĵ���������Ӧ�����:\n");
				printf("\n�޸������밴1:\n");
				printf("�޸������밴2:\n");
				printf("�޸ĳ��浥λ�밴3:\n");
				printf("�޸ļ۸��밴4:\n");
				//�ҵ��鼮��������鼮Ҫ�޸ĵ����ݵ����
				scanf("%d", &select);
				while (select > 4 || select < 1) {
					printf("������Ŵ�������������!\n");
					scanf("%d", &select);
				}
				//��������޸Ķ�Ӧ������
				switch (select)
				{
				case 1:printf("������������������:\n");scanf("%s", (p + i)->book_name);printf("�޸���ɣ�\n");break;
				case 2:printf("�����������ߵ�����:\n");scanf("%s", (p + i)->author);printf("�޸���ɣ�\n");break;
				case 3:printf("�������³����������:\n");scanf("%s", (p + i)->Press);printf("�޸���ɣ�\n");break;
				case 4:printf("�������¼۸�:\n");scanf("%d", &(p + i)->price);printf("�޸���ɣ�\n");break;
				}
				break;
			}

		if (!k)
			printf("\n�Ҳ���Ҫ�޸ĵ��鼮!\n");

		printf("\n�Ƿ�������޸ģ�\nYES/1 or NO/0:\n");
		scanf("%d", &x);

	} while (x);

	display(books, n);
	printf("�����������:");
	getch();
}