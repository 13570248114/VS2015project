#include"BST.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

BST makeBST()
{
	BST root = NULL;
	/*Get a list of words from collection.txt*/
	urlList List_of_Urls = GetCollection();
	urlNode* node = List_of_Urls->head;
	char word[20];
	char *t = ".txt";
	FILE *fp;
	int num = 0;

	while (node != NULL)
	{
		/*The url and. Txt splicing, open the corresponding url file*/
		char file[20];
		num = 0;
		strcpy(file, node->url);
		strcat(file, t);
		if ((fp = fopen(file, "r")) == NULL)               //Open operation is not successful
		{
			printf("%s can not be opened.\n", file);
			exit(1);                                                             //End the implementation of the program
		}
		/*Read the word inside the open url file*/
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
					root = insertBST(root, word, node->url);                //Insert the word into the word tree
				}
			}
		}
		node = node->next;                //Prepare to read the next url file
		fclose(fp);                             //Close the current file
	}
	return root;
}

char* normalise_word(char* word)                             //Word processing
{
	int len = strlen(word);
	int i;
	if (word[len - 1] == '.' || word[len - 1] == ',' || word[len - 1] == ';' || word[len - 1] == '?')          //Remove the characters after the word
	{
		word[len - 1] = '\0';
		--len;
	}
    for (i = 0;i < len;i++)                                                   //Turn words into lowercase
		if (word[i] >= 'A'&&word[i] <= 'Z')
			word[i] += 'a' - 'A';
	return word;
}

BST insertBST(BST root, char* word, char* url)
{
	if (root == NULL)                            //A word is not in the tree but a new node is created
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
			root->Urls = insertNode_sort(root->Urls, url);                //If the word is already in the tree, add the url to the url list of the tree node where the word is located
		}
	}
	return root;
}

void PrintBST(BST root, FILE *fp)
{
	if (root != NULL)
	{
		urlNode* node;
		PrintBST(root->left, fp);
		printf("%s ", root->word);
		fprintf(fp, "%s ", root->word);
		for (node = root->Urls->head;node != NULL;node = node->next) {
			printf(" %s", node->url);
			fprintf(fp, " %s", node->url);
		}
		printf("\n");
		fprintf(fp, "\n");
		PrintBST(root->right, fp);
	}
}

void destoryBST(BST root)                                //free space
{
	if (root != NULL)
	{
		destoryBST(root->left);                             //Firstly free of space around the two child nodes
		destoryBST(root->right);
		freeList(root->Urls);                                   //Then free the linked list within the node
		free(root);                                                 //Finally release the node
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
		else                                                    //have found
		{
			return root->Urls;
		}
	}
	else
		return NULL;                                     //do not find
}

BST_URL insertBST_URL(BST_URL root, char* url, double PR)
{
	if (root == NULL)                            //url is not in the tree to create a new node
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
		destoryBST_URL(root->left);                             //Firstly free of space around the two child nodes
		destoryBST_URL(root->right);
		free(root);                                                 //Finally free the node
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
