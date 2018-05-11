#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"BST.h"
#include"readData.h"

typedef struct wordListNode {
	char word[20];
	struct wordListNode* next;
}wordListNode;

typedef struct wordList {
	wordListNode* head;
	wordListNode* tail;
}wordList;

wordList* insertWord(wordList* wl, char* word)
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

void freeWordList(wordList* wl)
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

wordList* get_words_from_line(char* line)                    //��һ���ַ�����ȡ����
{
	wordList* wl = NULL;
	int len = strlen(line);
	if(len==0)
		return NULL;
	while (line[len - 1] == ' '|| line[len - 1]=='\n')                                           //ȥ����β�Ŀո�ͻ��з�
		len--;

	char word[20];
	int j = 0;
	for (int i = 0;i < len;i++)
	{
		if (line[i] != ' '&&line[i] != ',') {                                                   //���Ƿָ�������ַ���ŵ�word[j]
			word[j] = line[i];
			j++;
		}	
		else                                                                    //�����ָ���ʱ����\0����ӵ�����ĩβ
		{
			word[j] = '\0';
			if(j > 0)
				wl = insertWord(wl, word);                              //��������뵥��
			j = 0;
		}
	}
	word[j] = '\0';                                                        //�������һ������
	wl = insertWord(wl, word);
	return wl;
}


int main()
{
	int argc = 4;
	char* argv[] = { "aa","mars","moon","moons"};
	FILE *pagerankList, *invertedIndex;
	if ((pagerankList = fopen("pagerankList.txt", "r")) == NULL)               //�򿪲������ɹ�
	{
		printf("pagerankList.txt can not be opened.\n");
		exit(1);                                                             //���������ִ��
	}
	if ((invertedIndex = fopen("invertedIndex.txt", "r")) == NULL)               //�򿪲������ɹ�
	{
		printf("invertedIndex.txt can not be opened.\n");
		exit(1);                                                             //���������ִ��
	}

	char line[1000];
	char word[20];
	BST root = NULL;
	while (fgets(line, sizeof(line), invertedIndex) != NULL)
	{
		wordList* wl = get_words_from_line(line);
		wordListNode* node = wl->head;
		strcpy(word, node->word);
		node = node->next;
		while (node != NULL) {
			root = insertBST(root, word, node->word);
			node = node->next;
		}
		freeWordList(wl);
	}
	//PrintBST(root, NULL);
	
	char url[20];
	double PR;
	BST_URL root_url = NULL;
	while (fgets(line, sizeof(line), pagerankList) != NULL)
	{
		wordList* wl = get_words_from_line(line);
		wordListNode* node = wl->head;
		strcpy(url, node->word);
		node = node->next->next;
		PR = atof(node->word);
		root_url = insertBST_URL(root_url, url, PR);
		freeWordList(wl);
	}
	//PrintBST_URL(root_url);
	
	urlList URLs = NULL;
	for (int i = 1;i < argc;i++)
	{
		urlList urls = findURL(root, argv[i]);
        printURLs(urls);
		urlNode* node = urls->head;
		while (node != NULL) {
			URLs = insertNode_sort(URLs, node->url);
			node = node->next;
		}
		freeList(urls);
	}

	for (urlNode* node = URLs->head;node != NULL;node = node->next)
	{
		node->PR = findPR(root_url, node->url);
	}
	
	sort(URLs);
	printURLs(URLs);
	/*
	urlNode* node = URLs->head;
	int pn = 0;
	for (;pn < 30 && node != NULL;++pn, node = node->next)
	{
		printf("%s\n", node->url);
	}
	*/
}
