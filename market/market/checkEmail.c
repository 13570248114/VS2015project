#include"head.h"

int checkEmail(char* email) {
	int len, i, j = -1, k = -1;
	len = strlen(email);
	for (i = 0;i < len;i++) {
		if (email[i] == '@') {
			if (j == -1)
				j = i;
			else
				return FALSE;
		}
		if (email[i] == '.') {
			if (k == -1)
				k = i;
			else
				return FALSE;
		}
	}
	if (j != -1 && k != -1 && (k - j > 1))
		return TRUE;
	else
		return FALSE;
}