#include"head.h"
int check_no_num(char* s, int size)          
{
	int i;
	for (i = 0;i < size;i++)
		if (s[i] > '9' || s[i] < '0')            //检查输入的日期字符串是否含有非数字字符，有则不合法
			return 1;
	return 0;
}

int check_data(char* s, int size)                  //检查输入的日期字符串是否符合常理
{
	int isrun;
	int run[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	int ping[12]= { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int year, month, day;
	year = (s[0] - '0') * 1000 + (s[1] - '0') * 100 + (s[2] - '0') * 10 + s[3] - '0';
	month = (s[4] - '0') * 10 + s[5] - '0';
	day= (s[6] - '0') * 10 + s[7] - '0';

	if (month > 12||month<1)                      //月份范围出错
		return 1;

	if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))       
	{
		if (day > run[month - 1])                      //天数范围出错
			return 1;
	}
	else
		if (day > ping[month - 1])
			return 1;
	return 0;
}