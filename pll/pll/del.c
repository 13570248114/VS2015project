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
		printf("\n������Ҫɾ���Ĵ������ĵ���:");
		scanf("%s",no);

		for(i=0,p=list;i<*n;i++)             //������Ϣ�����Ҷ�Ӧ�����ɾ��
			if(!strcmp(no, (p+i)->no))
			{
				k=1;
				for (j = i;j < *n - 1;j++)
				{
					*(p + j) = *(p + j + 1);    //��ɾ�������������з����ǰ�ƶ�һ��λ��
				}
					
				(*n)--;
				printf("��ɾ��!\n");
				break;
			}
			if(!k)
				printf("\n�Ҳ���Ҫɾ���Ĵ�����!\n\n");
		
			printf("\n�Ƿ������ɾ����\nYES/1 or NO/0:\n");
			scanf("%d",&x);
			
	}while(x);

	display(list,*n);
	printf("�����������:");
	getch();
}