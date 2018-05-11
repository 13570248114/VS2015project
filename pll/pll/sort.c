#include"head.h"

int smaller(book_msg* books, int i,int j,int select)    //用于比较大小关系的函数
{
	if (select == 0)                                       //如果选择按书名排序，则用书名的字典顺序比较两个书籍的大小关系
		if (strcmp(books[i].book_name, books[j].book_name) < 0)
			return 1;
		else
			return 0;

	else if (select == 1)                                //如果选择按价格排序，则用价格高低比较两个书籍的大小关系
		if (books[i].price < books[j].price)
			return 1;
		else
			return 0;

	else
		return -1;
}

void sort(book_msg* books, int n)
{
    int i,j,select;
	book_msg t;
	system("cls");

	printf("\n按书名排序请按0 \n按价格排序请按1:\n");
	scanf("%d", &select);
	while (select>1 || select<0)
	{
		printf("输入的数字范围错误，请重新输入\n");
		scanf("%d", &select);
	}
	
	for(i=0;i<n-1;i++)                  //冒泡排序
	{
		for(j=0;j<n-i-1;j++)
			if(smaller(books,j+1, j, select))       //大小关系比较调用了上面的函数，意思是if(books[j+1]<books[j])
			{
				t=books[j];
				books[j]=books[j+1];
				books[j].num = j+1 ;               //要更新一下序号信息，因为序号从1开始，所以比数组的索引号多1
				books[j+1]=t;
				books[j + 1].num = j + 2;
			}		
	}

	printf("排序结果如下:\n");
	display(books, n);
	printf("按任意键返回:");
	getch();
}