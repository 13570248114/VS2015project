#include"head.h"
int main()
{
	int j,num=0;
	Plist list[SIZE];                       //���������
	Plist* p= list;

	while(1)
    {
	    menu();                         //��ʾ�˵�����
		scanf("%d",&j);
		switch(j)                   
		{
		case 0:read_file(list,&num);break;   //���ļ��ж�ȡ��Ϣ
        case 1:save_file(list,num);break;    //������Ϣ���ļ�
		case 2:input(list, &num);break;       //������Ϣ
		case 3:del(list,&num);break;         //ɾ����Ϣ
		case 4:modify(list,num);break;  //�޸���Ϣ
		case 5:display(list,num);printf("�����������:");getch();break;      //��ʾ������Ϣ
		case 6:find(list, num);break;              //����
		case 7:count(list, num);break;            //ͳ��
		case 8:exit(0);
		}	
	}
}