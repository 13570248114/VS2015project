#include"head.h"
#define getNum(ch) (ch-'0')
int checkTime(char* time) {
	int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int days2[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	int len, i , year, month ,day, hour, minute;
	len = strlen(time);
	if (len != 16)
		return FALSE;
	for (i = 0;i < len;i++){
		if (i != 4 && i != 7 && i != 10 && i != 13) {
			if (!isNumber(time[i]))
				return FALSE;
		}
		else {
			if (time[i] != ':')
				return FALSE;
		}
	}
	year = getNum(time[0]) * 1000 + getNum(time[1]) * 100 + getNum(time[2]) * 10 + getNum(time[3]);
	month= getNum(time[5]) * 10 + getNum(time[6]);
	day= getNum(time[8]) * 10 + getNum(time[9]);
	hour= getNum(time[11]) * 10 + getNum(time[12]);
	minute= getNum(time[14]) * 10 + getNum(time[15]);

	if (month == 0 || month > 12)
		return FALSE;
	if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
		if (day > days2[month - 1] || day == 0)
			return FALSE;
	}
	else
		if (day > days[month - 1] || day == 0)
			return FALSE;
	if (hour > 23)
		return FALSE;
	if (minute > 59)
		return FALSE;
	return TRUE;
}