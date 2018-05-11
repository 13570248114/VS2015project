// testt.cpp : �������̨Ӧ�ó������ڵ㡣
//

// new_comute2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include <fstream>  //�ļ����⺯��
#include<math.h>
using namespace std;

#define Inf 65530
int** dist;
int shortest_path_num_vertes = 0;   //��¼���ս��·���Ľڵ���

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

struct beround  //�ؾ���
{
	int vertex1;
	int vertex2;
	int specialNumOfvertex1;
	int specialNumOfvertex2;
};
typedef beround* isRound;

struct Notpass_said  //���ܾ����ߵ����˵Ķ���
{
	int v1;
	int v2;

};
Notpass_said* not_said;  //����һ�����飬�����Ԫ��ΪNotpass_said


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

		List->PointU[i].graph = static_cast<Table> (malloc(sizeof(struct Led_table)));
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

	int Num_notpass_said;   //�洢���ܾ����ߵ�����

	cout << "�����벻�ܾ����ıߵ�����: ";
	cin >> Num_notpass_said;
	not_said = static_cast<Notpass_said*>(malloc(sizeof(Notpass_said)*Num_notpass_said));
	for (int i = 0; i != Num_notpass_said; ++i)
	{
		cout << "�������" << i + 1 << "�����ܾ����ıߵ���������: ";
		cin >> v >> w;
		not_said[i].v1 = v;
		not_said[i].v2 = w;
	}


	ifstream infile;
	infile.open("C:\\Users\\lin\Desktop\\temporary\\data.txt", ios::in);   //���ļ���ָ���ļ�·��
																	   //�������txt�ļ����ڽӱ�ֵ
	for (int i = 0;i < List->num;i++)
	{

		while (!infile.eof())            // ��δ���ļ�����һֱѭ�� 
		{
			infile >> v >> w >> weight;
			//�����forѭ�����ڲ���������ı��Ƿ�Ϊ���ܾ����ı�
			for (int i = 0; i != Num_notpass_said; ++i)
			{
				if ((v == not_said[i].v1 && w == not_said[i].v2) || (w == not_said[i].v1 && v == not_said[i].v2))
				{
					weight = Inf;   //���Ϊ���ܾ����ıߣ��Ͱ�Ȩֵ��Ϊ�����
				}
			}

			Insert(List->PointU[i].graph, v, w, weight, 0);   //ͼΪ����ͼ�����˫�򶼸�ֵ
			Insert(List->PointU[i].graph, w, v, weight, 0);
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
		int temp = i;
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
				Insert(List->PointU[i].graph, specialVertex[k], temp, 0, 1);   //ͼΪ����ͼ�����˫�򶼸�ֵ
																			   //Insert(List->PointU[temp].graph, specialVertex[k], i, 0,1);
			}
		}
	}

}
int is_special(int j, int* specialVertex, int numOfSpecialVer)
{
	for (int p = 0; p != numOfSpecialVer; ++p)
	{
		if (j == specialVertex[p])
			return p;
	}

	return -1;
}



int isRoundVertex(int vertex1, isRound isRoundPoint, int isRoundNum)///////////////////////////////////////////
{

	for (int i = 0; i < isRoundNum; i++)
		if ((vertex1 == isRoundPoint[i].vertex1) || (vertex1 == isRoundPoint[i].vertex2))
			return i;
	return -1;
}

bool is_shut(PointUnionLists List, int i, int j)
{

	position mp2 = List->PointU[i].graph->firstedge[j]->next;
	while (mp2 != NULL)
	{
		if (mp2->vertexOrblock == 1)
		{
			return true;

		}
		mp2 = mp2->next;
	}
	return false;
}


