//���ڲ���Tsp.c�ĺ���
#include<stdio.h>
#include <time.h>  

//���漸������������Tsp.c�ж���
extern int* x;  
extern int* bestx;
extern int* bestw;
FILE *fp;

void Tsp(int**, int, int);             //��ٷ�����Tsp
int** CreateGraph(int n);              //ͼ�þ����ʾ���˺�����������ͼ�Ķ�����n�Զ�����һ��ͼ�Ķ�ά����
void printGraph(int**g, int n);        //��ӡͼ�Ķ�ά����ĺ���
//int k[5][5] = { { 0,3,3,2,6 },{ 3,0,7,3,2 },{ 3,7,0,2,5 },{ 2,3,2,0,3 },{ 6,2,5,3,0 } };

int main()
{
	int** g;
	int n;

	if ((fp = fopen("result.txt", "w")) == NULL) {
		printf("File cannot be opened/n");
		exit();
	}

	printf("��������еĸ���n�Գ�ʼ��һ������ͼͼ�ľ���,�ߵ�Ȩ���������:\n");
	scanf("%d", &n);
	clock_t start, finish;                //���ڼ�ʱ�ı���
	g=CreateGraph(n);                     //���ݶ�����n����һ��ͼg
	printGraph(g, n);                     //��ӡ��ͼ�Ķ�ά����

	x = (int*)malloc(sizeof(int)*n);      //����x�����ڴ��һ�����е���ʱ����
	for (int i = 0;i < n;i++)             //��ʼ��һ������
		x[i] = i;
	bestx = (int*)malloc(sizeof(int)*n);  //���������ڱ�������·�����Ǹ�����

	printf("���г���(0,1,...n-1)��ȫ���������ɵ�·���������������ʾ��\n");
	fprintf(fp,"���г���(0,1,...n-1)��ȫ���������ɵ�·���������������ʾ��\n");
	start = clock();                      //��ʼ��ʱ
	Tsp(g, n, 1);                         //��ټ���Tsp
	finish = clock();                     //������ʱ

	printf("\n����ʱ���ǣ�%ld����\n", finish - start);     //��ӡ����ʱ��
	fprintf(fp,"\n����ʱ���ǣ�%ld����\n", finish - start);
	printf("����·���е���ʹ����ǣ�%d\n\n", bestw);                //��ӡ����·���е���ʹ���
	fprintf(fp,"����·���е���ʹ����ǣ�%d\n\n", bestw);

	for (int i = 0;i < n;i++)                       //�������ͷ�������Ŀռ�
		free(g[i]);
	free(g);
	free(x);
	free(bestx);

	if (fclose(fp) != 0) {
		printf("File cannot be closed/n");
		exit(1);
	}
	return 0;
}

int** CreateGraph(int n)            //�˺�����������ͼ�Ķ�����n�Զ�����һ��ͼ�Ķ�ά����
{
	int i, j;
	int** g = (int**)malloc(sizeof(int*)*n);      //����ռ�
	for(int i=0;i<n;i++)
		g[i]= (int*)malloc(sizeof(int)*n);
	
	srand((unsigned)time(NULL));                  //�������������
	for(i=0;i<n;i++)
		for (j = i + 1;j < n;j++)
		{
			g[i][j] = g[j][i] = (rand() % (2*n)) + 1;      //������һ������ͼ��������һ���Գƾ���
			                                               //g[i][j]Ϊ����i������j��Ȩ�أ���rand()�������������ΧΪ1��2n,nΪ������
		}
	for (i = 0;i < n;i++)                                  //�Խ����ϵ�Ȩ��ֵΪ0
		g[i][i] = 0;
	return g;
}

void printGraph(int**g, int n)
{
	int i, j;
	printf("���й�ģΪ%d��һ��ͼ�ľ���������ʾ��\n",n);
	fprintf(fp,"���й�ģΪ%d��һ��ͼ�ľ���������ʾ��\n", n);
	for (i = 0;i < n;i++)
	{
		for (j = 0;j < n;j++)
		{
			printf("%d\t", g[i][j]);
			fprintf(fp,"%d\t", g[i][j]);
		}
			
		printf("\n");
		fprintf(fp,"\n");
	}
	printf("\n");
	fprintf(fp, "\n");
}