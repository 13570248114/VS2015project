#include"head.h"
void read_file(Plist* list, int* n)
{
	FILE* fp;
	Plist *p = list;
	*n = 0;

	system("cls");
	//打开文件并格式化读入内容
   	if( (fp=fopen("message.txt","r")) != NULL ){
		while (fscanf(fp, "%s%s%s%s%s%s", p->vno, p->dname, p->pname, p->pno, p->no, p->date) != EOF) {
			    (*n)++;
				 p++;
			}
		fclose(fp);
		printf("\n所有信息已经从当前工作目录下的message.txt读入\n");
	}
	else
		printf("\n当前没有可读入的文件，请回到主菜单录入信息\n");
	
	 printf("\n\n按任意键返回:");
	 getch();
}