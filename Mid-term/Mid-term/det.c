#include"head.h"


void swap(int* a, int* b)         //Exchange the values of a and b
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

bool negative(Equation equ, int* source)      //To determine whether the sign of each item is positive or negative
{
	int n = 0;
	for (int i = 0;i < equ.n - 1;i++)                //Calculate the reverse order number
		for (int j = i + 1;j < equ.n;j++)
			if (source[i] > source[j])
				n++;
	if (n % 2 == 0)
		return false;
	return true;
}

void calculate(Equation equ, int* source, int begin, int end, double* result)      //Find all combinations of different rows and different columns, calculate the matrix determinant  recursively
{
	double item = 1;
	if (begin == end)                                                                              
	{
		for (int row = 0;row < equ.n; row++)
			item *= equ.A[row][source[row]];
		if (negative(equ, source))
			item *= -1;
		*result += item;
	}
	else
	{
		for (int i = begin;i <= end;i++)
		{
			swap(source + begin, source + i);
			calculate(equ, source, begin + 1, end,result);
			swap(source + begin, source + i);
		}
	}
}

double det(Equation equ)                                                                       
{
	int* source = (int*)malloc(sizeof(int)*equ.n);
	for (int i = 0;i < equ.n;i++)
		source[i] = i;                                                    //The initial sequence of columns            
	double result = 0;
	calculate(equ, source, 0, equ.n - 1, &result);             //Calculate the determinant
	return result;
}