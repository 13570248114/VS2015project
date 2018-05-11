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
	
	L1 = mapTriple.map(mapAbsoluteValue.map(list));                                                    //ӳ��3������ֵ
	L2 = filterForTwoDigitPositive.filter(filterOdd.filter(L1));                                       //���˳���������λ��
	int min = reduceMinimum.reduce(L2).back();                                                         //�ҳ���Сֵ,reduce�෵�ص���vector,��Сֵ��vector�����һ��
	int gcd = reduceGCD.reduce(L2).back();                                                             //�ҳ����Լ����reduce�෵�ص���vector,��Сֵ��vector�����һ��
	cout << min << " " << gcd << endl;
}
