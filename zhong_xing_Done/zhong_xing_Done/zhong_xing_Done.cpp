// new_comute2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include <fstream>  //�ļ����⺯��
#include<string>
#include<math.h>

using namespace std;

//////////////////////////////////////////////////////����////////////////////////////////////////////////////
#define Inf 65530
int** dist;                         //��¼��̳��ȵ�����
int shortest_path_num_vertes = 0;   //��¼���ս��·���Ķ�����
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////��һ���֣�ͼ�Ľ�ģ����ʼ��////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////�ڽӱ��Լ����õ��������ṹ���壨��ʼ��////////////////////////////////////////////
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

struct PointUnion       //������ͼ��һ���ڽӱ��ټ�һ������Ľṹ
{
	int* flag;
	Table graph;
};
typedef PointUnion* PointUnions;

struct PointUnionList       //�������ڶ����ڽӱ�ṹ����
{
	int num;              //�ڽӱ���ܸ���
	PointUnions PointU;   //�ڽӱ�����ṹ�����ͷָ��
};
typedef PointUnionList* PointUnionLists;

struct node {            //�����и��ڽӱ����飬���һ����ı�ʾ������˵�������ڵڼ����ڽӱ�ĵڼ�����
	int block;          //�ڽӱ�ı��
	int number;         //�õ�Ϊ�ڽӱ���Ϊ block��ʱ��ĵ�number����
};
node*** pre;

struct beround  //�ؾ���   
{
	int vertex1;          //�ؾ��ߵ����˵Ķ���
	int vertex2;
};
typedef beround* isRound;

struct Notpass_said  //���ܾ����ߵ����˵Ķ���
{
	int v1;
	int v2;

};
Notpass_said* not_said;  //����һ�����飬�����Ԫ��ΪNotpass_said
////////////////////////////////////////////�ڽӱ��Լ����õ��������ṹ���壨������////////////////////////////////////////////

////////////////////////////////////////////��ʼ���ڽӱ�ṹ����ĺ���(��ʼ)////////////////////////////////////////////////
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
			List->PointU[i].graph->firstedge[j] = (position)(malloc(sizeof(EdgeNode)));   //����һ������
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
////////////////////////////////////////////��ʼ���ڽӱ�ṹ����ĺ���(����)////////////////////////////////////////////////

