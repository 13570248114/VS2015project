//用于测试Tsp.c的函数
#include<stdio.h>
#include <time.h>  

//下面几个变量都是在Tsp.c中定义
extern int* x;  
extern int* bestx;
extern int* bestw;
FILE *fp;

void Tsp(int**, int, int);             //穷举法计算Tsp
int** CreateGraph(int n);              //图用矩阵表示，此函数根据输入图的顶点数n自动生成一个图的二维矩阵
void printGraph(int**g, int n);        //打印图的二维矩阵的函数
//int k[5][5] = { { 0,3,3,2,6 },{ 3,0,7,3,2 },{ 3,7,0,2,5 },{ 2,3,2,0,3 },{ 6,2,5,3,0 } };

int main()
{
	int** g;
	int n;

	if ((fp = fopen("result.txt", "w")) == NULL) {
		printf("File cannot be opened/n");
		exit();
	}

	printf("请输入城市的个数n以初始化一个无向图图的矩阵,边的权重随机决定:\n");
	scanf("%d", &n);
	clock_t start, finish;                //用于计时的变量
	g=CreateGraph(n);                     //根据顶点数n创建一个图g
	printGraph(g, n);                     //打印该图的二维矩阵

	x = (int*)malloc(sizeof(int)*n);      //数组x是用于存放一个排列的临时变量
	for (int i = 0;i < n;i++)             //初始化一个排列
		x[i] = i;
	bestx = (int*)malloc(sizeof(int)*n);  //该数组用于保存最优路径的那个排列

	printf("所有城市(0,1,...n-1)的全排列所构成的路径及其代价如下所示：\n");
	fprintf(fp,"所有城市(0,1,...n-1)的全排列所构成的路径及其代价如下所示：\n");
	start = clock();                      //开始计时
	Tsp(g, n, 1);                         //穷举计算Tsp
	finish = clock();                     //结束计时

	printf("\n计算时间是：%ld毫秒\n", finish - start);     //打印计算时间
	fprintf(fp,"\n计算时间是：%ld毫秒\n", finish - start);
	printf("所有路径中的最低代价是：%d\n\n", bestw);                //打印所有路径中的最低代价
	fprintf(fp,"所有路径中的最低代价是：%d\n\n", bestw);

	for (int i = 0;i < n;i++)                       //下面是释放所申请的空间
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

int** CreateGraph(int n)            //此函数根据输入图的顶点数n自动生成一个图的二维矩阵
{
	int i, j;
	int** g = (int**)malloc(sizeof(int*)*n);      //申请空间
	for(int i=0;i<n;i++)
		g[i]= (int*)malloc(sizeof(int)*n);
	
	srand((unsigned)time(NULL));                  //产生随机数种子
	for(i=0;i<n;i++)
		for (j = i + 1;j < n;j++)
		{
			g[i][j] = g[j][i] = (rand() % (2*n)) + 1;      //由于是一个无向图，所以是一个对称矩阵
			                                               //g[i][j]为顶点i到顶点j的权重，用rand()产生，随机数范围为1～2n,n为顶点数
		}
	for (i = 0;i < n;i++)                                  //对角线上的权重值为0
		g[i][i] = 0;
	return g;
}

void printGraph(int**g, int n)
{
	int i, j;
	printf("城市规模为%d的一个图的矩阵如下所示：\n",n);
	fprintf(fp,"城市规模为%d的一个图的矩阵如下所示：\n", n);
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