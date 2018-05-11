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
#define UNIT_TEST 0                                                                 //����һ����UNIT_TEST����UNIT_TEST��Ϊ1ʱ����е�Ԫ���ԣ�Ϊ0ʱ�������ĿҪ��Ĳ���

#if UNIT_TEST

void displayVector(vector<int> list) {                                              //���ڴ�ӡ�����ڵ���������
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
		              -70, -15, -108, -123 };                                                          //��������
	cout << "original : ";
	displayVector(list);                                                                              //�ȴ�ӡ��ԭʼ����
	cout << "Triple : ";
	displayVector(mapTriple.map(list));                                                               //��ӡ����mapTriple
	cout << "Square : ";
	displayVector(mapSquare.map(list));                                                               //��ӡ����mapSquare
	cout << "AbsoluteValue : ";
	displayVector(mapAbsoluteValue.map(list));                                                        //��ӡ����mapAbsoluteValue
	cout << "Odd : " ;
	displayVector(filterOdd.filter(list));                                                            //��ӡ����filterOdd
	cout << "NonPositive : ";
	displayVector(filterNonPositive.filter(list));                                                    //��ӡ����filterNonPositive
	cout << "TwoDigitPositive : ";
	displayVector(filterForTwoDigitPositive.filter(list));                                            //��ӡ����filterForTwoDigitPositive
	cout << "min : "<<reduceMinimum.reduce(list).back() << endl;                                      //��ӡ����reduceMinimum
	cout << "GCD : "<<reduceGCD.reduce(mapAbsoluteValue.map(list)).back() << endl;                    //��ӡ����reduceGCD
	return 0;
}

#else                                                                                                 //��UNIT_TEST��Ϊ0��ʵ������Ĵ���
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

	if(TESTING)                                                                                      //��TESTINGΪ1�����ò�����������
		list = { 6, -11, 53, -16, 73, 128, 105, 104, -71, -179, 102, 12, 21, -145, -99, 199,
		        -156, -186, 43, -189 };
	else {                                                                                           //�����ֶ���������
		cout << "please input 20 integers : " << endl;
		int num;
		for (int i = 0;i < 20;i++) {
			cin >> num;
			list.push_back(num);
		}	
	}

	L1 = mapTriple.map(mapAbsoluteValue.map(list));                                                    //ӳ��3������ֵ
	L2 = filterForTwoDigitPositive.filter(filterOdd.filter(L1));                                       //���˳���������λ��
	int min = reduceMinimum.reduce(L2).back();                                                         //�ҳ���Сֵ,reduce�෵�ص���vector,��Сֵ��vector�����һ��
	int gcd = reduceGCD.reduce(L2).back();                                                             //�ҳ����Լ����reduce�෵�ص���vector,��Сֵ��vector�����һ��
	cout << min << " " << gcd << endl;
}

#endif