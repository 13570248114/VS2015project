#include"head.h"
void input(book_msg *books, int *n)
{
	book_msg *p=books+*n;
	int i;
	system("cls");
	do
	{
			printf("\n请输入第%d条书籍信息（以空格为分隔符）：",(*n)+1);
        	printf("\n书名\t作者\t出版单位\t价格\n:");
			scanf("%s%s%s%d",p->book_name,p->author,p->Press,&p->price);                                   
			(*n)++;
			p->num = *n;
            p++; 
	        printf("\n结束输入请按0；\n继续输入请按1：\n");
            scanf("%d",&i);			
	}while(i); 
	display(books,*n);
    printf("\n输入结束！");
	printf("按回车返回：");
	getch();
}