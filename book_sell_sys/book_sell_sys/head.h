#include<stdio.h>
#include <errno.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE  80

typedef struct{
	int num;                                       //�鼮���
	char book_name[20];                            //����
    char author[20];                               //����
    char Press[20];                                //������
	int price;                                     //�۸�
}book_msg;

typedef struct {
	int num;
	int count;
}buy_book;

void input(book_msg *books,int *n);
void read_file(book_msg* books,int* n);
void save_file(book_msg* books,int n);
void del(book_msg* books, int *n);
void modify(book_msg* books, int n);
void find(book_msg* books,int n);
int smaller(book_msg* books, int i, int j, int select);
void sort(book_msg* books,int n);
void display(book_msg* books,int n);
void menu();
int buy(book_msg* books, int n);
int main();
