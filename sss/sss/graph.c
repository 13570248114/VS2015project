#include"graph.h"
#include<stdlib.h>
#include<string.h>

graph init_graph()
{
	int i,j;
	graph g = (graph)malloc(sizeof(Graph));                                      //The following is a graph of the application space and initialize the operation
	g->List_of_Urls = GetCollection();                                               //Save url list
	g->num_of_vertex = g->List_of_Urls->num_of_node;
	g->adjmatrix = (int**)malloc(sizeof(int*)*g->num_of_vertex);
	for (i = 0;i < g->num_of_vertex;i++)
		g->adjmatrix[i] = (int*)malloc(sizeof(int)*g->num_of_vertex);
	for (i = 0;i < g->num_of_vertex;i++)
		for (j = 0;j < g->num_of_vertex;j++)
			g->adjmatrix[i][j] = 0;
	return g;
}


graph link_graph(graph g)
{
	char url[20];
	char *t = ".txt";
	FILE *fp;
	int num = 0,i,j;
	urlNode* node = g->List_of_Urls->head;                                           //node is the head node of the url list
	for (i = 0;i < g->num_of_vertex; i++,node = node->next)             //For each vertex, create a connection based on the contents of the file
	{
		//Open the i node corresponding url file
		char file[20];
		num = 0;
		strcpy(file, node->url);
		strcat(file, t);
		if ((fp = fopen(file, "r")) == NULL)               //Open operation is not successful
		{
			printf("%s can not be opened.\n",file);
			exit(1);                                                             //End the implementation of the program
		}

		//Read from the file the node to which the node is attached
		while (fscanf(fp, "%s", url) > 0)
		{
			if (url[0] == '#'&&num < 2)
				num++;                                               //2 '#', and the beginning of the string 'u' is a valid content
			else if (url[0] == 'u'&&num < 2)
			{
				j = getVertexNum(g, url);
				g->adjmatrix[i][j] = 1;
			}
			else if (num == 2)
				break;
			else
				continue;
		}
		fclose(fp);
	}
	return g;
}

int outDegree(graph g, int vertex)                            //Calculate the out-degree of the node labeled vertex
{
	int outDegree = 0,j;
	for (j = 0;j < g->num_of_vertex;j++)
		if (g->adjmatrix[vertex][j] != 0)
			++outDegree;
	return outDegree !=0? outDegree:g->num_of_vertex;            //If the exit is 0, then the number of exits for the vertices
}

void freeGraph(graph g)                                           //free
{
	int i;
	freeList(g->List_of_Urls);
	for (i = 0;i < g->num_of_vertex;i++)
		free(g->adjmatrix[i]);
	free(g->adjmatrix);
	free(g);
}

int getVertexNum(graph g, char* url)                          //According to the url to find the vertex's label
{
	urlNode* node = g->List_of_Urls->head;
	while (strcmp(node->url, url) != 0)
		node = node->next;
	return node->vertex;
}
