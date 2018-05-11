#include<iostream>
using namespace std;

int main()
{
	int sum=0;
	for (int i = 0;i <= 1440;i++)
		sum += i/60*100+i%60;
	cout << sum;
}
