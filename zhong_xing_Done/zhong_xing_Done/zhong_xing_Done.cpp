// new_comute2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include <fstream>  //文件流库函数
#include<string>
#include<math.h>

using namespace std;

//////////////////////////////////////////////////////定义////////////////////////////////////////////////////
#define Inf 65530
int** dist;                         //记录最短长度的数组
int shortest_path_num_vertes = 0;   //记录最终结果路径的顶点数
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////第一部分，图的建模（开始）////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////邻接表以及所用到的其他结构定义（开始）////////////////////////////////////////////
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

struct PointUnion       //这里是图的一个邻接表再加一个数组的结构
{
	int* flag;
	Table graph;
};
typedef PointUnion* PointUnions;

struct PointUnionList       //这里用于定义邻接表结构数组
{
	int num;              //邻接表的总个数
	PointUnions PointU;   //邻接表数组结构数组的头指针
};
typedef PointUnionList* PointUnionLists;

struct node {            //上述有个邻接表数组，因此一个点的表示方法是说明他是在第几个邻接表的第几个点
	int block;          //邻接表的编号
	int number;         //该点为邻接表编号为 block的时候的第number个点
};
node*** pre;

struct beround  //必经边   
{
	int vertex1;          //必经边的两端的顶点
	int vertex2;
};
typedef beround* isRound;

struct Notpass_said  //不能经过边的两端的顶点
{
	int v1;
	int v2;

};
Notpass_said* not_said;  //构建一个数组，数组的元素为Notpass_said
////////////////////////////////////////////邻接表以及所用到的其他结构定义（结束）////////////////////////////////////////////

////////////////////////////////////////////初始化邻接表结构数组的函数(开始)////////////////////////////////////////////////
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
			List->PointU[i].graph->firstedge[j] = (position)(malloc(sizeof(EdgeNode)));   //申请一个顶点
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
////////////////////////////////////////////初始化邻接表结构数组的函数(结束)////////////////////////////////////////////////

