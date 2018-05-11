// compute_path.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<queue>
using namespace std;

typedef int Vertex;

#define sumOfVertex 5
#define numOfSpecialVertex 4
int specialVertex[numOfSpecialVertex] = { 0,1,2,5 };
int Graph[sumOfVertex][sumOfVertex];
//定义链表节点////////////////////////////////////
typedef struct TreeNode *Position;
struct TreeNode {
	int vertex;
	int weight;
	Position Next;
};

//定义邻接表结构/////////////////////////////////////
typedef struct adjaceency_list *adjaceency;
struct adjaceency_list {
	int numVertex;      //大小
	Position* table;   //表地址
};

//邻接表初始化函数////////////////////////////////////
adjaceency initAdjaceency_list(int numVertex)
{
	//申请一个邻接表地址,给邻接表赋初值
	adjaceency adja = (adjaceency)malloc(sizeof(adjaceency_list));
	adja->numVertex = numVertex;
	if (adja == NULL)
		cout << "Error";

	//申请一个table地址
	adja->table = (Position*)malloc(sizeof(Position)*(adja->numVertex));
	if (adja->table == NULL)
		cout << "Error";

	//给邻接表每一个表项添加一个链表表头
	for (int i = 0; i < adja->numVertex; i++) {
		adja->table[i] = (Position)malloc(sizeof(TreeNode));
		if (adja->table[i] == NULL)
			cout << "Error";
		else {
			adja->table[i]->vertex = specialVertex[i];
			adja->table[i]->weight = 0;       //给每个邻接表项的链表头的权重设为0
			adja->table[i]->Next = NULL;
		}
	}
	return adja;
}

//邻接表的插入函数，制定一个顶点per_ver,把邻接的顶点aft_ver插入其后//////////////////////////////////
void Insert(adjaceency adja, Vertex per_ver, Vertex aft_ver, int weight)
{
	//申请一个链表节点地址
	Position inser = (Position)malloc(sizeof(TreeNode));
	if (inser == NULL)
		cout << "Error";

	//从头插入，修改指针
	inser->vertex = aft_ver;
	inser->weight = weight;                   //从per_ver指向aft_ver的权重
	inser->Next = adja->table[per_ver]->Next;
	adja->table[per_ver]->Next = inser;
}

void graphToAdja(adjaceency adja, int graph[sumOfVertex][sumOfVertex])
{
	for (int i = 0;i < adja->numVertex;i++)
	{

	}
}

int main()
{
	adjaceency adja = initAdjaceency_list(numOfSpecialVertex);
    return 0;
}

