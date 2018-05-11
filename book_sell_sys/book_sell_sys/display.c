#include"head.h"
void display(book_msg* books, int n)
{
	book_msg *p;
	system("cls");
	printf("当前书籍信息如下:\n");
	printf("\n序号\t书名\t作者\t出版单位\t价格\n");
	for(p=books;p<books+n;p++)
	{	
		printf("%d\t%s\t%s\t%s\t\t%d\n", p->num, p->book_name, p->author, p->Press, p->price);         
	}
	printf("\n");
}