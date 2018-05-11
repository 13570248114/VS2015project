#ifndef BST_H
#define BST_H
#include"readData.h"
typedef struct BST_node                    //Binary tree to the word as a key, url list as a value
{
	char word[20];
	urlList Urls;
	struct BST_node* left;
	struct BST_node* right;
}BST_node;

typedef BST_node* BST;

char* normalise_word(char* word);
BST insertBST(BST root, char* word, char* url);         //Binary tree insert
BST makeBST();                                                    //Build a binary tree
void PrintBST(BST root, FILE *fp);                            //print a binary tree
void destoryBST(BST root);                                     //free a binary tree
urlList findURL(BST root, char* word);                       //Use the word as the key to find the url list

typedef struct BST_URL_node                                  //Binary tree, url as a key, PR value
{
	char url[20];
	double PR;
	struct BST_URL_node* left;
	struct BST_URL_node* right;
}BST_URL_node;

typedef BST_URL_node* BST_URL;

BST_URL insertBST_URL(BST_URL root, char* url, double PR);             //insert
void destoryBST_URL(BST_URL root);                                     //free
double findPR(BST_URL root, char* url);                                //Find the url corresponding PR
void PrintBST_URL(BST_URL root);                                       //Print binary tree

#endif // !BST_H

