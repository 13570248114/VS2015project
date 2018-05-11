// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<math.h>
using namespace std;

#define numOfVertex 3
#define numOfSpecialV 2
int spacialVertexList = { 1 };
#define Inf 65530
typedef int Vertex;
int graph[numOfVertex][numOfVertex];


int C(int k, int n)         //计算组合数
{
	int* result = (int*)malloc(sizeof(int)*(n + 1));
	result[0] = 1;
	result[1] = 1;
	for (int i = 2;i <= n;i++)
		result[i] = i*result[i - 1];

	int Result = result[n] / (result[k] * result[n - k]);
	free(result);

	return Result;
}

int* sumC(int n)   //计算从组合数C(0,n)到C(k,n)的和
{
	int* sumCC = (int*)malloc(sizeof(int)*(n + 1));
	sumCC[0] = C(0, n);
	for (int i = 1;i <= n;i++)
		sumCC[i] = sumCC[i - 1] + C(i, n);
	return sumCC;
}

struct newVertex
{
	Vertex ver;
	int numOfLayer;
};
typedef newVertex* newVertexList;

struct VertexList
{
	int numOfVertexs;
	int numOfNewVertex;
	newVertexList List;
};
typedef VertexList* vertexList;

vertexList initVertexList(int numOfVertexs, int specialPointNum,int* sumCC)
{
	vertexList vertexlist = (vertexList)malloc(sizeof(VertexList));
	vertexlist->numOfVertexs = numOfVertexs;
	vertexlist->numOfNewVertex= vertexlist->numOfVertexs*pow(2, specialPointNum);
	vertexlist->List = (newVertexList)malloc(sizeof(newVertex)*vertexlist->numOfNewVertex);
	
	int layer = 0;

	for (int i = 0;i < vertexlist->numOfNewVertex;i++)
	{
		vertexlist->List[i].ver = i%vertexlist->numOfVertexs;
		
		if (i/ vertexlist->numOfVertexs+1>sumCC[layer])
			layer++;
		vertexlist->List[i].numOfLayer = layer;
	}

	return vertexlist;
}


struct newTable
{
	int numOfVertexs;
	int** table;
};
typedef newTable* newTablePointer;

newTablePointer initNewTable(int graph[numOfVertex][numOfVertex], int numOfVertexs,int specialPointNum, vertexList vertexlist)
{
	newTablePointer TablePointer = (newTablePointer)malloc(sizeof(newTable));
	TablePointer->numOfVertexs = numOfVertexs*pow(2, specialPointNum);
	TablePointer->table = (int**)malloc(sizeof(int*)*TablePointer->numOfVertexs);
	for (int i = 0;i < TablePointer->numOfVertexs;i++)
		TablePointer->table[i] = (int*)malloc(sizeof(int)*TablePointer->numOfVertexs);

	for(int i=0;i<TablePointer->numOfVertexs;i++)
		for (int j = 0;j < TablePointer->numOfVertexs;j++)
		{
			TablePointer->table[i][j] = Inf;
		}
	for (int k = 0;k < TablePointer->numOfVertexs;k = k + numOfVertexs)
		for (int i = k, icount = 0;icount < numOfVertexs;icount++, i++)
			for (int j = k, jcount = 0;jcount < numOfVertexs;jcount++, j++)
				TablePointer->table[i][j] = graph[vertexlist->List[i].ver][vertexlist->List[j].ver];

	//for (int Layer = 1;Layer <= specialPointNum;Layer++)
		//for (int num = 0;num < C(num, specialPointNum);num++)
			
	return TablePointer;
}

void print(newTablePointer TablePointer)
{
	for (int i = 0;i < TablePointer->numOfVertexs;i++)
	{
		for (int j = 0;j < TablePointer->numOfVertexs;j++)
			cout << TablePointer->table[i][j] << '\t';
		cout << endl;
	}
	cout << endl;
}


int main()
{
	int graph[numOfVertex][numOfVertex] = { {0,1,1},{1,0,1},{1,1,0} };
	int* sumCC = sumC(numOfSpecialV);
	vertexList vertexlist = initVertexList(numOfVertex, numOfSpecialV, sumCC);
	newTablePointer TablePointer = initNewTable(graph, numOfVertex, numOfSpecialV, vertexlist);
	print(TablePointer);
    return 0;
}

