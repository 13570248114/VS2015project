#include"head.h"

void makeCustomer(customer* cusList, int* cusNum) {
	customer* cus = cusList + *cusNum;
	int i;
	system("cls");
	do
	{
		printf("\n请输入第%d个顾客的信息：", (*cusNum) + 1);
		printf("\nID 姓名 性别(男/女) 电话 密码 邮箱 收货地址 账户余额\n:");
		scanf("%s%s%s%s%s%s%s%f", cus->ID,cus->name,cus->sex,cus->phone,cus->password,cus->email,cus->address,&cus->menoy);
		while (!checkCAID(cus->ID)) {
			printf("无效的ID，请重新输入！\n");
			scanf("%s", cus->ID);
		}
		while (cus->sex!="男"&&cus->sex != "女"){
			printf("无效的性别，请重新输入！\n");
			scanf("%s", cus->sex);
		}
		while (!checkPhone(cus->phone)){
			printf("无效的电话，请重新输入！\n");
			scanf("%s", cus->phone);
		}
		while (!checkEmail(cus->email)){
			printf("无效的邮箱，请重新输入！\n");
			scanf("%s", cus->email);
		}
		while (cus->menoy < 0){
			printf("无效的账户余额，请重新输入！\n");
			scanf("%s", cus->menoy);
		}
		(*cusNum)++;
		cus++;
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