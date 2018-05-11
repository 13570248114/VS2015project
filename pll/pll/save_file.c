#include"head.h"
void save_file(Plist* books, int n)
{
	system("cls");
	Plist *p;
	FILE *fp=fopen("message.txt","w"); //可写的形式打开文件
    if(!fp)
	   printf("文件打开有误");

	//格式化写入
	for(p=books;p<books+n;p++)
	{
		fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\n", p->vno, p->dname, p->pname, p->pno, p->no, p->date);
	}

	fflush(fp); //数据刷新 数据立即更新
	fclose(fp);  //关闭文件
    printf("\n所有信息已经保存到当前工作目录下的message.txt\n");
    printf("\n\n按任意键返回:");
	getch();
}