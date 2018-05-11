#include"head.h"
void read_file(book_msg* books, int* n)
{
	system("cls");
	FILE* fp;
	book_msg *p = books+*n;

	//打开文件并格式化读入内容
   	if( (fp=fopen("message.txt","r")) != NULL ){
		while (fscanf(fp, "%d%s%s%s%d", &p->num,p->book_name, p->author, p->Press, &p->price) != EOF) {
			    (*n)++;
				p->num = *n;
				p++;
			}
		fclose(fp);
		printf("\n所有书籍信息已经从当前工作目录下的message.txt读入\n");
	}
	else
		printf("\n当前没有可读入的文件，请回到主菜单录入信息\n");
	
	 printf("\n\n按任意键返回:");
	 getch();
}