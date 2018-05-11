#include"Inventory.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
Inventory* Inventory_form_file()
{
	FILE *fp;
	if ((fp = fopen("inventory.txt", "r")) == NULL)
	{
		printf("can't open file\n");
		exit(1);
	}
	Inventory* head = (Inventory*)malloc(sizeof(Inventory));
	head->next = NULL;
	Inventory* prenode = head;
	Inventory* node = (Inventory*)malloc(sizeof(Inventory));
	char buf[100];
	char *temp[5];
	for (int i = 0;i < 5;i++)
		temp[i] = (char*)malloc(sizeof(char) * 20);
	int k = 0;
	while (fgets(buf, sizeof(buf), fp) != NULL)
	{
		for (int i = 0, j = 0;i < strlen(buf);i++)
		{
			if (buf[i] == ',' || buf[i] == '\0' || buf[i] == '\n')
			{
				temp[k][j] = '\0';
				k++;
				j = 0;
			}
			else if (buf[i] != ' ')
			{
				temp[k][j] = buf[i];
				j++;
			}
		}
		strcpy(node->item.component_type, temp[0]);
		strcpy(node->item.stock_code, temp[1]);
		node->item.stock_num = atoi(temp[2]);
		node->item.price = atoi(temp[3]);
		strcpy(node->item.add_info, temp[4]);
		node->next = NULL;
		prenode->next = node;
		prenode = node;
		node = (Inventory*)malloc(sizeof(Inventory));
		k = 0;
	}
	free(node);
	for (int i = 0;i < 5;i++)
		free(temp[i]);
	printf("all message has been read from inventory.txt\n");
	return head;
}

StockItem* find_by_code(Inventory* head, char* code)
{
	for (Inventory* inv = head->next; inv != NULL; inv = inv->next)
	{
		if (strcmp(inv->item.stock_code, code) == 0)
		{
			return &inv->item;
		}
	}
	return NULL;
}

void printInv(Inventory* head)
{
	for (Inventory* node = head->next; node != NULL; node = node->next)
	{
		printItem(&node->item);
	}
}

void sortInv(Inventory* head)
{
	"http://www.cnblogs.com/TenosDoIt/p/3666585.html";
}
