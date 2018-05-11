#ifndef HEAD_H
#define HEAD_H

#include<stdio.h>
#include <errno.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE  80
#define TRUE 1
#define FALSE 0
#define ADMIN 1
#define CUSTOMER 2

typedef struct {
	char ID[20];
	char name[20];
	char sex[2];
	char phone[20];
	char password[20];
	char email[20];
	char address[32];
	float menoy;
}customer;

typedef struct {
	char ID[20];
	char name[20];
	char password[20];
	char email[20];
	char superMardetName[32];
}administrator;


typedef struct {
	char ID[20];
	char superMardetName[32];
	double sellPrice;
	double inPrice;
	int stocks;
	double discountPrice;
	char diacountSTime[20];
	char diacountETime[20];
}commodity;

typedef struct {
	char ID[40];
	char BuyTime[20];
	commodity* comList;
	int sumPrice;
}order;

typedef struct {
	customer* cusList;
	int* cusNum;
	administrator* adminList;
	int* adminNum;
}people;

int checkCAID(char* id);
int isAlpha(char ch);
int isNumber(char ch);
int checkPhone(char* phone);
int checkEmail(char* email);
int checkCommodity(char* id);
int checkTime(char* time);
int login(customer* cus, administrator* admin);
void menu(int type);
void makeCustomer(customer* cusList, int* cusNum);
void makeAdministrator(administrator* adminList, int* adminNum);


/*
void input(book_msg *books, int *n);
void read_file(book_msg* books, int* n);
void save_file(book_msg* books, int n);
void del(book_msg* books, int *n);
void modify(book_msg* books, int n);
void find(book_msg* books, int n);
int smaller(book_msg* books, int i, int j, int select);
void sort(book_msg* books, int n);
void display(book_msg* books, int n);
void menu();
int buy(book_msg* books, int n);
*/
int main();

#endif // !HEAD_H

