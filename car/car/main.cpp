#include"head.h"
#include"page1.h"
#include"page2.h"

int main()
{
	page1 page_1;
	page2 page_2;
	while (1)
	{
		system("cls");
		cout << "\n\n\n\t\t\t\t       ���⳵����ϵͳ\t\n\n\n" << endl;
		cout << "\t\t\t****************************************************" << endl;
		cout << "\t\t\t*                     ���˵�                       *" << endl;
		cout << "\t\t\t****************************************************\n\n" << endl;
		cout << "\t\t           0 ���⳵��Ϣ����      1 ������Ϣ���� \n" << endl;
		cout << "\t\t           2 �˳�ϵͳ       \n" << endl;
		cout << "\t\t        ��ѡ��[0/1/2]:" << endl;
		int k;
		cin >> k;
		if (k == 0)
			page_1.menu(1);
		else if (k == 1)
			page_2.menu(1, page_1);
		if (k == 2)
			exit(0);
		else
			cout << "�����������������" << endl;

	}
}

