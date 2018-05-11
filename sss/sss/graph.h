#ifndef GRAPH_H
#define GRAPH_H
#include"readData.h"

typedef struct {                                    //Graph structure, adjacency matrix representation
	urlList List_of_Urls;
	int num_of_vertex;                            //The number of vertices
	int** adjmatrix;                                 //Adjacency matrix, with the label to record the vertices on the map, the label is 0 Corresponding to the url List_of_Urls head node, labeled n-1 corresponds to the last node, and so on
}Graph;

typedef Graph* graph;

graph init_graph();                                 //Initialization diagram
int getVertexNum(graph g, char* url);     //Obtain the url corresponding to the node label
graph link_graph(graph g);                      //According to the contents of the file to connect the vertices of the graph
int outDegree(graph g, int vertex);            //Find vertices labeled vertex
void freeGraph(graph g);
#endif // !GRAPH_H

