#include"head.h"
void read_file(book_msg* books, int* n)
{
	system("cls");
	FILE* fp;
	book_msg *p = books+*n;

	//���ļ�����ʽ����������
   	if( (fp=fopen("message.txt","r")) != NULL ){
		while (fscanf(fp, "%d%s%s%s%d", &p->num,p->book_name, p->author, p->Press, &p->price) != EOF) {
			    (*n)++;
				p->num = *n;
				p++;
			}
		fclose(fp);
		printf("\n�����鼮��Ϣ�Ѿ��ӵ�ǰ����Ŀ¼�µ�message.txt����\n");
	}
	else
		printf("\n��ǰû�пɶ�����ļ�����ص����˵�¼����Ϣ\n");
	
	 printf("\n\n�����������:");
	 getch();
}