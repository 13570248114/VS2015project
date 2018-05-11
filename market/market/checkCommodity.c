#include"head.h"

int checkCommodity(char* id) {
	int len, i;
	len = strlen(id);
	if (len != 6)
		return FALSE;
	for (i = 0;i < 2;i++)
		if (!isAlpha(id[i]) )
			return FALSE;
	for (i = 2;i < len;i++)
		if (!isNumber(id[i]))
			return FALSE;
	return TRUE;
}