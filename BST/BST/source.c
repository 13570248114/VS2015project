#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char mo[12][20] = { "January","February","March","April","May","June","July","August","September","October","November","December" };

typedef struct node Node;
struct node
{
	long key;
	int day;
	int month;
	char year[3];
	Node* next;
};

Node* insertnode(Node* head, Node* node)
{
	if (head == NULL)
		head = node;
	else
	{
		Node* q = head;
		while (q->next != NULL)
			q = q->next;
		q->next = node;
	}
	return head;
}

typedef struct tree Tree;
struct tree{
	long key;
	Tree* left;
	Tree* right;
	Tree* father;
	char first_name[20];
	char last_name[20];
	int day;
	char month[20];
	char year[3];
};

Tree* insert(Tree* head, Tree* node,Tree* father)
{
	if (head == NULL)
	{
		head = node;
		head->father = father;
	}
	else
	{
		if (node->key > head->key)
			head->right = insert(head->right, node, head);
		else if (node->key < head->key)
			head->left = insert(head->left, node, head);
	}
	return head;
}

Tree* input(Node *nodehead)
{
	char temp[20];
	long i;
	Tree* T, *head;
	head = NULL;
	scanf("%s", temp);
	if (strcmp(temp, "BIRTHDAYS_START")==0)
	{
		while(1)
		{
			T = (Tree*)malloc(sizeof(Tree));
			scanf("%s", T->month);
			if (strcmp(T->month, "QUERIES_START") == 0) break;
			scanf("%d%s%s%s", &T->day, T->year, T->first_name, T->last_name);
			T->left = T->right = NULL;
			T->key = 0;
			for (i = 1; i <= 12; i++)
				if (strcmp(T->month, mo[i - 1])==0)
					T->key += i * 100;
			i = (T->year[0] - '0') * 10 + (T->year[1] - '0');
			if (i > 16)
				i += 1900;
			else
				i += 2000;
			T->key += i * 10000;
			T->key += T->day;
			head=insert(head, T, NULL);
		}
		return head;
	}
}

Tree* search(Tree* head, Node* node, Tree* father)
{
	if (head == NULL)
	{
		Tree* q;
		long k3 = node->key;
		q = father;
		while (q&&q->key < k3)
			q = q->father;
		return q;
	}
	
		
		
	if ((node->key) < (head->key))
		return search(head->left,node,head);
	else
		if ((node->key) > (head->key))
			return search(head->right,node,head);
		else
			return head;
}



int main()
{
	long i;
	Node* nodehead = NULL;
	Node* q = NULL;
	Tree* temp;
	Tree* t=input(nodehead);
	Node* no1= malloc(sizeof(Node));
	while (scanf("%d%d%s", &no1->day, &no1->month, no1->year) != EOF)
	{
		Node* no = malloc(sizeof(Node));
		no->day = no1->day;
		no->month = no1->month;
		strcpy(no->year, no1->year);
		i = (no->year[0] - '0') * 10 + (no->year[1] - '0');
		if (i > 16)
			i += 1900;
		else
			i += 2000;
		no->key = i * 10000;
		no->key += (no->month) * 100 + no->day;
		no->next = NULL;
		nodehead=insertnode(nodehead, no);
	}
	q = nodehead;
	while (q)
	{
		temp = search(t, q,NULL);
		if(temp==NULL)
			printf("no subsequent birthday\n");
		else if (temp->key == q->key)
			printf("%s %s\n", temp->first_name, temp->last_name);
		else 
			printf("first subsequent birthday: %s %s\n", temp->first_name, temp->last_name);
		q = q->next;
	}
}
