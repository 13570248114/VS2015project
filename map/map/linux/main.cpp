#include"MapTriple.h"
#include"MapSquare.h"
#include"MapAbsoluteValue .h"
#include"FilterNonPositive.h"
#include"FilterForTwoDigitPositive.h"
#include"FilterOdd.h"
#include"ReduceMinimum .h"
#include"ReduceGCD.h"
#include<iostream>
using namespace std;                                                        

int main() {
	MapTriple mapTriple;
	MapSquare mapSquare;
	MapAbsoluteValue mapAbsoluteValue;
	FilterForTwoDigitPositive filterForTwoDigitPositive;
	FilterNonPositive filterNonPositive;
	FilterOdd filterOdd;
	ReduceMinimum reduceMinimum;
	ReduceGCD reduceGCD;
	vector<int> list, L1, L2;

	cout << "please input 20 integers : " << endl;
	int num;
	for (int i = 0;i < 20;i++) {
		cin >> num;
		list.push_back(num);
	}	
	
	L1 = mapTriple.map(mapAbsoluteValue.map(list));                                                    //映射3倍绝对值
	L2 = filterForTwoDigitPositive.filter(filterOdd.filter(L1));                                       //过滤出奇数的两位数
	int min = reduceMinimum.reduce(L2).back();                                                         //找出最小值,reduce类返回的是vector,最小值在vector的最后一个
	int gcd = reduceGCD.reduce(L2).back();                                                             //找出最大公约数，reduce类返回的是vector,最小值在vector的最后一个
	cout << min << " " << gcd << endl;
}
