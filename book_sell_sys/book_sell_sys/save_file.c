#include"head.h"
void save_file(book_msg* books, int n)
{
	system("cls");
	book_msg *p;
	FILE *fp=fopen("message.txt","w"); //��д����ʽ���ļ�
    if(!fp)
	   printf("�ļ�������");

	//��ʽ��д��
	for(p=books;p<books+n;p++)
	{
		fprintf(fp, "%d\t%s\t%s\t%s\t%d\n",p->num, p->book_name, p->author, p->Press, p->price);
	}

	fflush(fp); //����ˢ�� ������������
	fclose(fp);  //�ر��ļ�
    printf("\n�����鼮��Ϣ�Ѿ����浽��ǰ����Ŀ¼�µ�message.txt\n");
    printf("\n\n�����������:");
	getch();
}