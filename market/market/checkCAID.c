#include"head.h"

int checkCAID(char* id) {
	int len, i;
	len = strlen(id);
	if (len < 6 || len>10)
		return FALSE;
	for (i = 0;i < len;i++)
		if (!isAlpha(id[i]) && !isNumber(id[i]))
			return FALSE;
	return TRUE;
}