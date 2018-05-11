// testt.cpp : 定义控制台应用程序的入口点。
//

// new_comute2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include <fstream>  //文件流库函数
#include<math.h>
using namespace std;

#define Inf 65530
int** dist;
int shortest_path_num_vertes = 0;   //记录最终结果路径的节点数

									/////////////////////邻接表的相关定义//////////////////////
typedef struct EdgeNode *position;
typedef struct Led_table* Table;


struct EdgeNode     //边表结点 
{
	int adjvex;    // 邻接点域,存储该顶点对应的下标 
	int weight;     // 对应边的权值
	position next; // 链域,指向下一个邻接点
	bool vertexOrblock;                   //1代表指向块，0代表指向普通结点
};

struct Led_table       // 邻接表结构 
{
	int data;                //邻接表的大小
	position *firstedge;       //边表头指针，可以理解为数组
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

struct beround  //必经边
{
	int vertex1;
	int vertex2;
	int specialNumOfvertex1;
	int specialNumOfvertex2;
};
typedef beround* isRound;

struct Notpass_said  //不能经过边的两端的顶点
{
	int v1;
	int v2;

};
Notpass_said* not_said;  //构建一个数组，数组的元素为Notpass_said


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
			List->PointU[i].graph->firstedge[j] = (position)(malloc(sizeof(EdgeNode)));   //申请一个节点
			if (List->PointU[i].graph->firstedge[j] == NULL)
			{
				cout << "out of space!!!";
			}
			List->PointU[i].graph->firstedge[j]->adjvex = j;   //此参数在此时没有意义
			List->PointU[i].graph->firstedge[j]->weight = 0;   //此参数在此时没有意义
			List->PointU[i].graph->firstedge[j]->next = NULL;
			List->PointU[i].graph->firstedge[j]->vertexOrblock = 0;
		}
	}
	return List;
}

