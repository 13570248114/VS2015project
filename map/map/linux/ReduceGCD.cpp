#include"ReduceGCD.h"
int ReduceGCD::binaryOperator(int x, int y) {
	int n = x < y ? x : y;          
	for (int i = n;i >= 1;i--) {                   //��x��y�н�С������ʼ�ݼ���ֱ��x,y���������Ǹ������������Լ��
		if (x%i == 0 && y%i == 0)
			return i;
	}
}