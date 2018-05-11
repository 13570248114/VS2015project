#include"BST.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

BST makeBST()
{
	BST root = NULL;
	urlList List_of_Urls = GetCollection();
	urlNode* node = List_of_Urls->head;
	char word[20];
	char *t = ".txt";
	FILE *fp;
	int num = 0;
	while (node != NULL)
	{
		char file[20];
		num = 0;
		strcpy(file, node->url);
		strcat(file, t);
		if ((fp = fopen(file, "r")) == NULL)               //打开操作不成功
		{
			printf("%s can not be opened.\n", file);
			exit(1);                                                             //结束程序的执行
		}

		while (fscanf(fp, "%s", word) > 0)
		{
			if (num < 3 && word[0] == '#')
			{
				num++;
			}
			else if (num >= 3)
			{
				if (strcmp(word, "#start") == 0 || strcmp(word, "Section-1") == 0 || strcmp(word, "#end") == 0 || strcmp(word, "Section-2") == 0)
					continue;
				else
				{
					normalise_word(word);
					root = insertBST(root, word, node->url);                //把单词插入单词树
				}
			}
		}
		node = node->next;
	}
	return root;
}

char* normalise_word(char* word)
{
	int len = strlen(word);
	if (word[len - 1] == '.' || word[len - 1] == ',' || word[len - 1] == ';' || word[len - 1] == '?')          //去掉单词后面的字符
	{
		word[len - 1] = '\0';
		--len;
	}
	for (int i = 0;i < len;i++)                                                   //将单词化为小写
		if (word[i] >= 'A'&&word[i] <= 'Z')
			word[i] += 'a' - 'A';
	return word;
}

BST insertBST(BST root, char* word, char* url)
{
	if (root == NULL)                            //单词不在树上则创建一个新节点
	{
		root = (BST)malloc(sizeof(BST_node));
		root->left = root->right = NULL;
		strcpy(root->word, word);
		root->Urls = insertNode_sort(NULL, url);
	}
	else
	{
		if (strcmp(word, root->word) > 0)
			root->right = insertBST(root->right, word, url);
		else if (strcmp(word, root->word) < 0)
			root->left = insertBST(root->left, word, url);
		else
		{
			root->Urls = insertNode_sort(root->Urls, url);                //如果该单词已经在树上，则将url添加到单词所在树节点的url链表上
		}
	}
	return root;
}

void PrintBST(BST root, FILE *fp)
{
	if (root != NULL)
	{
		PrintBST(root->left, fp);
		printf("%s ", root->word);
//		fprintf(fp, "%s ", root->word);
		for (urlNode* node = root->Urls->head;node != NULL;node = node->next) {
			printf(" %s", node->url);
//			fprintf(fp, " %s", node->url);
		}
		printf("\n");
//		fprintf(fp, "\n");
		PrintBST(root->right, fp);
	}
}

void destoryBST(BST root)                                //释放空间
{
	if (root != NULL)
	{
		destoryBST(root->left);                             //先释放左右两个子节点的空间
		destoryBST(root->right);
		freeList(root->Urls);                                   //再释放节点内的链表
		free(root);                                                 //最后释放本节点
	}
}

urlList findURL(BST root, char* word)
{
	if (root != NULL)
	{
		if (strcmp(word, root->word) > 0)
			return findURL(root->right, word);
		else if (strcmp(word, root->word) < 0)
			return findURL(root->left, word);
		else
		{
			return root->Urls;
		}
	}
	else
		return NULL;
}

BST_URL insertBST_URL(BST_URL root, char* url, double PR)
{
	if (root == NULL)                            //单词不在树上则创建一个新节点
	{
		root = (BST_URL)malloc(sizeof(BST_URL_node));
		root->left = root->right = NULL;
		strcpy(root->url, url);
		root->PR = PR;
	}
	else
	{
		if (strcmp(url, root->url) > 0)
			root->right = insertBST_URL(root->right, url, PR);
		else if (strcmp(url, root->url) < 0)
			root->left = insertBST_URL(root->left, url, PR);
	}
	return root;
}

void destoryBST_URL(BST_URL root)
{
	if(root != NULL)
	{
		destoryBST_URL(root->left);                             //先释放左右两个子节点的空间
		destoryBST_URL(root->right);
		free(root);                                                 //最后释放本节点
	}
}

double findPR(BST_URL root, char* url)
{
	if (root != NULL)
	{
		if (strcmp(url, root->url) > 0)
			return findPR(root->right, url);
		else if (strcmp(url, root->url) < 0)
			return findPR(root->left, url);
		else
		{
			return root->PR;
		}
	}
	else
		return -1;
}

void PrintBST_URL(BST_URL root)
{
	if (root != NULL)
	{
		PrintBST_URL(root->left);
		printf("%s      %.7f\n", root->url, root->PR);
		PrintBST_URL(root->right);
	}
}