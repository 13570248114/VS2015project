#include"head.h"

int smaller(book_msg* books, int i,int j,int select)    //���ڱȽϴ�С��ϵ�ĺ���
{
	if (select == 0)                                       //���ѡ���������������������ֵ�˳��Ƚ������鼮�Ĵ�С��ϵ
		if (strcmp(books[i].book_name, books[j].book_name) < 0)
			return 1;
		else
			return 0;

	else if (select == 1)                                //���ѡ�񰴼۸��������ü۸�ߵͱȽ������鼮�Ĵ�С��ϵ
		if (books[i].price < books[j].price)
			return 1;
		else
			return 0;

	else
		return -1;
}

void sort(book_msg* books, int n)
{
    int i,j,select;
	book_msg t;
	system("cls");

	printf("\n�����������밴0 \n���۸������밴1:\n");
	scanf("%d", &select);
	while (select>1 || select<0)
	{
		printf("��������ַ�Χ��������������\n");
		scanf("%d", &select);
	}
	
	for(i=0;i<n-1;i++)                  //ð������
	{
		for(j=0;j<n-i-1;j++)
			if(smaller(books,j+1, j, select))       //��С��ϵ�Ƚϵ���������ĺ�������˼��if(books[j+1]<books[j])
			{
				t=books[j];
				books[j]=books[j+1];
				books[j].num = j+1 ;               //Ҫ����һ�������Ϣ����Ϊ��Ŵ�1��ʼ�����Ա�����������Ŷ�1
				books[j+1]=t;
				books[j + 1].num = j + 2;
			}		
	}

	printf("����������:\n");
	display(books, n);
	printf("�����������:");
	getch();
}