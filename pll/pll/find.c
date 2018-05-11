#include"head.h"
void find(Plist* list,int n)
{
	int k,y,select;
	char temp[20];
	Plist *p;
	system("cls");

	do{
		k=0;
		printf("\n请输入要查找的处罚单的单号:");
		scanf("%s", temp);

		//遍历查找
		for(p=list;p<list+n;p++)
			if(!strcmp(temp, p->no))
			{
				k=1;                        //找到则把标志位设为1
				printf(" 已找到:");
				printf("\n车牌号\t驾驶员姓名\t交警姓名\t交警编号\t处罚单编号\t处罚日期\n");
				printf("%s\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n", p->vno, p->dname, p->pname, p->pno, p->no, p->date);
				break;
			}

			if(!k)
			printf("找不到!\n");

		printf("是否继续查找\nYES/1 or NO/0:\n");
		scanf("%d",&y);
	}while(y);

	printf("按任意键返回:");
	getch();
}