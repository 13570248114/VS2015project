#include"head.h"

void makeCustomer(customer* cusList, int* cusNum) {
	customer* cus = cusList + *cusNum;
	int i;
	system("cls");
	do
	{
		printf("\n�������%d���˿͵���Ϣ��", (*cusNum) + 1);
		printf("\nID ���� �Ա�(��/Ů) �绰 ���� ���� �ջ���ַ �˻����\n:");
		scanf("%s%s%s%s%s%s%s%f", cus->ID,cus->name,cus->sex,cus->phone,cus->password,cus->email,cus->address,&cus->menoy);
		while (!checkCAID(cus->ID)) {
			printf("��Ч��ID�����������룡\n");
			scanf("%s", cus->ID);
		}
		while (cus->sex!="��"&&cus->sex != "Ů"){
			printf("��Ч���Ա����������룡\n");
			scanf("%s", cus->sex);
		}
		while (!checkPhone(cus->phone)){
			printf("��Ч�ĵ绰�����������룡\n");
			scanf("%s", cus->phone);
		}
		while (!checkEmail(cus->email)){
			printf("��Ч�����䣬���������룡\n");
			scanf("%s", cus->email);
		}
		while (cus->menoy < 0){
			printf("��Ч���˻������������룡\n");
			scanf("%s", cus->menoy);
		}
		(*cusNum)++;
		cus++;
		do {
			printf("\n��0�������룬������1��");
			scanf("%d", &i);
			if (i != 1 && i != 2)
				printf("�������\n");
		} while (i != 1 && i != 2);
	} while (i);
	//display(a, *n);
	printf("\n���������");
	printf("���س����أ�");
	getch();
}