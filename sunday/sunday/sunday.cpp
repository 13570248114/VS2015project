// sunday.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include"stdlib.h"
#include"conio.h"
#include<iostream>
using namespace std;
#define cel 1500
#define row 5000


int findIndex(const char* words, char word)
{
	for (int i = strlen(words) - 1;i >= 0;i--) {
		if (words[i] == word) {
			return i;
		}
	}
	return -1;
}

int Sunday(const char *source, const char *words) {

	int sourcr_i = 0, words_j = 0, srclen = strlen(source), wordlen = strlen(words);
	int locate = 0, index = -1;

	while (sourcr_i<srclen) {
		if (source[sourcr_i] == words[words_j]) {
			if (words_j == wordlen - 1) {
				printf("ƥ��ɹ�...");
				return true;
			}
			sourcr_i++;words_j++;
		}
		else {  //���ֲ����λ��
			locate = wordlen - words_j + sourcr_i;       //�ַ�������ĵ�һ���ַ�λ��
			index = findIndex(words, source[locate]);
			if (index == -1) {                          //δ�ҵ�λ�ã�����
				sourcr_i = locate + 1;
				words_j = 0;
			}
			else {                                     //�ҵ�λ��
				sourcr_i = locate - index;
				words_j = 0;
			}
		}
	}
	printf("ƥ��ʧ��..");
	return false;
}


int main()
{
   
	char dictionary[row][cel];
	FILE *fp = fopen("E:\\project\\1706-1-2505\\dictionary.txt", "r");
	fgets(dictionary[0], cel , fp);
	cout << dictionary[0];
	//const char words[] = "laaasaa";
	//cout<<Sunday(dictionary[0], words);
   // return 0;
}

