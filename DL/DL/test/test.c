

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listIteratorInt.h"

char *myitoa(int *i){
  char *str;
  if(i == NULL){ return "NULL";}
  
  if ((str = malloc(20*sizeof(char))) == NULL) { return "Error";}
  sprintf(str, "%d", *i);
  return str;
}

/* ------ Helper functions for Operations on ADT ---------
*/

void adddsp(IteratorInt it, int v){
  int result = add(it , v); 
  printf("add %d, returns %d \n", v, result );
   
}
void nextdsp(IteratorInt it){
  printf("next, returns %s \n", myitoa(next(it)) ) ;   
}
void findnextdsp(IteratorInt it,int v) {
	printf("findNext, returns %s \n", myitoa(findNext(it,v)));
}
void prevdsp(IteratorInt it){
  printf("previous, returns %s \n", myitoa(previous(it)) );   
}
void findprevdsp(IteratorInt it,int v) {
	printf("findPrevious, returns %s \n", myitoa(findPrevious(it,v)));
}
void deletedsp(IteratorInt it){
  printf("delete, returns %d \n", deleteElm(it)) ;   
}

void setdsp(IteratorInt it, int v) {
	int result = set(it, v);
	printf("set %d, returns %d \n", v, result);

}

void printAll(IteratorInt it)
{
	reset(it);
	printf("\nprintf all:\n");
	while (hasNext(it))
		nextdsp(it);
}

int main(int argc, char *argv[]) {
  
	  int TestNo = 2;
	  IteratorInt it = IteratorIntNew();
	   int a[5] = { 25, 14, 32, 53 , 8  };
	  
	   if (TestNo == 1) {                    //链表中只有一个元素的测试
		   adddsp(it, a[0]);
		   deletedsp(it);                      //检查delete在没有调用next等函数前是否能成功

		   nextdsp(it);                        //单元素下左右两边迭代器的情况
		   prevdsp(it);
		   deletedsp(it);                      //检查能否成功删除

		   adddsp(it, a[0]);
		   prevdsp(it); 
		   setdsp(it, 100);                  //检查set

		   printf("hasnext: %d\n", hasNext(it));                     //检查hasnest等
		   printf("hasprev: %d\n", hasPrevious(it));

		   prevdsp(it);
		   setdsp(it, 100);
		   findnextdsp(it, a[0]);                                           //检查单元素下的findnext等
		   findprevdsp(it, a[0]);

		   findprevdsp(it, 14);                                             //查找不存在于链表的元素的前面一个元素的特殊情况
	   }
	   else
	   {
		   for(int i=0;i<5;i++)
			   adddsp(it, a[i]);
		   printAll(it);                    //游标已到最右
		   nextdsp(it);                  //检查游标已到最右的next和havenext
		   printf("hasnext: %d\n", hasNext(it));

		   prevdsp(it);
		   prevdsp(it);
		   deletedsp(it);                 //检查 prevdsp(it)及deletedsp(it)
		   printAll(it);                    //游标已到最右

		   prevdsp(it);
		   prevdsp(it);
		   adddsp(it, 14);               //检查在某处插入元素的结果，在未插入之前it->nextEle是32，要看插入后是否it->nextEle还是是32
		   printAll(it);                    //游标已到最右

		   reset(it);                    
		   findnextdsp(it, 14);        //检查有两个相同的数相邻的时候findNext的结果
		   findnextdsp(it, 14);

		   findnextdsp(it, 14);

		   nextdsp(it);
		   nextdsp(it);
		   findprevdsp(it, 14);       //检查有两个相同的数相邻的时候findNext的结果
		   findprevdsp(it, 14);

		   reset(it);                    
		   nextdsp(it);                   //检查set
		   setdsp(it, 8);
		   printAll(it);                    //游标已到最右

		   reset(it);
		   findnextdsp(it, 8);        //检查有两个相同的数不相邻的时候findNext的结果
		   findnextdsp(it, 8);
		   nextdsp(it);                   //检查findnext不成功时迭代器的位置

		   printAll(it);                    //游标已到最右
		   findprevdsp(it, 8);       //检查有两个不相同的数相邻的时候findprevious的结果
		   findprevdsp(it, 8);
	   }
	   freeIt(it);

	

  	return EXIT_SUCCESS;

}
