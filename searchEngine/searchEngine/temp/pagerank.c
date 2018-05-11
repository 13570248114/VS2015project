#include"graph.h"
#include"readData.h"
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdio.h>

typedef struct {                      //最后输出内容中，每行要记录的信息
	char url[20];
	int out_degree;
	double PR;
}Page;

void printPR(Page* p, int n)                      //打印PageRank到终端和文件
{
	FILE *fp;
	if ((fp = fopen("pagerankList.txt", "w")) == NULL)               //打开操作不成功
	{
		printf("pagerankList.txt can not be opened.\n");
		exit(1);                                                             //结束程序的执行
	}
	for (int i = 0;i < n;i++)
	{
		printf("%s, %d, %.7f\n", p[i].url, p[i].out_degree, p[i].PR);
		fprintf(fp,"%s, %d, %.7f\n", p[i].url, p[i].out_degree, p[i].PR);
	}
	printf("\n");
}

Page* calculatePageRank(double d, double diffPR, int maxIterations)
{
	graph g = init_graph();
	g = link_graph(g);
	int n = g->num_of_vertex;
	int** adjmatrix = g->adjmatrix;

	double* oldPR = (double*)malloc(sizeof(double)*n);                       //用来记录上一轮迭代中PR的值
	double* newPR = (double*)malloc(sizeof(double)*n);                      //用来记录本轮迭代中PR的值
	int* out_degree = (int*)malloc(sizeof(int)*n);                                 //用来记录每个节点的出度
	for (int i = 0;i < n;++i)
	{
		oldPR[i] = newPR[i] = (double)1.0 / n;
		out_degree[i] = outDegree(g, i);
	}
	int  iteration = 0;
	double diff = diffPR;
	

	while (iteration < maxIterations&&diff >= diffPR)              //PageRank算法
	{
		++iteration;
		for (int i = 0;i < n;++i)
		{
			newPR[i] = (1 - d) / n;
			double PRL = 0;
			for (int j = 0;j < n;j++)
				if (adjmatrix[j][i] != 0)
					PRL += oldPR[j] / out_degree[j];
			newPR[i] += d*PRL;
		}
		diff = 0;
		for (int i = 0;i < n;++i)
		{
			diff += fabs(newPR[i] - oldPR[i]);
			oldPR[i] = newPR[i];
		}
	}

	Page* pr = (Page*)malloc(sizeof(Page)*n);          //未排序的pages
	urlNode* node = g->List_of_Urls->head;
	for (int i = 0;i < n;++i)
	{
		pr[i].PR = newPR[i];
		pr[i].out_degree = out_degree[i];
		strcpy(pr[i].url, node->url);
		node = node->next;
	}

	int* sort = (int*)malloc(sizeof(int)*n);                //对pages根据pr[i].PR的值进行排序，此次排序不移动pr[i].PR的值，只计算排序后pr[i].PR的位置
	for (int i = 0;i < n;i++)
		sort[i] = i;
	for (int i = 0;i < n - 1;i++)
	{
		for (int j = 0;j < n - i - 1;j++)
		{
			if (pr[sort[j]].PR < pr[sort[j+1]].PR)
			{
				int temp = sort[j];
				sort[j] = sort[j + 1];
				sort[j + 1] = temp;
			}
		}
	}

	Page* PageRank = (Page*)malloc(sizeof(Page)*n);    //根据上面的排序结果，在新的储存区域按序存放pages
	for (int i = 0;i < n;i++)
	{
		PageRank[i].out_degree = pr[sort[i]].out_degree;
		PageRank[i].PR = pr[sort[i]].PR;
		strcpy(PageRank[i].url, pr[sort[i]].url);
	}

	printPR(PageRank, n);                                           //打印到文件
	free(pr);                                                               //释放空间
	free(out_degree);
	free(newPR);
	free(oldPR);
	freeGraph(g);
	return PageRank;
}


int main(int argc,char *argv[])
{
	if (argc != 4)
		printf("Input error!");
	else
	{
		double d = atof(argv[1]);
		double diffPR = atof(argv[2]);
		int  iters= atoi(argv[3]);
		calculatePageRank(d, diffPR, iters);
	}
	
}



