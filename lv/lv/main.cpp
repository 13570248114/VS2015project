#include<iostream>
#include<map>
using namespace std;

typedef struct TreeNode *Position;
struct TreeNode {
	int vertex;
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
	adja->table = (Position*)malloc(sizeof(Position)*(adja->numVertex + 1));
	if (adja->table == NULL)
		cout << "Error";

	//���ڽӱ�ÿһ���������һ�������ͷ
	for (int i = 0; i < adja->numVertex; i++) {
		adja->table[i] = (Position)malloc(sizeof(TreeNode));
		if (adja->table[i] == NULL)
			cout << "Error";
		else {
			adja->table[i]->vertex = i;
			adja->table[i]->Next = NULL;
		}
	}
	return adja;
}

void Insert(adjaceency adja, int per_ver, int aft_ver)
{
	//����һ������ڵ��ַ
	Position inser = (Position)malloc(sizeof(TreeNode));
	if (inser == NULL)
		cout << "Error";

	//��ͷ���룬�޸�ָ��
	inser->vertex = aft_ver;
	inser->Next = adja->table[per_ver]->Next;
	adja->table[per_ver]->Next = inser;
}

void dfs(adjaceency adja, int per_ver)
{
	Position p = adja->table[per_ver]->Next;
	while (p != nullptr)
	{
		dfs(adja, p->vertex);
		p = p->Next;
	}

}

int main()
{

	int n, L;
	cin >> n >> L;
	adjaceency adja = initAdjaceency_list(n);
	int* parent = (int*)malloc(sizeof(int)*n);
	//parent[0] = 0;
	for (int i = 0;i < n - 1;i++)
		cin >> parent[i];
	for (int i = 0;i < n - 1;i++)
	{
		Insert(adja, parent[i], i + 1);
		Insert(adja, i+1, parent[i]);
	}
	for (int i = 0;i < L;i++)
	{
		adja->table[0]->Next->vertex;
	}
}

