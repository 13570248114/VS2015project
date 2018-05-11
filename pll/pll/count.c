#include"head.h"

void count(Plist* list, int n)
{
	int k, y, select;
	char temp[20],max[20],min[20];
	Plist *p;
	system("cls");

	do {
		k = 0;
		//检查输入是否合法////////////////////////////////////
		printf("\n请输入要统计的驾驶员姓名:");
		scanf("%s", temp);
		printf("请输入某个时间段的起点,格式要求为与20170707(2017年7月7日)相同：\n");
		scanf("%s", min);
		while (check_no_num(min, 8))
		{
			printf("输入不合法，请重新输入！<<endl");
			scanf("%s", min);
		}
		while (check_data(min, 8))
		{
			printf("日期输入不合法，请重新输入日期,请检查时间是否符合常理！\n");
			scanf("%s", min);
		}

		printf("请输入某个时间段的终点,格式要求为与20170707(2017年7月7日)相同：\n");
		scanf("%s", max);
		while (check_no_num(max, 8))
		{
			printf("输入不合法，请重新输入！<<endl");
			scanf("%s", max);
		}
		while (check_data(max, 8))
		{
			printf("日期输入不合法，请重新输入日期,请检查时间是否符合常理！\n");
			scanf("%s", max);
		}
		while (strcmp(max, min) < 0)
		{
			printf("终点比起点早，输入不合法，请重新输入！\n");
			scanf("%s", max);
		}
		//////////////////////////////////////////////////////////////////

		//遍历查找/////////////////////////////////////////////////////////////////
		for (p = list;p<list + n;p++)
			if ((!strcmp(temp, p->dname))&&(strcmp(max, p->date)>=0)&& (strcmp(min, p->date) <= 0))  //满足姓名和两个时间要求的话
			{
				if (!k)printf("已找到:\n车牌号\t驾驶员姓名\t交警姓名\t交警编号\t处罚单编号\t处罚日期\n");
				k = 1;                        //找到则把标志位设为1
				printf("%s\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n", p->vno, p->dname, p->pname, p->pno, p->no, p->date);
			}

		if (!k)
			printf("在该时间段内该车主没有处罚记录!\n");

		printf("是否继续查找\nYES/1 or NO/0:\n");
		scanf("%d", &y);
	} while (y);

	printf("按任意键返回:");
	getch();
}