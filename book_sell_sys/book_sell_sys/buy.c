#include"head.h"
int buy(book_msg* books, int n)
{
	//////��ʼ������
	buy_book books_list[SIZE];
	int sum = 0,count=0,flag=1;
	book_msg p;
	int i = 0, j;

	system("cls");                 //����
	display(books, n);             //��ʾ�����鼮��Ϣ
	printf("\n");
	
	if (n == 0)                    //�ȼ���鼮��Ϣ�Ƿ�Ϊ�գ������ܹ���Ҫ�ص����˵�����鼮��Ϣ
	{
		printf("�鼮����Ϊ�գ��뷵�����˵����ļ�������Ϣ�����ֶ�����\n\n");
		printf("�����������:");
		getch();
		return 0;
	}
	
	//�����鼮��Ϣ¼��
	do
	{
		printf("������һ��ϣ��������鼮�����\n");           //����Χ���
		scanf("%d", &books_list[i].num);
		if (books_list[i].num > n|| books_list[i].num<1)
		{
			printf("������뷶Χ����ȷ������������;\n");
			continue;
		}

		printf("���������Ϊ %d ���鼮�Ĺ�������\n", books_list[i].num);
		scanf("%d", &books_list[i].count);
		if (books_list[i].count < 1)
		{
			printf("�������뷶Χ���Ϸ�������������\n");
			scanf("%d", &books_list[i].count);
		}

		i++;
		printf("¼����ϣ��Ƿ���Ҫ������鼮��������1��0��\nYES/1 or NO/0:\n");
		scanf("%d", &flag);
	} while (flag);
	
	system("cls");                         //¼����ɺ�����

	printf("\n\n\n\t\t\t�����嵥\t\n\n\n");
	printf("���鵥λ:\tͼ���\t\t���鵥��:\t8088\n");
	printf("------------------------------------------------------\n");
	printf("���\t����\t����\t���浥λ\t����\t����\n");
	for (j = 0;j < i;j++) {
		p = books[books_list[j].num-1];                                                 //��Ϊ�鼮�źŴ�1��ʼ���������0��ʼ
		printf("%d\t%s\t%s\t%s\t\t%d\t%d\n", p.num, p.book_name, p.author, p.Press, p.price, books_list[j].count);
		sum += p.price*books_list[j].count;
		count += books_list[j].count;
	}
	printf("------------------------------------------------------\n");
	printf("�ϼƹ���:\t%d��\t\t�ϼƽ��:\t%dԪ\n",count,sum);

	printf("�����������:");
	getch();
	return 1;
}