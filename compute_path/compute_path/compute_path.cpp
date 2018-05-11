// compute_path.cpp : �������̨Ӧ�ó������ڵ㡣
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
//��������ڵ�////////////////////////////////////
typedef struct TreeNode *Position;
struct TreeNode {
	int vertex;
	int weight;
	Position Next;
};

//�����ڽӱ�ṹ/////////////////////////////////////
typedef struct adjaceency_list *adjaceency;
struct adjaceency_list {
	int numVertex;      //��С
	Position* table;   //���ַ
};

//�ڽӱ��ʼ������////////////////////////////////////
adjaceency initAdjaceency_list(int numVertex)
{
	//����һ���ڽӱ��ַ,���ڽӱ���ֵ
	adjaceency adja = (adjaceency)malloc(sizeof(adjaceency_list));
	adja->numVertex = numVertex;
	if (adja == NULL)
		cout << "Error";

	//����һ��table��ַ
	adja->table = (Position*)malloc(sizeof(Position)*(adja->numVertex));
	if (adja->table == NULL)
		cout << "Error";

	//���ڽӱ�ÿһ���������һ�������ͷ
	for (int i = 0; i < adja->numVertex; i++) {
		adja->table[i] = (Position)malloc(sizeof(TreeNode));
		if (adja->table[i] == NULL)
			cout << "Error";
		else {
			adja->table[i]->vertex = specialVertex[i];
			adja->table[i]->weight = 0;       //��ÿ���ڽӱ��������ͷ��Ȩ����Ϊ0
			adja->table[i]->Next = NULL;
		}
	}
	return adja;
}

//�ڽӱ�Ĳ��뺯�����ƶ�һ������per_ver,���ڽӵĶ���aft_ver�������//////////////////////////////////
void Insert(adjaceency adja, Vertex per_ver, Vertex aft_ver, int weight)
{
	//����һ������ڵ��ַ
	Position inser = (Position)malloc(sizeof(TreeNode));
	if (inser == NULL)
		cout << "Error";

	//��ͷ���룬�޸�ָ��
	inser->vertex = aft_ver;
	inser->weight = weight;                   //��per_verָ��aft_ver��Ȩ��
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

