#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"BST.h"
#include"readData.h"

typedef struct wordListNode {           //Word list node
	char word[20];
	struct wordListNode* next;
}wordListNode;

typedef struct wordList {             //Record the head and tail pointer of the word list
	wordListNode* head;
	wordListNode* tail;
}wordList;

wordList* insertWord(wordList* wl, char* word)                   //Insert a word into the word list and insert it from the back
{
	wordListNode* node = (wordListNode*)malloc(sizeof(wordListNode));
	strcpy(node->word, word);
	node->next = NULL;

	if (wl == NULL)
	{
		wl = (wordList*)malloc(sizeof(wordList));
		wl->head = wl->tail = node;
	}
	else
	{
		wl->tail->next = node;
		wl->tail = node;
	}
	return wl;
}

void freeWordList(wordList* wl)           //free the list
{
	wordListNode* node = wl->head;
	wordListNode* pnode = node;
	while (node != NULL)
	{
		pnode = node;
		node = node->next;
		free(pnode);
	}
	free(wl);
}

wordList* get_words_from_line(char* line)                    //Extract words from one line of characters
{
	wordList* wl = NULL;
	int len = strlen(line);
	char word[20];
	int j = 0;
	if(len==0)
		return NULL;
	while (line[len - 1] == ' '|| line[len - 1]=='\n')                                           //Remove the trailing white space and newline characters
		len--;

	for (int i = 0;i < len;i++)
	{
		if (line[i] != ' '&&line[i] != ',') {                                                   //If not delimiter then put the character stored in word [j]
			word[j] = line[i];
			j++;
		}
		else                                                                    //'\ 0' is added to the end of the word when it encounters a delimiter
		{
			word[j] = '\0';
			if(j > 0)
				wl = insertWord(wl, word);                              //Insert a word into the list
			j = 0;
		}
	}
	word[j] = '\0';                                                        //Handle the last word
	wl = insertWord(wl, word);
	return wl;
}


int main()
{
	int argc = 4;
	char* argv[4] = { "sss", "planet", "planets", "revealed" };
	char line[1000];
	char word[20];
	BST root = NULL;
	wordList* wl;
	wordListNode* node;
	char url[20];
	double PR;
	BST_URL root_url = NULL;
	int i;
	urlList urls;
	urlNode* unode;
	urlList URLs = NULL;                                   //Retrieve the resulting URL list, about to retrieve each word when the url is inserted into this list, called the search URL list
	/*open pagerankList.txt and invertedIndex.txt*/
	FILE *pagerankList, *invertedIndex;
	if ((pagerankList = fopen("pagerankList.txt", "r")) == NULL)               //Firstly open two files
	{
		printf("pagerankList.txt can not be opened.\n");
		exit(1);                                                             //End the implementation of the program
	}
	if ((invertedIndex = fopen("invertedIndex.txt", "r")) == NULL)               //when open operation is not successful
	{
		printf("invertedIndex.txt can not be opened.\n");
		exit(1);                                                             //End the implementation of the program
	}
	/*With invertedIndex.txt in the contents of the word as the key to establish a binary tree, the key is the word value is url list*/
	while (fgets(line, sizeof(line), invertedIndex) != NULL)
	{
		wl = get_words_from_line(line);        //After reading a row from the file, the words in the row are separated by a space, and the words in the row are stored in a word list, each word occupying one node
		node = wl->head;
		strcpy(word, node->word);                            //The first node in the list is a word, and the remaining nodes are url
		node = node->next;
		while (node != NULL) {
			root = insertBST(root, word, node->word);   //word is a word, node-> word content is url
			node = node->next;
		}
		freeWordList(wl);                                         //free the word list generated this time
	}

	/*Use pagerankList.txt in the contents of the url as a key to establish a binary tree*/
	while (fgets(line, sizeof(line), pagerankList) != NULL)
	{
		wl = get_words_from_line(line);             //Also get the word list first
		node = wl->head;                         //The first node in the list is the url
		strcpy(url, node->word);
		node = node->next->next;                                  //The corresponding PR value of the url is stored in the third node
		PR = atof(node->word);
		root_url = insertBST_URL(root_url, url, PR);             //Create a binary tree, the key is url, the value is PR
		freeWordList(wl);
	}

	/*According to the retrieved word to generate a URL list, each URL contains two main list of information: 1. The URL contains the number of words retrieved, stored in node-> vertex, 2. The url PR value*/
	
	for (i = 1;i < argc;i++)                          //Each cycle to deal with a retrieved word
	{
		urls = findURL(root, argv[i]);          //In the BST tree, use the word as the key to find the url list that contains the word
		unode = urls->head;
		while (unode != NULL) {                          //Insert all the URLs retrieved by this word into URLs
			URLs = insertNode_sort(URLs, unode->url);       //When inserted, it records the number of times the url is inserted and the number of times a url is inserted equals the number of words it contains
			unode = unode->next;
		}
		freeList(urls);            /////////////////////////////////////////////////É¾³ý
	}

	/*Assign PR values to each url node in URLs*/
	for (unode = URLs->head;unode != NULL;unode = unode->next)
	{
		unode->PR = findPR(root_url, unode->url);          //Find the corresponding PR value of the url according to the value of url in BST_URL and assign it to the corresponding node in the URLs list
	}

	sort(URLs);                                                  //Sort the above url list
	printURLs(URLs);                                           //Output to standard output

}
