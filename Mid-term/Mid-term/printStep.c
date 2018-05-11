#include"head.h"

void printStep(Equation equ, int nStep)
{
	printf(" - Step %d - \n", nStep);
	for (int i = 0;i <equ.n;i++)
	{
		printf("\t|");
		for (int j = 0;j <equ.n;j++)
		{ 
			printf("%-10.4f ",equ.A[i][j]);
		}
		printf("| %-10.4f |\n",equ.b[i]);
	}
	printf("\n\n");
}