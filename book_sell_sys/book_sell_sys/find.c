#include"head.h"
void find(book_msg* books,int n)
{
	int k,y,select;
	char temp[20];
	book_msg *p;
	system("cls");

	do{
		k=0;

		//��ѡ���鼮��ѯ��ʽ
		printf("\n��������ѯ�밴0 \n�����߲�ѯ�밴1:\n");
		scanf("%d", &select);
		while (select>1||select<0)
		{
			printf("��������ַ�Χ��������������\n");
			scanf("%d", &select);
		}

		//��һ���ַ�������temp���ݴ�����������������
		if(select==0)printf("����������\n");
		else
			printf("��������������\n");
		scanf("%s",temp);

		//��������
		for(p=books;p<books+n;p++)
			if((select==0&&strcmp(temp,p->book_name)==0)|| (select == 1 && strcmp(temp, p->author) == 0))  
			{
				k=1;                        //�ҵ���ѱ�־λ��Ϊ1
				printf(" ���ҵ�:");
				printf("\n���\t����\t����\t���浥λ\t�۸�\n");
				printf("%d\t%s\t%s\t%s\t\t%d\n", p->num, p->book_name, p->author, p->Press, p->price);
				break;
			}

			if(!k)
			printf("�Ҳ���!\n");

		printf("�Ƿ��������\nYES/1 or NO/0:\n");
		scanf("%d",&y);
	}while(y);

	printf("�����������:");
	getch();
}