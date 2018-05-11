#ifndef GRAPH_H
#define GRAPH_H
#include"readData.h"

typedef struct {                                    //图结构，邻接矩阵表示
	urlList List_of_Urls;                            //储存url的链表
	int num_of_vertex;                            //顶点的数量
	int** adjmatrix;                                 //邻接矩阵，用标号来记录图上的顶点，标号为0对应的是上述url的链表List_of_Urls头节点，标号为n-1对应最后一个节点，以此类推
}Graph;

typedef Graph* graph;

graph init_graph();                                 //初始化图
int getVertexNum(graph g, char* url);     //获得url所对应的节点标号
graph link_graph(graph g);                      //根据文件内容连接图上顶点
int outDegree(graph g, int vertex);            //求标号为vertex的顶点的出度
void freeGraph(graph g);
#endif // !GRAPH_H

