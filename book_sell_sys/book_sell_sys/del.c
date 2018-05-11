#include"head.h"
void del(book_msg* books, int *n)
{
	int i,j,k,x;
	book_msg* p;
	int num;
	
	do{
		k=0;
		system("cls");
		display(books, *n);
		printf("\n请输入要删除的书籍序号:");
		scanf("%d",&num);

		for(i=0,p=books;i<*n;i++)             //遍历书籍信息，查找对应书籍并删除
			if(num==(p+i)->num)
			{
				k=1;
				for (j = i;j < *n - 1;j++)
				{
					*(p + j) = *(p + j + 1);    //被删除书籍后面的所有书籍往前移动一个位置
					(p + j)->num--;
				}
					
				(*n)--;
				printf("已删除!\n");
				break;
			}
			if(!k)
				printf("\n找不到要删除的书籍!\n\n");
		
			printf("\n是否继续作删除？\nYES/1 or NO/0:\n");
			scanf("%d",&x);
			
	}while(x);

	display(books,*n);
	printf("按任意键返回:");
	getch();
}