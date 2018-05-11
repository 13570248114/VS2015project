#include"head.h"
void modify(book_msg* books, int n)
{
	int i, j, k, x,select;
	book_msg* p;
	int num;
	
	system("cls");
	display(books, n);        //显示一次书籍

	do {
		k = 0;
		//输入待修改书籍的序号
		printf("\n请输入要修改书籍的序号:");
		scanf("%d", &num);
		if (num > n || num<1)
		{
			printf("序号输入范围不正确，请重新输入;\n");
			scanf("%d", &num);
		}

		for (i = 0, p = books;i<n;i++)             //遍历书籍信息，查找对应书籍并删除
			if (num == (p + i)->num)
			{
				k = 1;
				printf("\n已找到该书籍，请输入要修改的内容所对应的序号:\n");
				printf("\n修改书名请按1:\n");
				printf("修改作者请按2:\n");
				printf("修改出版单位请按3:\n");
				printf("修改价格请按4:\n");
				//找到书籍后，输入该书籍要修改的内容的序号
				scanf("%d", &select);
				while (select > 4 || select < 1) {
					printf("输入序号错误，请重新输入!\n");
					scanf("%d", &select);
				}
				//根据序号修改对应的内容
				switch (select)
				{
				case 1:printf("请输入新书名的名字:\n");scanf("%s", (p + i)->book_name);printf("修改完成！\n");break;
				case 2:printf("请输入新作者的名字:\n");scanf("%s", (p + i)->author);printf("修改完成！\n");break;
				case 3:printf("请输入新出版社的名字:\n");scanf("%s", (p + i)->Press);printf("修改完成！\n");break;
				case 4:printf("请输入新价格:\n");scanf("%d", &(p + i)->price);printf("修改完成！\n");break;
				}
				break;
			}

		if (!k)
			printf("\n找不到要修改的书籍!\n");

		printf("\n是否继续作修改？\nYES/1 or NO/0:\n");
		scanf("%d", &x);

	} while (x);

	display(books, n);
	printf("按任意键返回:");
	getch();
}