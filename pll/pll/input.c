#include"head.h"
void input(Plist *list, int *n)
{
	Plist *p=list+*n;
	int i,j,x=0;
	system("cls");
	do
	{
			printf("\n请输入第%d条罚单信息（以空格为分隔符）：",(*n)+1);
        	printf("\n车牌号\t驾驶员姓名\t交警姓名\t交警编号\t处罚单编号\t处罚日期(格式为20170701))\n:");
			scanf("%s%s%s%s%s%s",p->vno,p->dname,p->pname,p->pno,p->no,p->date);  
			
			//先检查单号是否跟之前的重复
			do
			{
				for (j = 0;j < (*n);j++)
					if (!strcmp(list[j].no, p->no))
					{
						printf("错误：处罚单号已存在，请重新输入处罚单号！\n");
						x = 1;
						break;
					}
				if (j == (*n))break;
				scanf("%s", p->no);
			} while (x);
			/////////////////////////////////

			//再检查输入的处罚日期是否合法//////////////////////////////////////////////////
			while (check_no_num(p->date, 8))
			{
				printf("处罚日期输入不合法，请重新输入处罚日期,格式为20170701！\n");
				scanf("%s", p->date);
			}
			while (check_data(p->date, 8))
			{
				printf("处罚日期输入不合法，请重新输入处罚日期,请检查时间是否符合常理！\n");
				scanf("%s", p->date);
			}
			////////////////////////////////////////////////

			//都合法才把指针指向下一位
			(*n)++;
            p++; 
	        printf("\n结束输入请按0；\n继续输入请按1：\n");
			scanf("%d", &i);
	}while(i); 

	display(list,*n);             //显示一次
    printf("\n输入结束！");
	printf("按回车返回：");
	getch();
}