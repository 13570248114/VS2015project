#include"head.h"

int login(customer* cus, administrator* admin)
{
	char username[50];
	char password[50];
	int i = 3;                             //�û��������������3��
	printf("\n\n\t��ӭʹ�����ϳ��й���ϵͳ\n\n");
	while (i)
	{
		printf("\n please input the username:");
		gets(username);                            //�����û���
		printf("\n please input the password: ");
		gets(password);                             //�����û�����

		if ((strcmp(username, admin->ID) == 0) && (strcmp(password, admin->password) == 0))   //����û����������Ƿ�ƥ�䣬Ĭ���˺���admim,������admin
			return ADMIN;
		else if ((strcmp(username, cus->ID) == 0) && (strcmp(password, cus->password) == 0))
			return CUSTOMER;
		else
		{
			i--;
			if (i)
				printf("\n�û������������������������.......\n");
		}
	}
	return FALSE;
}