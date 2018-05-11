#include"head.h"
int check_no_num(char* s, int size)          
{
	int i;
	for (i = 0;i < size;i++)
		if (s[i] > '9' || s[i] < '0')            //�������������ַ����Ƿ��з������ַ������򲻺Ϸ�
			return 1;
	return 0;
}

int check_data(char* s, int size)                  //�������������ַ����Ƿ���ϳ���
{
	int isrun;
	int run[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	int ping[12]= { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int year, month, day;
	year = (s[0] - '0') * 1000 + (s[1] - '0') * 100 + (s[2] - '0') * 10 + s[3] - '0';
	month = (s[4] - '0') * 10 + s[5] - '0';
	day= (s[6] - '0') * 10 + s[7] - '0';

	if (month > 12||month<1)                      //�·ݷ�Χ����
		return 1;

	if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))       
	{
		if (day > run[month - 1])                      //������Χ����
			return 1;
	}
	else
		if (day > ping[month - 1])
			return 1;
	return 0;
}