#include"head.h"
int buy(book_msg* books, int n)
{
	//////初始化变量
	buy_book books_list[SIZE];
	int sum = 0,count=0,flag=1;
	book_msg p;
	int i = 0, j;

	system("cls");                 //清屏
	display(books, n);             //显示所有书籍信息
	printf("\n");
	
	if (n == 0)                    //先检查书籍信息是否为空，空则不能购买，要回到主菜单添加书籍信息
	{
		printf("书籍数据为空，请返回主菜单从文件读入信息或者手动输入\n\n");
		printf("按任意键返回:");
		getch();
		return 0;
	}
	
	//欲购书籍信息录入
	do
	{
		printf("请输入一个希望购买的书籍的序号\n");           //作范围检查
		scanf("%d", &books_list[i].num);
		if (books_list[i].num > n|| books_list[i].num<1)
		{
			printf("序号输入范围不正确，请重新输入;\n");
			continue;
		}

		printf("请输入序号为 %d 的书籍的购买数量\n", books_list[i].num);
		scanf("%d", &books_list[i].count);
		if (books_list[i].count < 1)
		{
			printf("数量输入范围不合法，请重新输入\n");
			scanf("%d", &books_list[i].count);
		}

		i++;
		printf("录入完毕，是否需要再添加书籍？请输入1或0：\nYES/1 or NO/0:\n");
		scanf("%d", &flag);
	} while (flag);
	
	system("cls");                         //录入完成后清屏

	printf("\n\n\n\t\t\t购书清单\t\n\n\n");
	printf("购书单位:\t图书馆\t\t购书单号:\t8088\n");
	printf("------------------------------------------------------\n");
	printf("序号\t书名\t作者\t出版单位\t单价\t数量\n");
	for (j = 0;j < i;j++) {
		p = books[books_list[j].num-1];                                                 //因为书籍信号从1开始，而数组从0开始
		printf("%d\t%s\t%s\t%s\t\t%d\t%d\n", p.num, p.book_name, p.author, p.Press, p.price, books_list[j].count);
		sum += p.price*books_list[j].count;
		count += books_list[j].count;
	}
	printf("------------------------------------------------------\n");
	printf("合计购书:\t%d册\t\t合计金额:\t%d元\n",count,sum);

	printf("按任意键返回:");
	getch();
	return 1;
}