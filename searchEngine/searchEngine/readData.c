#include"readData.h"
#include<stdlib.h>
#include<string.h>


urlList insertNode(urlList List_of_Urls, char *url)
{
	urlNode* node = (urlNode*)malloc(sizeof(urlNode));
	strcpy(node->url, url);
	node->next = NULL;

	if (List_of_Urls == NULL)                                      //如果链表开始为空，则初始化链表
	{
		node->vertex = 0;
		List_of_Urls = (urlList)malloc(sizeof(urlL));
		List_of_Urls->tail = List_of_Urls->head = node;
		List_of_Urls->num_of_node = 1;
	}
	else                                                                     //否则从尾端插入节点
	{
		node->vertex = List_of_Urls->tail->vertex + 1;
		List_of_Urls->tail->next = node;
		List_of_Urls->tail = node;
		++List_of_Urls->num_of_node;
	}
	return List_of_Urls;
}


urlList GetCollection()
{
	urlList List_of_Urls = NULL;
	FILE *fp;
	if ((fp = fopen("collection.txt","r") )== NULL)               //打开操作不成功
	{
		printf("Collection.txt can not be opened.\n");
		exit(1);                                                             //结束程序的执行
	}

	char url[20];
	while (fscanf(fp, "%s", url) > 0)                                //根据文件内容向链表插入节点
	{
		List_of_Urls = insertNode(List_of_Urls, url);
	}
	fclose(fp);
	return List_of_Urls;
}

void freeList(urlList List_of_Urls)                            //释放空间
{
	urlNode* node = List_of_Urls->head;
	urlNode* tnode;
	while (node != NULL)
	{
		tnode = node;
		node = node->next;
		free(tnode);
	}
	free(List_of_Urls);
}

urlList insertNode_sort(urlList List_of_Urls, char *url)       //按字典序插入节点, 在此，node->vertex 表示node->url被插入的次数
{
	urlNode* node = (urlNode*)malloc(sizeof(urlNode));
	strcpy(node->url, url);

	if (List_of_Urls == NULL)                                      //如果链表开始为空，则初始化链表
	{
		List_of_Urls = (urlList)malloc(sizeof(urlL));
		node->next = NULL;
		node->vertex = 1;                                                //该url只插入过一次
		List_of_Urls->tail = List_of_Urls->head = node;
		List_of_Urls->num_of_node = 1;
	}
	else                                                                     //否则按序插入节点
	{                                      
		++List_of_Urls->num_of_node;
		if (strcmp(url, List_of_Urls->head->url) < 0)      //当新加入的节点的字典序在头结点的前面
		{
			node->vertex = 1;                                        //该url只插入过一次
			node->next = List_of_Urls->head->next;
			List_of_Urls->head = node;
		}
		else if (strcmp(url, List_of_Urls->tail->url) > 0)       //当新加入的节点的字典序在尾结点的后面
		{
			node->vertex = 1;                                           //该url只插入过一次
			node->next = NULL;
			List_of_Urls->tail->next = node;
			List_of_Urls->tail = node;
		}
		else                                                                     //否则就找位置插入
		{
			urlNode* back_node = List_of_Urls->head;
			urlNode* front_node = back_node;
			while (strcmp(url, back_node->url) > 0)
			{
				front_node = back_node;
				back_node = back_node->next;
			}
			if (strcmp(url, back_node->url) < 0)
			{
				node->next = back_node;
				front_node->next = node;
				node->vertex = 1;                                      //该url只插入过一次
			}
			else if (strcmp(url, back_node->url) == 0)         //url已在链表则不再插入
			{
				free(node);
				back_node->vertex++;                               //把该url插入的次数加1
			}
		}
	}
	return List_of_Urls;
}

void sort(urlList List_of_Urls)
{
	urlNode* front_node, *back_node;
	for(front_node = List_of_Urls->head;front_node !=NULL;front_node = front_node->next)
		for (back_node = front_node->next;back_node != NULL;back_node = back_node->next)
		{
			if (front_node->vertex < back_node->vertex)
			{
				exchangeNode(front_node, back_node);
			}
		}

	
	urlNode* headnode = List_of_Urls->head;
	int num = headnode->vertex;
	while (headnode!=NULL&&headnode->next != NULL)
	{
		num = headnode->vertex;
		front_node = headnode;
		back_node = front_node->next;
		if (back_node->vertex == front_node->vertex)
		{
			for (front_node = headnode;front_node!=NULL&&front_node->vertex == num; front_node = front_node->next)
				for (back_node = front_node->next; back_node!=NULL&&back_node->vertex == num;back_node = back_node->next)
				{
					if (front_node->PR < back_node->PR)
					{
						exchangeNode(front_node, back_node);
					}
				}
		}
		if (front_node != NULL)
			headnode = front_node->next;
		else
			headnode = NULL;
	}
	
}

void exchangeNode(urlNode* n1, urlNode* n2)
{
	urlNode n;
	n.vertex = n1->vertex;
	n.PR = n1->PR;
	strcpy(n.url, n1->url);

	n1->vertex = n2->vertex;
	n1->PR = n2->PR;
	strcpy(n1->url, n2->url);

	n2->vertex = n.vertex;
	n2->PR = n.PR;
	strcpy(n2->url, n.url);
}

void printURLs(urlList List_of_Urls)
{
	for (urlNode* n = List_of_Urls->head;n != NULL;n = n->next)
		printf("%s   %d   %.7f\n", n->url, n->vertex, n->PR);
}




