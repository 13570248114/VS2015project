#include<iostream>
using namespace std;

#define Inf 65536
int **pre;     //直接前驱节点矩阵，用来求最短路径
int Num_nodes = 7;   //总的节点数，设为全局变量
					 //int **cost;     //图的邻接矩阵描述，全局变量
int *dist, *pdist;  //记录起点到节点的当前最短路径


int cost[7][7] = { { 0 , 5 , 4 ,Inf,Inf,Inf,Inf },
{ 5 , 0 , 3 ,Inf, 3 , 1 ,Inf },
{ 4 , 3 , 0 , 5 ,Inf, 4 ,Inf },
{ Inf,Inf, 5 , 0 , 2 , 2 , 2 },
{ Inf, 3 ,Inf, 2 , 0 , 2 , 4 },
{ Inf, 1 , 4 , 2 , 2 , 0 ,Inf },
{ Inf,Inf,Inf, 2 , 4 ,Inf, 0 }
};

/*
void make_cost ()
{
int v,w,weight;
cost = static_cast<int**>(malloc(sizeof(int*)*Num_nodes));
for(int i = 0; i != Num_nodes; ++i)
{
cost[i] = static_cast<int*>(malloc(sizeof(int)*Num_nodes));
}
for(int p = 0; p != Num_nodes; ++p)
{
for(int q = 0; q != Num_nodes; ++q)
{
if(q == p)
{
cost[p][q] = 0;    //对角线赋值为0
}
else
{
cost[p][q] = Inf;       //其他赋初值为Inf
}

}
}
cout << "Please enter the two nodes and the weights of them, be careful to iterate through all the edges" << endl;
while(cin >> v >> w >> weight)
{
cost[v][w] = weight;
cost[w][v] = weight;
}

}
*/

void computer_pre(int star, int Limit_num_nodes)    //计算pre矩阵，star为起点,Limit_num_nodes为限制的节点数
{

	// decltype(pree) pre;

	pre = static_cast<int**>(malloc(sizeof(int*)*(Limit_num_nodes - 1)));   //如果限制的节点数为Limit_num_nodes，那么pre矩阵就应该有Limit_num_nodes - 1行
	for (int i = 0; i != Limit_num_nodes - 1; ++i)
	{
		pre[i] = static_cast<int*>(malloc(sizeof(int)*Num_nodes));   //对每一行pre矩阵申请Num_nodes个位置
	}

	for (int m = 0; m != Limit_num_nodes - 1; ++m)    //把pre矩阵所有的元素初始化为起点编号
	{
		for (int j = 0; j != Num_nodes; ++j)
		{
			pre[m][j] = star;
		}
	}
	dist = static_cast<int*>(malloc(sizeof(int)*Num_nodes));   //dist[j]记录起点到节点j的当前最短路径
	pdist = static_cast<int*>(malloc(sizeof(int)*Num_nodes));  //pdist数组记录上一轮循环dist数组的值
	for (int i = 0; i != Num_nodes; ++i)
	{
		dist[i] = cost[star][i];      //全部初始化
		pdist[i] = cost[star][i];
	}

	for (int m = 1; m != Limit_num_nodes - 1; ++m)   //Limit_num_nodes为限制的节点数
	{
		for (int j = 0; j != Num_nodes; ++j) //Num_nodes为总的节点数
		{
			for (int i = 0; i != Num_nodes; ++i)
			{
				if (dist[j] > pdist[i] + cost[i][j])
				{
					dist[j] = pdist[i] + cost[i][j];
					pre[m][j] = i;
				}
			}
			if (dist[j] == pdist[j])
			{
				pre[m][j] = pre[m - 1][j];
			}
		}
		for (int u = 0; u != Num_nodes; ++u)
		{
			pdist[u] = dist[u]; // 此处为把dist的值全部赋给pdist，即1 <= u <= n
		}

	}
	//delete dist;    //释放内存
	//delete pdist;

}

void printf_weight(int star, int i)   //起点star到节点i的最短路径
{
	cout << "the shortest path of the node " << i << " from the node " << star << " is " << dist[i] << endl;
}




void printf_path(int star, int i, int n)  //打印从起点s到节点i的限制节点数为k的最短路径，n为限制节点数-1
{
	n--;
	if (i != star)   //s为起点
	{
		printf_path(star, pre[n][i], n); //k为限制的节点数
		cout << "->";
	}
	cout << "v" << i;

}

/*
int cost[7][7] = {{ 0,  5,  4 ,Inf,Inf,Inf,Inf},
{Inf, 0,  3 ,Inf, 3 , 1 ,Inf},
{Inf,Inf, 0 , 5 ,Inf, 4 ,Inf},
{Inf,Inf,Inf, 0 , 2 ,Inf, 2 },
{Inf,Inf,Inf,Inf, 0 ,Inf, 4 },
{Inf,Inf,Inf, 2 , 2 , 0 ,Inf},
{Inf,Inf,Inf,Inf,Inf,Inf, 0 }
};
*/






int main()
{

	//cout << "Please enter the number of nodes" << endl;
	//cin >> Num_nodes;
	//make_cost ();




	for (int p = 0; p != Num_nodes; ++p)              //打印cost
	{
		for (int q = 0; q != Num_nodes; ++q)
		{
			cout << cost[p][q] << "\t";
		}
		cout << endl;
	}
	cout << endl;

	computer_pre(0, 3);   //起点为0，限制节点数为4
	printf_weight(0, 5);
	printf_path(0, 5, 2);
	cout << endl;
	computer_pre(5, 3);   //起点为0，限制节点数为4
	printf_weight(5, 6);
	printf_path(5, 6, 2);


	while (1);

	return 0;
}
