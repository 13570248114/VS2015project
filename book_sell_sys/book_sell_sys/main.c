#include"head.h"
int main()
{
	int j,num=0;
	book_msg books[SIZE];                       //�鼮������
	book_msg* p=books;

	while(1)
    {
	    menu();                         //��ʾ�˵�����
		scanf("%d",&j);
		switch(j)                   
		{
		case 0:read_file(books,&num);break;   //���ļ��ж�ȡ�鼮
        case 1:save_file(books,num);break;    //�����鼮��Ϣ���ļ�
		case 2:input(books, &num);break;       //�����鼮��Ϣ
		case 3:del(books,&num);break;         //ɾ���鼮��Ϣ
		case 4:modify(books,num);break;  //�޸��鼮��Ϣ
		case 5:display(books,num);printf("�����������:");getch();break;      //��ʾ�����鼮��Ϣ
        case 6:find(books,num);break;             //�����鼮������Ϣ
		case 7:sort(books,num);break;             //�鼮��Ϣ����
		case 8:buy(books, num);break;           //�鼮����
		case 9:exit(0);                            //�˳�
		}	
	}
}