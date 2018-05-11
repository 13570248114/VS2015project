//穷举法计算旅行商问题的函数
#include<stdio.h>
int w,t;           //w路径代价的临时变量，t是用于交换的临时变量
int* bestx;        //存储最优路径的数组
int* x;            //存储路径的数组
int bestw=65535;   //用于存放最低代价的全局变量
extern FILE *fp;
void Tsp(int **g, int n, int s)            //递归实现全排列
{
	if (s == n)                           //如果s=n说明x[0]...x[n-1]已经是一个排列
	{
		w = 0;                            //w用于存放该排列下的路径代价和
		printf("bestx:");
		for (int i = 0;i < n;i++)         //计算该排列下的路径代价和
		{
			bestx[i] = x[i];
			printf("%d ", bestx[i]);
			fprintf(fp, "%d ", bestx[i]);

			if (i < n - 1)                 //计算路径x[0],x[1]...x[n-1],x[0]的路径代价和
				w += g[x[i]][x[i + 1]];   
			else
				w += g[x[i]][x[0]];          
		}
       
		printf("w:%d\n", w);               //打印该路径的代价
		fprintf(fp,"w:%d\n", w);
		if (bestw > w)                     //检查是否比当前的最小代价要小，是的话则更新最小代价
			bestw = w;
	}
	else
	{
		for (int i = s;i < n;i++)          //逐层递归产生全排列，产生排列的思想见说明文档
		{
			t = x[i];                      //交换
			x[i] = x[s];
			x[s] = t;

			Tsp(g, n, s + 1);              //递归下一层

			t = x[i];                      //交换回来，保证每一层递归后保持上一层的顺序
			x[i] = x[s];
			x[s] = t;
		}
	}
}