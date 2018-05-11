#include"head.h"

void menu(int type)
{
	if (type == CUSTOMER) {
		system("cls");
		printf("\n\n\n\t\t\t\t   欢迎使用网上超市管理系统\t\n\n\n");
		printf("\t\t\t*****************************************\n");
		printf("\t\t\t*                 主菜单                *\n");
		printf("\t\t\t*****************************************\n\n\n");
		printf("\t\t           0 商品查询                        1 购买商品 \n\n");
		printf("\t\t           2 个人信息管理                   3 取消订单 \n\n");
		printf("\t\t           4 查询购买后的订单记录          \n\n");
		printf("\t\t        请选择[0/1/2/3/4]:");
		char input;
		do {
			scanf("%c", &input);
			if (input<'0' || input>'4')
				printf("Invalid input, please input again!\n");
		} while (input<'0' || input>'4');

	}
	else if (type == ADMIN) {
		system("cls");
		printf("\n\n\n\t\t\t\t   欢迎使用网上超市管理系统\t\n\n\n");
		printf("\t\t\t*****************************************\n");
		printf("\t\t\t*                 主菜单                *\n");
		printf("\t\t\t*****************************************\n\n\n");
		printf("\t\t           0 订单管理                        1 商品管理 \n\n");
		printf("\t\t           2 个人信息管理                    \n\n");
		printf("\t\t        请选择[0/1/2]:");
		char input;
		do {
			scanf("%c", &input);
			if (input<'0' || input>'2')
				printf("Invalid input, please input again!\n");
		} while (input<'0' || input>'2');
	}
}