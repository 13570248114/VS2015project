#include"head.h"
void display(book_msg* books, int n)
{
	book_msg *p;
	system("cls");
	printf("��ǰ�鼮��Ϣ����:\n");
	printf("\n���\t����\t����\t���浥λ\t�۸�\n");
	for(p=books;p<books+n;p++)
	{	
		printf("%d\t%s\t%s\t%s\t\t%d\n", p->num, p->book_name, p->author, p->Press, p->price);         
	}
	printf("\n");
}