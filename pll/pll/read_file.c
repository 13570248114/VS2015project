#include"head.h"
void read_file(Plist* list, int* n)
{
	FILE* fp;
	Plist *p = list;
	*n = 0;

	system("cls");
	//���ļ�����ʽ����������
   	if( (fp=fopen("message.txt","r")) != NULL ){
		while (fscanf(fp, "%s%s%s%s%s%s", p->vno, p->dname, p->pname, p->pno, p->no, p->date) != EOF) {
			    (*n)++;
				 p++;
			}
		fclose(fp);
		printf("\n������Ϣ�Ѿ��ӵ�ǰ����Ŀ¼�µ�message.txt����\n");
	}
	else
		printf("\n��ǰû�пɶ�����ļ�����ص����˵�¼����Ϣ\n");
	
	 printf("\n\n�����������:");
	 getch();
}