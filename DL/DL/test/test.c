

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
	  
	   if (TestNo == 1) {                    //������ֻ��һ��Ԫ�صĲ���
		   adddsp(it, a[0]);
		   deletedsp(it);                      //���delete��û�е���next�Ⱥ���ǰ�Ƿ��ܳɹ�

		   nextdsp(it);                        //��Ԫ�����������ߵ����������
		   prevdsp(it);
		   deletedsp(it);                      //����ܷ�ɹ�ɾ��

		   adddsp(it, a[0]);
		   prevdsp(it); 
		   setdsp(it, 100);                  //���set

		   printf("hasnext: %d\n", hasNext(it));                     //���hasnest��
		   printf("hasprev: %d\n", hasPrevious(it));

		   prevdsp(it);
		   setdsp(it, 100);
		   findnextdsp(it, a[0]);                                           //��鵥Ԫ���µ�findnext��
		   findprevdsp(it, a[0]);

		   findprevdsp(it, 14);                                             //���Ҳ������������Ԫ�ص�ǰ��һ��Ԫ�ص��������
	   }
	   else
	   {
		   for(int i=0;i<5;i++)
			   adddsp(it, a[i]);
		   printAll(it);                    //�α��ѵ�����
		   nextdsp(it);                  //����α��ѵ����ҵ�next��havenext
		   printf("hasnext: %d\n", hasNext(it));

		   prevdsp(it);
		   prevdsp(it);
		   deletedsp(it);                 //��� prevdsp(it)��deletedsp(it)
		   printAll(it);                    //�α��ѵ�����

		   prevdsp(it);
		   prevdsp(it);
		   adddsp(it, 14);               //�����ĳ������Ԫ�صĽ������δ����֮ǰit->nextEle��32��Ҫ��������Ƿ�it->nextEle������32
		   printAll(it);                    //�α��ѵ�����

		   reset(it);                    
		   findnextdsp(it, 14);        //�����������ͬ�������ڵ�ʱ��findNext�Ľ��
		   findnextdsp(it, 14);

		   findnextdsp(it, 14);

		   nextdsp(it);
		   nextdsp(it);
		   findprevdsp(it, 14);       //�����������ͬ�������ڵ�ʱ��findNext�Ľ��
		   findprevdsp(it, 14);

		   reset(it);                    
		   nextdsp(it);                   //���set
		   setdsp(it, 8);
		   printAll(it);                    //�α��ѵ�����

		   reset(it);
		   findnextdsp(it, 8);        //�����������ͬ���������ڵ�ʱ��findNext�Ľ��
		   findnextdsp(it, 8);
		   nextdsp(it);                   //���findnext���ɹ�ʱ��������λ��

		   printAll(it);                    //�α��ѵ�����
		   findprevdsp(it, 8);       //�������������ͬ�������ڵ�ʱ��findprevious�Ľ��
		   findprevdsp(it, 8);
	   }
	   freeIt(it);

	

  	return EXIT_SUCCESS;

}