void computer_pre(int star, int Limit_num_nodes, PointUnionLists List, int numOfSpecialVer, int* specialVertex, isRound isRoundPoint, int isRoundNum)    //����pre����starΪ���,Limit_num_nodesΪ���ƵĽڵ�����table1λ�ڽӱ�
{

	int Num_nodes = List->PointU->graph->data*List->num;
	int numOfVertex = List->PointU->graph->data;
	pre = static_cast<node***>(malloc(sizeof(node**)*Limit_num_nodes - 1));   //������ƵĽڵ���ΪLimit_num_nodes����ôpre�����Ӧ����Limit_num_nodes - 1��
	for (int i = 0; i != Limit_num_nodes - 1; ++i)
	{
		pre[i] = static_cast<node**>(malloc(sizeof(node*)*List->num));   //��ÿһ��pre��������Num_nodes��λ��
		for (int j = 0;j < List->num;j++)
		{
			pre[i][j] = static_cast<node*>(malloc(sizeof(node)*List->PointU->graph->data));
		}
	}
	for (int m = 0; m != Limit_num_nodes - 1; ++m)
	{
		for (int i = 0; i < List->num; ++i) //Num_nodesΪ�ܵĽڵ���
		{
			for (int j = 0;j < List->PointU->graph->data;j++)
			{
				pre[m][i][j].block = 0;                                            //��i���j����
				pre[m][i][j].number = star;
			}
		}
	}
	dist = static_cast<int**>(malloc(sizeof(int*)*List->num));   //dist[j]��¼��㵽�ڵ�j�ĵ�ǰ���·��
	int** pdist = static_cast<int**>(malloc(sizeof(int*)*List->num));  //pdist�����¼��һ��ѭ��dist�����ֵ
	for (int i = 0; i < List->num; ++i)
	{
		dist[i] = static_cast<int*>(malloc(sizeof(int)*List->PointU->graph->data));
		pdist[i] = static_cast<int*>(malloc(sizeof(int)*List->PointU->graph->data));
	}


	for (int i = 0; i < List->num; ++i) //Num_nodesΪ�ܵĽڵ���
		for (int j = 0;j < List->PointU->graph->data;j++)  //���Ȱ����·��������Ϊ�����
		{
			dist[i][j] = Inf;      //ȫ����ʼ��
			pdist[i][j] = Inf;
		}
	dist[0][0] = 0;
	pdist[0][0] = 0;


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
		for (int i = 0; i<List->num; ++i) //��i��
		{
			for (int j = 0;j < List->PointU->graph->data;++j)  //��j���ڵ�
			{
				bool handled = false;
				if (isRoundVertex(j, isRoundPoint, isRoundNum) != -1)  //j�Ǳؾ��ߵĶ˵�
				{
					int numsaid = isRoundVertex(j, isRoundPoint, isRoundNum);       //�ߵı��
					int nextvertex;  //��j�����ıؾ��ߵ���һ���˵�
					if (j == isRoundPoint[numsaid].vertex1)
						nextvertex = isRoundPoint[numsaid].vertex2;
					else
						nextvertex = isRoundPoint[numsaid].vertex1;

					if (is_shut(List, i, j) && !is_shut(List, i, nextvertex))
					{
						position mp3 = List->PointU[i].graph->firstedge[j]->next;
						while (mp3->adjvex != nextvertex) mp3 = mp3->next;
						dist[i][j] = pdist[i][nextvertex] + mp3->weight;
						pre[m][i][j].number = nextvertex;
						pre[m][i][j].block = i;

						while (mp3->vertexOrblock != 1)mp3 = mp3->next;
						dist[mp3->adjvex][j] = dist[i][j];
						pdist[mp3->adjvex][j] = dist[i][j];  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						pre[m][mp3->adjvex][j].block = i;
						pre[m][mp3->adjvex][j].number = j;

						handled = true;
					}
				}
				if (!handled) //j����ͨ�ĵ������ͨ�ıؾ��㣬���Ǳؾ��ߵĶ˵�
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
						else   //���mp�Ǳؾ��ڵ�
						{
							dist[mp->adjvex][j] = dist[i][j];
							pdist[mp->adjvex][j] = dist[i][j];  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

							pre[m][mp->adjvex][j].block = i;
							pre[m][mp->adjvex][j].number = j;
						}
						mp = mp->next;
					}

				}


				//��Ҫ��Ϊʲô������һ���
				if ((dist[i][j] == pdist[i][j] && is_shut(List, i, j)) || (dist[i][j] == pdist[i][j] && (is_special(j, specialVertex, numOfSpecialVer) == -1)))
				{
					pre[m][i][j].block = pre[m - 1][i][j].block;
					pre[m][i][j].number = pre[m - 1][i][j].number;
				}
			}
		}
		for (int i = 0; i < List->num; ++i)
			for (int j = 0;j < List->PointU->graph->data;j++)
				pdist[i][j] = dist[i][j]; // �˴�Ϊ��dist��ֵȫ������pdist
										  /*
										  for (int i = 0; i < List->num; ++i)
										  {
										  for (int j = 0; j < List->PointU->graph->data; j++)
										  cout << pdist[i][j] << '\t'; // �˴�Ϊ��dist��ֵȫ������pdist
										  cout << endl;
										  }
										  cout << endl;
										  */
	}

}

void printf_weight(node star, node end)   //���star���ڵ�i�����·��
{
	cout << "the shortest path of the node " << end.number << " from the node " << star.number << " is " << dist[end.block][end.number] << endl;
}



void printf_path(node star, node end, int n, int* specialVertex, int numOfSpecialVer)  //��ӡ�����s���ڵ�i�����ƽڵ���Ϊk�����·����nһ��Ҫ��Ϊ���ƽڵ���-1
{
	n--;
	if (n >= 0 && end.number != pre[n][end.block][end.number].number)
	{
		if (is_special(end.number, specialVertex, numOfSpecialVer) != -1)
		{
			n++;
		}
	}
	if (end.number != star.number)   //sΪ���
	{
		printf_path(star, pre[n][end.block][end.number], n, specialVertex, numOfSpecialVer); //kΪ���ƵĽڵ���
		if (end.number != pre[n][end.block][end.number].number)
			cout << "->";
	}
	if (n >= 0 && end.number != pre[n][end.block][end.number].number || end.number == star.number)
	{
		cout << "v" << end.number;
		shortest_path_num_vertes++;
	}


}
void printf_pre(node*** p, int Limit_num_nodes, PointUnionLists List)
{
	for (int i = 0; i != Limit_num_nodes - 1; ++i)
	{
		for (int j = 0; j != List->num; ++j)
		{
			for (int k = 0; k != List->PointU->graph->data; ++k)
			{
				cout << p[i][j][k].block << "," << p[i][j][k].number << "\t";
			}
			cout << endl;
		}
		cout << endl;
		cout << endl;
	}
}

