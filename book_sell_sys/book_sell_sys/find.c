#include"head.h"
void find(book_msg* books,int n)
{
	int k,y,select;
	char temp[20];
	book_msg *p;
	system("cls");

	do{
		k=0;

		//先选择书籍查询方式
		printf("\n按书名查询请按0 \n按作者查询请按1:\n");
		scanf("%d", &select);
		while (select>1||select<0)
		{
			printf("输入的数字范围错误，请重新输入\n");
			scanf("%d", &select);
		}

		//用一个字符串数组temp来暂存书名或者作者名字
		if(select==0)printf("请输入书名\n");
		else
			printf("请输入作者名字\n");
		scanf("%s",temp);

		//遍历查找
		for(p=books;p<books+n;p++)
			if((select==0&&strcmp(temp,p->book_name)==0)|| (select == 1 && strcmp(temp, p->author) == 0))  
			{
				k=1;                        //找到则把标志位设为1
				printf(" 已找到:");
				printf("\n序号\t书名\t作者\t出版单位\t价格\n");
				printf("%d\t%s\t%s\t%s\t\t%d\n", p->num, p->book_name, p->author, p->Press, p->price);
				break;
			}

			if(!k)
			printf("找不到!\n");

		printf("是否继续查找\nYES/1 or NO/0:\n");
		scanf("%d",&y);
	}while(y);

	printf("按任意键返回:");
	getch();
}