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
		printf("\n������Ҫɾ�����鼮���:");
		scanf("%d",&num);

		for(i=0,p=books;i<*n;i++)             //�����鼮��Ϣ�����Ҷ�Ӧ�鼮��ɾ��
			if(num==(p+i)->num)
			{
				k=1;
				for (j = i;j < *n - 1;j++)
				{
					*(p + j) = *(p + j + 1);    //��ɾ���鼮����������鼮��ǰ�ƶ�һ��λ��
					(p + j)->num--;
				}
					
				(*n)--;
				printf("��ɾ��!\n");
				break;
			}
			if(!k)
				printf("\n�Ҳ���Ҫɾ�����鼮!\n\n");
		
			printf("\n�Ƿ������ɾ����\nYES/1 or NO/0:\n");
			scanf("%d",&x);
			
	}while(x);

	display(books,*n);
	printf("�����������:");
	getch();
}