////////////////////////////////////////////�ڽӱ�Ĳ��뺯��(��ʼ)///////////////////////////////////////////////////////////
void Insert(Table table1, int v, int w, int weig, bool vertexOrblock)   //��ʾ����һ����Ϊ<v,w>,��Ȩ��Ϊweig����ͷ����
{
	position p = static_cast<position>(malloc(sizeof(EdgeNode)));   //����һ������
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
////////////////////////////////////////////�ڽӱ�Ĳ��뺯��(����)///////////////////////////////////////////////////////////

/////////////////////////////////////��data.txt�ļ���ȡͼ���бߵ�Ȩ�أ�Ȼ����ڽӱ�ṹ���鸳ֵ����ʼ��//////////////////////
void make_table(PointUnionLists List, string location)
{
	int v, w, weight;
	int Num_notpass_said;   //�洢���ܾ����ߵ�����

	cout << "�����벻�ܾ����ıߵ�����: ";
	cin >> Num_notpass_said;
	cout << "�������벻�ܾ����ıߵ����˶��㣬�벻Ҫ����ͱؾ�����ͬ�ıߣ���������" << endl;
	if (Num_notpass_said > 0)
	{
		not_said = static_cast<Notpass_said*>(malloc(sizeof(Notpass_said)*Num_notpass_said));
		for (int i = 0; i != Num_notpass_said; ++i)
		{
			cout << "�������" << i + 1 << "�����ܾ����ıߵ���������: ";
			cin >> v >> w;
			not_said[i].v1 = v;
			not_said[i].v2 = w;
		}
	}

	ifstream infile;
	infile.open(location, ios::in);   //���ļ���ָ���ļ�·��
																	   //�������txt�ļ����ڽӱ�ֵ
	for (int i = 0;i < List->num;i++)         //����List->num��������ͼ
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
/////////////////////////////////////��data.txt�ļ���ȡͼ���бߵ�Ȩ�أ�Ȼ����ڽӱ�ṹ���鸳ֵ��������/////////////////////////////

///////////////////////////////////���ڽӱ�ṹ�����������໥�������ڽӱ���������������������뿴˵���ĵ���[��ʼ]///////////////////////////////////////////////
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
////////////////////////���ڽӱ�ṹ�����������໥�������ڽӱ���������������������뿴˵���ĵ���[����]/////////////////////////////

/////////////////////////////////////��һ���֣�ͼ�Ľ�ģ��������////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////�ڶ����֣��������·��Ȩ�ؼ���¼���·������ʼ��//////////////////////////////////////////////////////

////////////////////////�жϱ��Ϊj�Ķ����ǲ��Ǳؾ�����ĺ��������򷵻����ڱؾ��������еı�ţ������򷵻�-1(��ʼ)///////////////////
int is_special(int j, int* specialVertex, int numOfSpecialVer)
{
	for (int p = 0; p != numOfSpecialVer; ++p)
	{
		if (j == specialVertex[p])
			return p;
	}

	return -1;
}
////////////////////////�жϱ��Ϊj�Ķ����ǲ��Ǳؾ�����ĺ��������򷵻����ڱؾ��������еı�ţ������򷵻�-1(����)///////////////////

/////////////�жϱ��Ϊvertex1�Ķ����ǲ��Ǳؾ��߶���ĺ��������򷵻������ڵıؾ��ڱ����еı�ţ������򷵻�-1(��ʼ)///////////////////
int isRoundVertex(int vertex1, isRound isRoundPoint, int isRoundNum)///////////////////////////////////////////
{

	for (int i = 0; i < isRoundNum; i++)
		if ((vertex1 == isRoundPoint[i].vertex1) || (vertex1 == isRoundPoint[i].vertex2))
			return i;
	return -1;
}
/////////////�жϱ��Ϊvertex1�Ķ����ǲ��Ǳؾ��߶���ĺ��������򷵻������ڵıؾ��ڱ����еı�ţ������򷵻�-1(����)///////////////////

/////�ж��ڵ�i���ڽӱ�ĵ�j�������ǲ��Ƿ����(�����Ķ���Ϊ��һ���ڽӱ�ȥ����һ���ڽӱ����㣬�뿴˵���ĵ���[��ʼ]////////////////
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
/////�ж��ڵ�i���ڽӱ�ĵ�j�������ǲ��Ƿ����(�����Ķ���Ϊ��һ���ڽӱ�ȥ����һ���ڽӱ����㣬�뿴˵���ĵ���[����]////////////////

/////////////////////////////////////////////////��������Լ�������·���ĺ���(��ʼ)/////////////////////////////////////////////////////////////////
void computer_pre(int star, int Limit_num_nodes, PointUnionLists List, int numOfSpecialVer, int* specialVertex, isRound isRoundPoint, int isRoundNum)  
{

	int Num_nodes = List->PointU->graph->data*List->num;
	int numOfVertex = List->PointU->graph->data;
	pre = static_cast<node***>(malloc(sizeof(node**)*Limit_num_nodes - 1));   //������ƵĶ�����ΪLimit_num_nodes����ôpre�����Ӧ����Limit_num_nodes - 1��
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
		for (int i = 0; i < List->num; ++i) //Num_nodesΪ�ܵĶ�����
		{
			for (int j = 0;j < List->PointU->graph->data;j++)
			{
				pre[m][i][j].block = 0;                                            //��i���j����
				pre[m][i][j].number = star;
			}
		}
	}
	dist = static_cast<int**>(malloc(sizeof(int*)*List->num));   //dist[j]��¼��㵽����j�ĵ�ǰ���·��
	int** pdist = static_cast<int**>(malloc(sizeof(int*)*List->num));  //pdist�����¼��һ��ѭ��dist�����ֵ
	for (int i = 0; i < List->num; ++i)
	{
		dist[i] = static_cast<int*>(malloc(sizeof(int)*List->PointU->graph->data));
		pdist[i] = static_cast<int*>(malloc(sizeof(int)*List->PointU->graph->data));
	}


	for (int i = 0; i < List->num; ++i) //Num_nodesΪ�ܵĶ�����
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
	for (int m = 1; m != Limit_num_nodes - 1; ++m)   //Limit_num_nodesΪ���ƵĶ�����
	{
		for (int i = 0; i<List->num; ++i) //��i��
		{
			for (int j = 0;j < List->PointU->graph->data;++j)  //��j������
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
						pdist[mp3->adjvex][j] = dist[i][j];  
						pre[m][mp3->adjvex][j].block = i;
						pre[m][mp3->adjvex][j].number = j;

						handled = true;
					}
				}
				if (!handled) //����û�д����
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
						else   //���mp�Ǳؾ�����
						{
							dist[mp->adjvex][j] = dist[i][j];
							pdist[mp->adjvex][j] = dist[i][j];  

							pre[m][mp->adjvex][j].block = i;
							pre[m][mp->adjvex][j].number = j;
						}
						mp = mp->next;
					}

				}

				if ((dist[i][j] == pdist[i][j] && is_shut(List, i, j)) || (dist[i][j] == pdist[i][j] && (is_special(j, specialVertex, numOfSpecialVer) == -1)))
				{
					pre[m][i][j].block = pre[m - 1][i][j].block;
					pre[m][i][j].number = pre[m - 1][i][j].number;
				}
			}
		}
		for (int i = 0; i < List->num; ++i)
			for (int j = 0;j < List->PointU->graph->data;j++)
				pdist[i][j] = dist[i][j]; 
	}

}
/////////////////////////////////////////////////��������Լ�������·���ĺ���(����)/////////////////////////////////////////////////////////////////

