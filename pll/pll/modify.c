#include"head.h"
void modify(Plist* list, int n)
{
	int i, j, k, x,select;
	Plist* p;
	char no[20];
	
	do {
		system("cls");
		display(list, n);        //��ʾһ����Ϣ
		k = 0;
		//������޸ĵĴ��������
		printf("\n������Ҫ�޸ĵĴ��������:");
		scanf("%s", no);
	

		for (i = 0, p = list;i<n;i++)             //������Ϣ�����Ҷ�Ӧ������
			if (!strcmp(no, (p + i)->no))
			{
				k = 1;
				printf("\n���ҵ��÷����������Ҫ�޸ĵ���������Ӧ�����:\n");
				printf("\n�޸ĳ��ƺ��밴1:\n");
				printf("�޸ļ�ʻԱ�����밴2:\n");
				printf("�޸Ľ��������밴3:\n");
				printf("�޸Ľ�������밴4:\n");
				//�ҵ����������Ҫ�޸ĵ����ݵ����
				scanf("%d", &select);
				while (select > 4 || select < 1) {
					printf("������Ŵ�������������!\n");
					scanf("%d", &select);
				}
				//��������޸Ķ�Ӧ������
				switch (select)
				{
				case 1:printf("�������³��ƺ�:\n");scanf("%s", (p + i)->vno);printf("�޸���ɣ�\n");break;
				case 2:printf("�������¼�ʻԱ����:\n");scanf("%s", (p + i)->dname);printf("�޸���ɣ�\n");break;
				case 3:printf("�������½�������:\n");scanf("%s", (p + i)->pname);printf("�޸���ɣ�\n");break;
				case 4:printf("�����뽻�����:\n");scanf("%s", (p + i)->pno);printf("�޸���ɣ�\n");break;
				}
				break;
			}

		if (!k)
			printf("\n�Ҳ���Ҫ�޸ĵĴ�����!\n");

		printf("\n�Ƿ�������޸ģ�\nYES/1 or NO/0:\n");
		scanf("%d", &x);

	} while (x);

	display(list, n);
	printf("�����������:");
	getch();
}