////////////////////////////////////////////邻接表的插入函数(开始)///////////////////////////////////////////////////////////
void Insert(Table table1, int v, int w, int weig, bool vertexOrblock)   //表示存在一条边为<v,w>,且权重为weig，从头插入
{
	position p = static_cast<position>(malloc(sizeof(EdgeNode)));   //申请一个顶点
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
////////////////////////////////////////////邻接表的插入函数(结束)///////////////////////////////////////////////////////////

/////////////////////////////////////从data.txt文件读取图所有边的权重，然后给邻接表结构数组赋值（开始）//////////////////////
void make_table(PointUnionLists List, string location)
{
	int v, w, weight;
	int Num_notpass_said;   //存储不能经过边的条数

	cout << "请输入不能经过的边的条数: ";
	cin >> Num_notpass_said;
	cout << "下面输入不能经过的边的两端顶点，请不要输入和必经边相同的边，否则会出错" << endl;
	if (Num_notpass_said > 0)
	{
		not_said = static_cast<Notpass_said*>(malloc(sizeof(Notpass_said)*Num_notpass_said));
		for (int i = 0; i != Num_notpass_said; ++i)
		{
			cout << "请输入第" << i + 1 << "条不能经过的边的两个顶点: ";
			cin >> v >> w;
			not_said[i].v1 = v;
			not_said[i].v2 = w;
		}
	}

	ifstream infile;
	infile.open(location, ios::in);   //打开文件，指定文件路径
																	   //下面根据txt文件给邻接表赋值
	for (int i = 0;i < List->num;i++)         //复制List->num个给定的图
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
/////////////////////////////////////从data.txt文件读取图所有边的权重，然后给邻接表结构数组赋值（结束）/////////////////////////////

///////////////////////////////////将邻接表结构数组中所有相互独立的邻接表相关联起来（怎样关联请看说明文档）[开始]///////////////////////////////////////////////
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
////////////////////////将邻接表结构数组中所有相互独立的邻接表相关联起来（怎样关联请看说明文档）[结束]/////////////////////////////

/////////////////////////////////////第一部分，图的建模（结束）////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////第二部分，计算最短路径权重及记录最短路径（开始）//////////////////////////////////////////////////////

////////////////////////判断编号为j的顶点是不是必经顶点的函数，是则返回他在必经顶点数列的编号，不是则返回-1(开始)///////////////////
int is_special(int j, int* specialVertex, int numOfSpecialVer)
{
	for (int p = 0; p != numOfSpecialVer; ++p)
	{
		if (j == specialVertex[p])
			return p;
	}

	return -1;
}
////////////////////////判断编号为j的顶点是不是必经顶点的函数，是则返回他在必经顶点数列的编号，不是则返回-1(结束)///////////////////

/////////////判断编号为vertex1的顶点是不是必经边顶点的函数，是则返回他所在的必经节边数列的编号，不是则返回-1(开始)///////////////////
int isRoundVertex(int vertex1, isRound isRoundPoint, int isRoundNum)///////////////////////////////////////////
{

	for (int i = 0; i < isRoundNum; i++)
		if ((vertex1 == isRoundPoint[i].vertex1) || (vertex1 == isRoundPoint[i].vertex2))
			return i;
	return -1;
}
/////////////判断编号为vertex1的顶点是不是必经边顶点的函数，是则返回他所在的必经节边数列的编号，不是则返回-1(结束)///////////////////

/////判断在第i个邻接表的第j个顶点是不是发射点(发射点的定义为从一个邻接表去另外一个邻接表的起点，请看说明文档）[开始]////////////////
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
/////判断在第i个邻接表的第j个顶点是不是发射点(发射点的定义为从一个邻接表去另外一个邻接表的起点，请看说明文档）[结束]////////////////

/////////////////////////////////////////////////计算满足约束的最短路径的函数(开始)/////////////////////////////////////////////////////////////////
void computer_pre(int star, int Limit_num_nodes, PointUnionLists List, int numOfSpecialVer, int* specialVertex, isRound isRoundPoint, int isRoundNum)  
{

	int Num_nodes = List->PointU->graph->data*List->num;
	int numOfVertex = List->PointU->graph->data;
	pre = static_cast<node***>(malloc(sizeof(node**)*Limit_num_nodes - 1));   //如果限制的顶点数为Limit_num_nodes，那么pre矩阵就应该有Limit_num_nodes - 1行
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
		for (int i = 0; i < List->num; ++i) //Num_nodes为总的顶点数
		{
			for (int j = 0;j < List->PointU->graph->data;j++)
			{
				pre[m][i][j].block = 0;                                            //第i块第j个点
				pre[m][i][j].number = star;
			}
		}
	}
	dist = static_cast<int**>(malloc(sizeof(int*)*List->num));   //dist[j]记录起点到顶点j的当前最短路径
	int** pdist = static_cast<int**>(malloc(sizeof(int*)*List->num));  //pdist数组记录上一轮循环dist数组的值
	for (int i = 0; i < List->num; ++i)
	{
		dist[i] = static_cast<int*>(malloc(sizeof(int)*List->PointU->graph->data));
		pdist[i] = static_cast<int*>(malloc(sizeof(int)*List->PointU->graph->data));
	}


	for (int i = 0; i < List->num; ++i) //Num_nodes为总的顶点数
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
	for (int m = 1; m != Limit_num_nodes - 1; ++m)   //Limit_num_nodes为限制的顶点数
	{
		for (int i = 0; i<List->num; ++i) //第i块
		{
			for (int j = 0;j < List->PointU->graph->data;++j)  //第j个顶点
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
						pdist[mp3->adjvex][j] = dist[i][j];  
						pre[m][mp3->adjvex][j].block = i;
						pre[m][mp3->adjvex][j].number = j;

						handled = true;
					}
				}
				if (!handled) //上面没有处理过
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
						else   //如果mp是必经顶点
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
/////////////////////////////////////////////////计算满足约束的最短路径的函数(结束)/////////////////////////////////////////////////////////////////

/////////////////////////////////////第二部分，计算最短路径权重及记录最短路径（结束）/////////////////////////////////////////////////////////////////////


/////////////////////////////////////第三部分，打印最短路径权重和以及最短路径（开始）/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////打印起点star到顶点i的最短路径的值///////////////////////////////////////////////////////////////////////
void printf_weight(node star, node end)   
{
	cout << "the shortest path of the node " << end.number << " from the node " << star.number << " is " << dist[end.block][end.number] << endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////打印从起点s到顶点i的限制顶点数为k的最短路径，n一点要设为限制顶点数-1//////////////////////////////////////////////////////
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

	if (end.number != star.number)   //s为起点
	{
		printf_path(star, pre[n][end.block][end.number], n, specialVertex, numOfSpecialVer); //k为限制的顶点数
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

/////////////////////////////////////第三部分，打印最短路径权重和以及最短路径（结束）///////////////////////////////////////////////////////////////////////////

int main()
{
	//////////////////////////////////////输入部分////////////////////////////////////////////////////////////////////////////////////
	string location;
	cout << "请按下面格式输入描述图的文件的txt文件的路径（图的起点默认为0，终点默认为最大的编号）：" << endl;
	cout << "C:\\Users\\lin\\Desktop\\temporary\\data.txt" << endl;
	cin >> location;

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
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////建模部分////////////////////////////////////////////////////////////////
	PointUnionLists List = initPointUnion(numOfVertex, numOfSpecialVer);          //初始化一个邻接表结构数组
	link(List, specialVertex, numOfSpecialVer);                                   //将邻接表结构数组中的每一个邻接表通过某些点相连相互关联起来
	make_table(List,location);                                                             //用data.txt文件给邻接表数组内的每一个邻接表赋值
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////计算部分////////////////////////////////////////////////////////////////////
	node star, end;                //定义终点和起点的结构                         
	star.block = 0;                //起点定义为第0个邻接表矩阵的第0个点
	star.number = 0;
	end.block = List->num - 1;      //终点定义为邻接表结构数组List内最后一个邻接表的最后一个点
	end.number = List->PointU->graph->data - 1;

	computer_pre(0, Limit_num_nodes, List, numOfSpecialVer, specialVertex, isRoundPoint, isRoundNum);   //计算最短路径的函数及记录最短路径,默认起点为0，终点为最大的编号
	while(dist[end.block][end.number] == Inf)
	{
		cout << "当约束最多经过点的个数为" << Limit_num_nodes << "时不存在路径从起点到达终点，请重新输入最多经过点的个数" << endl;
		cin >> Limit_num_nodes;
		computer_pre(0, Limit_num_nodes, List, numOfSpecialVer, specialVertex, isRoundPoint, isRoundNum);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////打印部分///////////////////////////////////////////////////////////////////
	

	printf_weight(star, end);        //打印从起点到终点的最短路径的总权重
	shortest_path_num_vertes = 0;    
	printf_path(star, end, Limit_num_nodes - 1, specialVertex, numOfSpecialVer);   //打印最短路径
	cout << endl;
	cout << "此最短路径的顶点数为：" << shortest_path_num_vertes << endl;           //打印所经过的顶点的个数
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return 0;

}

