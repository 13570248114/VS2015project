#include"BST.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	BST root = makeBST(NULL);
	FILE *fp;
	if ((fp = fopen("invertedIndex.txt", "w")) == NULL)               //打开操作不成功
	{
		printf("pagerankList.txt can not be opened.\n");
		exit(1);                                                             //结束程序的执行
	}
	PrintBST(root,fp);
	destoryBST(root);
}