#ifndef INVENTORY_H
#define INVENTORY_H
#include"StockItem.h"
typedef struct  inventory  Inventory;
struct  inventory {
	StockItem item;
	Inventory* next;
};
Inventory* Inventory_form_file();
StockItem* find_by_code(Inventory* head, char* code);
void printInv(Inventory* head);
void sortInv(Inventory* head);

#endif // !INVENTORY_H

