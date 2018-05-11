#include"Inventory.h"
#include"Sales.h"
#include"StockItem.h"
#include<stdio.h>
#include<string.h>
void transactions(Inventory*invHead, salesList*salist);
int main()
{
	Inventory* invHead = Inventory_form_file();
	salesList* salist = sales_form_file();
	//printInv(invHead);
	//printSalse(salist);
	transactions(invHead, salist);
	//printSalse(salist);
	printInv(invHead);
}

void transactions(Inventory*invHead, salesList*salist)
{
	StockItem* item;
	for (salesList* sale = salist->next, *presale = salist ;sale != NULL; presale=sale, sale = sale->next)
	{
		if ((item = find_by_code(invHead, sale->code)) != NULL)
		{
			sale->item = item;
			if (item->stock_num >= sale->purchased_num)
			{
				item->stock_num -= sale->purchased_num;
			}
			else
			{
				printf("%s error: stock code %s: the purchased number £¨%d£© is larger than stock number (%d)! \n", sale->Date, sale->code,sale->purchased_num,item->stock_num);
				presale->next = sale->next;
				free(sale);
				sale = presale;
			}
		}
		else
		{
			printf("%s error: the stock code can't match a stock in  inventory! \n", sale->Date);
			presale->next = sale->next;
			free(sale);
			sale = presale;
		}
	}
}