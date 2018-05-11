#include"head.h"

int login(customer* cus, administrator* admin)
{
	char username[50];
	char password[50];
	int i = 3;                             //用户密码错误上限是3次
	printf("\n\n\t欢迎使用网上超市管理系统\n\n");
	while (i)
	{
		printf("\n please input the username:");
		gets(username);                            //输入用户名
		printf("\n please input the password: ");
		gets(password);                             //输入用户密码

		if ((strcmp(username, admin->ID) == 0) && (strcmp(password, admin->password) == 0))   //检查用户名和密码是否匹配，默认账号是admim,密码是admin
			return ADMIN;
		else if ((strcmp(username, cus->ID) == 0) && (strcmp(password, cus->password) == 0))
			return CUSTOMER;
		else
		{
			i--;
			if (i)
				printf("\n用户名或者密码错误，请重新输入.......\n");
		}
	}
	return FALSE;
}