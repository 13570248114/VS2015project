// new_comute2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include <fstream>  //�ļ����⺯��
#include<math.h>
using namespace std;

#define Inf 65530
int** dist;

/////////////////////�ڽӱ����ض���//////////////////////
typedef struct EdgeNode *position;
typedef struct Led_table* Table;


struct EdgeNode     //�߱��� 
{
	int adjvex;    // �ڽӵ���,�洢�ö����Ӧ���±� 
	int weight;     // ��Ӧ�ߵ�Ȩֵ
	position next; // ����,ָ����һ���ڽӵ�
	bool vertexOrblock;                   //1����ָ��飬0����ָ����ͨ���
};

struct Led_table       // �ڽӱ�ṹ 
{
	int data;                //�ڽӱ�Ĵ�С
	position *firstedge;       //�߱�ͷָ�룬�������Ϊ����
};
/////////////////////////////////////////////////////////////////////
struct PointUnion
{
	int* flag;
	Table graph;
};
typedef PointUnion* PointUnions;

struct PointUnionList
{
	int num;
	PointUnions PointU;
};
typedef PointUnionList* PointUnionLists;

struct node {
	int block;
	int number;
};
node*** pre;

PointUnionLists initPointUnion(int numOfVertexs, int specialPointNum)
{
	PointUnionLists List = (PointUnionLists)malloc(sizeof(PointUnionList));
	List->num = pow(2, specialPointNum);
	List->PointU = (PointUnions)malloc(sizeof(PointUnion)*List->num);
	for (int i = 0;i < List->num;i++)
	{
		List->PointU[i].flag = (int*)malloc(sizeof(int)*specialPointNum);
		for (int j = 0;j < specialPointNum;j++)
			List->PointU[i].flag[j] = 0;

		List->PointU[i].graph= static_cast<Table> (malloc(sizeof(struct Led_table)));
		List->PointU[i].graph->data = numOfVertexs;
		List->PointU[i].graph->firstedge = static_cast<position*>(malloc(sizeof(position)*(List->PointU[i].graph->data)));

		for (int j = 0; j != List->PointU[i].graph->data; ++j)
		{
			List->PointU[i].graph->firstedge[j] = (position)(malloc(sizeof(EdgeNode)));   //����һ���ڵ�
			if (List->PointU[i].graph->firstedge[j] == NULL)
			{
				cout << "out of space!!!";
			}
			List->PointU[i].graph->firstedge[j]->adjvex = j;   //�˲����ڴ�ʱû������
			List->PointU[i].graph->firstedge[j]->weight = 0;   //�˲����ڴ�ʱû������
			List->PointU[i].graph->firstedge[j]->next = NULL;
			List->PointU[i].graph->firstedge[j]->vertexOrblock = 0;
		}
	}
	return List;
}

void Insert(Table table1, int v, int w, int weig, bool vertexOrblock)   //��ʾ����һ����Ϊ<v,w>,��Ȩ��Ϊweig����ͷ����
{
	position p = static_cast<position>(malloc(sizeof(EdgeNode)));   //����һ���ڵ�
	if (p == NULL)
	{
		cout << "out of space!!!";
	}
	p->adjvex = w;
	p->weight = weig;
	p->next = table1->firstedge[v]->next;
	p->vertexOrblock = vertexOrblock;
	table1->firstedge[v]->next = p;

}

void make_table(PointUnionLists List)
{
	int v, w, weight;
	ifstream infile;
	infile.open("E:\\project\\VS2015_project\\new_comute2\\data.txt", ios::in);   //���ļ���ָ���ļ�·��
	                         	//�������txt�ļ����ڽӱ�ֵ
	for (int i = 0;i < List->num;i++)
	{
		
		while (!infile.eof())            // ��δ���ļ�����һֱѭ�� 
		{
			infile >> v >> w >> weight;
			Insert(List->PointU[i].graph, v, w, weight,0);   //ͼΪ����ͼ�����˫�򶼸�ֵ
			Insert(List->PointU[i].graph, w, v, weight,0);
		}
		infile.seekg(0);
	}
	infile.close();   //�ر��ļ�
}


