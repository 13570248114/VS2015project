#include<stdio.h>
#include <errno.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 80

typedef struct {
	
char  vno[20];        //车牌号
char  dname[20];      //驾驶员姓名
char  pname[20];      //交警姓名
char  pno[20];        //交警编号
char  no[20];         //处罚单编号
char  date[20];       //处罚日期
} Plist;             //

int check_no_num(char* s, int size);       //检查输入日期是否含有非数字字符的函数
int check_data(char* s, int size);         //检查时间是否符合常理，如20170832是不合理的
void display(Plist* list, int n);          //显示函数
void input(Plist *list, int *n);           //输入函数
void menu();                               //菜单
void del(Plist* list, int *n);             //删除
void find(Plist* list, int n);             //查找
void read_file(Plist* list, int* n);        //读文件
void save_file(Plist* books, int n);        //写文件
void modify(Plist* list, int n);           //修改信息
int main();