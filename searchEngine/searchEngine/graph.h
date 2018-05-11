#ifndef GRAPH_H
#define GRAPH_H
#include"readData.h"

typedef struct {                                    //ͼ�ṹ���ڽӾ����ʾ
	urlList List_of_Urls;                            //����url������
	int num_of_vertex;                            //���������
	int** adjmatrix;                                 //�ڽӾ����ñ������¼ͼ�ϵĶ��㣬���Ϊ0��Ӧ��������url������List_of_Urlsͷ�ڵ㣬���Ϊn-1��Ӧ���һ���ڵ㣬�Դ�����
}Graph;

typedef Graph* graph;

graph init_graph();                                 //��ʼ��ͼ
int getVertexNum(graph g, char* url);     //���url����Ӧ�Ľڵ���
graph link_graph(graph g);                      //�����ļ���������ͼ�϶���
int outDegree(graph g, int vertex);            //����Ϊvertex�Ķ���ĳ���
void freeGraph(graph g);
#endif // !GRAPH_H

