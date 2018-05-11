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
		if ((fp = fopen(file, "r")) == NULL)               //�򿪲������ɹ�
		{
			printf("%s can not be opened.\n", file);
			exit(1);                                                             //���������ִ��
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
					root = insertBST(root, word, node->url);                //�ѵ��ʲ��뵥����
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
	if (word[len - 1] == '.' || word[len - 1] == ',' || word[len - 1] == ';' || word[len - 1] == '?')          //ȥ�����ʺ�����ַ�
	{
		word[len - 1] = '\0';
		--len;
	}
	for (int i = 0;i < len;i++)                                                   //�����ʻ�ΪСд
		if (word[i] >= 'A'&&word[i] <= 'Z')
			word[i] += 'a' - 'A';
	return word;
}

BST insertBST(BST root, char* word, char* url)
{
	if (root == NULL)                            //���ʲ��������򴴽�һ���½ڵ�
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
			root->Urls = insertNode_sort(root->Urls, url);                //����õ����Ѿ������ϣ���url��ӵ������������ڵ��url������
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

void destoryBST(BST root)                                //�ͷſռ�
{
	if (root != NULL)
	{
		destoryBST(root->left);                             //���ͷ����������ӽڵ�Ŀռ�
		destoryBST(root->right);
		freeList(root->Urls);                                   //���ͷŽڵ��ڵ�����
		free(root);                                                 //����ͷű��ڵ�
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
	if (root == NULL)                            //���ʲ��������򴴽�һ���½ڵ�
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
		destoryBST_URL(root->left);                             //���ͷ����������ӽڵ�Ŀռ�
		destoryBST_URL(root->right);
		free(root);                                                 //����ͷű��ڵ�
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