#include"head.h"
int main()
{
	int j,num=0;
	book_msg books[SIZE];                       //书籍的数组
	book_msg* p=books;

	while(1)
    {
	    menu();                         //显示菜单函数
		scanf("%d",&j);
		switch(j)                   
		{
		case 0:read_file(books,&num);break;   //从文件中读取书籍
        case 1:save_file(books,num);break;    //保存书籍信息到文件
		case 2:input(books, &num);break;       //输入书籍信息
		case 3:del(books,&num);break;         //删除书籍信息
		case 4:modify(books,num);break;  //修改书籍信息
		case 5:display(books,num);printf("按任意键返回:");getch();break;      //显示所有书籍信息
        case 6:find(books,num);break;             //查找书籍基本信息
		case 7:sort(books,num);break;             //书籍信息排序
		case 8:buy(books, num);break;           //书籍购买
		case 9:exit(0);                            //退出
		}	
	}
}