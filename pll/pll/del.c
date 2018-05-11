#include"head.h"
void del(Plist* list, int *n)
{
	int i,j,k,x;
	Plist* p;
	char no[20];
	
	do{
		k=0;
		system("cls");
	    display(list, *n);
		printf("\n请输入要删除的处罚单的单号:");
		scanf("%s",no);

		for(i=0,p=list;i<*n;i++)             //遍历信息，查找对应罚款单并删除
			if(!strcmp(no, (p+i)->no))
			{
				k=1;
				for (j = i;j < *n - 1;j++)
				{
					*(p + j) = *(p + j + 1);    //被删除罚款单后面的所有罚款单往前移动一个位置
				}
					
				(*n)--;
				printf("已删除!\n");
				break;
			}
			if(!k)
				printf("\n找不到要删除的处罚单!\n\n");
		
			printf("\n是否继续作删除？\nYES/1 or NO/0:\n");
			scanf("%d",&x);
			
	}while(x);

	display(list,*n);
	printf("按任意键返回:");
	getch();
}