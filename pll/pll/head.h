#include<stdio.h>
#include <errno.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 80

typedef struct {
	
char  vno[20];        //���ƺ�
char  dname[20];      //��ʻԱ����
char  pname[20];      //��������
char  pno[20];        //�������
char  no[20];         //���������
char  date[20];       //��������
} Plist;             //

int check_no_num(char* s, int size);       //������������Ƿ��з������ַ��ĺ���
int check_data(char* s, int size);         //���ʱ���Ƿ���ϳ�����20170832�ǲ������
void display(Plist* list, int n);          //��ʾ����
void input(Plist *list, int *n);           //���뺯��
void menu();                               //�˵�
void del(Plist* list, int *n);             //ɾ��
void find(Plist* list, int n);             //����
void read_file(Plist* list, int* n);        //���ļ�
void save_file(Plist* books, int n);        //д�ļ�
void modify(Plist* list, int n);           //�޸���Ϣ
int main();