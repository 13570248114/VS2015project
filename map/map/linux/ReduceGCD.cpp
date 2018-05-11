#include"ReduceGCD.h"
int ReduceGCD::binaryOperator(int x, int y) {
	int n = x < y ? x : y;          
	for (int i = n;i >= 1;i--) {                   //从x和y中较小的数开始递减，直到x,y都能整除那个数，就是最大公约数
		if (x%i == 0 && y%i == 0)
			return i;
	}
}