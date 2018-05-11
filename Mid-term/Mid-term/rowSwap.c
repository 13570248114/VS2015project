#include"head.h"

void rowSwapNoZero(Equation* equ, int row)
{
	for (int nrow = row + 1;nrow < equ->n;nrow++)     
	{
		if (equ->A[nrow][row] != 0)          // Looking for a row in whch the A[nrow][row] is not 0
		{
			for (int k = 0;k < equ->n;k++)    //Interchange two row
			{
				equ->A[nrow][k] += equ->A[row][k];
				equ->A[row][k] = equ->A[nrow][k] - equ->A[row][k];
				equ->A[nrow][k] -= equ->A[row][k];
			}
			equ->b[nrow] += equ->b[row];
			equ->b[row] = equ->b[nrow] - equ->b[row];
			equ->b[nrow] -= equ->b[row];
			break;
		}
	}
}