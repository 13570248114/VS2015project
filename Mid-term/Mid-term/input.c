#include"head.h"

void input(Equation * equ)
{
	printf("Enter the number of Equation: ");
	scanf("%d", &equ->n);
	//Dynamic application of memory space for matrix A and b
	equ->A = (double**)malloc(sizeof(double*)*(equ->n));
	for (int i = 0;i < equ->n;i++)
		equ->A[i] = (double*)malloc(sizeof(double)*(equ->n));
	equ->b = (double*)malloc(sizeof(double)*(equ->n));
	
	char select;
	do {
		//input
		for (int i = 0;i < equ->n;i++)
		{
			for (int j = 0;j < equ->n;j++)
			{
				printf("Enter the a%d%d: ", i, j);
				scanf("%lf", &equ->A[i][j]);
			}
			printf("Enter the b%d: ", i);
			scanf("%lf", &equ->b[i]);
		}
	   //output matrix A
		printf("You input is\n");
		int mid = equ->n / 2;
		for (int i = 0;i < equ->n;i++)
		{
			if (i == mid)
				printf("A = |");
			else
				printf("    |");
			for (int j = 0;j < equ->n;j++)
			{
				printf("%-10.4f", equ->A[i][j]);
			}
			printf("|\n");
		}
		printf("\n");

		//output b
		for (int i = 0;i <equ->n;i++)
		{
			if (i == mid)
				printf("b = |");
			else
				printf("    |");
			printf("%-10.4f", equ->b[i]);
			printf("|\n");
		}
		getchar();
		printf("\nIs this correct?(y/n): ");
		scanf("%c", &select);
	} while (select != 'y');
}