#include"head.h"
void input(Plist *list, int *n)
{
	Plist *p=list+*n;
	int i,j,x=0;
	system("cls");
	do
	{
			printf("\n�������%d��������Ϣ���Կո�Ϊ�ָ�������",(*n)+1);
        	printf("\n���ƺ�\t��ʻԱ����\t��������\t�������\t���������\t��������(��ʽΪ20170701))\n:");
			scanf("%s%s%s%s%s%s",p->vno,p->dname,p->pname,p->pno,p->no,p->date);  
			
			//�ȼ�鵥���Ƿ��֮ǰ���ظ�
			do
			{
				for (j = 0;j < (*n);j++)
					if (!strcmp(list[j].no, p->no))
					{
						printf("���󣺴��������Ѵ��ڣ����������봦�����ţ�\n");
						x = 1;
						break;
					}
				if (j == (*n))break;
				scanf("%s", p->no);
			} while (x);
			/////////////////////////////////

			//�ټ������Ĵ��������Ƿ�Ϸ�//////////////////////////////////////////////////
			while (check_no_num(p->date, 8))
			{
				printf("�����������벻�Ϸ������������봦������,��ʽΪ20170701��\n");
				scanf("%s", p->date);
			}
			while (check_data(p->date, 8))
			{
				printf("�����������벻�Ϸ������������봦������,����ʱ���Ƿ���ϳ���\n");
				scanf("%s", p->date);
			}
			////////////////////////////////////////////////

			//���Ϸ��Ű�ָ��ָ����һλ
			(*n)++;
            p++; 
	        printf("\n���������밴0��\n���������밴1��\n");
			scanf("%d", &i);
	}while(i); 

	display(list,*n);             //��ʾһ��
    printf("\n���������");
	printf("���س����أ�");
	getch();
}