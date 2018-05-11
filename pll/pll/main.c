#include"head.h"
int main()
{
	int j,num=0;
	Plist list[SIZE];                       //罚款单的数组
	Plist* p= list;

	while(1)
    {
	    menu();                         //显示菜单函数
		scanf("%d",&j);
		switch(j)                   
		{
		case 0:read_file(list,&num);break;   //从文件中读取信息
        case 1:save_file(list,num);break;    //保存信息到文件
		case 2:input(list, &num);break;       //输入信息
		case 3:del(list,&num);break;         //删除信息
		case 4:modify(list,num);break;  //修改信息
		case 5:display(list,num);printf("按任意键返回:");getch();break;      //显示所有信息
		case 6:find(list, num);break;              //查找
		case 7:count(list, num);break;            //统计
		case 8:exit(0);
		}	
	}
}