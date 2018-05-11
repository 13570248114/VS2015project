#include"head.h"

int checkPhone(char* phone) {
	int len, i;
	len = strlen(phone);
	if (len != 11)
		return FALSE;
	for (i = 0;i < len;i++)
		if (!isNumber(phone[i]))
			return FALSE;
	return TRUE;
}