void link(PointUnionLists List, int* specialVertex, int specialPointNum)
{
	int numOfVertex = List->PointU->graph->data;
	for (int i = 0;i < List->num;i++)
	{
		int temp=i;
		for (int k = 0;k < specialPointNum;k++)
		{
			List->PointU[i].flag[k] = temp % 2;
			temp /= 2;
		}
	}
	
	for (int i = 0;i < List->num;i++)
	{
		for (int k = 0;k < specialPointNum;k++)
		{
			int temp = i;
			if (List->PointU[i].flag[k] == 0)
			{
				temp += pow(2, k);
				Insert(List->PointU[i].graph, specialVertex[k], temp, 0,1);   //ͼΪ����ͼ�����˫�򶼸�ֵ
				Insert(List->PointU[temp].graph, specialVertex[k], i, 0,1);
			}
		}
	}

}


/*
Table initTable(PointUnionLists List)
{
	Table newtable = static_cast<Table> (malloc(sizeof(struct Led_table)));
	newtable->data = List->PointU->graph->data*List->num;
	newtable->firstedge = (position*)malloc(sizeof(position)*newtable->data);
	for (int j = 0; j != newtable->data; ++j)
	{
		newtable->firstedge[j] = (position)(malloc(sizeof(EdgeNode)));   //����һ���ڵ�
		if (newtable->firstedge[j] == NULL)
		{
			cout << "out of space!!!";
		}
		newtable->firstedge[j]->adjvex = j;   //�˲����ڴ�ʱû������
		newtable->firstedge[j]->weight = 0;   //�˲����ڴ�ʱû������
		newtable->firstedge[j]->next = NULL;
		newtable->firstedge[j]->vertexOrblock = 0;
	}
	int s = 0;
	for (int i = 0;i < List->num;i++)
		for (int j = 0;j < List->PointU->graph->data;j++)
		{
			newtable->firstedge[s]->next = List->PointU[i].graph->firstedge[j]->next;
			s++;
		}
	return newtable;
}
*/

void computer_pre(int star, int Limit_num_nodes, PointUnionLists List,int numOfSpecialVer)    //����pre����starΪ���,Limit_num_nodesΪ���ƵĽڵ�����table1λ�ڽӱ�
{
	
	int Num_nodes = List->PointU->graph->data*List->num;
	int numOfVertex = List->PointU->graph->data;
	pre = static_cast<node***>(malloc(sizeof(node**)*(Limit_num_nodes - 1)));   //������ƵĽڵ���ΪLimit_num_nodes����ôpre�����Ӧ����Limit_num_nodes - 1��
	for (int i = 0; i != Limit_num_nodes - 1; ++i)
	{
		pre[i] = static_cast<node**>(malloc(sizeof(node*)*List->num));   //��ÿһ��pre��������Num_nodes��λ��
		for (int j = 0;j < List->num;j++)
		{
			pre[i][j]= static_cast<node*>(malloc(sizeof(node)*List->PointU->graph->data));
		}
	}
	for (int m = 0; m != Limit_num_nodes - 1; ++m)
	{
		for (int i = 0; i < List->num; ++i) //Num_nodesΪ�ܵĽڵ���
		{
			for (int j = 0;j < List->PointU->graph->data;j++)
			{
				pre[m][i][j].block = 0;                                            //��i���j����
				pre[m][i][j].number= star;
			}
		}
	}
	dist = static_cast<int**>(malloc(sizeof(int*)*List->num));   //dist[j]��¼��㵽�ڵ�j�ĵ�ǰ���·��
	int** pdist = static_cast<int**>(malloc(sizeof(int*)*List->num));  //pdist�����¼��һ��ѭ��dist�����ֵ
	for (int i = 0; i < List->num; ++i)
	{
		dist[i]= static_cast<int*>(malloc(sizeof(int)*List->PointU->graph->data));
		pdist[i] = static_cast<int*>(malloc(sizeof(int)*List->PointU->graph->data));
	}


	for (int i = 0; i < List->num; ++i) //Num_nodesΪ�ܵĽڵ���
		for (int j = 0;j < List->PointU->graph->data;j++)  //���Ȱ����·��������Ϊ�����
		{
			dist[i][j] = Inf;      //ȫ����ʼ��
			pdist[i][j] = Inf;
		}

	//�����������ڽӱ�����ʼ��dist��pdist
	position p = List->PointU->graph[0].firstedge[star]->next;  //����һ��λ��ָ����������ĵ�һ��Ԫ��
	while (p != NULL)
	{
		dist[0][p->adjvex] = p->weight;
		pdist[0][p->adjvex] = p->weight;
		p = p->next;
	}

	//������Ϊ�ؼ����룬�����ڽӱ����pre����
	for (int m = 1; m != Limit_num_nodes - 1; ++m)   //Limit_num_nodesΪ���ƵĽڵ���
	{
		for (int i = 0; i<List->num; ++i) //Num_nodesΪ�ܵĽڵ���
		{
			for (int j = 0;j < List->PointU->graph->data;j++)
			{
				position mp = List->PointU[i].graph->firstedge[j]->next;
				while (mp != NULL)
				{
					if (mp->vertexOrblock == 0)
					{
						if (dist[i][j] > pdist[i][mp->adjvex] + mp->weight)  //��������˵����ط�Ӧ����ͼ�����ڽӱ��������ǵ�ͼ������ģ�����Ҳ������ôд
						{
							dist[i][j] = pdist[i][mp->adjvex] + mp->weight;
							pre[m][i][j].number = mp->adjvex;
							pre[m][i][j].block = i;
						}
					}
					else
					{
						dist[mp->adjvex][j] = dist[i][j];
						pre[m][mp->adjvex][j].block= i;
						pre[m][i][j].number= j;
					}
					mp = mp->next;
				}
				
				if (dist[i][j] == pdist[i][j])
				{
					pre[m][i][j].block= pre[m - 1][i][j].block;
					pre[m][i][j].number = pre[m - 1][i][j].number;
				}
			}
		}
		for (int i = 0; i < List->num; ++i) 
			for (int j = 0;j < List->PointU->graph->data;j++) 
		             pdist[i][j] = dist[i][j]; // �˴�Ϊ��dist��ֵȫ������pdist
	}
	//delete dist;    //�ͷ��ڴ�
	//delete pdist;

}