void printf_dist(PointUnionLists List)
{
	for (int i = 0; i != List->num; ++i)
	{
		for (int j = 0; j != List->PointU->graph->data; ++j)
			cout << dist[i][j] << "\t";
		cout << endl;
	}

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

int main()
{
	cout << "���������ܸ�����";
	int numOfVertex;
	cin >> numOfVertex;

	cout << "��������ྭ����ĸ�����";
	int Limit_num_nodes;
	cin >> Limit_num_nodes;

	cout << "������ؾ���ĸ���(�����������յ㣬���������뾭���ߵ����˶��㣬����1--4�Ǳؾ��ߣ���Ҫ��1��4Ҳ�����ؾ���)��";
	int numOfSpecialVer;
	cin >> numOfSpecialVer;
	while (numOfSpecialVer + 2> numOfVertex)
	{
		cout << "���󣺱ؾ���ĸ������������յ���ܵĵ����" << numOfVertex - 2 << "������������ؾ���ĸ�����";
		cin >> numOfSpecialVer;
	}

	int* specialVertex = (int*)malloc(sizeof(int)*(numOfSpecialVer));
	cout << "������ؾ���(��ѱؾ��ߵ����˶���Ҳ�����ؾ�������)��" << endl;
	for (int i = 0; i < numOfSpecialVer; i++)
		cin >> specialVertex[i];

	cout << "������ؾ��ߵ�������";
	int isRoundNum;  //�ؾ��ߵ�����
	cin >> isRoundNum;
	isRound isRoundPoint = (isRound)malloc(sizeof(beround)*isRoundNum);
	if (isRoundNum > 0)
	{
		for (int i = 0; i < isRoundNum; i++)
		{
			cout << "�������" << i + 1 << "���ؾ��ߵ����˶��㣺";
			cin >> isRoundPoint[i].vertex1 >> isRoundPoint[i].vertex2;
			while (is_special(isRoundPoint[i].vertex1, specialVertex, numOfSpecialVer) == -1 || is_special(isRoundPoint[i].vertex2, specialVertex, numOfSpecialVer) == -1)
			{
				cout << "�ñߵ����˶��㲻�ڱؾ���Ľ���ڣ������������" << i + 1 << "���ؾ��ߵ����˶��㣺";
				cin >> isRoundPoint[i].vertex1 >> isRoundPoint[i].vertex2;
			} //�������һ���㲻�ڱؾ���ļ�����
			isRoundPoint[i].specialNumOfvertex1 = is_special(isRoundPoint[i].vertex1, specialVertex, numOfSpecialVer);
			isRoundPoint[i].specialNumOfvertex2 = is_special(isRoundPoint[i].vertex2, specialVertex, numOfSpecialVer);
		}


		for (int i = 0; i < isRoundNum; i++)
		{
			cout << isRoundPoint[i].vertex1 << "---" << isRoundPoint[i].vertex2 << endl;
		}
	}
	/*
	cout << "������ؾ���ĸ�����";
	int numOfSpecialVer;
	cin>> numOfSpecialVer;
	int* specialVertex = (int*)malloc(sizeof(int)*(numOfSpecialVer));
	cout << "������ؾ��㣺"<<endl;

	for (int i = 0;i < numOfSpecialVer;i++)
	cin >> specialVertex[i];


	*/
	PointUnionLists List = initPointUnion(numOfVertex, numOfSpecialVer);
	link(List, specialVertex, numOfSpecialVer);

	make_table(List);
	//print(List);

	computer_pre(0, Limit_num_nodes, List, numOfSpecialVer, specialVertex, isRoundPoint, isRoundNum);
	node star, end;
	star.block = 0;
	star.number = 0;
	end.block = List->num - 1;
	end.number = List->PointU->graph->data - 1;
	printf_weight(star, end);
	shortest_path_num_vertes = 0;
	printf_path(star, end, Limit_num_nodes - 1, specialVertex, numOfSpecialVer);

	cout << endl;
	cout << "�����·���Ľڵ���Ϊ��" << shortest_path_num_vertes << endl;
	/*
	for (int i = 0;i < List->num;i++)
	{
	int temp = i;
	for (int k = 0;k < numOfSpecialVer;k++)
	{
	cout << List->PointU[i].flag[k] << '\t';

	}
	cout << endl;
	}
	*/
	//	printf_dist(List);
	//	cout << endl;
	//	cout << endl;
	//	printf_pre(pre, Limit_num_nodes, List);
	return 0;

}

