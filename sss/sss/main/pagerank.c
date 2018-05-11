#include"graph.h"
#include"readData.h"
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdio.h>

typedef struct {                      //In the last output content, need to record the information each line
	char url[20];
	int out_degree;
	double PR;
}Page;

void printPR(Page* p, int n)                      //Print PageRank to terminal and file
{
	FILE *fp;
	int i;
	if ((fp = fopen("pagerankList.txt", "w")) == NULL)               //If open operation is not successful,the execution
	{
		printf("pagerankList.txt can not be opened.\n");
		exit(1);                                                             //End the implementation of the program
	}
	for (i = 0;i < n;i++)
	{
		printf("%s, %d, %.7f\n", p[i].url, p[i].out_degree, p[i].PR);
		fprintf(fp,"%s, %d, %.7f\n", p[i].url, p[i].out_degree, p[i].PR);
	}
	printf("\n");
}

Page* calculatePageRank(double d, double diffPR, int maxIterations)
{
	int n,i,j,temp;
	int** adjmatrix;
	double *oldPR,*newPR;
	int* out_degree,*sort;
	int  iteration = 0;
	double diff = diffPR, PRL = 0;
	urlNode* node;
	Page *pr,*PageRank;
	graph g = init_graph();
	g = link_graph(g);
	n = g->num_of_vertex;
	adjmatrix = g->adjmatrix;

	oldPR = (double*)malloc(sizeof(double)*n);                       //Used to record the value of PR in the previous iteration
	newPR = (double*)malloc(sizeof(double)*n);                      //Used to record the value of PR in this iteration
	out_degree = (int*)malloc(sizeof(int)*n);                                 //Used to record the out degree of each node
	for (i = 0;i < n;++i)
	{
		oldPR[i] = newPR[i] = (double)1.0 / n;
		out_degree[i] = outDegree(g, i);
	}
	
	while (iteration < maxIterations&&diff >= diffPR)              //PageRank algorithm
	{
		++iteration;
		for (i = 0;i < n;++i)
		{
			newPR[i] = (1 - d) / n;
			PRL = 0;
			for (j = 0;j < n;j++)
				if (adjmatrix[j][i] != 0)
					PRL += oldPR[j] / out_degree[j];
			newPR[i] += d*PRL;
		}
		diff = 0;
		for (i = 0;i < n;++i)
		{
			diff += fabs(newPR[i] - oldPR[i]);
			oldPR[i] = newPR[i];
		}
	}

	pr = (Page*)malloc(sizeof(Page)*n);          //the Structure array to store unordered pages
	node = g->List_of_Urls->head;
	for (i = 0;i < n;++i)
	{
		pr[i].PR = newPR[i];
		pr[i].out_degree = out_degree[i];
		strcpy(pr[i].url, node->url);
		node = node->next;
	}

	sort = (int*)malloc(sizeof(int)*n);                //The pages are sorted according to the value of pr [i] .PR, this sort does not move the value of pr [i] .PR, only the position of the sorted pr [i] .PR
	for (i = 0;i < n;i++)
		sort[i] = i;
	for (i = 0;i < n - 1;i++)
	{
		for (j = 0;j < n - i - 1;j++)
		{
			if (pr[sort[j]].PR < pr[sort[j+1]].PR)
			{
				temp = sort[j];
				sort[j] = sort[j + 1];
				sort[j + 1] = temp;
			}
		}
	}

	PageRank = (Page*)malloc(sizeof(Page)*n);    //According to the above sorting results, in the new storage area in order to store the pages
	for (i = 0;i < n;i++)
	{
		PageRank[i].out_degree = pr[sort[i]].out_degree;
		PageRank[i].PR = pr[sort[i]].PR;
		strcpy(PageRank[i].url, pr[sort[i]].url);
	}

	printPR(PageRank, n);                                           //Print to file
	free(pr);                                                               //free space
	free(out_degree);
	free(newPR);
	free(oldPR);
	freeGraph(g);
	return PageRank;
}


int main(int argc,char *argv[])
{
	double d,diffPR;
	int iters;
	if (argc != 4)
		printf("Input error!");
	else
	{
		d = atof(argv[1]);
		diffPR = atof(argv[2]);
		iters= atoi(argv[3]);
		calculatePageRank(d, diffPR, iters);
	}

}



