#include"Time.h"
#include<iostream>
using namespace std;

int main()
{
	cout << "Test start" << endl;

	cout << "pleause input hour  minute  second for t1: (e.g : 1 0 0)" << endl;
	int hour, min, sec;
	cin >> hour >> min >> sec;
	Time t1(hour, min, sec);
	cout << "t1 = " << t1 << endl;
	cout << "pleause input hour  minute  second for t2: (e.g : 1 0 0)" << endl;
	cin >> hour >> min >> sec;
	Time t2(hour, min, sec);
	cout << "t2 = " << t2 << endl;

	cout << "\nTest 1: == , <=, >=" << endl;
	if (t1 == t2)
		cout << "t1 == t2" << endl;
	else if(t1 <= t2)
		cout << "t1 <= t2" << endl;
	else if (t1 >= t2)
		cout << "t1 >= t2" << endl;

	cout << "\nTest 2: - , -=, --" << endl;
	cout << "t1 - 30sec = " << t1 - 30 << endl;
	cout << "t2 -= 30sec , t2 = " << (t2 -= 30) << endl;
	cout << "--t1 = " << --t1 << endl;

	cout << "\nNow : " << "t1 = " << t1 << "      t2 = " << t2 << endl;
	cout << "Test 3: != , <, >" << endl;
	if (t1 != t2)
	{
		cout << "t1 != t2" << endl;
		if (t1 < t2)
			cout << "t1 < t2" << endl;
		else if (t1 > t2)
			cout << "t1 > t2" << endl;
	}
	else
		cout << "t1 == t2" << endl;

	cout << "\nTest 4: -- , -" << endl;
	cout << "t1-- = " << t1-- << endl;
	cout << "Now : " << "t1 = " << t1 << "      t2 = " << t2 << endl;
	cout << "t1 - t2 = " << t1 - t2 << endl;

	cout << "Test end" << endl;
}