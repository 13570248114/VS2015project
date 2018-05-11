#include"head.h"

void makeAdministrator(administrator* adminList, int* adminNum) {
	administrator* admin = adminList + *adminNum;
	int i;
	int have;
	system("cls");
	do
	{
		printf("\n请输入第%d个管理员的信息：", (*adminNum) + 1);
		printf("\nID 姓名 密码 邮箱 所属超市名称\n:");
		scanf("%s%s%s%s%s", admin->ID,  admin->password, admin->email, admin->superMardetName);

		while (!checkCAID(admin->ID)) {
			printf("无效的ID，请重新输入！\n");
			scanf("%s", admin->ID);
		}
		while (!checkEmail(admin->email)){
			printf("无效的邮箱，请重新输入！\n");
			scanf("%s", admin->email);
		}
		if (*adminNum != 0) {
			do {
				for (i = 0;i < *adminNum;i++) {
					if (strcmp(admin->superMardetName, (adminList + i)->superMardetName)==0) {
						printf("该超市已经有一个管理员，请重新输入另外一个超市！\n");
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
			printf("\n按0结束输入，继续按1：");
			scanf("%d", &i);
			if (i != 1 && i != 2)
				printf("输入错误！\n");
		} while (i != 1 && i != 2);
	} while (i);
	//display(a, *n);
	printf("\n输入结束！");
	printf("按回车返回：");
	getch();
}
