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
#define UNIT_TEST 0                                                                 //定义一个宏UNIT_TEST，当UNIT_TEST设为1时则进行单元测试，为0时则进行题目要求的测试

#if UNIT_TEST

void displayVector(vector<int> list) {                                              //用于打印容器内的所有整数
	for (auto i : list)
		cout << i << '\t';
	cout << "\n"<<endl;
}

int main() {

	MapTriple mapTriple;
	MapSquare mapSquare;
	MapAbsoluteValue mapAbsoluteValue;
	FilterForTwoDigitPositive filterForTwoDigitPositive;
	FilterNonPositive filterNonPositive;
	FilterOdd filterOdd;
	ReduceMinimum reduceMinimum;
	ReduceGCD reduceGCD;

	vector<int> list{ -5, -24, -123, -81, 200, 157, 84, 67, -83, -60, -72, 192, -25, -20, -50, -181,
		              -70, -15, -108, -123 };                                                          //测试用例
	cout << "original : ";
	displayVector(list);                                                                              //先打印出原始数列
	cout << "Triple : ";
	displayVector(mapTriple.map(list));                                                               //打印测试mapTriple
	cout << "Square : ";
	displayVector(mapSquare.map(list));                                                               //打印测试mapSquare
	cout << "AbsoluteValue : ";
	displayVector(mapAbsoluteValue.map(list));                                                        //打印测试mapAbsoluteValue
	cout << "Odd : " ;
	displayVector(filterOdd.filter(list));                                                            //打印测试filterOdd
	cout << "NonPositive : ";
	displayVector(filterNonPositive.filter(list));                                                    //打印测试filterNonPositive
	cout << "TwoDigitPositive : ";
	displayVector(filterForTwoDigitPositive.filter(list));                                            //打印测试filterForTwoDigitPositive
	cout << "min : "<<reduceMinimum.reduce(list).back() << endl;                                      //打印测试reduceMinimum
	cout << "GCD : "<<reduceGCD.reduce(mapAbsoluteValue.map(list)).back() << endl;                    //打印测试reduceGCD
	return 0;
}

#else                                                                                                 //若UNIT_TEST设为0则实行下面的代码
#define TESTING 0

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

	if(TESTING)                                                                                      //若TESTING为1，则用测试用例测试
		list = { 6, -11, 53, -16, 73, 128, 105, 104, -71, -179, 102, 12, 21, -145, -99, 199,
		        -156, -186, 43, -189 };
	else {                                                                                           //否则手动输入数列
		cout << "please input 20 integers : " << endl;
		int num;
		for (int i = 0;i < 20;i++) {
			cin >> num;
			list.push_back(num);
		}	
	}

	L1 = mapTriple.map(mapAbsoluteValue.map(list));                                                    //映射3倍绝对值
	L2 = filterForTwoDigitPositive.filter(filterOdd.filter(L1));                                       //过滤出奇数的两位数
	int min = reduceMinimum.reduce(L2).back();                                                         //找出最小值,reduce类返回的是vector,最小值在vector的最后一个
	int gcd = reduceGCD.reduce(L2).back();                                                             //找出最大公约数，reduce类返回的是vector,最小值在vector的最后一个
	cout << min << " " << gcd << endl;
}

#endif