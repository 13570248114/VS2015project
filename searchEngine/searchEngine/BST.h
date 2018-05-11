#ifndef BST_H
#define BST_H
#include"readData.h"
typedef struct BST_node
{
	char word[20];
	urlList Urls;
	struct BST_node* left;
	struct BST_node* right;
}BST_node;

typedef BST_node* BST;

char* normalise_word(char* word);
BST insertBST(BST root, char* word, char* url);
BST makeBST();
void PrintBST(BST root, FILE *fp);
void destoryBST(BST root);
urlList findURL(BST root, char* word);

typedef struct BST_URL_node
{
	char url[20];
	double PR;
	struct BST_URL_node* left;
	struct BST_URL_node* right;
}BST_URL_node;

typedef BST_URL_node* BST_URL;

BST_URL insertBST_URL(BST_URL root, char* url, double PR);
void destoryBST_URL(BST_URL root);
double findPR(BST_URL root, char* url);
void PrintBST_URL(BST_URL root);

#endif // !BST_H

