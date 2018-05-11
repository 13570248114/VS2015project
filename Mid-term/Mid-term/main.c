#include"head.h"

int main()
{
	Equation equ ;
	input(&equ);
	if (abs(det(equ)) <= 1e-15)                  //if det(A)==0,then no answer
		printf("|A| = 0, so no unique answer or no answer\n");
	else
	{
		printf("All intermediate steps are as follows\n");
		int step = 0;                                // count the steps
		printStep(equ, step);                    //print A and b in step n
		for (int col = 0;col < equ.n-1;col++) //Change matrix A to upper triangular matrix
		{
			if (equ.A[col][col] == 0)           //If the element on the diagonal is 0, find other row to exchange
			{
				rowSwapNoZero(&equ, col);
				step++;
				printStep(equ, step);
			}

			for (int row = col + 1;row < equ.n;row++)          // make the col-th column's element which under the diagonal be zero
			{
				double temp = equ.A[row][col] / equ.A[col][col];
				equ.b[row] -= temp*equ.b[col];
				for (int ncol = 0;ncol < equ.n;ncol++)
					equ.A[row][ncol] -= temp*equ.A[col][ncol];
			}
			step++;
			printStep(equ, step);
		}

		for (int col = equ.n - 1;col > 0;col--)               //Make the upper triangular matrix into a diagonal matrix
		{
			for (int row = col - 1;row >= 0;row--)
			{
				double temp = equ.A[row][col] / equ.A[col][col];
				equ.b[row] -= temp*equ.b[col];
				equ.A[row][col] = 0;
			}
			step++;
			printStep(equ, step);
		}

		for (int row = 0;row < equ.n;row++)                //Change the elements on the diagonal to 1
		{
			equ.b[row] /= equ.A[row][row];
			equ.A[row][row] = 1;
		}
		step++;
		printStep(equ, step);
		
		printf("<Answer>\n");                                //Print the answer
		int mid = equ.n / 2;
		for (int i = 0;i <equ.n;i++)
		{
			if (i == mid)
				printf("x = |");
			else
				printf("    |");
			printf("%-10.4f", equ.b[i]);
			printf("|\n");
		}
	}
}
