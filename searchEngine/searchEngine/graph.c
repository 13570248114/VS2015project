#include"graph.h"
#include<stdlib.h>
#include<string.h>

graph init_graph()
{
	graph g = (graph)malloc(sizeof(Graph));                                      //������ͼ������ռ�ͳ�ʼ���Ĳ���
	g->List_of_Urls = GetCollection();                                               //����url����
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
	urlNode* node = g->List_of_Urls->head;                                           //nodeΪurl�����ͷ���
	for (int i = 0;i < g->num_of_vertex; i++,node = node->next)             //��ÿһ�����㣬�����ļ����ݽ�������
	{
		//�򿪵�i���ڵ�����Ӧ��url�ļ�
		char file[20];
		num = 0;
		strcpy(file, node->url);
		strcat(file, t);
		if ((fp = fopen(file, "r")) == NULL)               //�򿪲������ɹ�
		{
			printf("%s can not be opened.\n",file);
			exit(1);                                                             //���������ִ��
		}

		//���ļ��ж�ȡ�ýڵ������ӵĽڵ�
		while (fscanf(fp, "%s", url) > 0)
		{
			if (url[0] == '#'&&num < 2)
				num++;                                               //2����#��֮�䣬���ַ�����ͷΪ��u��������Ч����
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

int outDegree(graph g, int vertex)                            //������Ϊvertex�ڵ�ĳ���
{
	int outDegree = 0;
	for (int j = 0;j < g->num_of_vertex;j++)
		if (g->adjmatrix[vertex][j] != 0)
			++outDegree;
	return outDegree !=0? outDegree:g->num_of_vertex;
}

void freeGraph(graph g)                                           //�ͷſռ�
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