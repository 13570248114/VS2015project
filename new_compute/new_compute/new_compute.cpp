// new_compute.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;

#define Inf 65536
#define num_of_Vertex 7

int cost[7][7] = { { 0,  1,  Inf ,Inf,Inf,Inf,Inf },
{ 1, 0,  1,Inf, Inf , Inf ,1 },
{ Inf,1, 0 , 1,Inf, Inf ,Inf },
{ Inf,Inf,1, 0 , 1 ,Inf, Inf },
{ Inf,Inf,Inf,1, 0 ,1, Inf },
{ Inf,Inf,Inf, Inf , 1 , 0 ,2 },
{ Inf,1,Inf,Inf,Inf,2, 0 }
};

struct Vertex
{
	int value;
	bool ishave;
};

int min(int i, int j)
{
	return i < j ? i : j;
}

Vertex ver[num_of_Vertex];
int D[num_of_Vertex][num_of_Vertex];
int preD[num_of_Vertex][num_of_Vertex];
void compute()
{
	for (int i = 0;i <= num_of_Vertex;i++)
	{
		ver[i].value = i;
		ver[i].ishave = false;
	}
	ver[3].value = true;
	ver[4].value = true;

	for (int i = 0;i < num_of_Vertex;i++)
		for (int j = 0;j < num_of_Vertex;j++)
			D[i][j] = cost[i][j];

	for (int k = 1;k < num_of_Vertex;k++)
	{
		for (int i = 0;i < num_of_Vertex;i++)
			for (int j = 0;j < num_of_Vertex;j++)
			{
				preD[i][j] = D[i][j];
			}

		for (int i = 0;i <= num_of_Vertex;i++)
			for (int j = 0;j < num_of_Vertex;j++)
			{
				//if (k==2)  D[i][j] = preD[i][k] + preD[k][j];
				//else
				    D[i][j] = min(preD[i][j], preD[i][k] + preD[k][j]);
			}		
	}

	for (int k = 1;k < num_of_Vertex;k++)
	{
		for (int i = 0;i < num_of_Vertex;i++)
			for (int j = 0;j < num_of_Vertex;j++)
			{
				preD[i][j] = D[i][j];
			}

		for (int i = 0;i <= num_of_Vertex;i++)
			for (int j = 0;j < num_of_Vertex;j++)
			{
				if (k==2||k==4)
				{
					D[i][j] = preD[i][k] + preD[k][j];
					ver[i].ishave = false;
				}
				else
				   D[i][j] = min(preD[i][j], preD[i][k] + preD[k][j]);
			}
	}


	for (int i = 0;i < num_of_Vertex;i++)
	{
		for (int j = 0;j < num_of_Vertex;j++)
			cout << D[i][j] << '\t';
		cout << endl;
	}
}
int main()
{
	compute();
    return 0;
}

