#ifndef HEAD_H
#define HEAD_H
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

typedef struct {             //Matrix equation structure
	double **A;
	double *b;
	int n;
}Equation;

void input(Equation * equ);                    //input function 
void printStep(Equation equ, int nStep);   //Output the matrix of each step
double det(Equation equ);                      //Calculate the determinant of A
void rowSwapNoZero(Equation* equ, int i);   //If the diagonal element is 0, the line is exchanged
int main();               
#endif // !HEAD_H