void printf_weight(node star, node end)   //���star���ڵ�i�����·��
{
	cout << "the shortest path of the node " << end.number << " from the node " << star.number<< " is " << dist[end.block][end.number] << endl;
}


void printf_path(node star, node end, int n)  //��ӡ�����s���ڵ�i�����ƽڵ���Ϊk�����·����nһ��Ҫ��Ϊ���ƽڵ���-1
{
	n--;
	if (end.block != star.block&&end.number != star.number)   //sΪ���
	{
		printf_path(star, pre[n][end.block][end.number], n); //kΪ���ƵĽڵ���
		cout << "->";
	}
	cout << "v" << end.number;

}


//��ӡ�ڽӱ�//////////////////////////////////////////
void print(PointUnionLists List)
{
	cout << "Vertex" << endl;
	for (int i = 0; i < List->num; i++)
	{
		for (int j = 0;j < List->PointU[i].graph->data;j++)
		{

			position p = List->PointU[i].graph->firstedge[j];
			while (p != NULL) {
				cout << p->adjvex << '\t';
				p = p->next;
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;
}
/*
//��ӡ�ڽӱ�//////////////////////////////////////////
void printTable(Table newtable)
{
	cout << "Vertex" << endl;
	for (int i = 0; i < newtable->data; i++)
	{
		position p = newtable->firstedge[i];
		while (p != NULL) {
			cout << p->adjvex << '\t';
			p = p->next;
		}
		cout << endl;
	}
	cout << endl;
}
*/
int main()
{
	cout << "���������ܸ�����";
	int numOfVertex;
	cin >> numOfVertex;
	cout << "��������ྭ����ĸ�����";
	int Limit_num_nodes;
	cin >> Limit_num_nodes;
	
	cout << "������ؾ���ĸ�����";
	int numOfSpecialVer;
	cin>> numOfSpecialVer;
	int* specialVertex = (int*)malloc(sizeof(int)*(numOfSpecialVer + 1));
	cout << "������ؾ��㣺"<<endl;
	
	for (int i = 0;i < numOfSpecialVer;i++)
		cin >> specialVertex[i];
	for (int i = 0;i < numOfSpecialVer;i++)
		cout<< specialVertex[i]<<'\t';
	cout << endl;
	
	PointUnionLists List = initPointUnion(numOfVertex, numOfSpecialVer);
	link(List, specialVertex, numOfSpecialVer);
	
	make_table(List);
	print(List);

	computer_pre(0, Limit_num_nodes, List, numOfSpecialVer);
	node star, end;
	star.block = 0;
	star.number = 0;
	end.block = List->num - 1;
	end.number= List->PointU->graph->data - 1;
	printf_weight(star, end);
	printf_path(star, end, Limit_num_nodes-1);
	cout << endl;
	for (int i = 0;i < List->num;i++)
	{
		int temp = i;
		for (int k = 0;k < numOfSpecialVer;k++)
		{
			cout << List->PointU[i].flag[k] << '\t';
		
		} 
		cout << endl;
	}
    return 0;
}

