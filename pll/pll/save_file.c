#include"head.h"
void save_file(Plist* books, int n)
{
	system("cls");
	Plist *p;
	FILE *fp=fopen("message.txt","w"); //��д����ʽ���ļ�
    if(!fp)
	   printf("�ļ�������");

	//��ʽ��д��
	for(p=books;p<books+n;p++)
	{
		fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\n", p->vno, p->dname, p->pname, p->pno, p->no, p->date);
	}

	fflush(fp); //����ˢ�� ������������
	fclose(fp);  //�ر��ļ�
    printf("\n������Ϣ�Ѿ����浽��ǰ����Ŀ¼�µ�message.txt\n");
    printf("\n\n�����������:");
	getch();
}