/////////////////////////////////////�ڶ����֣��������·��Ȩ�ؼ���¼���·����������/////////////////////////////////////////////////////////////////////


/////////////////////////////////////�������֣���ӡ���·��Ȩ�غ��Լ����·������ʼ��/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////��ӡ���star������i�����·����ֵ///////////////////////////////////////////////////////////////////////
void printf_weight(node star, node end)   
{
	cout << "the shortest path of the node " << end.number << " from the node " << star.number << " is " << dist[end.block][end.number] << endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////��ӡ�����s������i�����ƶ�����Ϊk�����·����nһ��Ҫ��Ϊ���ƶ�����-1//////////////////////////////////////////////////////
void printf_path(node star, node end, int n, int* specialVertex, int numOfSpecialVer)  
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
		printf_path(star, pre[n][end.block][end.number], n, specialVertex, numOfSpecialVer); //kΪ���ƵĶ�����
		if (end.number != pre[n][end.block][end.number].number)
			cout << "->";
	}
	if (n >= 0 && end.number != pre[n][end.block][end.number].number || end.number == star.number)
	{
		cout << "v" << end.number;
		shortest_path_num_vertes++;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////�������֣���ӡ���·��Ȩ�غ��Լ����·����������///////////////////////////////////////////////////////////////////////////

int main()
{
	//////////////////////////////////////���벿��////////////////////////////////////////////////////////////////////////////////////
	string location;
	cout << "�밴�����ʽ��������ͼ���ļ���txt�ļ���·����ͼ�����Ĭ��Ϊ0���յ�Ĭ��Ϊ���ı�ţ���" << endl;
	cout << "C:\\Users\\lin\\Desktop\\temporary\\data.txt" << endl;
	cin >> location;

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
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////��ģ����////////////////////////////////////////////////////////////////
	PointUnionLists List = initPointUnion(numOfVertex, numOfSpecialVer);          //��ʼ��һ���ڽӱ�ṹ����
	link(List, specialVertex, numOfSpecialVer);                                   //���ڽӱ�ṹ�����е�ÿһ���ڽӱ�ͨ��ĳЩ�������໥��������
	make_table(List,location);                                                             //��data.txt�ļ����ڽӱ������ڵ�ÿһ���ڽӱ�ֵ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////���㲿��////////////////////////////////////////////////////////////////////
	node star, end;                //�����յ�����Ľṹ                         
	star.block = 0;                //��㶨��Ϊ��0���ڽӱ����ĵ�0����
	star.number = 0;
	end.block = List->num - 1;      //�յ㶨��Ϊ�ڽӱ�ṹ����List�����һ���ڽӱ�����һ����
	end.number = List->PointU->graph->data - 1;

	computer_pre(0, Limit_num_nodes, List, numOfSpecialVer, specialVertex, isRoundPoint, isRoundNum);   //�������·���ĺ�������¼���·��,Ĭ�����Ϊ0���յ�Ϊ���ı��
	while(dist[end.block][end.number] == Inf)
	{
		cout << "��Լ����ྭ����ĸ���Ϊ" << Limit_num_nodes << "ʱ������·������㵽���յ㣬������������ྭ����ĸ���" << endl;
		cin >> Limit_num_nodes;
		computer_pre(0, Limit_num_nodes, List, numOfSpecialVer, specialVertex, isRoundPoint, isRoundNum);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////��ӡ����///////////////////////////////////////////////////////////////////
	

	printf_weight(star, end);        //��ӡ����㵽�յ�����·������Ȩ��
	shortest_path_num_vertes = 0;    
	printf_path(star, end, Limit_num_nodes - 1, specialVertex, numOfSpecialVer);   //��ӡ���·��
	cout << endl;
	cout << "�����·���Ķ�����Ϊ��" << shortest_path_num_vertes << endl;           //��ӡ�������Ķ���ĸ���
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return 0;

}

