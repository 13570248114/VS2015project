#include"BST.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	FILE *fp;
	BST root = makeBST(NULL);
	if ((fp = fopen("invertedIndex.txt", "w")) == NULL)               //If the opening operation is unsuccessful, the execution mode
	{
		printf("pagerankList.txt can not be opened.\n");
		exit(1);                                                             //End the implementation of the program
	}
	PrintBST(root,fp);
	destoryBST(root);
}
