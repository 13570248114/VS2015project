#include"readData.h"
#include<stdlib.h>
#include<string.h>


urlList insertNode(urlList List_of_Urls, char *url)
{
	urlNode* node = (urlNode*)malloc(sizeof(urlNode));
	strcpy(node->url, url);
	node->next = NULL;

	if (List_of_Urls == NULL)                                      //If the list starts empty, the list is initialized
	{
		node->vertex = 0;
		List_of_Urls = (urlList)malloc(sizeof(urlL));
		List_of_Urls->tail = List_of_Urls->head = node;
		List_of_Urls->num_of_node = 1;
	}
	else                                                                     //Otherwise, insert the node from the tail
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
	char url[20];
	FILE *fp;
	urlList List_of_Urls = NULL;
	if ((fp = fopen("collection.txt","r") )== NULL)               //Open operation is not successful
	{
		printf("Collection.txt can not be opened.\n");
		exit(1);                                                             //End the implementation of the program
	}

	while (fscanf(fp, "%s", url) > 0)                                //Insert a node into the linked list based on the contents of the file
	{
		List_of_Urls = insertNode(List_of_Urls, url);
	}
	fclose(fp);
	return List_of_Urls;
}

void freeList(urlList List_of_Urls)                            //free
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

urlList insertNode_sort(urlList List_of_Urls, char *url)       //Insert the nodes in dictionary order, where node-> vertex indicates the number of times node-> url is inserted
{
	urlNode* node = (urlNode*)malloc(sizeof(urlNode));
	urlNode* back_node,*front_node;
	strcpy(node->url, url);

	if (List_of_Urls == NULL)                                      //If the list starts empty, the list is initialized
	{
		List_of_Urls = (urlList)malloc(sizeof(urlL));
		node->next = NULL;
		node->vertex = 1;                                                //The url was inserted only once
		List_of_Urls->tail = List_of_Urls->head = node;
		List_of_Urls->num_of_node = 1;
	}
	else                                                                     //Otherwise insert the node in order
	{
		++List_of_Urls->num_of_node;
		if (strcmp(url, List_of_Urls->head->url) < 0)      //When the newly added node dictionary order in front of the head node
		{
			node->vertex = 1;                                        //The url was inserted only once
			node->next = List_of_Urls->head; ///////////////////////////////////////////////////////////////////////////////////////
			List_of_Urls->head = node;
		}
		else if (strcmp(url, List_of_Urls->tail->url) > 0)       //When the newly added node dictionary order in the tail node behind
		{
			node->vertex = 1;                                           //The url was inserted only once
			node->next = NULL;
			List_of_Urls->tail->next = node;
			List_of_Urls->tail = node;
		}
		else                                                                     //Otherwise find the location to insert
		{
			back_node = List_of_Urls->head;
			front_node = back_node;
			while (strcmp(url, back_node->url) > 0)                   //Find the insertion location
			{
				front_node = back_node;
				back_node = back_node->next;
			}
			if (strcmp(url, back_node->url) < 0)
			{
				node->next = back_node;
				front_node->next = node;
				node->vertex = 1;                                      //The url was inserted only once
			}
			else if (strcmp(url, back_node->url) == 0)         //url is no longer inserted in the list
			{
				free(node);
				back_node->vertex++;                               //Add 1 to the number of times when the url is inserted
			}
		}
	}
	return List_of_Urls;
}

void sort(urlList List_of_Urls)                                     //Sort, first press the number of words retrieved row, then press PR value row
{
	urlNode* front_node, *back_node,*headnode;
	int num;
	/*Sorted by the number of words retrieved, the vertex of each linked list node stores the number of terms contained in the url*/
	for(front_node = List_of_Urls->head;front_node !=NULL;front_node = front_node->next)
		for (back_node = front_node->next;back_node != NULL;back_node = back_node->next)
		{
			if (front_node->vertex < back_node->vertex)
			{
				exchangeNode(front_node, back_node);
			}
		}

	/*Sort by PR value grouped*/
	headnode = List_of_Urls->head;
	num = headnode->vertex;
	while (headnode!=NULL&&headnode->next != NULL)             //Headnode stored in the header of each group of url, here to ensure that the last group of url if there is only one url, then do not sort
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
			headnode = front_node;                      //Update headnode to point to the next set of url
		}
		else
			headnode = front_node->next;
	}
}

void exchangeNode(urlNode* n1, urlNode* n2)        //Exchange the contents of two nodes
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
	int i = 0;
	urlNode* n;
	for (n = List_of_Urls->head;n != NULL&&i<30;n = n->next,i++){
		printf("%s %d %.7f\n", n->url,n->vertex,n->PR);
		//printf("%s\n", n->url);
    }
}




