#ifndef STOCKITEM_H
#define STOCKITEM_H

typedef struct stockitem{
	char component_type[20];
	char stock_code[20];
	int stock_num;
	int price;
	char add_info[20];
}StockItem;

void copy_item(StockItem* destination, StockItem* source);
void printItem(StockItem* source);
#endif // !STOCKITEM_H
