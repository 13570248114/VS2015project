#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int row, col, v;
	struct node *down, *right;
}Node;

typedef struct
{
	int mu, nu, tu; 
	Node *rlink[5000], *clink[5000];
}CrossLink;

CrossLink *CreatCrossLink2(CrossLink *H, int i, int j, int v)
{
	Node *p, *q;
	p = (Node *)malloc(sizeof(Node));
	p->row = i;
	p->col = j;
	p->v = v;
	q = H->rlink[i];
	if (q == NULL || q->col>j) 
	{
		p->right = q;
		H->rlink[i] = p;
	}
	else
	{
		while (q->right && (q->right->col)<j)
			q = q->right;
		p->right = q->right;
		q->right = p;         
	}

	q = H->clink[j];
	if (q == NULL || q->row>i)
	{
		p->down = q;
		H->clink[j] = p;
	}
	else
	{
		while (q->down && (q->down->row)<i)
			q = q->down;
		p->down = q->down;
		q->down = p;   
	}
	return H;
}

CrossLink *CreatCrossLink1(CrossLink *H)
{
	int  maxi=0, maxj=0, k;
	H = (CrossLink *)malloc(sizeof(CrossLink));
	scanf("%d", &H->tu); 
	if ((H->tu) < 0)
		return H;
	Node *no =(Node*) malloc(sizeof(Node)*(H->tu));

	for (k = 0;k < H->tu;k++)
	{
		scanf("%d%d%d", &no[k].row,&no[k].col,&no[k].v);
		if (no[k].row > maxi) maxi = no[k].row;
		if (no[k].col > maxj) maxj = no[k].col;
	}
	H->mu = (maxi >= maxj ? maxi : maxj);
	H->nu = H->mu;

	for (k = 0;k <= H->mu;k++)
		H->rlink[k] = NULL;
	for (k = 0;k <= H->nu;k++)
		H->clink[k] = NULL;

	for (k = 0;k < H->tu;k++)
	{
		CreatCrossLink2(H, no[k].row, no[k].col, no[k].v);
	}
	return H;
}


int main()
{
	CrossLink *A, *B, *C;
	Node *aq, *bq, *q;
	int i, k, temp;
	C = (CrossLink *)malloc(sizeof(CrossLink));
	A = (CrossLink *)malloc(sizeof(CrossLink));
	B = (CrossLink *)malloc(sizeof(CrossLink));

	A = CreatCrossLink1(A);
	B = CreatCrossLink1(B);
	
	if (((A->tu) < 0) || ((B->tu) < 0))
		return 0;
	C->mu = A->mu;
	C->nu = B->nu;
	
	if (A->tu*B->tu == 0)
	{
		return 0;
	}
	else
	{
		for (k = 0;k <= C->mu;k++)
			C->rlink[k] = NULL;
		for (k = 0;k <= C->nu;k++)
			C->clink[k] = NULL;

		C->tu = 0;

		for (i = 0;i <= (A->mu);i++)
		{
			q = A->rlink[i];
			if (q)
			{
				for (int j = 0;j <= B->nu;j++)
				{
					temp = 0;
					aq = q;
					bq = B->clink[j];
					while (aq&&bq)
					{
						if (aq->col == bq->row)
						{
							temp = temp + (aq->v)*(bq->v);
							aq = aq->right;
							bq = bq->down;
						}
						else if (aq->col < bq->row)
							aq = aq->right;
						else
							bq = bq->down;
					}

					if (temp != 0)
					{
						(C->tu)++;
						CreatCrossLink2(C, i, j, temp);
					}
				}
			}
		}
		
		if ((C->tu) != 0)
		{
			printf("SHOULD BE:\n");
			for (i = 0;i <= C->mu;i++)
			{
				q = C->rlink[i];
				while (q)
				{
					printf("%d %d %d\n", q->row, q->col, q->v);
					q = q->right;
				}
			}
		}
	}
	return 0;

}