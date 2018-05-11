// zhongxing_pengyue.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include<iostream>
using namespace std;

#define Inf 65536
#define k  3


int dist[7], pdist[7];
int pre[k-2+1][7];   //!!!!!!!!!

int cost[7][7] = { { 0,  5,  4 ,Inf,Inf,Inf,Inf },
{ Inf, 0,  3 ,Inf, 3 , 1 ,Inf },
{ Inf,Inf, 0 , 5 ,Inf, 4 ,Inf },
{ Inf,Inf,Inf, 0 , 2 ,Inf, 2 },
{ Inf,Inf,Inf,Inf, 0 ,Inf, 4 },
{ Inf,Inf,Inf, 2 , 2 , 0 ,Inf },
{ Inf,Inf,Inf,Inf,Inf,Inf, 0 }
};
/*
int cost[7][7] = {{ 0 , 5 , 4 ,Inf,Inf,Inf,Inf},
{ 5 , 0 , 3 ,Inf, 3 , 1 ,Inf},
{ 4 , 3 , 0 , 5 ,Inf, 4 ,Inf},
{Inf,Inf, 5 , 0 , 2 , 2 , 2 },
{Inf, 3 ,Inf, 2 , 0 , 2 , 4 },
{Inf, 1 , 4 , 2 , 2 , 0 ,Inf},
{Inf,Inf,Inf, 2 , 4 ,Inf, 0 }
};
*/



void make_cost(int Num_nodes)
{
	int **cost;
	cost = static_cast<int**>(malloc(sizeof(int*)*Num_nodes));
	for(int i=0;i<Num_nodes;i++)
		cost[i] = static_cast<int*>(malloc(sizeof(int)*Num_nodes));
	for (int p = 0; p != Num_nodes; ++p)
	{
		for (int q = 0; q != Num_nodes; ++q)
		{
			cost[p][q] = Inf;
		}
	}

}


void printf(int i)
{
	cout << "the shortest path of node " << i << " is " << dist[i] << endl;
}

void printf_path(int i, int s, int n)  //��ӡ�����s���ڵ�i�����ƽڵ���Ϊk�����·������������������������������
{
	if (i != s)   //sΪ���
	{
		printf_path(pre[n--][i], s, n); //kΪ���ƵĽڵ�������������������������������������
		cout << "->";
	}
	cout << "v" << i;

}

void computer_pre(int star)    //starΪ���
{
	for (int m = 0; m <=k-2; ++m)//////////////////����������������������������
	{
		for (int j = 0; j != 7; ++j)
		{
			pre[m][j] = star;
		}
	}

	for (int i = 0; i != 7; ++i)
	{
		dist[i] = cost[star][i];
		pdist[i] = cost[star][i];
	}

	for (int m = 1; m <= k - 2; ++m)   //kΪ���ƵĽڵ���
	{
		for (int j = 0; j != 7; ++j) //nΪ�ܵĽڵ���
		{
			for (int i = 0; i != 7; ++i)
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
		for (int u = 0; u != 7; ++u)
		{
			pdist[u] = dist[u]; // �˴�Ϊ��dist��ֵȫ������pdist����1 <= u <= n
		}

	}

	///////////////////////////////////////////////////////////////////////!!!!!!!!!!!!!!!
	for (int m = 0; m <= k - 2; ++m)
	{
		for (int j = 0; j != 7; ++j)
		{
			cout<<pre[m][j]<<'\t';
		}
		cout << endl;
	}
}




int main()
{
	
	//computer_pre(0);
	//printf(5);
	//printf_path(5, 0, k-2);  //��ӡ�����s���ڵ�i�����ƽڵ���Ϊk�����·��!!!!!!!!!!!!!!
	//cout << endl;

    //computer_pre(5);
	//printf(6);
    //printf_path(6, 5, k-2);  //��ӡ�����s���ڵ�i�����ƽڵ���Ϊk�����·��!!!!!!!!!!!!!!


	//cout << endl;
	//int Num_nodes;
	//cout << "Please enter the number of nodes" << endl;
	//cin >> Num_nodes;
	return 0;
}

