#include"head.h"

void menu(int type)
{
	if (type == CUSTOMER) {
		system("cls");
		printf("\n\n\n\t\t\t\t   ��ӭʹ�����ϳ��й���ϵͳ\t\n\n\n");
		printf("\t\t\t*****************************************\n");
		printf("\t\t\t*                 ���˵�                *\n");
		printf("\t\t\t*****************************************\n\n\n");
		printf("\t\t           0 ��Ʒ��ѯ                        1 ������Ʒ \n\n");
		printf("\t\t           2 ������Ϣ����                   3 ȡ������ \n\n");
		printf("\t\t           4 ��ѯ�����Ķ�����¼          \n\n");
		printf("\t\t        ��ѡ��[0/1/2/3/4]:");
		char input;
		do {
			scanf("%c", &input);
			if (input<'0' || input>'4')
				printf("Invalid input, please input again!\n");
		} while (input<'0' || input>'4');

	}
	else if (type == ADMIN) {
		system("cls");
		printf("\n\n\n\t\t\t\t   ��ӭʹ�����ϳ��й���ϵͳ\t\n\n\n");
		printf("\t\t\t*****************************************\n");
		printf("\t\t\t*                 ���˵�                *\n");
		printf("\t\t\t*****************************************\n\n\n");
		printf("\t\t           0 ��������                        1 ��Ʒ���� \n\n");
		printf("\t\t           2 ������Ϣ����                    \n\n");
		printf("\t\t        ��ѡ��[0/1/2]:");
		char input;
		do {
			scanf("%c", &input);
			if (input<'0' || input>'2')
				printf("Invalid input, please input again!\n");
		} while (input<'0' || input>'2');
	}
}