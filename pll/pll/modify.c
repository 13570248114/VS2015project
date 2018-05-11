#include"head.h"
void modify(Plist* list, int n)
{
	int i, j, k, x,select;
	Plist* p;
	char no[20];
	
	do {
		system("cls");
		display(list, n);        //显示一次信息
		k = 0;
		//输入待修改的处罚单编号
		printf("\n请输入要修改的处罚单编号:");
		scanf("%s", no);
	

		for (i = 0, p = list;i<n;i++)             //遍历信息，查找对应处罚单
			if (!strcmp(no, (p + i)->no))
			{
				k = 1;
				printf("\n已找到该罚款单，请输入要修改的内容所对应的序号:\n");
				printf("\n修改车牌号请按1:\n");
				printf("修改驾驶员姓名请按2:\n");
				printf("修改交警姓名请按3:\n");
				printf("修改交警编号请按4:\n");
				//找到罚款单后，输入要修改的内容的序号
				scanf("%d", &select);
				while (select > 4 || select < 1) {
					printf("输入序号错误，请重新输入!\n");
					scanf("%d", &select);
				}
				//根据序号修改对应的内容
				switch (select)
				{
				case 1:printf("请输入新车牌号:\n");scanf("%s", (p + i)->vno);printf("修改完成！\n");break;
				case 2:printf("请输入新驾驶员姓名:\n");scanf("%s", (p + i)->dname);printf("修改完成！\n");break;
				case 3:printf("请输入新交警姓名:\n");scanf("%s", (p + i)->pname);printf("修改完成！\n");break;
				case 4:printf("请输入交警编号:\n");scanf("%s", (p + i)->pno);printf("修改完成！\n");break;
				}
				break;
			}

		if (!k)
			printf("\n找不到要修改的处罚单!\n");

		printf("\n是否继续作修改？\nYES/1 or NO/0:\n");
		scanf("%d", &x);

	} while (x);

	display(list, n);
	printf("按任意键返回:");
	getch();
}