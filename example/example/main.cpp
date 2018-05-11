#include<iostream>
using namespace std;

#define Inf 65536
int **pre;     //ֱ��ǰ���ڵ�������������·��
int Num_nodes = 7;   //�ܵĽڵ�������Ϊȫ�ֱ���
					 //int **cost;     //ͼ���ڽӾ���������ȫ�ֱ���
int *dist, *pdist;  //��¼��㵽�ڵ�ĵ�ǰ���·��


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
cost[p][q] = 0;    //�Խ��߸�ֵΪ0
}
else
{
cost[p][q] = Inf;       //��������ֵΪInf
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

void computer_pre(int star, int Limit_num_nodes)    //����pre����starΪ���,Limit_num_nodesΪ���ƵĽڵ���
{

	// decltype(pree) pre;

	pre = static_cast<int**>(malloc(sizeof(int*)*(Limit_num_nodes - 1)));   //������ƵĽڵ���ΪLimit_num_nodes����ôpre�����Ӧ����Limit_num_nodes - 1��
	for (int i = 0; i != Limit_num_nodes - 1; ++i)
	{
		pre[i] = static_cast<int*>(malloc(sizeof(int)*Num_nodes));   //��ÿһ��pre��������Num_nodes��λ��
	}

	for (int m = 0; m != Limit_num_nodes - 1; ++m)    //��pre�������е�Ԫ�س�ʼ��Ϊ�����
	{
		for (int j = 0; j != Num_nodes; ++j)
		{
			pre[m][j] = star;
		}
	}
	dist = static_cast<int*>(malloc(sizeof(int)*Num_nodes));   //dist[j]��¼��㵽�ڵ�j�ĵ�ǰ���·��
	pdist = static_cast<int*>(malloc(sizeof(int)*Num_nodes));  //pdist�����¼��һ��ѭ��dist�����ֵ
	for (int i = 0; i != Num_nodes; ++i)
	{
		dist[i] = cost[star][i];      //ȫ����ʼ��
		pdist[i] = cost[star][i];
	}

	for (int m = 1; m != Limit_num_nodes - 1; ++m)   //Limit_num_nodesΪ���ƵĽڵ���
	{
		for (int j = 0; j != Num_nodes; ++j) //Num_nodesΪ�ܵĽڵ���
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
			pdist[u] = dist[u]; // �˴�Ϊ��dist��ֵȫ������pdist����1 <= u <= n
		}

	}
	//delete dist;    //�ͷ��ڴ�
	//delete pdist;

}

void printf_weight(int star, int i)   //���star���ڵ�i�����·��
{
	cout << "the shortest path of the node " << i << " from the node " << star << " is " << dist[i] << endl;
}




void printf_path(int star, int i, int n)  //��ӡ�����s���ڵ�i�����ƽڵ���Ϊk�����·����nΪ���ƽڵ���-1
{
	n--;
	if (i != star)   //sΪ���
	{
		printf_path(star, pre[n][i], n); //kΪ���ƵĽڵ���
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




	for (int p = 0; p != Num_nodes; ++p)              //��ӡcost
	{
		for (int q = 0; q != Num_nodes; ++q)
		{
			cout << cost[p][q] << "\t";
		}
		cout << endl;
	}
	cout << endl;

	computer_pre(0, 3);   //���Ϊ0�����ƽڵ���Ϊ4
	printf_weight(0, 5);
	printf_path(0, 5, 2);
	cout << endl;
	computer_pre(5, 3);   //���Ϊ0�����ƽڵ���Ϊ4
	printf_weight(5, 6);
	printf_path(5, 6, 2);


	while (1);

	return 0;
}
