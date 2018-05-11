#include"head.h"

int isAlpha(char ch) {
	if (ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z')
		return TRUE;
	else
		return FALSE;
}