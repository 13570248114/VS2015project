#include"head.h"

void makeAdministrator(administrator* adminList, int* adminNum) {
	administrator* admin = adminList + *adminNum;
	int i;
	int have;
	system("cls");
	do
	{
		printf("\n�������%d������Ա����Ϣ��", (*adminNum) + 1);
		printf("\nID ���� ���� ���� ������������\n:");
		scanf("%s%s%s%s%s", admin->ID,  admin->password, admin->email, admin->superMardetName);

		while (!checkCAID(admin->ID)) {
			printf("��Ч��ID�����������룡\n");
			scanf("%s", admin->ID);
		}
		while (!checkEmail(admin->email)){
			printf("��Ч�����䣬���������룡\n");
			scanf("%s", admin->email);
		}
		if (*adminNum != 0) {
			do {
				for (i = 0;i < *adminNum;i++) {
					if (strcmp(admin->superMardetName, (adminList + i)->superMardetName)==0) {
						printf("�ó����Ѿ���һ������Ա����������������һ�����У�\n");
						have = TRUE;
						break;
					}
					else
						have = FALSE;
				}
			} while (have);
		}
		(*adminNum)++;
		admin++;
		do {
			printf("\n��0�������룬������1��");
			scanf("%d", &i);
			if (i != 1 && i != 2)
				printf("�������\n");
		} while (i != 1 && i != 2);
	} while (i);
	//display(a, *n);
	printf("\n���������");
	printf("���س����أ�");
	getch();
}
