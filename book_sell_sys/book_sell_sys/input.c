#include"head.h"
void input(book_msg *books, int *n)
{
	book_msg *p=books+*n;
	int i;
	system("cls");
	do
	{
			printf("\n�������%d���鼮��Ϣ���Կո�Ϊ�ָ�������",(*n)+1);
        	printf("\n����\t����\t���浥λ\t�۸�\n:");
			scanf("%s%s%s%d",p->book_name,p->author,p->Press,&p->price);                                   
			(*n)++;
			p->num = *n;
            p++; 
	        printf("\n���������밴0��\n���������밴1��\n");
            scanf("%d",&i);			
	}while(i); 
	display(books,*n);
    printf("\n���������");
	printf("���س����أ�");
	getch();
}