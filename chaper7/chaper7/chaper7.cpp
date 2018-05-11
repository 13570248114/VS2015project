// chaper7.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include "apue.h"

static void my_exit1(void);
static void my_exit1(void);

int main()
{
	if (atexit(my_exit1) != 0)
		err_sys("can't register my_exit1");
	if (atexit(my_exit2) != 0)
		err_sys("can't register my_exit2");
	printf("main is done\n");
    return 0;
}

static void my_exit1(void)
{
	printf("first is done\n");
}

static void my_exit2(void)
{
	printf("second is done\n");
}
