#ifndef SALES_H
#define SALES_H
#include"StockItem.h"
typedef struct slist{
	char Date[11];
	StockItem* item;
	int purchased_num;
	char code[20];
	struct slist *next;
}salesList;

salesList* sales_form_file();
void printSalse(salesList* head);
void delsteSale(salesList* preSale, salesList* deleteSale);
#endif // !SALES_H