void Insert(Table table1, int v, int w, int weig, bool vertexOrblock)   //表示存在一条边为<v,w>,且权重为weig，从头插入
{
	position p = static_cast<position>(malloc(sizeof(EdgeNode)));   //申请一个节点
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

	int Num_notpass_said;   //存储不能经过边的条数

	cout << "请输入不能经过的边的条数: ";
	cin >> Num_notpass_said;
	not_said = static_cast<Notpass_said*>(malloc(sizeof(Notpass_said)*Num_notpass_said));
	for (int i = 0; i != Num_notpass_said; ++i)
	{
		cout << "请输入第" << i + 1 << "条不能经过的边的两个顶点: ";
		cin >> v >> w;
		not_said[i].v1 = v;
		not_said[i].v2 = w;
	}


	ifstream infile;
	infile.open("C:\\Users\\lin\Desktop\\temporary\\data.txt", ios::in);   //打开文件，指定文件路径
																	   //下面根据txt文件给邻接表赋值
	for (int i = 0;i < List->num;i++)
	{

		while (!infile.eof())            // 若未到文件结束一直循环 
		{
			infile >> v >> w >> weight;
			//下面的for循环用于查找所输入的边是否为不能经过的边
			for (int i = 0; i != Num_notpass_said; ++i)
			{
				if ((v == not_said[i].v1 && w == not_said[i].v2) || (w == not_said[i].v1 && v == not_said[i].v2))
				{
					weight = Inf;   //如果为不能经过的边，就把权值设为无穷大
				}
			}

			Insert(List->PointU[i].graph, v, w, weight, 0);   //图为无向图，因此双向都赋值
			Insert(List->PointU[i].graph, w, v, weight, 0);
		}
		infile.seekg(0);
	}
	infile.close();   //关闭文件
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
				Insert(List->PointU[i].graph, specialVertex[k], temp, 0, 1);   //图为无向图，因此双向都赋值
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


void computer_pre(int star, int Limit_num_nodes, PointUnionLists List, int numOfSpecialVer, int* specialVertex, isRound isRoundPoint, int isRoundNum)    //计算pre矩阵，star为起点,Limit_num_nodes为限制的节点数，table1位邻接表
{

	int Num_nodes = List->PointU->graph->data*List->num;
	int numOfVertex = List->PointU->graph->data;
	pre = static_cast<node***>(malloc(sizeof(node**)*Limit_num_nodes - 1));   //如果限制的节点数为Limit_num_nodes，那么pre矩阵就应该有Limit_num_nodes - 1行
	for (int i = 0; i != Limit_num_nodes - 1; ++i)
	{
		pre[i] = static_cast<node**>(malloc(sizeof(node*)*List->num));   //对每一行pre矩阵申请Num_nodes个位置
		for (int j = 0;j < List->num;j++)
		{
			pre[i][j] = static_cast<node*>(malloc(sizeof(node)*List->PointU->graph->data));
		}
	}
	for (int m = 0; m != Limit_num_nodes - 1; ++m)
	{
		for (int i = 0; i < List->num; ++i) //Num_nodes为总的节点数
		{
			for (int j = 0;j < List->PointU->graph->data;j++)
			{
				pre[m][i][j].block = 0;                                            //第i块第j个点
				pre[m][i][j].number = star;
			}
		}
	}
	dist = static_cast<int**>(malloc(sizeof(int*)*List->num));   //dist[j]记录起点到节点j的当前最短路径
	int** pdist = static_cast<int**>(malloc(sizeof(int*)*List->num));  //pdist数组记录上一轮循环dist数组的值
	for (int i = 0; i < List->num; ++i)
	{
		dist[i] = static_cast<int*>(malloc(sizeof(int)*List->PointU->graph->data));
		pdist[i] = static_cast<int*>(malloc(sizeof(int)*List->PointU->graph->data));
	}


	for (int i = 0; i < List->num; ++i) //Num_nodes为总的节点数
		for (int j = 0;j < List->PointU->graph->data;j++)  //首先把最短路径矩阵都设为无穷大
		{
			dist[i][j] = Inf;      //全部初始化
			pdist[i][j] = Inf;
		}
	dist[0][0] = 0;
	pdist[0][0] = 0;


	//接下来根据邻接表来初始化dist和pdist
	position p = List->PointU->graph[0].firstedge[star]->next;  //定义一个位置指向起点的链表的第一个元素
	while (p != NULL)
	{
		dist[0][p->adjvex] = p->weight;
		pdist[0][p->adjvex] = p->weight;
		p = p->next;
	}

	//接下来为关键代码，根据邻接表计算pre矩阵
	for (int m = 1; m != Limit_num_nodes - 1; ++m)   //Limit_num_nodes为限制的节点数
	{
		for (int i = 0; i<List->num; ++i) //第i块
		{
			for (int j = 0;j < List->PointU->graph->data;++j)  //第j个节点
			{
				bool handled = false;
				if (isRoundVertex(j, isRoundPoint, isRoundNum) != -1)  //j是必经边的端点
				{
					int numsaid = isRoundVertex(j, isRoundPoint, isRoundNum);       //边的标号
					int nextvertex;  //与j相连的必经边的另一个端点
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
				if (!handled) //j是普通的点或者普通的必经点，不是必经边的端点
				{
					position mp = List->PointU[i].graph->firstedge[j]->next;
					while (mp != NULL)
					{
						if (mp->vertexOrblock == 0)
						{

							if (dist[i][j] > pdist[i][mp->adjvex] + mp->weight)  //理论上来说这个地方应该用图的逆邻接表，但是我们的图是无向的，所以也可以这么写
							{
								dist[i][j] = pdist[i][mp->adjvex] + mp->weight;
								pre[m][i][j].number = mp->adjvex;
								pre[m][i][j].block = i;
							}
						}
						else   //如果mp是必经节点
						{
							dist[mp->adjvex][j] = dist[i][j];
							pdist[mp->adjvex][j] = dist[i][j];  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

							pre[m][mp->adjvex][j].block = i;
							pre[m][mp->adjvex][j].number = j;
						}
						mp = mp->next;
					}

				}


				//不要问为什么，调了一天的
				if ((dist[i][j] == pdist[i][j] && is_shut(List, i, j)) || (dist[i][j] == pdist[i][j] && (is_special(j, specialVertex, numOfSpecialVer) == -1)))
				{
					pre[m][i][j].block = pre[m - 1][i][j].block;
					pre[m][i][j].number = pre[m - 1][i][j].number;
				}
			}
		}
		for (int i = 0; i < List->num; ++i)
			for (int j = 0;j < List->PointU->graph->data;j++)
				pdist[i][j] = dist[i][j]; // 此处为把dist的值全部赋给pdist
										  /*
										  for (int i = 0; i < List->num; ++i)
										  {
										  for (int j = 0; j < List->PointU->graph->data; j++)
										  cout << pdist[i][j] << '\t'; // 此处为把dist的值全部赋给pdist
										  cout << endl;
										  }
										  cout << endl;
										  */
	}

}

void printf_weight(node star, node end)   //起点star到节点i的最短路径
{
	cout << "the shortest path of the node " << end.number << " from the node " << star.number << " is " << dist[end.block][end.number] << endl;
}



void printf_path(node star, node end, int n, int* specialVertex, int numOfSpecialVer)  //打印从起点s到节点i的限制节点数为k的最短路径，n一点要设为限制节点数-1
{
	n--;
	if (n >= 0 && end.number != pre[n][end.block][end.number].number)
	{
		if (is_special(end.number, specialVertex, numOfSpecialVer) != -1)
		{
			n++;
		}
	}
	if (end.number != star.number)   //s为起点
	{
		printf_path(star, pre[n][end.block][end.number], n, specialVertex, numOfSpecialVer); //k为限制的节点数
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
//打印邻接表//////////////////////////////////////////
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
	cout << "请输入点的总个数：";
	int numOfVertex;
	cin >> numOfVertex;

	cout << "请输入最多经过点的个数：";
	int Limit_num_nodes;
	cin >> Limit_num_nodes;

	cout << "请输入必经点的个数(不包括起点和终点，但包括必须经过边的两端顶点，比如1--4是必经边，则要把1，4也当作必经点)：";
	int numOfSpecialVer;
	cin >> numOfSpecialVer;
	while (numOfSpecialVer + 2> numOfVertex)
	{
		cout << "错误：必经点的个数大于起点和终点间总的点个数" << numOfVertex - 2 << "，请重新输入必经点的个数：";
		cin >> numOfSpecialVer;
	}

	int* specialVertex = (int*)malloc(sizeof(int)*(numOfSpecialVer));
	cout << "请输入必经点(请把必经边的两端顶点也当作必经点输入)：" << endl;
	for (int i = 0; i < numOfSpecialVer; i++)
		cin >> specialVertex[i];

	cout << "请输入必经边的条数：";
	int isRoundNum;  //必经边的条数
	cin >> isRoundNum;
	isRound isRoundPoint = (isRound)malloc(sizeof(beround)*isRoundNum);
	if (isRoundNum > 0)
	{
		for (int i = 0; i < isRoundNum; i++)
		{
			cout << "请输入第" << i + 1 << "条必经边的两端顶点：";
			cin >> isRoundPoint[i].vertex1 >> isRoundPoint[i].vertex2;
			while (is_special(isRoundPoint[i].vertex1, specialVertex, numOfSpecialVer) == -1 || is_special(isRoundPoint[i].vertex2, specialVertex, numOfSpecialVer) == -1)
			{
				cout << "该边的两端顶点不在必经点的结合内，请重新输入第" << i + 1 << "条必经边的两端顶点：";
				cin >> isRoundPoint[i].vertex1 >> isRoundPoint[i].vertex2;
			} //如果至少一个点不在必经点的集合内
			isRoundPoint[i].specialNumOfvertex1 = is_special(isRoundPoint[i].vertex1, specialVertex, numOfSpecialVer);
			isRoundPoint[i].specialNumOfvertex2 = is_special(isRoundPoint[i].vertex2, specialVertex, numOfSpecialVer);
		}


		for (int i = 0; i < isRoundNum; i++)
		{
			cout << isRoundPoint[i].vertex1 << "---" << isRoundPoint[i].vertex2 << endl;
		}
	}
	/*
	cout << "请输入必经点的个数：";
	int numOfSpecialVer;
	cin>> numOfSpecialVer;
	int* specialVertex = (int*)malloc(sizeof(int)*(numOfSpecialVer));
	cout << "请输入必经点："<<endl;

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
	cout << "此最短路径的节点数为：" << shortest_path_num_vertes << endl;
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

