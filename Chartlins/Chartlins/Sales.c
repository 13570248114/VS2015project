#include"Sales.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

salesList* sales_form_file()
{
	FILE * fp;
	if ((fp = fopen("sales.txt", "r")) == NULL)
	{
		printf("open file error!");
		exit(1);
	}
	salesList *head = (salesList *)malloc(sizeof(salesList));
	head->next = NULL;
	salesList *preSales = head;
	salesList *sales = (salesList *)malloc(sizeof(salesList));
	char buf[100];
	char *temp[3];
	for (int i = 0;i < 3;i++)
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
		strcpy(sales->Date, temp[0]);
		strcpy(sales->code, temp[1]);
		sales->purchased_num = atoi(temp[2]);
		sales->item = NULL;
		sales->next = NULL;
		preSales->next = sales;
		preSales = sales;
		sales = (salesList *)malloc(sizeof(salesList));
		k = 0;
	}
	free(sales);
	for (int i = 0;i < 3;i++)
		free(temp[i]);
	return head;
}

void printSalse(salesList* head)
{
	for (salesList* sale = head->next;sale != NULL;sale = sale->next)
	{
		printf("%s,%s,%d\n", sale->Date, sale->code, sale->purchased_num);
	}
}

void delsteSale(salesList* preSale, salesList* deleteSale)
{
	preSale->next = deleteSale->next;
	free(deleteSale);
	deleteSale = preSale;
}