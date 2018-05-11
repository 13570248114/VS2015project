#include"StockItem.h"
#include<string.h>

void copy_item( StockItem* destination, StockItem* source)
{
	strcpy(destination->component_type, source->component_type);
	strcpy(destination->stock_code, source->stock_code);
	destination->stock_num = source->stock_num;
	destination->price = source->price;
	strcpy(destination->add_info, source->add_info);
}

void printItem(StockItem* item)
{
	printf("%s,%s,%d,%d,%s\n", item->component_type, item->stock_code, item->stock_num, item->price, item->add_info);
}
