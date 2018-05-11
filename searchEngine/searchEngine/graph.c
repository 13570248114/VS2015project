#include"graph.h"
#include<stdlib.h>
#include<string.h>

graph init_graph()
{
	graph g = (graph)malloc(sizeof(Graph));                                      //以下是图的申请空间和初始化的操作
	g->List_of_Urls = GetCollection();                                               //储存url链表
	g->num_of_vertex = g->List_of_Urls->num_of_node;
	g->adjmatrix = (int**)malloc(sizeof(int*)*g->num_of_vertex);
	for (int i = 0;i < g->num_of_vertex;i++)
		g->adjmatrix[i] = (int*)malloc(sizeof(int)*g->num_of_vertex);
	for (int i = 0;i < g->num_of_vertex;i++)
		for (int j = 0;j < g->num_of_vertex;j++)
			g->adjmatrix[i][j] = 0;
	return g;
}


graph link_graph(graph g)
{
	char url[20];
	char *t = ".txt";
	FILE *fp;
	int num = 0;
	urlNode* node = g->List_of_Urls->head;                                           //node为url链表的头结点
	for (int i = 0;i < g->num_of_vertex; i++,node = node->next)             //对每一个顶点，根据文件内容建立连接
	{
		//打开第i个节点所对应的url文件
		char file[20];
		num = 0;
		strcpy(file, node->url);
		strcat(file, t);
		if ((fp = fopen(file, "r")) == NULL)               //打开操作不成功
		{
			printf("%s can not be opened.\n",file);
			exit(1);                                                             //结束程序的执行
		}

		//从文件中读取该节点所连接的节点
		while (fscanf(fp, "%s", url) > 0)
		{
			if (url[0] == '#'&&num < 2)
				num++;                                               //2个‘#’之间，且字符串开头为‘u’的是有效内容
			else if (url[0] == 'u'&&num < 2)
			{
				int j = getVertexNum(g, url);
				g->adjmatrix[i][j] = 1;
			}
			else if (num == 2)
				break;
			else
				continue;
		}
	}
	return g;
}

int outDegree(graph g, int vertex)                            //计算标号为vertex节点的出度
{
	int outDegree = 0;
	for (int j = 0;j < g->num_of_vertex;j++)
		if (g->adjmatrix[vertex][j] != 0)
			++outDegree;
	return outDegree !=0? outDegree:g->num_of_vertex;
}

void freeGraph(graph g)                                           //释放空间
{
	freeList(g->List_of_Urls);
	for (int i = 0;i < g->num_of_vertex;i++)
		free(g->adjmatrix[i]);
	free(g->adjmatrix);
}

int getVertexNum(graph g, char* url)
{
	urlNode* node = g->List_of_Urls->head;
	while (strcmp(node->url, url) != 0)
		node = node->next;
	return node->vertex;
}